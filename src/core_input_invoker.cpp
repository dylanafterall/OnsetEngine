// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_input_invoker.cpp
//  uses COMMANDER design pattern
//  layer of abstraction, allowing user to set/reset keybinds 
// -----------------------------------------------------------------------------

#include "core_input_invoker.h"


// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// initialize and destroy
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

void InputInvoker::initialize(
    GLFWwindow* glfwWindow,
    entt::registry* registryPtr, 
    unsigned int screenWidth, 
    unsigned int screenHeight
) {
    m_glfwWindow = glfwWindow;
    m_registryPtr = registryPtr;
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    m_lastX = screenWidth / 2;
    m_lastY = screenHeight / 2;

    // glfw callback functions for user input 
    glfwSetWindowUserPointer(m_glfwWindow, this);

    // keyboard input
    auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        static_cast<InputInvoker*>(glfwGetWindowUserPointer(window))->handleKeyInput(window, key, scancode, action, mods);
    };
    glfwSetKeyCallback(m_glfwWindow, key_callback);
    // glfwSetInputMode(m_glfwWindow, GLFW_STICKY_KEYS, 1);
    // glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

    // mouse input
    auto mouse_callback = [](GLFWwindow* window, double xposIn, double yposIn) {
        static_cast<InputInvoker*>(glfwGetWindowUserPointer(window))->handleMouseInput(xposIn, yposIn);
    };
    glfwSetCursorPosCallback(m_glfwWindow, mouse_callback);
    // tell GLFW to capture our mouse
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // scroll input
    auto scroll_callback = [](GLFWwindow* window, double xoffset, double yoffset) {
        static_cast<InputInvoker*>(glfwGetWindowUserPointer(window))->handleScrollInput(static_cast<float>(yoffset));
    };
    glfwSetScrollCallback(m_glfwWindow, scroll_callback);

    // set input commands 
    setScrollUpCommand(new CameraZoomInCommand());
    setScrollDownCommand(new CameraZoomOutCommand());
    setCursorLeftCommand(new WestCommand());
    setCursorDownCommand(new SouthCommand());
    setCursorRightCommand(new EastCommand());
    setCursorUpCommand(new NorthCommand());
    setCursorUp_rightCommand(new NortheastCommand());
    setCursorUp_leftCommand(new NorthwestCommand());
    setCursorDown_leftCommand(new SouthwestCommand());
    setCursorDown_rightCommand(new SoutheastCommand());
    setAKeyCommand(new LeftCommand);
    setSKeyCommand(new DownCommand());
    setDKeyCommand(new RightCommand());
    setWKeyCommand(new UpCommand());
    setEKeyCommand(new ToggleSelectModeCommand());
    setHKeyCommand(new CameraLeftCommand());
    setJKeyCommand(new CameraDownCommand());
    setKKeyCommand(new CameraUpCommand());
    setLKeyCommand(new CameraRightCommand());
    setUKeyCommand(new CameraForwardCommand());
    setIKeyCommand(new CameraBackwardCommand());
    set7KeyCommand(new CameraPitchUpCommand());
    set8KeyCommand(new CameraPitchDownCommand());
    set9KeyCommand(new CameraYawLeftCommand());
    set0KeyCommand(new CameraYawRightCommand());
    setShiftAKeyCommand(new SelectedLeftCommand);
    setShiftSKeyCommand(new SelectedDownCommand);
    setShiftDKeyCommand(new SelectedRightCommand);
    setShiftWKeyCommand(new SelectedUpCommand);
}

void InputInvoker::destroy() {
    delete m_scrollUpMove;
    delete m_scrollDownMove;
    delete m_cursorLeftMove;
    delete m_cursorDownMove;
    delete m_cursorRightMove;
    delete m_cursorUpMove;
    delete m_cursorUp_rightMove;
    delete m_cursorUp_leftMove;
    delete m_cursorDown_leftMove;
    delete m_cursorDown_rightMove;
    delete m_keyA;
    delete m_keyS;
    delete m_keyD;
    delete m_keyW;
    delete m_keyE;
    delete m_keyH;
    delete m_keyJ;
    delete m_keyK;
    delete m_keyL;
    delete m_keyU;
    delete m_keyI;
    delete m_key7;
    delete m_key8;
    delete m_key9;
    delete m_key0;
    delete m_keyShiftA;
    delete m_keyShiftS;
    delete m_keyShiftD;
    delete m_keyShiftW;
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// handling inputs
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

void InputInvoker::handleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, true);
                break;
            case GLFW_KEY_A:
                if (mods == GLFW_MOD_SHIFT) {
                    m_keyShiftA->execute(*m_registryPtr);
                    break;
                }
                m_keyA->execute(*m_registryPtr);
                break;
            case GLFW_KEY_S:
                if (mods == GLFW_MOD_SHIFT) {
                    m_keyShiftS->execute(*m_registryPtr);
                    break;
                }
                m_keyS->execute(*m_registryPtr);
                break;
            case GLFW_KEY_D:
                if (mods == GLFW_MOD_SHIFT) {
                    m_keyShiftD->execute(*m_registryPtr);
                    break;
                }
                m_keyD->execute(*m_registryPtr);
                break;
            case GLFW_KEY_W:
                if (mods == GLFW_MOD_SHIFT) {
                    m_keyShiftW->execute(*m_registryPtr);
                    break;
                }
                m_keyW->execute(*m_registryPtr);
                break;
            case GLFW_KEY_E:
                m_keyE->execute(*m_registryPtr);
                break;
            case GLFW_KEY_H:
                m_keyH->execute(*m_registryPtr);
                break;
            case GLFW_KEY_J:
                m_keyJ->execute(*m_registryPtr);
                break;
            case GLFW_KEY_K:
                m_keyK->execute(*m_registryPtr);
                break;
            case GLFW_KEY_L:
                m_keyL->execute(*m_registryPtr);
                break;
            case GLFW_KEY_U:
                m_keyU->execute(*m_registryPtr);
                break;
            case GLFW_KEY_I:
                m_keyI->execute(*m_registryPtr);
                break;
            case GLFW_KEY_7:
                m_key7->execute(*m_registryPtr);
                break;
            case GLFW_KEY_8:
                m_key8->execute(*m_registryPtr);
                break;
            case GLFW_KEY_9:
                m_key9->execute(*m_registryPtr);
                break;
            case GLFW_KEY_0:
                m_key0->execute(*m_registryPtr);
                break;
        }
    }
}

void InputInvoker::handleMouseInput(double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (m_firstMouse) {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    // reversed since y-coordinates go from bottom to top
    float yoffset = m_lastY - ypos;

    m_lastX = xpos;
    m_lastY = ypos;

    // call InputCommander
    // if cursor is moving to the right
    if (xoffset > 0) {
        if (yoffset > 0) {m_cursorUp_rightMove->execute(*m_registryPtr);}
        else if (yoffset < 0) {m_cursorDown_rightMove->execute(*m_registryPtr);}
        else {m_cursorRightMove->execute(*m_registryPtr);}
    }
    // else if cursor is moving to the left
    else if (xoffset < 0) {
        if (yoffset > 0) {m_cursorUp_leftMove->execute(*m_registryPtr);}
        else if (yoffset < 0) {m_cursorDown_leftMove->execute(*m_registryPtr);}
        else {m_cursorLeftMove->execute(*m_registryPtr);}
    }
    // else cursor is moving, but not left or right
    else {
        if (yoffset > 0) {m_cursorUpMove->execute(*m_registryPtr);}
        else {m_cursorDownMove->execute(*m_registryPtr);}
    }
}

void InputInvoker::handleScrollInput(float yoffset) {
    // positive yoffset means scroll down
    if (yoffset > 0) {m_scrollDownMove->execute(*m_registryPtr);}
    // negative yoffset is scroll up
    else {m_scrollUpMove->execute(*m_registryPtr);}
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// setting scroll wheel 
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

void InputInvoker::setScrollUpCommand(IInputCommand* command) {
    m_scrollUpMove = command;
}

void InputInvoker::setScrollDownCommand(IInputCommand* command) {
    m_scrollDownMove = command;
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// setting cursor 
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

void InputInvoker::setCursorLeftCommand(IInputCommand* command) {
    m_cursorLeftMove = command;
}

void InputInvoker::setCursorDownCommand(IInputCommand* command) {
    m_cursorDownMove = command;
}

void InputInvoker::setCursorRightCommand(IInputCommand* command) {
    m_cursorRightMove = command;
}

void InputInvoker::setCursorUpCommand(IInputCommand* command) {
    m_cursorUpMove = command;
}

void InputInvoker::setCursorUp_rightCommand(IInputCommand* command) {
    m_cursorUp_rightMove = command;
}

void InputInvoker::setCursorUp_leftCommand(IInputCommand* command) {
    m_cursorUp_leftMove = command;
}

void InputInvoker::setCursorDown_leftCommand(IInputCommand* command) {
    m_cursorDown_leftMove = command;
}

void InputInvoker::setCursorDown_rightCommand(IInputCommand* command) {
    m_cursorDown_rightMove = command;
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// setting keys
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

void InputInvoker::setAKeyCommand(IInputCommand* command) {
    m_keyA = command;
}

void InputInvoker::setSKeyCommand(IInputCommand* command) {
    m_keyS = command;
}

void InputInvoker::setDKeyCommand(IInputCommand* command) {
    m_keyD = command;
}

void InputInvoker::setWKeyCommand(IInputCommand* command) {
    m_keyW = command;
}

void InputInvoker::setEKeyCommand(IInputCommand* command) {
    m_keyE = command;
}

void InputInvoker::setHKeyCommand(IInputCommand* command) {
    m_keyH = command;
}

void InputInvoker::setJKeyCommand(IInputCommand* command) {
    m_keyJ = command;
}

void InputInvoker::setKKeyCommand(IInputCommand* command) {
    m_keyK = command;
}

void InputInvoker::setLKeyCommand(IInputCommand* command) {
    m_keyL = command;
}

void InputInvoker::setUKeyCommand(IInputCommand* command) {
    m_keyU = command;
}

void InputInvoker::setIKeyCommand(IInputCommand* command) {
    m_keyI = command;
}

void InputInvoker::set7KeyCommand(IInputCommand* command) {
    m_key7 = command;
}

void InputInvoker::set8KeyCommand(IInputCommand* command) {
    m_key8 = command;
}

void InputInvoker::set9KeyCommand(IInputCommand* command) {
    m_key9 = command;
}

void InputInvoker::set0KeyCommand(IInputCommand* command) {
    m_key0 = command;
}

void InputInvoker::setShiftAKeyCommand(IInputCommand* command) {
    m_keyShiftA = command;
}

void InputInvoker::setShiftSKeyCommand(IInputCommand* command) {
    m_keyShiftS = command;
}

void InputInvoker::setShiftDKeyCommand(IInputCommand* command) {
    m_keyShiftD = command;
}

void InputInvoker::setShiftWKeyCommand(IInputCommand* command) {
    m_keyShiftW = command;
}