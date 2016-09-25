#pragma once

#include "Task.h"
#include <string>
#include <vector>

PTR( Command );

class Command : public Task {
public:
	static std::string getTag( ) { return "COMMAND"; }
	static CommandPtr getTask( );
public:
	Command( );
	virtual ~Command( );
public:
	void update( );
public:
	std::string get( );
private:
	void execute( );
	void parser( );
private:
	std::string _command;
	std::vector< std::string > _word;
};