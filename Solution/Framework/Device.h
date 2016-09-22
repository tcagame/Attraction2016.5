#pragma once

#include "Task.h"
#include "Network.h"
#include <string>

PTR( Device );

class Device : public Task {
public:
	static std::string getTag( ) { return "DEVICE"; }
	static DevicePtr getTask( );
public:
	Device( );
	virtual ~Device( );
public:
	virtual void update( );
public:
	char getDirX( ) const;
	char getDirY( ) const;
	unsigned char getButton( ) const;
public:
	void resetup( );
private:
	struct DATA {
		char x;
		char y;
		unsigned char button;
	};
private:
	DATA _data;
};