#pragma once
#include "Task.h"
#include <string>

PTR( TableDrawerTest );
PTR( TableDrawer );
PTR( Status );

class TableDrawerTest : public Task {
public:
	static std::string getTag( ) { return "TABLEDRAWERTEST"; }
	static TableDrawerTestPtr getTask( );
public:
	TableDrawerTest();
	virtual ~TableDrawerTest();
public:
	void update( );
private:
	StatusPtr _status;
	TableDrawerPtr _td_test;
};

