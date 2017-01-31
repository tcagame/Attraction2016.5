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
	void makeTableScene( );
	void makeTableCommand( );
	void makeTableConnect( );

	void drawLog( );
	void drawScene( );
	void drawCommand( );
	void drawConnect( );
	void drawStatus( );
private:
	TableDrawerPtr _log;
	TableDrawerPtr _scene;
	TableDrawerPtr _command;
	TableDrawerPtr _connect;
};