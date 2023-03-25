// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_input_commander.h
//	uses COMMANDER design pattern
//  contains code to execute for all input commands (via keyboard, mouse, etc)
// -----------------------------------------------------------------------------

#ifndef CORE_INPUT_COMMANDER_H
#define CORE_INPUT_COMMANDER_H

#include "core_log_macros.h"

#include "entt/entt.hpp"


/** 
 * \brief   The IInputCommand class.
 * \details Used by InputInvoker class to assign game behavior to user input. 
 * 			Implementation of the Command Programming Pattern: encapsulates an
 * 			input request as an object, allowing re-mapping of commands to 
 * 			input keybinds. Exists to be overridden by derived Commands.
 */
class IInputCommand {
public:
	virtual ~IInputCommand() {}
	virtual void execute(entt::dispatcher&) const = 0;
};

/** 
 * \brief   The LeftCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Moves the player entity left by using Box2D's ApplyForce() 
 * 			functionality.
 */
class LeftCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The DownCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Moves the player entity down by using Box2D's ApplyForce() 
 * 			functionality.
 */
class DownCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The RightCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Moves the player entity right by using Box2D's ApplyForce() 
 * 			functionality.
 */
class RightCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The UpCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Moves the player entity up by using Box2D's ApplyForce() 
 * 			functionality.
 */
class UpCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The SelectedLeftCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Moves the player entity and all selected entities left by 
 * 			using Box2D's ApplyForce() functionality.
 */
class SelectedLeftCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The SelectedDownCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Moves the player entity and all selected entities down by 
 * 			using Box2D's ApplyForce() functionality.
 */
class SelectedDownCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The SelectedRightCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Moves the player entity and all selected entities right by 
 * 			using Box2D's ApplyForce() functionality.
 */
class SelectedRightCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The SelectedUpCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Moves the player entity and all selected entities up by 
 * 			using Box2D's ApplyForce() functionality.
 */
class SelectedUpCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The ToggleSelectModeCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Toggles 'Select Mode' - enabling stenciling of the player object
 * 			and dynamic sphere objects it contacts.
 */
class ToggleSelectModeCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

// -----------------------------------------------------------------------------
/** 
 * \brief   The NorthCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Logs a unique message. Only used for testing cursor movement input.
 */
class NorthCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The WestCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Logs a unique message. Only used for testing cursor movement input.
 */
class WestCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The SouthCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Logs a unique message. Only used for testing cursor movement input.
 */
class SouthCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The EastCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Logs a unique message. Only used for testing cursor movement input.
 */
class EastCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The NortheastCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Logs a unique message. Only used for testing cursor movement input.
 */
class NortheastCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The NorthwestCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Logs a unique message. Only used for testing cursor movement input.
 */
class NorthwestCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The SouthwestCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Logs a unique message. Only used for testing cursor movement input.
 */
class SouthwestCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The SoutheastCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Logs a unique message. Only used for testing cursor movement input.
 */
class SoutheastCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

// -----------------------------------------------------------------------------
/** 
 * \brief   The CameraUpCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Translates camera entities up.
 */
class CameraUpCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The CameraDownCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Translates camera entities down.
 */
class CameraDownCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The CameraLeftCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Translates camera entities left.
 */
class CameraLeftCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The CameraRightCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Translates camera entities right.
 */
class CameraRightCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The CameraForwardCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Translates camera entities forward.
 */
class CameraForwardCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The CameraBackwardCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Translates camera entities backward.
 */
class CameraBackwardCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The CameraZoomInCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Camera view zooms in (does not translate or rotate). Analogous 
 * 			to changing camera lens.
 */
class CameraZoomInCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The CameraZoomOutCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Camera view zooms out (does not translate or rotate). Analogous 
 * 			to changing camera lens.
 */
class CameraZoomOutCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The CameraPitchUpCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Rotates camera entities up.
 */
class CameraPitchUpCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The CameraPitchDownCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Rotates camera entities down.
 */
class CameraPitchDownCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The CameraYawLeftCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Rotates camera entities left.
 */
class CameraYawLeftCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

/** 
 * \brief   The CameraYawRightCommand class.
 * \details Derived from IInputCommand. Pointed to by InputInvoker class.
 * 			Rotates camera entities right.
 */
class CameraYawRightCommand : public IInputCommand {
public:
	void execute(entt::dispatcher&) const override;
};

#endif // CORE_INPUT_COMMANDER_H