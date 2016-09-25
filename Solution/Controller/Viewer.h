#pragma once
#include "Task.h"
#include <string>

PTR( Viewer );

class Viewer : public Task {
public:
	static ViewerPtr getTask( );
	static std::string getTag( ){ return "VIEWER"; }
public:
	Viewer( );
	virtual ~Viewer( );
public:
	void update( );
private:
	void drawLog( );
	void drawCommand( );
	void drawConnect( );
	void drawBox( int x1, int y1, int x2, int y2 );
};