// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_assetmanager.cpp
//  implementation of AssetManager class, for loading/removing assets
// -----------------------------------------------------------------------------

#include "core_assetmanager.hpp"

#define STB_IMAGE_IMPLEMENTATION    // required before stb include - only once
#include "stb/stb_image.h"

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Constructor and Destructor
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// AssetManager(): -------------------------------------------------------------
AssetManager::AssetManager() {
    spdlog::info("AssetManager constructor called!");
}

// ~AssetManager(): ------------------------------------------------------------
AssetManager::~AssetManager() {
    spdlog::info("AssetManager destructor called, clearing assets!");
    clearAssets();
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// 'Set' functions
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// setTexutre(): ---------------------------------------------------------------
void AssetManager::setTexture(const std::string& assetId, const char* texturePath) {
    // generate and bind texture for OpenGL configuration
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

     // set the texture WRAPPING parameters - (s,t,r is equivalent of x,y,z)
    glTexParameteri(        // acts on currently active/bound texture
        GL_TEXTURE_2D,      // specify texture target (texture is in 2D)
        GL_TEXTURE_WRAP_S,  // what option to set and for which texture axis 
        GL_CLAMP_TO_BORDER           // wrapping mode
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // set texture FILTERING parameters
    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,  // minifying or magnifying? scaling down or up?
        GL_LINEAR   // nearest texel center, linear interpolation, or Mipmaps
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // load texture from filepath
    int width, height, nrChannels;
    // tell stb_image.h to flip loaded textures on the y-axis
    stbi_set_flip_vertically_on_load(true); // needed due to OpenGL coordinates 
    unsigned char* data = stbi_load(
        texturePath,
        &width, 
        &height, 
        &nrChannels,    // number of color channels 
        0
    );
    if (data) {
        glTexImage2D(
            GL_TEXTURE_2D,      // texture target (1D/2D/3D) 
            0,                  // level of detail (0 to nth mipmap reduction) 
            GL_RGBA,            // number of color components (RGBA for .png) 
            width,       
            height, 
            0,                  // border, value must be 0 
            GL_RGBA,            // format of pixel data (RGBA for .png) 
            GL_UNSIGNED_BYTE,   // data type of pixel data 
            data                // pointer to image data in memory
        );
        glGenerateMipmap(GL_TEXTURE_2D);
        
        // add new texture to Asset Manager's texture map
        textures.emplace(assetId, texture);
        spdlog::info("New Texture added to Asset Manager with id = " + assetId);
    }
    else {
        spdlog::error("Failed to load texture");
    }
    
    // de-allocate the memory for texture from stbi
    stbi_image_free(data);
}

// setVShader(): ---------------------------------------------------------------
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
        spdlog::error("VShader file not successfully read: {}", e.what());
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
    spdlog::info("New VShader added to Asset Manager with id = " + assetId);
}
 
// setFShader(): ---------------------------------------------------------------
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
        spdlog::error("FShader file not successfully read: {}", e.what());
    }

    const char* fShaderCode = fragmentCode.c_str();

    // compile fragment shader 
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkShaderErrors(fragment, "FRAGMENT");

    // add fshader to asset manager's map
    fshaders.emplace(assetId, fragment); 
    spdlog::info("New FShader added to Asset Manager with id = " + assetId);
}

// setShaderProgram(): ---------------------------------------------------------
void AssetManager::setShaderProgram(const std::string& assetId, unsigned int vertexShader, unsigned int fragmentShader) {
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // check shader linking for errors 
    checkShaderProgramErrors(shaderProgram);

    // add shaderProgram to asset manager's map 
    shaderPrograms.emplace(assetId, shaderProgram);
    spdlog::info("New ShaderProgram added to Asset Manager with id = " + assetId);
}

/*
// setModel(): -----------------------------------------------------------------
void AssetManager::setModel(const std::string& assetId, const char* modelPath) {
    FILE* file;
    file = fopen(modelPath, "r");
    char line[1024];

    // temporary vectors for vertices, tex coords, and indices
    std::vector<int> v;
    std::vector<int> tc;
    std::vector<int> i;
    vertices.emplace(assetId, v);
    textureCoordinates.emplace(assetId, tc);
    indices.emplace(assetId, i);

    while (fgets(line, 1024, file)) {
        //vertex data
        if (strncmp(line, "v ", 2) == 0) {
            float xCoord;
            float yCoord;
            float zCoord;
            // note to future self: I am bad at creating obj files from Blender,
            // thus the order of vertices in my obj file goes x -> z -> (-1)*y
            sscanf(line, "v %f %f %f", &xCoord, &zCoord, &yCoord);
            yCoord *= -1;
            vertices[assetId].emplace_back(xCoord);
            vertices[assetId].emplace_back(yCoord);
            vertices[assetId].emplace_back(zCoord);
        }

        // texture coordinate data
        if (strncmp(line, "vt ", 3) == 0) {
            float uCoord;
            float vCoord;
            sscanf(line, "vt %f %f", &uCoord, &vCoord);
            textureCoordinates[assetId].emplace_back(uCoord);
            textureCoordinates[assetId].emplace_back(vCoord);
        }

        // index data
        if (strncmp(line, "f ", 2) == 0) {
            // each line contains 3 vertices, A, B, and C
            // each vertex has a vertex index, texCoord index, normal index
            int vertexA;
            int vertexB;
            int vertexC;
            int texCoordA;
            int texCoordB;
            int texCoordC;
            int normalA;
            int normalB;
            int normalC;
            sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", 
                &vertexA, &texCoordA, &normalA,
                &vertexB, &texCoordB, &normalB,
                &vertexC, &texCoordC, &normalC
            );
            indices[assetId].emplace_back(vertexA);
            indices[assetId].emplace_back(vertexB);
            indices[assetId].emplace_back(vertexC);
        }
    }

    unsigned int sizeV = vertices[assetId].size();
    unsigned int sizeTC = textureCoordinates[assetId].size();
    unsigned int sizeI = indices[assetId].size();
    sizeVertices.emplace(assetId, sizeV);
    sizeTextureCoordinates.emplace(assetId, sizeTC);
    sizeIndices.emplace(assetId, sizeI);
}
*/

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// 'Get' functions
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// getTexture(): ---------------------------------------------------------------
unsigned int AssetManager::getTexture(const std::string& assetId) {
    return textures[assetId];
}

// getVShader(): ---------------------------------------------------------------
unsigned int AssetManager::getVShader(const std::string& assetId) {
    return vshaders[assetId];
}

// getFShader(): ---------------------------------------------------------------
unsigned int AssetManager::getFShader(const std::string& assetId) {
    return fshaders[assetId];
}

// getShaderProgram(): ---------------------------------------------------------
unsigned int AssetManager::getShaderProgram(const std::string& assetId) {
    return shaderPrograms[assetId];
}

/*
// getVertices(): --------------------------------------------------------------
std::vector<float> AssetManager::getVertices(const std::string& assetId) {
    return vertices[assetId];
}

// getTextureCoordinates(): ----------------------------------------------------
std::vector<float> AssetManager::getTextureCoordinates(const std::string& assetId) {
    return textureCoordinates[assetId];
}

// getIndices(): ---------------------------------------------------------------
std::vector<int> AssetManager::getIndices(const std::string& assetId) {
    return indices[assetId];
}

// getSizeVertices(): ----------------------------------------------------------
unsigned int AssetManager::getSizeVertices(const std::string& assetId) {
    return sizeVertices[assetId];
}

// getSizeTextureCoordinates(): ------------------------------------------------
unsigned int AssetManager::getSizeTextureCoordinates(const std::string& assetId) {
    return sizeTextureCoordinates[assetId];
}

// getSizeIndices(): -----------------------------------------------------------
unsigned int AssetManager::getSizeIndices(const std::string& assetId) {
    return sizeIndices[assetId];
}
*/

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Misc functions
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// clearAssets(): --------------------------------------------------------------
void AssetManager::clearAssets() {
    for (auto texture : textures) {
        glDeleteTextures(1, &texture.second);
    }
    textures.clear();
    
    for (auto vshader : vshaders) {
        glDeleteShader(vshader.second);
    }
    vshaders.clear();

    for (auto fshader : fshaders) {
        glDeleteShader(fshader.second);
    }
    fshaders.clear();

    for (auto program : shaderPrograms) {
        glDeleteProgram(program.second);
    }
    shaderPrograms.clear();

    /*
    for (auto v : vertices) {
        std::vector<float>().swap(v.second);
    }
    vertices.clear();
    sizeVertices.clear();

    for (auto tc : textureCoordinates) {
        std::vector<float>().swap(tc.second);
    }
    textureCoordinates.clear();
    sizeTextureCoordinates.clear();

    for (auto i : indices) {
        std::vector<int>().swap(i.second);
    }
    indices.clear();
    sizeIndices.clear();
    */
}

// checkShaderErrors(): --------------------------------------------------------
void AssetManager::checkShaderErrors(unsigned int shader, std::string type) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success) {
        spdlog::info("Compiled shader of type: {}", type);
    }
    else {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        spdlog::error(
            "Shader compilation error of type: {}: {}", 
            type, 
            infoLog
        );
    }
}

// checkShaderProgramErrors(): -------------------------------------------------
void AssetManager::checkShaderProgramErrors(unsigned int program) {
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success) {
        spdlog::info("Linked shaders into shader program object");
    }
    else {
        char infoLog[1024];
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        spdlog::error(
            "Shader linking error of type: LINKER: {}",
            infoLog
        );
    }
}
