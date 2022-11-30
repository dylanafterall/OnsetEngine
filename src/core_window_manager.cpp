// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_window_manager.cpp
//  implementation: handling GLFW window data/functionality  
// -----------------------------------------------------------------------------

#include "core_window_manager.h"


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

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// initialize and destroy
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

void WindowManager::initialize(unsigned int screenWidth, unsigned int screenHeight) {
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    // initialize GLFW library  
    if (!glfwInit()) {
        ONSET_FATAL("Failed to initialize GLFW");
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

    // create a GLFW window 
    m_glfwWindow = glfwCreateWindow(
        m_screenWidth,
        m_screenHeight,
        "",             // initial window title
        NULL,           // glfwGetPrimaryMonitor() or NULL for windowed mode
        NULL            // which window whose context to share resources with
    );
    if (!m_glfwWindow) {
        ONSET_FATAL("Failed to create GLFW window");
        glfwTerminate();
        return;
    }

    // only one current context per thread, only one thread per current context
    glfwMakeContextCurrent(m_glfwWindow);
    // tell GLFW to call this on window resize
    glfwSetFramebufferSizeCallback(m_glfwWindow, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // glfwGetProcAddress defines the correct function based on OS 
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        ONSET_FATAL("Failed to initialize GLAD");
        return;
    }

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);    // used for z-buffer
}

void WindowManager::destroy() {
    glfwTerminate();
}