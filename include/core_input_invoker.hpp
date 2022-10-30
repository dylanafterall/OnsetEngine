// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_input_invoker.hpp
//  uses COMMANDER design pattern
//  layer of abstraction, allowing user to set/reset keybinds
// -----------------------------------------------------------------------------

#ifndef CORE_INPUT_INVOKER_HPP
#define CORE_INPUT_INVOKER_HPP

#include "core_input_commander.hpp"

#include "GLFW/glfw3.h"
#include "spdlog/spdlog.h"

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// COMMAND PATTERN: Invoker (see commands in system_input.hpp)
// _____________________________________________________________________________
// -----------------------------------------------------------------------------
class InputInvoker {
public:
    InputInvoker();
    ~InputInvoker();

    void setAKeyCommand(IInputCommand*);
    void setSKeyCommand(IInputCommand*);
    void setDKeyCommand(IInputCommand*);
    void setWKeyCommand(IInputCommand*);

    void handleInput(GLFWwindow*, int, int);

private:
    IInputCommand* m_keyA;
    IInputCommand* m_keyS;
    IInputCommand* m_keyD;
    IInputCommand* m_keyW; 
};

#endif // CORE_INPUT_INVOKER_HPP