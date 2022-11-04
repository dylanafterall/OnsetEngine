// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_window.cpp
//  implementation: handling GLFW window data/functionality  
// -----------------------------------------------------------------------------

#include "core_window.hpp"

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Callback Function Declarations 
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow*, int, int);

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Constructor and Destructor
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// Window(): -------------------------------------------------------------------
Window::Window(unsigned int screenWidth, unsigned int screenHeight) {
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    spdlog::info("Window constructor called!");
}

// ~Window(): ------------------------------------------------------------------
Window::~Window() {
    // destroy windows, de-allocate GLFW resources, set library to uninitialized 
    glfwTerminate();
    spdlog::info("Window destructor called!");
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Setup
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// setInvoker(): ---------------------------------------------------------------
void Window::setInvoker(InputInvoker* invoker) {
    m_invoker = invoker;
}

// initialize(): ---------------------------------------------------------------
void Window::initialize() {
    // initialize GLFW library  
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

    // create a GLFW window 
    m_glfwWindow = glfwCreateWindow(
        m_screenWidth,
        m_screenHeight,
        "",             // initial window title
        NULL,           // glfwGetPrimaryMonitor() or NULL for windowed mode
        NULL            // which window whose context to share resources with
    );
    if (!m_glfwWindow) {
        spdlog::critical("Failed to create GLFW window");
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
        spdlog::critical("Failed to initialize GLAD");
        return;
    }

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);    // used for z-buffer

    // handling user input -----------------------------------------------------

    // before processing keyboard input, need to set initial commands for keys
    m_invoker->setAKeyCommand(new LeftCommand());
    m_invoker->setSKeyCommand(new DownCommand());
    m_invoker->setDKeyCommand(new RightCommand());
    m_invoker->setWKeyCommand(new UpCommand());

    // callback functions for user input
    glfwSetWindowUserPointer(m_glfwWindow, m_invoker);

    // keyboard input
    auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        static_cast<InputInvoker*>(glfwGetWindowUserPointer(window))->handleKeyInput(window, key, action);
    };
    glfwSetKeyCallback(m_glfwWindow, key_callback);
    // glfwSetInputMode(m_glfwWindow, GLFW_STICKY_KEYS, 1);
    // glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

    // mouse input
    auto mouse_callback = [](GLFWwindow* window, double xposIn, double yposIn) {
        static_cast<InputInvoker*>(glfwGetWindowUserPointer(window))->handleMouseInput(window, xposIn, yposIn);
    };
    glfwSetCursorPosCallback(m_glfwWindow, mouse_callback);
    // tell GLFW to capture our mouse
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // scroll input
    auto scroll_callback = [](GLFWwindow* window, double xoffset, double yoffset) {
        static_cast<InputInvoker*>(glfwGetWindowUserPointer(window))->handleScrollInput(window, xoffset, yoffset);
    };
    glfwSetScrollCallback(m_glfwWindow, scroll_callback);
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// Callback Function Definitions
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// framebuffer_size_callback(): ------------------------------------------------
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