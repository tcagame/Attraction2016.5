#pragma once
#include "Task.h"
#include "Network.h"
#include "smart_ptr.h"
#include <string>

PTR( Status );
PTR( TableDrawer );

class Status : public Task {
public:
	static std::string getTag( ) { return "STATUS"; }
	static StatusPtr getTask( );
public:
	Status( );
	virtual ~Status( );
public:
	void update( );
	void draw( );
	void setInput( CLIENTDATA data );
private:
	std::string getButtonBinary( unsigned char button_key );
private:
	TableDrawerPtr _td;
	CLIENTDATA _data;
};

