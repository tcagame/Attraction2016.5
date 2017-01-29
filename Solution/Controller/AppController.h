#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( AppController );

class AppController : public Task {
public:
	static AppControllerPtr getTask( );
	static std::string getTag( ){ return "APPCONTROLLER"; }
public:
	AppController( );
	virtual ~AppController( );
public:
	void initialize( );
	void update( );
	void finalize( );
};

