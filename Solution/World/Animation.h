#pragma once
#include "smart_ptr.h"

PTR( Animation );

class Animation {
public:
enum MV1 {
	MV1_PLAYER,
	MV1_PLAYER_WAIT,
	MV1_PLAYER_WALK,
	MV1_PLAYER_ATTACK_BEGIN,
	MV1_PLAYER_ATTACK_LOOP,
	MV1_PLAYER_ATTACK_END,
	MV1_PLAYER_DEAD,
	MV1_GOBLIN_WAIT,
	MV1_GOBLIN_WALK,
	MV1_GOBLIN_ATTACK,
	MV1_GOBLIN_DAMAGE,
	MV1_GOBLIN_DEAD,
	MV1_MINOTAUR,
	MV1_MINOTAUR_WAIT,
	MV1_MINOTAUR_WALK,
	MV1_MINOTAUR_SMASH,
	MV1_MINOTAUR_DAMAGE,
	MV1_MINOTAUR_DEAD,
	MV1_BACK_GROUND,
	MV1_MAX
};
public:
	Animation( MV1 mesh = MV1_MAX, MV1 motion = MV1_MAX, double anim_speed = 1.0 );
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
	MV1 _motion;
	MV1 _mesh;
};

