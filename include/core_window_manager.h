// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_window.h
//  header: handling GLFW window data/functionality  
// -----------------------------------------------------------------------------
#ifndef CORE_WINDOW_MANAGER_H
#define CORE_WINDOW_MANAGER_H

// GLAD before GLFW - glad.h includes OpenGL headers required for GLFW
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "core_log_macros.h"

/** 
 * \brief   The WindowManager class.
 * \details Used by the Game class to create a window via the GLFW external
 *          library. Receives user input via GLFW callback functions on 
 *          associated GLFW window, then directs those inputs to the game's
 *          InputInvoker class object.
 */
class WindowManager {
public:
    /**
     * \brief   The default constructor.
     */
    WindowManager() = default;
    /**
     * \brief   The default destructor. 
     */
    ~WindowManager() = default;

    /**
     * \brief   The function initialize. 
     * \details This function initializes the GLFW library, creates a window,
     *          sets user input commands, and receives user input via GLFW 
     *          callback functions. 
     * \param   screenWidth   Screen width for aspect ratio.
     * \param   screenHeight  Screen height for aspect ratio.
     * \return  void, none.
     */
    void initialize(unsigned int, unsigned int);
    /**
     * \brief   The function destroy. 
     * \details This function destroys glfw windows, de-allocate glfw 
     *          resources, and sets glfw library to uninitialized . 
     * \return  void, none.
     */
    void destroy();

    /**
     * \brief Variable used to store game's aspect ratio.
     */
    unsigned int m_screenWidth;
    /**
     * \brief Variable used to store game's aspect ratio. 
     */
    unsigned int m_screenHeight;

    /**
     * \brief Pointer to game's GLFW generated window.
     */
    GLFWwindow* m_glfwWindow;
};

#endif // CORE_WINDOW_MANAGER_H