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
#include "entt/entt.hpp"
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

    void setInvokerRegistry(entt::registry*);
    void setInvokerAspect(unsigned int, unsigned int);

    void setScrollUpCommand(IInputCommand*);
    void setScrollDownCommand(IInputCommand*);

    void setCursorLeftCommand(IInputCommand*);
    void setCursorDownCommand(IInputCommand*);
    void setCursorRightCommand(IInputCommand*);
    void setCursorUpCommand(IInputCommand*);
    void setCursorUp_rightCommand(IInputCommand*);
    void setCursorUp_leftCommand(IInputCommand*);
    void setCursorDown_leftCommand(IInputCommand*);
    void setCursorDown_rightCommand(IInputCommand*);
    
    void setAKeyCommand(IInputCommand*);
    void setSKeyCommand(IInputCommand*);
    void setDKeyCommand(IInputCommand*);
    void setWKeyCommand(IInputCommand*);
    void setHKeyCommand(IInputCommand*);
    void setJKeyCommand(IInputCommand*);
    void setKKeyCommand(IInputCommand*);
    void setLKeyCommand(IInputCommand*);
    void setUKeyCommand(IInputCommand*);
    void setIKeyCommand(IInputCommand*);
    void set7KeyCommand(IInputCommand*);
    void set8KeyCommand(IInputCommand*);
    void set9KeyCommand(IInputCommand*);
    void set0KeyCommand(IInputCommand*);

    void handleKeyInput(GLFWwindow*, int, int);
    void handleMouseInput(double, double);
    void handleScrollInput(float);

private:
    entt::registry* m_registryPtr;

    unsigned int m_screenWidth; // game class will initially set to scr_width
    unsigned int m_screenHeight; // game class will initially set to scr_height
    float m_lastX; // game class will initially set to scr_width / 2
    float m_lastY; // game class will initially set to scr_height / 2
    bool m_firstMouse = true;

    IInputCommand* m_scrollUpMove;
    IInputCommand* m_scrollDownMove;

    IInputCommand* m_cursorLeftMove;
    IInputCommand* m_cursorDownMove;
    IInputCommand* m_cursorRightMove;
    IInputCommand* m_cursorUpMove;
    IInputCommand* m_cursorUp_rightMove;
    IInputCommand* m_cursorUp_leftMove;
    IInputCommand* m_cursorDown_leftMove;
    IInputCommand* m_cursorDown_rightMove;
    
    IInputCommand* m_keyA;
    IInputCommand* m_keyS;
    IInputCommand* m_keyD;
    IInputCommand* m_keyW; 
    IInputCommand* m_keyH;
    IInputCommand* m_keyJ;
    IInputCommand* m_keyK;
    IInputCommand* m_keyL;
    IInputCommand* m_keyU;
    IInputCommand* m_keyI;
    IInputCommand* m_key7;
    IInputCommand* m_key8;
    IInputCommand* m_key9;
    IInputCommand* m_key0;
};

#endif // CORE_INPUT_INVOKER_HPP