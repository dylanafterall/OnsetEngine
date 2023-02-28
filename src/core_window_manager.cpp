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
    // use multisample buffer w/ N samples instead of normal buffer (for MSAA)
    glfwWindowHint(GLFW_SAMPLES, 4);

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

    // tell GLFW to capture our mouse
    glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // configure global opengl state
    // _________________________________________________________________________
    // -------------------------------------------------------------------------
    // enable z-buffer
    glEnable(GL_DEPTH_TEST);
    // passes if the fragment's depth value is less than the stored depth value
    glDepthFunc(GL_LESS); 
    // enable stencil-buffer
    glEnable(GL_STENCIL_TEST);
    // describe whether OpenGL should pass or discard fragments based on the stencil buffer's content
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    // contains three options to specify how to update stencil buffer
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    // enable blending for object transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // enable backface culling
    glEnable(GL_CULL_FACE); 
    //  enable multisampling - used in MSAA
    glEnable(GL_MULTISAMPLE);  

    // depth-testing options for future reference
    // temporarily use a read-only depth buffer (disable writing to depth buffer)
    // glDepthMask(GL_FALSE); 
    // the depth test always passes.
    // glDepthFunc(GL_ALWAYS);
    // the depth test never passes.
    // glDepthFunc(GL_NEVER); 
    // passes if the fragment's depth value is less than the stored depth value.
    // glDepthFunc(GL_LESS); 
    // passes if the fragment's depth value is equal to the stored depth value.
    // glDepthFunc(GL_EQUAL); 
    // passes if the fragment's depth value is less than or equal to the stored depth value.
    // glDepthFunc(GL_LEQUAL); 
    // passes if the fragment's depth value is greater than the stored depth value.
    // glDepthFunc(GL_GREATER); 
    // passes if the fragment's depth value is not equal to the stored depth value.
    // glDepthFunc(GL_NOTEQUAL); 
    // passes if the fragment's depth value is greater than or equal to the stored depth value.
    // glDepthFunc(GL_GEQUAL); 
}

void WindowManager::destroy() {
    glfwTerminate();
}