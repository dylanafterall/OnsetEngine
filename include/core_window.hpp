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
#include "spdlog/spdlog.h"

#include "core_input_invoker.hpp"

class Window {
public:
    Window(unsigned int, unsigned int);
    ~Window();

    void initialize();
    void setInvoker(InputInvoker*);

    unsigned int m_screenWidth;
    unsigned int m_screenHeight;
    InputInvoker* m_invoker;
    GLFWwindow* m_glfwWindow;
};

#endif // CORE_WINDOW_HPP
