#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>
#include "Network.h"

PTR( AppController );

class AppController : public Task {
public:
	static AppControllerPtr getTask( );
	static std::string getTag( ){ return "APPCONTROLLER"; }
public:
	AppController( );
	virtual ~AppController( );
private:
	void updateTitle( );
	void updatePlay( CLIENTDATA data );
public:
	void initialize( );
	void update( );
	void finalize( );
private:
	unsigned char _scene;
};

