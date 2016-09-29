#pragma once
#include "Task.h"
#include <string>

PTR( Viewer );
PTR( TableDrawer );

class Viewer : public Task {
public:
	static ViewerPtr getTask( );
	static std::string getTag( ){ return "VIEWER"; }
public:
	Viewer( );
	virtual ~Viewer( );
public:
	void initialize( );
	void update( );
private:
	void makeTableLog( );
	void makeTableCommand( );
	void makeTableConnect( );

	void drawLog( );
	void drawCommand( );
	void drawConnect( );
	void drawStatus( );
private:
	TableDrawerPtr _log;
	TableDrawerPtr _command;
	TableDrawerPtr _connect;
};