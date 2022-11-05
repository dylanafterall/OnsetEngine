// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_input_invoker.cpp
//  uses COMMANDER design pattern
//  layer of abstraction, allowing user to set/reset keybinds 
// -----------------------------------------------------------------------------

#include "core_input_invoker.hpp"

// InputInvoker(): -------------------------------------------------------------
InputInvoker::InputInvoker() {
    spdlog::info("InputInvoker constructor called!");
}

// ~InputInvoker(): ------------------------------------------------------------
InputInvoker::~InputInvoker() {
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

    spdlog::info("InputInvoker destructor called!");
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// setting up invoker
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// setInvokerRegistry(): -------------------------------------------------------
void InputInvoker::setInvokerRegistry(entt::registry* registryPtr) {
    m_registryPtr = registryPtr;
}

// setInvokerAspect(): ---------------------------------------------------------
void InputInvoker::setInvokerAspect(unsigned int screenWidth, unsigned int screenHeight) {
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    m_lastX = screenWidth / 2;
    m_lastY = screenHeight / 2;
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// setting scroll wheel 
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// setScrollUpCommand(): -------------------------------------------------------
void InputInvoker::setScrollUpCommand(IInputCommand* command) {
    m_scrollUpMove = command;
}

// setScrollDownCommand(): -----------------------------------------------------
void InputInvoker::setScrollDownCommand(IInputCommand* command) {
    m_scrollDownMove = command;
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// setting cursor 
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// setCursorLeftCommand(): -----------------------------------------------------
void InputInvoker::setCursorLeftCommand(IInputCommand* command) {
    m_cursorLeftMove = command;
}

// setCursorDownCommand(): -----------------------------------------------------
void InputInvoker::setCursorDownCommand(IInputCommand* command) {
    m_cursorDownMove = command;
}

// setCursorRightCommand(): ----------------------------------------------------
void InputInvoker::setCursorRightCommand(IInputCommand* command) {
    m_cursorRightMove = command;
}

// setCursorUpCommand(): -------------------------------------------------------
void InputInvoker::setCursorUpCommand(IInputCommand* command) {
    m_cursorUpMove = command;
}

// setCursorUp_rightCommand(): -------------------------------------------------
void InputInvoker::setCursorUp_rightCommand(IInputCommand* command) {
    m_cursorUp_rightMove = command;
}

// setCursorUp_leftCommand(): --------------------------------------------------
void InputInvoker::setCursorUp_leftCommand(IInputCommand* command) {
    m_cursorUp_leftMove = command;
}

// setCursorDown_leftCommand(): ------------------------------------------------
void InputInvoker::setCursorDown_leftCommand(IInputCommand* command) {
    m_cursorDown_leftMove = command;
}

// setCursorDown_rightCommand(): ----------------------------------------------
void InputInvoker::setCursorDown_rightCommand(IInputCommand* command) {
    m_cursorDown_rightMove = command;
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// setting keys
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// setAKeyCommand(): -----------------------------------------------------------
void InputInvoker::setAKeyCommand(IInputCommand* command) {
    m_keyA = command;
}

// setSKeyCommand(): -----------------------------------------------------------
void InputInvoker::setSKeyCommand(IInputCommand* command) {
    m_keyS = command;
}

// setDKeyCommand(): -----------------------------------------------------------
void InputInvoker::setDKeyCommand(IInputCommand* command) {
    m_keyD = command;
}

// setWKeyCommand(): -----------------------------------------------------------
void InputInvoker::setWKeyCommand(IInputCommand* command) {
    m_keyW = command;
}

// setHKeyCommand(): -----------------------------------------------------------
void InputInvoker::setHKeyCommand(IInputCommand* command) {
    m_keyH = command;
}

// setJKeyCommand(): -----------------------------------------------------------
void InputInvoker::setJKeyCommand(IInputCommand* command) {
    m_keyJ = command;
}

// setKKeyCommand(): -----------------------------------------------------------
void InputInvoker::setKKeyCommand(IInputCommand* command) {
    m_keyK = command;
}

// setLKeyCommand(): -----------------------------------------------------------
void InputInvoker::setLKeyCommand(IInputCommand* command) {
    m_keyL = command;
}

// setUKeyCommand(): -----------------------------------------------------------
void InputInvoker::setUKeyCommand(IInputCommand* command) {
    m_keyU = command;
}

// setIKeyCommand(): -----------------------------------------------------------
void InputInvoker::setIKeyCommand(IInputCommand* command) {
    m_keyI = command;
}

// set7KeyCommand(): -----------------------------------------------------------
void InputInvoker::set7KeyCommand(IInputCommand* command) {
    m_key7 = command;
}

// set8KeyCommand(): -----------------------------------------------------------
void InputInvoker::set8KeyCommand(IInputCommand* command) {
    m_key8 = command;
}

// set9KeyCommand(): -----------------------------------------------------------
void InputInvoker::set9KeyCommand(IInputCommand* command) {
    m_key9 = command;
}

// set0KeyCommand(): -----------------------------------------------------------
void InputInvoker::set0KeyCommand(IInputCommand* command) {
    m_key0 = command;
}

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// handling inputs
// _____________________________________________________________________________
// -----------------------------------------------------------------------------

// handleKeyInput(): -----------------------------------------------------------
void InputInvoker::handleKeyInput(GLFWwindow* window, int key, int action) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        m_keyA->execute(*m_registryPtr);
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        m_keyS->execute(*m_registryPtr);
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        m_keyD->execute(*m_registryPtr);
    }
    else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        m_keyW->execute(*m_registryPtr);
    }
    else if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        m_keyH->execute(*m_registryPtr);
    }
    else if (key == GLFW_KEY_J && action == GLFW_PRESS) {
        m_keyJ->execute(*m_registryPtr);
    }
    else if (key == GLFW_KEY_K && action == GLFW_PRESS) {
        m_keyK->execute(*m_registryPtr);
    }
    else if (key == GLFW_KEY_L && action == GLFW_PRESS) {
        m_keyL->execute(*m_registryPtr);
    }
    else if (key == GLFW_KEY_U && action == GLFW_PRESS) {
        m_keyU->execute(*m_registryPtr);
    }
    else if (key == GLFW_KEY_I && action == GLFW_PRESS) {
        m_keyI->execute(*m_registryPtr);
    }
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
        m_key7->execute(*m_registryPtr);
    }
    else if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
        m_key8->execute(*m_registryPtr);
    }
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
        m_key9->execute(*m_registryPtr);
    }
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
        m_key0->execute(*m_registryPtr);
    }
}

// handleMouseInput(): ---------------------------------------------------------
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

// handleScrollInput(): --------------------------------------------------------
void InputInvoker::handleScrollInput(float yoffset) {
    // positive yoffset means scroll down
    if (yoffset > 0) {m_scrollDownMove->execute(*m_registryPtr);}
    // negative yoffset is scroll up
    else {m_scrollUpMove->execute(*m_registryPtr);}
}