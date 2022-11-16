// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_asset_manager.h
//  header of AssetManager class, functionality for adding/removing assets
// -----------------------------------------------------------------------------
#ifndef CORE_ASSET_MANAGER_H
#define CORE_ASSET_MANAGER_H

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

    unsigned int getTexture(const std::string&);
    unsigned int getVShader(const std::string&);
    unsigned int getFShader(const std::string&);
    unsigned int getShaderProgram(const std::string&);

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
};

#endif // CORE_ASSET_MANAGER_H