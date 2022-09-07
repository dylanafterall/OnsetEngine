// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_assetmanager.h
//  header of AssetManager class, functionality for adding/removing assets
// -----------------------------------------------------------------------------
#ifndef CORE_ASSETMANAGER_H
#define CORE_ASSETMANAGER_H

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"

#include <map>
#include <fstream>
#include <sstream>
#include <string>

class AssetManager {
public:
    AssetManager();
    ~AssetManager();

    void clearAssets();
    void checkShaderErrors(unsigned int shader, std::string type);

    void setTexture(const std::string& assetId, const char* texturePath);
    void setVShader(const std::string& assetId, const char* vertexPath);
    void setFShader(const std::string& assetId, const char* fragmentPath);

    unsigned int getTexture(const std::string& assetId);
    unsigned int getVShader(const std::string& assetId);
    unsigned int getFShader(const std::string& assetId);

private:
    // unaffiliated texture data (no corresponding mesh)
    std::map<std::string, unsigned int> textures;

    // shader data
    std::map<std::string, unsigned int> vshaders;
    std::map<std::string, unsigned int> fshaders;
};

#endif // CORE_ASSETMANAGER_H