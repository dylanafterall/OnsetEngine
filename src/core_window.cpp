// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_window.cpp
//  implementation: handling GLFW window data/functionality  
// -----------------------------------------------------------------------------

#include "core_window.hpp"

#include "spdlog/spdlog.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Callback Function Declarations 

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Constructor and Destructor

Window::Window() {
    spdlog::info("Window constructor called!");
}

Window::~Window() {
    // destroy windows, de-allocate GLFW resources, set library to uninitialized 
    glfwTerminate();

    spdlog::info("Window destructor called!");
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// initialize

void Window::initialize() {
    // initialize GLFW library ................................................. 
    if (!glfwInit()) {
        spdlog::critical("Failed to initialize GLFW");
        return;
    }
    // set hints for next call to glfwCreateWindow()
    // using OpenGL version 3.3 with Core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // create a GLFW window ....................................................
    m_glfwWindow = glfwCreateWindow(
        SCR_WIDTH,
        SCR_HEIGHT,
        "",             // initial window title
        NULL,           // glfwGetPrimaryMonitor() or NULL for windowed mode
        NULL            // which window whose context to share resources with
    );
    if (!m_glfwWindow) {
        spdlog::critical("Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    // make context of window current on the calling thread
    // only one current context per thread, only one thread per current context
    glfwMakeContextCurrent(m_glfwWindow);
    // register callback function - tell GLFW to call this on window resize
    glfwSetFramebufferSizeCallback(m_glfwWindow, framebuffer_size_callback);

    // glad: load all OpenGL function pointers .................................
    // glfwGetProcAddress defines the correct function based on OS 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::critical("Failed to initialize GLAD");
        return;
    }
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Callback Function Definitions

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // gets called when window first displayed and any subsequent resizing 
    // glViewport maps OpenGL's coordinates into screen coordinates
    //  - OpenGL coordinates (both x and y) will range from (-1 to 1) 
    //  - we must map those coordinates to (0, width) and (0, height)
    glViewport(
        0,          // lower left corner x-coordinate
        0,          // lower left corner y-coordinate
        width,      // width of viewport 
        height      // height of viewport
    );
}
