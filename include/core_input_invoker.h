// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_input_invoker.h
//  uses COMMANDER design pattern
//  layer of abstraction, allowing user to set/reset keybinds
// -----------------------------------------------------------------------------

#ifndef CORE_INPUT_INVOKER_H
#define CORE_INPUT_INVOKER_H

#include "core_input_commander.h"

#include "GLFW/glfw3.h"
#include "entt/entt.hpp"


/** 
 * \brief   The InputInvoker class.
 * \details Used by Game class as a layer of abstraction between glfw user input
 *          callback functions and the commands for those associated inputs. Is 
 *          an implementation of the Command Pattern, interfacing with the 
 *          IInputCommand class. Allows for re-binding of commands to inputs.
 */
class InputInvoker {
public:
    /**
     * \brief   The default constructor. 
     */
    InputInvoker() = default;
    /**
     * \brief   The default destructor. 
     */
    ~InputInvoker() = default;

    /**
     * \brief   The function initialize. 
     * \details This function sets member variables, glfw callback functions
     *          for user input (keyboard, mouse, scrollwheel), and sets 
     *          an IInputCommand class for each input option.
     * \param   glfwWindow      For using glfw callback functions.
     * \param   registryPtr     For passing game's registry to IInputCommander classes.
     * \param   screenWidth     For calculating m_lastX and mouse input direction.
     * \param   screenHeight    For calculating m_lastY and mouse input direction.
     * \return  void, none.
     */
    void initialize(GLFWwindow*, entt::registry*, unsigned int, unsigned int);
    /**
     * \brief   The function destroy. 
     * \details This function de-allocates heap memory reserved for 
     *          IInputCommand class instances (allocated in initialize).
     * \return  void, none.
     */
    void destroy();
    /**
     * \brief   The function handleKeyInput. 
     * \details This function processes user keyboard input, directing each 
     *          key to its IInputCommand class (set in initialize()).
     * \param   window      For identifying the glfw window for associated input .
     * \param   key         For identifying which key user inputted.
     * \param   action      For identifying how key was inputted (ex: press vs repeat).
     * \return  void, none.
     */
    void handleKeyInput(GLFWwindow*, int, int);
    /**
     * \brief   The function handleMouseInput. 
     * \details This function calculates the change in mouse position by 
     *          magnitude and direction, then directs each directional input
     *          to an IInputCommand class (set in initialize()).
     * \param   xposIn      For difference between previous and current mouse position.
     * \param   yposIn      For difference between previous and current mouse position.
     * \return  void, none.
     */
    void handleMouseInput(double, double);
    /**
     * \brief   The function handleScrollInput. 
     * \details This function processes user scrollwheel input, directing each 
     *          input (up or down) to an IInputCommand class (set in initialize()).
     * \param   yoffset      For determining if scrollwheel input was up or down.
     * \return  void, none.
     */
    void handleScrollInput(float);

    /**
     * \brief   The function setScrollUpCommand. 
     * \details This function assigns the scrollwheel-up input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setScrollUpCommand(IInputCommand*);
    /**
     * \brief   The function setScrollDownCommand. 
     * \details This function assigns the scrollwheel-down input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setScrollDownCommand(IInputCommand*);
    /**
     * \brief   The function setCursorLeftCommand. 
     * \details This function assigns the cursor-left input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setCursorLeftCommand(IInputCommand*);
    /**
     * \brief   The function setCursorDownCommand. 
     * \details This function assigns the cursor-down input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setCursorDownCommand(IInputCommand*);
    /**
     * \brief   The function setCursorRightCommand. 
     * \details This function assigns the cursor-right input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setCursorRightCommand(IInputCommand*);
    /**
     * \brief   The function setCursorUpCommand. 
     * \details This function assigns the cursor-up input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setCursorUpCommand(IInputCommand*);
    /**
     * \brief   The function setCursorUp_rightCommand. 
     * \details This function assigns the cursor-up&right input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setCursorUp_rightCommand(IInputCommand*);
    /**
     * \brief   The function setCursorUp_leftCommand. 
     * \details This function assigns the cursor-up&left input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setCursorUp_leftCommand(IInputCommand*);
    /**
     * \brief   The function setCursorDown_leftCommand. 
     * \details This function assigns the cursor-down&left input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setCursorDown_leftCommand(IInputCommand*);
    /**
     * \brief   The function setCursorDown_rightCommand. 
     * \details This function assigns the cursor-down&right input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setCursorDown_rightCommand(IInputCommand*);
    /**
     * \brief   The function setAKeyCommand. 
     * \details This function assigns the key-A input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setAKeyCommand(IInputCommand*);
    /**
     * \brief   The function setSKeyCommand. 
     * \details This function assigns the key-S input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setSKeyCommand(IInputCommand*);
    /**
     * \brief   The function setDKeyCommand. 
     * \details This function assigns the key-D input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setDKeyCommand(IInputCommand*);
    /**
     * \brief   The function setWKeyCommand. 
     * \details This function assigns the key-W input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setWKeyCommand(IInputCommand*);
    /**
     * \brief   The function setEKeyCommand. 
     * \details This function assigns the key-E input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setEKeyCommand(IInputCommand*);
    /**
     * \brief   The function setHKeyCommand. 
     * \details This function assigns the key-H input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setHKeyCommand(IInputCommand*);
    /**
     * \brief   The function setJKeyCommand. 
     * \details This function assigns the key-J input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setJKeyCommand(IInputCommand*);
    /**
     * \brief   The function setKKeyCommand. 
     * \details This function assigns the key-K input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setKKeyCommand(IInputCommand*);
    /**
     * \brief   The function setLKeyCommand. 
     * \details This function assigns the key-L input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setLKeyCommand(IInputCommand*);
    /**
     * \brief   The function setUKeyCommand. 
     * \details This function assigns the key-U input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setUKeyCommand(IInputCommand*);
    /**
     * \brief   The function setIKeyCommand. 
     * \details This function assigns the key-I input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void setIKeyCommand(IInputCommand*);
    /**
     * \brief   The function set7KeyCommand. 
     * \details This function assigns the key-7 input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void set7KeyCommand(IInputCommand*);
    /**
     * \brief   The function set8KeyCommand. 
     * \details This function assigns the key-8 input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void set8KeyCommand(IInputCommand*);
    /**
     * \brief   The function set9KeyCommand. 
     * \details This function assigns the key-9 input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void set9KeyCommand(IInputCommand*);
    /**
     * \brief   The function set0KeyCommand. 
     * \details This function assigns the key-0 input a IInputCommand 
     *          class.
     * \param   command     The desired IInputCommand class to assign.
     * \return  void, none.
     */
    void set0KeyCommand(IInputCommand*);

private:
    /**
     * \brief Pointer to the game's glfw window for callback functions.
     */
    GLFWwindow* m_glfwWindow;
    /**
     * \brief Pointer to game's registry to pass to IInputCommand classes.
     */
    entt::registry* m_registryPtr;
    /**
     * \brief The game's window width, for calculating initial mouse position.
     */
    unsigned int m_screenWidth;
    /**
     * \brief The game's window height, for calculating initial mouse position.
     */
    unsigned int m_screenHeight;
    /**
     * \brief Initially m_screenWidth / 2, for calculating change in mouse position.
     */
    float m_lastX; 
    /**
     * \brief Initially m_screenHeight / 2, for calculating change in mouse position.
     */
    float m_lastY;
    /**
     * \brief For setting the mouse's initial position upon first cursor movement input.
     */
    bool m_firstMouse = true;

    /**
     * \brief Pointer to the IInputCommand class for a scrollwheel-up input.
     */
    IInputCommand* m_scrollUpMove;
    /**
     * \brief Pointer to the IInputCommand class for a scrollwheel-down input.
     */
    IInputCommand* m_scrollDownMove;
    /**
     * \brief Pointer to the IInputCommand class for a cursor-left input.
     */
    IInputCommand* m_cursorLeftMove;
    /**
     * \brief Pointer to the IInputCommand class for a cursor-down input.
     */
    IInputCommand* m_cursorDownMove;
    /**
     * \brief Pointer to the IInputCommand class for a cursor-right input.
     */
    IInputCommand* m_cursorRightMove;
    /**
     * \brief Pointer to the IInputCommand class for a cursor-up input.
     */
    IInputCommand* m_cursorUpMove;
    /**
     * \brief Pointer to the IInputCommand class for a cursor-up&right input.
     */
    IInputCommand* m_cursorUp_rightMove;
    /**
     * \brief Pointer to the IInputCommand class for a cursor-up&left input.
     */
    IInputCommand* m_cursorUp_leftMove;
    /**
     * \brief Pointer to the IInputCommand class for a cursor-down&left input.
     */
    IInputCommand* m_cursorDown_leftMove;
    /**
     * \brief Pointer to the IInputCommand class for a cursor-down&right input.
     */
    IInputCommand* m_cursorDown_rightMove;
    /**
     * \brief Pointer to the IInputCommand class for a key-A input.
     */
    IInputCommand* m_keyA;
    /**
     * \brief Pointer to the IInputCommand class for a key-S input.
     */
    IInputCommand* m_keyS;
    /**
     * \brief Pointer to the IInputCommand class for a key-D input.
     */
    IInputCommand* m_keyD;
    /**
     * \brief Pointer to the IInputCommand class for a key-W input.
     */
    IInputCommand* m_keyW; 
    /**
     * \brief Pointer to the IInputCommand class for a key-E input.
     */
    IInputCommand* m_keyE; 
    /**
     * \brief Pointer to the IInputCommand class for a key-H input.
     */
    IInputCommand* m_keyH;
    /**
     * \brief Pointer to the IInputCommand class for a key-J input.
     */
    IInputCommand* m_keyJ;
    /**
     * \brief Pointer to the IInputCommand class for a key-K input.
     */
    IInputCommand* m_keyK;
    /**
     * \brief Pointer to the IInputCommand class for a key-L input.
     */
    IInputCommand* m_keyL;
    /**
     * \brief Pointer to the IInputCommand class for a key-U input.
     */
    IInputCommand* m_keyU;
    /**
     * \brief Pointer to the IInputCommand class for a key-I input.
     */
    IInputCommand* m_keyI;
    /**
     * \brief Pointer to the IInputCommand class for a key-7 input.
     */
    IInputCommand* m_key7;
    /**
     * \brief Pointer to the IInputCommand class for a key-8 input.
     */
    IInputCommand* m_key8;
    /**
     * \brief Pointer to the IInputCommand class for a key-9 input.
     */
    IInputCommand* m_key9;
    /**
     * \brief Pointer to the IInputCommand class for a key-0 input.
     */
    IInputCommand* m_key0;
};

#endif // CORE_INPUT_INVOKER_H