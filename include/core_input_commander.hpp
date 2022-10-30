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
	void execute() const override {
		std::cout << "Move left" << std::endl;
	}
};

class DownCommand : public IInputCommand {
public:
	void execute() const override {
		std::cout << "Move down" << std::endl;
	}
};

class RightCommand : public IInputCommand {
public:
	void execute() const override {
		std::cout << "Move right" << std::endl;
	}
};

class UpCommand : public IInputCommand {
public:
	void execute() const override {
		std::cout << "Move up" << std::endl;
	}
};

#endif // CORE_INPUT_COMMANDER_HPP