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

#include "component_camera.h"
#include "component_player.h"
#include "component_body_circle.h"
#include "component_body_polygon.h"
#include "core_log_macros.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "entt/entt.hpp"
#include "box2d/box2d.h"

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// COMMAND PATTERN : ICommand
// _____________________________________________________________________________
// -----------------------------------------------------------------------------
class IInputCommand {
public:
	virtual ~IInputCommand() {}
	virtual void execute(entt::registry&) const = 0;
};

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// COMMAND PATTERN : Derived Commands
// _____________________________________________________________________________
// -----------------------------------------------------------------------------
class LeftCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class DownCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class RightCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class UpCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

// -----------------------------------------------------------------------------
class NorthCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class WestCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class SouthCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class EastCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class NortheastCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class NorthwestCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class SouthwestCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class SoutheastCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

// -----------------------------------------------------------------------------
class CameraUpCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class CameraDownCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class CameraLeftCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class CameraRightCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class CameraForwardCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class CameraBackwardCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class CameraZoomInCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class CameraZoomOutCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class CameraPitchUpCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class CameraPitchDownCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class CameraYawLeftCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

class CameraYawRightCommand : public IInputCommand {
public:
	void execute(entt::registry&) const override;
};

#endif // CORE_INPUT_COMMANDER_H