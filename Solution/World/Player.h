#pragma once
#include "Character.h"
#include "smart_ptr.h"

PTR( Player );

class Player : public Character {
public:
	enum PLAYER_STATE {
		PLAYER_STATE_WAIT,
		PLAYER_STATE_WALK,
		PLAYER_STATE_ATTACK,
		PLAYER_STATE_DEAD,
	};
public:
	Player( unsigned char player_id, Character::STATUS status );
	virtual ~Player( );
public:
	void otherUpdate( );
protected:
	struct CONTROLL {
		Vector move;
		enum ACTION {
			NONE,
			ATTACK,
		} action;
	};
private:
	void attack( const CONTROLL& controll );
	void walk( const CONTROLL& controll );
	CONTROLL makeControll( );
private:
	const int _player_id;
	PLAYER_STATE _player_state;
	PLAYER_STATE _before_state;
};
