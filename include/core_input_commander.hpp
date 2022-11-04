// -----------------------------------------------------------------------------
// Onset Engine
// https://github.com/dylanafterall/OnsetEngine.git
//
// core_input_commander.hpp
//	uses COMMANDER design pattern
//  contains code to execute for all input commands (via keyboard, mouse, etc)
// -----------------------------------------------------------------------------

#ifndef CORE_INPUT_COMMANDER_HPP
#define CORE_INPUT_COMMANDER_HPP

#include "component_camera.hpp"

#include "entt/entt.hpp"

#include <iostream>

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

#endif // CORE_INPUT_COMMANDER_HPP