#pragma once
#include "smart_ptr.h"

PTR( Animation );

class Animation {
public:
enum MOTION {
	MOTION_PLAYER,
	MOTION_PLAYER_WAIT,
	MOTION_PLAYER_WALK,
	MOTION_PLAYER_ATTACK_FIRE,
	MOTION_PLAYER_DEAD,
	MOTION_GOBLIN_WAIT,
	MOTION_GOBLIN_WALK,
	MOTION_GOBLIN_ATTACK,
	MOTION_GOBLIN_DAMAGE,
	MOTION_GOBLIN_DEAD,
	MOTION_MAX
};
public:
	Animation( MOTION mesh = MOTION_MAX, MOTION motion = MOTION_MAX, double anim_speed = 1.0 );
	virtual ~Animation( );
public:
	void update( );
	bool isEndAnimation( ) const;
	int getMotion( ) const;
	int getMesh( ) const;
	double getAnimTime( ) const;
	double getEndAnimTime( ) const;
	void setAnimationTime( double anim_time );
private:
	double _anim_time;
	double _max_anim_time;
	double _anim_speed;
	MOTION _motion;
	MOTION _mesh;
};

