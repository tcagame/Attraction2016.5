#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( Viewer );

class Viewer : public Task {
public:
	static ViewerPtr getTask( );
	static std::string getTag( ){ return "VIEWER"; }
public:
	Viewer( );
	virtual ~Viewer( );
	void initialize( );
public:
	void update( );
	//READY
	void drawTitle( );
	//PLAY
	void drawGroundModel( );
	void drawBackGround( );
	void drawPlayer( );
	void drawBullet( );
	void updateCamera( );
	//CLEAR
	//DEAD
};

