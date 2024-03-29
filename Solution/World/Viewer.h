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
	void drawEnemy( );
	void drawDarkKnight( );
	void drawDarkMonk( );
	void drawUI( );
	void drawField( );
	void drawDebugMessage( );
	//CLEAR
	void drawClear( );
	//DEAD
	void drawGameover( );
};

