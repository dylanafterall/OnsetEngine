
// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_window.h
//  header: handling GLFW window data/functionality  
// -----------------------------------------------------------------------------
#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

// GLAD before GLFW - glad.h includes OpenGL headers required for GLFW
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Window {
public:
    Window();
    ~Window();

    void initialize();

    GLFWwindow* m_glfwWindow;
};

#endif // CORE_WINDOW_H