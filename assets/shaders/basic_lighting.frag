#version 330 core
out vec4 FragColor;

#define NR_POINT_LIGHTS 3

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
    float farPlane;
    bool shadowFlag;
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
};

struct PointShadow {
    samplerCube depthCube;
    float farPlane;
    bool shadowFlag;
};

struct SpotShadow {
    sampler2D depthTex;
    mat4 lightSpaceMatrix;
    bool shadowFlag;
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
uniform SpotLight spotLight;
uniform PointShadow pointShadows[NR_POINT_LIGHTS];
uniform SpotShadow spotShadow;

// ____________________________________________________________________________
// helper function declarations
// ----------------------------------------------------------------------------

// directional lights
mat3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
// point lights
mat3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float ShadowCubeCalculation(PointLight light, PointShadow pShadow, vec3 fragPos);
// spot lights
mat3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float ShadowTexCalculation(SpotLight light, SpotShadow sShadow, vec4 fragPosLightSpace);

// ____________________________________________________________________________
// ----------------------------------------------------------------------------
// main function
// ____________________________________________________________________________
// ----------------------------------------------------------------------------

void main() {    
    vec3 normal = normalize(fs_in.Normal);
    vec3 viewDir = normalize(viewPos - fs_in.FragPos); 

    // directional lights 
    mat3 dirLighting = CalcDirLight(dirLight, normal, viewDir);
    vec3 totalLighting = dirLighting[0] + dirLighting[1] + dirLighting[2];

    // point lights
    for (int i = 0; i < NR_POINT_LIGHTS; i++) {
        mat3 pointLighting = CalcPointLight(pointLights[i], normal, fs_in.FragPos, viewDir);
        float cubeShadow = ShadowCubeCalculation(pointLights[i], pointShadows[i], fs_in.FragPos);
        totalLighting += (pointLighting[0] + (1.0 - cubeShadow) * (pointLighting[1] + pointLighting[2])); 
    }

    // spot lights
    mat3 spotLighting = CalcSpotLight(spotLight, normal, fs_in.FragPos, viewDir);
    vec4 fragPosSpace = spotShadow.lightSpaceMatrix * vec4(fs_in.FragPos, 1.0);
    float texShadow = 0.0;
    if (spotShadow.shadowFlag) {
        texShadow = ShadowTexCalculation(spotLight, spotShadow, fragPosSpace);
    }
    totalLighting += (spotLighting[0] + (1.0 - texShadow) * (spotLighting[1] + spotLighting[2]));

    // final output
    FragColor = vec4(totalLighting, 1.0);
}

// ____________________________________________________________________________
// directional lights
// ----------------------------------------------------------------------------
mat3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, fs_in.TexCoords));

    float spec = 0.0f;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, fs_in.TexCoords));
    return mat3(ambient, diffuse, specular);
}

// ____________________________________________________________________________
// point lights
// ----------------------------------------------------------------------------
mat3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(lightDir, normal), 0.0);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, fs_in.TexCoords));

    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, fs_in.TexCoords));


    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return mat3(ambient, diffuse, specular);
}

float ShadowCubeCalculation(PointLight light, PointShadow pShadow, vec3 fragPos) {
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - light.position;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // PCF
    float shadow = 0.0;
    float bias = 0.15;
    int samples = 20;
    float viewDistance = length(viewPos - fragPos);
    float diskRadius = (1.0 + (viewDistance / pShadow.farPlane)) / 25.0;
    for(int i = 0; i < samples; ++i) {
        float closestDepth = texture(pShadow.depthCube, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= pShadow.farPlane;   // undo mapping [0;1]
        if(currentDepth - bias > closestDepth)
            shadow += 1.0;
    }
    shadow /= float(samples);   
        
    return shadow;
}

// ____________________________________________________________________________
// spot lights
// ----------------------------------------------------------------------------
mat3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    // diffuse shading
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(lightDir, normal), 0.0);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, fs_in.TexCoords));

    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, fs_in.TexCoords));

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return mat3(ambient, diffuse, specular);
}

float ShadowTexCalculation(SpotLight light, SpotShadow sShadow, vec4 fragPosLightSpace) {
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(sShadow.depthTex, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(light.position - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(sShadow.depthTex, 0);
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(sShadow.depthTex, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}