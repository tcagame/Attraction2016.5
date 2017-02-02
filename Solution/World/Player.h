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
		PLAYER_STATE_DAMAGE,
		PLAYER_STATE_DEAD,
	};
protected:
	struct CONTROLL {
		Vector move;
		enum ACTION {
			NONE,
			ATTACK
		} action;
	};
private:
	enum ATTACK {
		ATTACK_NONE,
		ATTACK_BRGIN,
		ATTACK_LOOP,
		ATTACK_END
	};
public:
	Player( unsigned char player_id, Character::STATUS status );
	virtual ~Player( );
public:
	void otherUpdate( );
	int getTotaldamage( );
private:
	void animationUpdate( );
	CONTROLL makeControll( );
	void swicthState( CONTROLL controll );
	void walk( CONTROLL controll );
	void attack( CONTROLL controll );
	void onAttack( );
private:
	const int _player_id;
	PLAYER_STATE _player_state;
	PLAYER_STATE _before_state;

	ATTACK _attack;
	ATTACK _before_attack;

	int _stack_damage;
	bool _attack_loop;
	bool _attack_end;
	bool _is_damage;
};
