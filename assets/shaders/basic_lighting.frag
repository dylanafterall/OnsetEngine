#version 330 core
out vec4 FragColor;

#define NR_POINT_LIGHTS 3
#define NR_SPOT_LIGHTS 3

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    samplerCube depthCube;
    float farPlane;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    sampler2D depthTex;
    mat4 lightSpaceMatrix;
};

vec3 gridSamplingDisk[20] = vec3[] (    // array of offset direction for sampling
   vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1), 
   vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
   vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
   vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
   vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

// ____________________________________________________________________________
// ----------------------------------------------------------------------------
// inputs from vertex shader and RenderSystem
// ____________________________________________________________________________
// ----------------------------------------------------------------------------

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

// ____________________________________________________________________________
// helper function declarations
// ----------------------------------------------------------------------------

float ShadowCubeCalculation(vec3 lightPosition, float farPlane, samplerCube depthCube, vec3 fragPos);
float ShadowTexCalculation(vec3 lightPosition, sampler2D depthTex, vec4 fragPosLightSpace);

// ____________________________________________________________________________
// ----------------------------------------------------------------------------
// main function
// ____________________________________________________________________________
// ----------------------------------------------------------------------------

void main() {    
    vec3 normal = normalize(fs_in.Normal);
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);

    // ________________________________________________________________________
    // directional lights 
    // ------------------------------------------------------------------------
    vec3 lightDir = normalize(-dirLight.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 ambient = dirLight.ambient * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 diffuse = dirLight.diffuse * diff * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 halfwayDir = normalize(lightDir + viewDir); 
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = dirLight.specular * spec * vec3(texture(material.specular, fs_in.TexCoords));
    vec3 totalLighting = ambient + diffuse + specular;

    // ________________________________________________________________________
    // point lights
    // ------------------------------------------------------------------------
    float distance, attenuation, cubeShadow;
    for (int i = 0; i < NR_POINT_LIGHTS; i++) {
        lightDir = normalize(pointLights[i].position - fs_in.FragPos);
        diff = max(dot(lightDir, normal), 0.0);
        distance = length(pointLights[i].position - fs_in.FragPos);
        attenuation = 1.0 / (pointLights[i].constant + pointLights[i].linear * distance + pointLights[i].quadratic * (distance * distance)); 
        ambient = pointLights[i].ambient * vec3(texture(material.diffuse, fs_in.TexCoords));
        diffuse = pointLights[i].diffuse * diff * vec3(texture(material.diffuse, fs_in.TexCoords));
        halfwayDir = normalize(lightDir + viewDir); 
        spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
        specular = pointLights[i].specular * spec * vec3(texture(material.specular, fs_in.TexCoords));
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
        cubeShadow = ShadowCubeCalculation(pointLights[i].position, pointLights[i].farPlane, pointLights[i].depthCube, fs_in.FragPos);
        totalLighting += (ambient + (1.0 - cubeShadow) * (diffuse + specular)); 
    }

    // ________________________________________________________________________
    // spot lights
    // ------------------------------------------------------------------------
    mat3 spotLighting;
    vec4 fragPosSpace;
    float theta, epsilon, intensity, texShadow;
    for (int j = 0; j < NR_SPOT_LIGHTS; j++) {
        lightDir = normalize(spotLights[j].position - fs_in.FragPos);
        diff = max(dot(lightDir, normal), 0.0);
        distance = length(spotLights[j].position - fs_in.FragPos);
        attenuation = 1.0 / (spotLights[j].constant + spotLights[j].linear * distance + spotLights[j].quadratic * (distance * distance));
        theta = dot(lightDir, normalize(-spotLights[j].direction)); 
        epsilon = spotLights[j].cutOff - spotLights[j].outerCutOff;
        intensity = clamp((theta - spotLights[j].outerCutOff) / epsilon, 0.0, 1.0);
        ambient = spotLights[j].ambient * vec3(texture(material.diffuse, fs_in.TexCoords));
        diffuse = spotLights[j].diffuse * diff * vec3(texture(material.diffuse, fs_in.TexCoords));
        halfwayDir = normalize(lightDir + viewDir); 
        spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
        specular = spotLights[j].specular * spec * vec3(texture(material.specular, fs_in.TexCoords));
        ambient *= attenuation * intensity;
        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;
        fragPosSpace = spotLights[j].lightSpaceMatrix * vec4(fs_in.FragPos, 1.0);
        texShadow = ShadowTexCalculation(spotLights[j].position, spotLights[j].depthTex, fragPosSpace);
        totalLighting += (ambient + (1.0 - texShadow) * (diffuse + specular));
    }

    // final output
    FragColor = vec4(totalLighting, 1.0);
}

// ____________________________________________________________________________
// shadow mapping
// ----------------------------------------------------------------------------
float ShadowCubeCalculation(vec3 lightPosition, float farPlane, samplerCube depthCube, vec3 fragPos) {
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - lightPosition;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // PCF
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / farPlane)) / 25.0;
    for(int i = 0; i < samples; ++i) {
        float closestDepth = texture(depthCube, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= farPlane;   // undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);   
        
    return shadow;
}

float ShadowTexCalculation(vec3 lightPosition, sampler2D depthTex, vec4 fragPosLightSpace) {
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(depthTex, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPosition - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(depthTex, 0);
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(depthTex, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}