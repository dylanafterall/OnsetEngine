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

#include <iostream>

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// COMMAND PATTERN : ICommand
// _____________________________________________________________________________
// -----------------------------------------------------------------------------
class IInputCommand {
public:
	virtual ~IInputCommand() {}
	virtual void execute() const = 0;
};

// _____________________________________________________________________________
// -----------------------------------------------------------------------------
// COMMAND PATTERN : Derived Commands
// _____________________________________________________________________________
// -----------------------------------------------------------------------------
class LeftCommand : public IInputCommand {
public:
	void execute() const override;
};

class DownCommand : public IInputCommand {
public:
	void execute() const override;
};

class RightCommand : public IInputCommand {
public:
	void execute() const override;
};

class UpCommand : public IInputCommand {
public:
	void execute() const override;
};

#endif // CORE_INPUT_COMMANDER_HPP