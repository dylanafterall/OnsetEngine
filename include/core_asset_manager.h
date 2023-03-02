// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_asset_manager.h
//  header of AssetManager class, functionality for adding/removing assets
// -----------------------------------------------------------------------------
#ifndef CORE_ASSET_MANAGER_H
#define CORE_ASSET_MANAGER_H

#include "core_log_macros.h"

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "box2d/box2d.h"

#include <map>
#include <fstream>
#include <sstream>
#include <string>

/** 
 * \brief   The AssetManager class.
 * \details Used by the Game class to import triangulated mesh data, textures,
 *          and shaders. Each game level specifies which assets to store to 
 *          a std::map, then is able to copy from the map for each entity that
 *          needs the respective mesh/texture/shader.
 */
class AssetManager {
public:
    /**
     * \brief   The default constructor. 
     */
    AssetManager() = default;
    /**
     * \brief   The default destructor. 
     */
    ~AssetManager() = default;

    /**
     * \brief   The function setTexture. 
     * \details This function imports a texture file - .png or .jpg from the
     *          assets directory, assigns the texture an ID for OpenGL, and 
     *          saves a copy of its ID in a std::map member variable.
     * \param   assetId      ID name to serve as key in std::map textures.
     * \param   texturePath  Relative path to texture asset.
     * \param   repeat       To declare if repeated texture pattern desired.
     * \param   gamma        TO declare if gamma correction desired.
     * \return  void, none.
     */
    void setTexture(const std::string&, const char*, bool, bool);
    /**
     * \brief   The function setCubemap. 
     * \details This function imports a std::vector of 6 texture files - 
     *          .png or .jpg from the assets directory, assigns the texture 
     *          an ID for OpenGL, and saves a copy of its ID in a std::map 
     *          member variable.
     * \param   assetId      ID name to serve as key in std::map textures.
     * \param   faces        std::vector of 6 texture filepaths (.jpg/.png)
     * \param   gamma        To declare if gamma correction desired.
     * \return  void, none.
     */
    void setCubemap(const std::string&, std::vector<std::string>, bool);
    /**
     * \brief   The function setVShader. 
     * \details This function imports a vertex shader file - .vert from the
     *          assets directory, assigns the shader an ID for OpenGL, and 
     *          saves a copy of its ID in a std::map member variable.
     * \param   assetId      ID name to serve as key in std::map vshaders.
     * \param   vertexPath   Relative path to .vert shader asset.
     * \return  void, none.
     */
    void setVShader(const std::string&, const char*);
    /**
     * \brief   The function setFShader. 
     * \details This function imports a fragment shader file - .frag from the
     *          assets directory, assigns the shader an ID for OpenGL, and 
     *          saves a copy of its ID in a std::map member variable.
     * \param   assetId      ID name to serve as key in std::map fshaders.
     * \param   fragmentPath Relative path to .frag shader asset.
     * \return  void, none.
     */
    void setFShader(const std::string&, const char*);
    /**
     * \brief   The function setShaderProgram. 
     * \details This function combines a vertex and fragment shader, both 
     *          stored in OpenGL as an unsigned int (ID), into a shader 
     *          program to be used in rendering. 
     * \param   assetId          ID name - key in std::map shaderPrograms.
     * \param   vertexShader     OpenGL's ID of vertex shader to combine.
     * \param   fragmentShader   OpenGL's ID of fragment shader to combine.
     * \return  void, none.
     */
    void setShaderProgram(const std::string&, unsigned int, unsigned int);

    /**
     * \brief   The function getTexture. 
     * \details This function, given a key for std::map textures, returns
     *          the associated unsigned int ID from OpenGL.
     * \param   program      The name of the key to search the textures
     *                       map for.
     * \retval  ID   An unsigned int stored by OpenGL for an associated
     *               texture asset.
     */
    unsigned int getTexture(const std::string&);
    /**
     * \brief   The function getCubemap. 
     * \details This function, given a key for std::map cubemaps, returns
     *          the associated unsigned int ID from OpenGL.
     * \param   program      The name of the key to search the cubemaps
     *                       map for.
     * \retval  ID   An unsigned int stored by OpenGL for an associated
     *               cubemap asset.
     */
    unsigned int getCubemap(const std::string&);
    /**
     * \brief   The function getVShader. 
     * \details This function, given a key for std::map vshaders, returns
     *          the associated unsigned int ID from OpenGL.
     * \param   program      The name of the key to search the vshaders
     *                       map for.
     * \retval  ID   An unsigned int stored by OpenGL for an associated
     *               vertex shader asset.   
     */
    unsigned int getVShader(const std::string&);
    /**
     * \brief   The function getFShader. 
     * \details This function, given a key for std::map fshaders, returns
     *          the associated unsigned int ID from OpenGL.
     * \param   program      The name of the key to search the fshaders
     *                       map for.
     * \retval  ID   An unsigned int stored by OpenGL for an associated
     *               fragment shader asset.   
     */
    unsigned int getFShader(const std::string&);
    /**
     * \brief   The function getShaderProgram. 
     * \details This function, given a key for std::map shaderPrograms, 
     *          returns the associated unsigned int ID from OpenGL.
     * \param   program      The name of the key to search the 
     *                       shaderPrograms map for.
     * \retval  ID   An unsigned int stored by OpenGL for an associated
     *               shader program asset.  
     */
    unsigned int getShaderProgram(const std::string&);

    /**
     * \brief   The function deleteAssets. 
     * \details This function calls OpenGL functions to free memory allocated
     *          for all texture, shader, and shader program assets. Also 
     *          clears the member variable std::maps.
     * \return  void, none.
     */
    void deleteAssets();
    /**
     * \brief   The function checkShaderErrors. 
     * \details This function checks for errors in the process of compiling 
     *          shader assets into OpenGL, before being added to std::map 
     *          vshaders and fshaders.
     * \param   shader       The ID - assigned by OpenGL - for a shader to
     *                       check for satisfactory compilation.
     * \param   type         The type of shader (ex. vertex, fragment) to 
     *                       check for satisfactory compilation.
     * \return  void, none.
     */
    void checkShaderErrors(unsigned int, std::string);
    /**
     * \brief   The function checkShaderProgramErrors. 
     * \details This function checks for errors in the process of combining 
     *          vertex and fragment shaders into an OpenGL shader program, 
     *          before being added to std::map shaderPrograms.
     * \param   program      The ID - assigned by OpenGL - for a shader
     *                       program, to check for satisfactory generation.
     * \return  void, none.
     */
    void checkShaderProgramErrors(unsigned int);

private:
    /**
     * \brief std::map used to store texture IDs for easy lookup when creating
     *        new game entities.
     */
    std::map<std::string, unsigned int> textures;
    /**
     * \brief std::map used to store cubemap-texture IDs for easy lookup when 
     *        creating new game entities.
     */
    std::map<std::string, unsigned int> cubemaps;
    
    /**
     * \brief std::map used to store vertex shader IDs for easy lookup when 
     *        creating new game entities.
     */
    std::map<std::string, unsigned int> vshaders;
    /**
     * \brief std::map used to store fragment shader IDs for easy lookup when 
     *        creating new game entities.
     */
    std::map<std::string, unsigned int> fshaders;
    
    /**
     * \brief std::map used to store shader program IDs for easy lookup when 
     *        creating new game entities.
     */
    std::map<std::string, unsigned int> shaderPrograms;
};

#endif // CORE_ASSET_MANAGER_H