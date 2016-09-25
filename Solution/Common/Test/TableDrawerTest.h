#pragma once
#include "Task.h"
#include <string>

PTR( TableDrawerTest );
PTR( TableDrawer );

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
	TableDrawerPtr _td_test;
};

