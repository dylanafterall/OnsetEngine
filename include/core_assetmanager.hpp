// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_assetmanager.hpp
//  header of AssetManager class, functionality for adding/removing assets
// -----------------------------------------------------------------------------
#ifndef CORE_ASSETMANAGER_HPP
#define CORE_ASSETMANAGER_HPP

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"
#include "box2d/box2d.h"

#include <map>
#include <fstream>
#include <sstream>
#include <string>

class AssetManager {
public:
    AssetManager();
    ~AssetManager();

    void setTexture(const std::string&, const char*);
    void setVShader(const std::string&, const char*);
    void setFShader(const std::string&, const char*);
    void setShaderProgram(const std::string&, unsigned int, unsigned int);
    //void setModel(const std::string&, const char*);

    unsigned int getTexture(const std::string&);
    unsigned int getVShader(const std::string&);
    unsigned int getFShader(const std::string&);
    unsigned int getShaderProgram(const std::string&);
    //std::vector<float> getVertices(const std::string&);
    //std::vector<float> getTextureCoordinates(const std::string&);
    //std::vector<int> getIndices(const std::string&);
    //unsigned int getSizeVertices(const std::string&);
    //unsigned int getSizeTextureCoordinates(const std::string&);
    //unsigned int getSizeIndices(const std::string&);

    void clearAssets();
    void checkShaderErrors(unsigned int, std::string);
    void checkShaderProgramErrors(unsigned int);

private:
    // independent texture data
    std::map<std::string, unsigned int> textures;
    // shader data
    std::map<std::string, unsigned int> vshaders;
    std::map<std::string, unsigned int> fshaders;
    // shader program data
    std::map<std::string, unsigned int> shaderPrograms;
    // model vertex data
    //std::map<std::string, std::vector<float>> vertices;
    //std::map<std::string, unsigned int> sizeVertices;
    // model tex coord data
    //std::map<std::string, std::vector<float>> textureCoordinates;
    //std::map<std::string, unsigned int> sizeTextureCoordinates;
    // model index data
    //std::map<std::string, std::vector<int>> indices;
    //std::map<std::string, unsigned int> sizeIndices;
};

#endif // CORE_ASSETMANAGER_HPP
