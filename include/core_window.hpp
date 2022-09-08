
// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_window.hpp
//  header: handling GLFW window data/functionality  
// -----------------------------------------------------------------------------
#ifndef CORE_WINDOW_HPP
#define CORE_WINDOW_HPP

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

#endif // CORE_WINDOW_HPP
