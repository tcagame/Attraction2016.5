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
	int getDirX( int i ) const;
	int getDirY( int i ) const;
	unsigned int getButton( int i ) const;
	int getDeviceNum( );//デバイスの個数を渡す
public:
	void resetup( );
private:
	CLIENTDATA _data;
	int _device_num;
};