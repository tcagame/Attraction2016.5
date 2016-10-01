#pragma once
#include "Character.h"
#include "smart_ptr.h"

PTR( Enemy );
PTR( Player );

class Enemy : public Character {
public:
	enum ENEMY_STATE {
		ENEMY_STATE_WAIT,
		ENEMY_STATE_WALK,
		ENEMY_STATE_ATTACK,
		ENEMY_STATE_DEAD,
	};
public:
	Enemy( Character::STATUS status );
	virtual ~Enemy( );
public:
	void otherUpdate( );
private:
	void searchTarget( );
	void switchStatus( );
	void moveToTarget( );
	void animationUpdate( );
	void onAttack( PlayerPtr player );
private:
	PlayerWeakPtr _target;
	ENEMY_STATE _state;
	ENEMY_STATE _before_state;
	bool _on_damage;
	int _before_hp;
};