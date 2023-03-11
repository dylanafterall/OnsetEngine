// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_asset_manager.cpp
//  implementation of AssetManager class, for loading/removing assets
// -----------------------------------------------------------------------------

#include "core_asset_manager.h"

#define STB_IMAGE_IMPLEMENTATION    // required before stb include - only once
#include "stb_image.h"

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// 'Set' functions
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

void AssetManager::setTexture(const std::string& assetId, const char* texturePath, bool repeat, bool gamma) {
    // generate and bind texture for OpenGL configuration
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if (repeat) {
        // set the texture WRAPPING parameters - (s,t,r is equivalent of x,y,z)
        glTexParameteri(        // acts on currently active/bound texture
        GL_TEXTURE_2D,          // specify texture target (texture is in 2D)
        GL_TEXTURE_WRAP_S,      // what option to set and for which texture axis 
        GL_REPEAT               // specify wrapping parameter         
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);   
    }
    else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
    }

    // set texture FILTERING parameters
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,  // minifying or magnifying? scaling down or up?
        GL_LINEAR_MIPMAP_LINEAR   // nearest texel center, linear interpolation, or Mipmaps
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // tell stb_image.h to flip loaded textures on the y-axis
    stbi_set_flip_vertically_on_load(true); // needed due to OpenGL coordinates 

    // load texture from filepath
    int width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum internalFormat, format;
        if (nrChannels == 1) {
            internalFormat = format = GL_RED;
        }
        else if (nrChannels == 3) {
            internalFormat = format = GL_RGB;
            if (gamma) {
                internalFormat = GL_SRGB;
            }
        }
        else {
            internalFormat = format = GL_RGBA;
            if (gamma) {
                internalFormat = GL_SRGB_ALPHA;
            }
        }

        glTexImage2D(
            GL_TEXTURE_2D,      // texture target (1D/2D/3D) 
            0,                  // level of detail (0 to nth mipmap reduction) 
            internalFormat,     // number of color components (RED / RGB / RGBA) 
            width,       
            height, 
            0,                  // border, value must be 0 
            format,             // format of pixel data (RED / RGB / RGBA) 
            GL_UNSIGNED_BYTE,   // data type of pixel data 
            data                // pointer to image data in memory
        );
        glGenerateMipmap(GL_TEXTURE_2D);
        // add new texture to Asset Manager's texture map
        textures.emplace(assetId, texture);
        ONSET_INFO("New Texture added to Asset Manager with id = {}", assetId);
    }
    else {
        ONSET_ERROR("Failed to load texture");
    }

    // de-allocate the memory for texture from stbi
    stbi_image_free(data);
}

void AssetManager::setCubemap(const std::string& assetId, std::vector<std::string> faces, bool gamma) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    stbi_set_flip_vertically_on_load(false);
    int width, height, nrComponents;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrComponents, 0);
        if (data) {
            GLenum internalFormat, format;
            if (nrComponents == 1) {
                internalFormat = format = GL_RED;
            }
            else if (nrComponents == 3) {
                internalFormat = format = GL_RGB;
                if (gamma) {
                    internalFormat = GL_SRGB;
                }
            }
            else {
                internalFormat = format = GL_RGBA;
                if (gamma) {
                    internalFormat = GL_SRGB_ALPHA;
                }
            }

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            ONSET_ERROR("Cubemap-texture failed to load at path: {}", faces[i]);
            stbi_image_free(data);
        }
    }
    stbi_set_flip_vertically_on_load(true);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    cubemaps.emplace(assetId, textureID);
    ONSET_INFO("New Cubemap added to Asset Manager with id = {}", assetId);
}

void AssetManager::setVShader(const std::string& assetId, const char* vertexPath) {
    // retrieve the vertex source code from filePath 
    std::string vertexCode;
    std::ifstream vShaderFile;

    // ensure ifstream objects can throw exceptions 
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open file
        vShaderFile.open(vertexPath);
        std::stringstream vShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        ONSET_ERROR("VShader file not successfully read: {}", e.what());
    }

    const char* vShaderCode = vertexCode.c_str();

    // compile vertex shader 
    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    // attach shader source code to shader object
    glShaderSource(
        vertex,         // shader object to compile
        1,              // how many strings to pass as source code 
        &vShaderCode,   // actual source code of vertex shader 
        NULL            // an array of string lengths
    );
    glCompileShader(vertex);
    checkShaderErrors(vertex, "VERTEX");

    // add vshader to asset manager's map
    vshaders.emplace(assetId, vertex);
    ONSET_INFO("New VShader added to Asset Manager with id = {}", assetId);
}
 
void AssetManager::setFShader(const std::string& assetId, const char* fragmentPath) {
    // retrieve the shader source code from filePath 
    std::string fragmentCode;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions 
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open file
        fShaderFile.open(fragmentPath);
        std::stringstream fShaderStream;
        // read file's buffer contents into streams
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        fShaderFile.close();
        // convert stream into string
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        ONSET_ERROR("FShader file not successfully read: {}", e.what());
    }

    const char* fShaderCode = fragmentCode.c_str();

    // compile fragment shader 
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkShaderErrors(fragment, "FRAGMENT");

    // add fshader to asset manager's map
    fshaders.emplace(assetId, fragment);
    ONSET_INFO("New FShader added to Asset Manager with id = {}", assetId);
}

void AssetManager::setGShader(const std::string& assetId, const char* geometryPath) {
    // retrieve the shader source code from filePath 
    std::string geometryCode;
    std::ifstream gShaderFile;

    // ensure ifstream objects can throw exceptions 
    gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open file
        gShaderFile.open(geometryPath);
        std::stringstream gShaderStream;
        // read file's buffer contents into streams
        gShaderStream << gShaderFile.rdbuf();
        // close file handlers
        gShaderFile.close();
        // convert stream into string
        geometryCode = gShaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        ONSET_ERROR("GShader file not successfully read: {}", e.what());
    }

    const char* gShaderCode = geometryCode.c_str();

    // compile geometry shader 
    unsigned int geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &gShaderCode, NULL);
    glCompileShader(geometry);
    checkShaderErrors(geometry, "GEOMETRY");

    // add fshader to asset manager's map
    gshaders.emplace(assetId, geometry);
    ONSET_INFO("New GShader added to Asset Manager with id = {}", assetId);
}

void AssetManager::setShaderProgram(const std::string& assetId, unsigned int vertexShader, unsigned int fragmentShader) {
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check shader linking for errors 
    checkShaderProgramErrors(shaderProgram);

    // add shaderProgram to asset manager's map 
    shaderPrograms.emplace(assetId, shaderProgram);
    ONSET_INFO("New ShaderProgram added to Asset Manager with id = {}", assetId);
}

void AssetManager::setShaderProgram(const std::string& assetId, unsigned int vertexShader, unsigned int geometryShader, unsigned int fragmentShader) {
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, geometryShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check shader linking for errors 
    checkShaderProgramErrors(shaderProgram);

    // add shaderProgram to asset manager's map 
    shaderPrograms.emplace(assetId, shaderProgram);
    ONSET_INFO("New ShaderProgram added to Asset Manager with id = {}", assetId);
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// 'Get' functions
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

unsigned int AssetManager::getTexture(const std::string& assetId) {
    return textures[assetId];
}

unsigned int AssetManager::getCubemap(const std::string& assetId) {
    return cubemaps[assetId];
}

unsigned int AssetManager::getVShader(const std::string& assetId) {
    return vshaders[assetId];
}

unsigned int AssetManager::getFShader(const std::string& assetId) {
    return fshaders[assetId];
}

unsigned int AssetManager::getGShader(const std::string& assetId) {
    return gshaders[assetId];
}

unsigned int AssetManager::getShaderProgram(const std::string& assetId) {
    return shaderPrograms[assetId];
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Misc functions
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

void AssetManager::deleteAssets() {
    for (auto texture : textures) {
        glDeleteTextures(1, &texture.second);
    }
    textures.clear();

    for (auto cubemap : cubemaps) {
        glDeleteTextures(1, &cubemap.second);
    }
    cubemaps.clear();
    
    for (auto vshader : vshaders) {
        glDeleteShader(vshader.second);
    }
    vshaders.clear();

    for (auto fshader : fshaders) {
        glDeleteShader(fshader.second);
    }
    fshaders.clear();

    for (auto gshader : gshaders) {
        glDeleteShader(gshader.second);
    }
    gshaders.clear();

    for (auto program : shaderPrograms) {
        glDeleteProgram(program.second);
    }
    shaderPrograms.clear();
}

void AssetManager::checkShaderErrors(unsigned int shader, std::string type) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success) {
        ONSET_INFO("Compiled shader of type: {}", type);
    }
    else {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        ONSET_ERROR(
            "Shader compilation error of type: {}: {}", 
            type, 
            infoLog
        );
    }
}

void AssetManager::checkShaderProgramErrors(unsigned int program) {
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success) {
        ONSET_INFO("Linked shaders into shader program object");
    }
    else {
        char infoLog[1024];
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        ONSET_ERROR(
            "Shader linking error of type: LINKER: {}",
            infoLog
        );
    }
}