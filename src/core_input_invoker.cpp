// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_input_invoker.cpp
//  uses COMMANDER design pattern
//  layer of abstraction, allowing user to set/reset keybinds 
// -----------------------------------------------------------------------------

#include "core_input_invoker.hpp"

InputInvoker::InputInvoker() {
    spdlog::info("InputInvoker constructor called!");
}

InputInvoker::~InputInvoker() {
    delete m_keyA;
    delete m_keyS;
    delete m_keyD;
    delete m_keyW;
    spdlog::info("InputInvoker destructor called!");
}

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

void InputInvoker::handleInput(GLFWwindow* window, int key, int action) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        m_keyA->execute();
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        m_keyS->execute();
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        m_keyD->execute();
    }
    else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        m_keyW->execute();
    }
}