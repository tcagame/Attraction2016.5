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
	enum ENEMY_TYPE {
		ENEMY_TYPE_MINOTAUR,
	};
public:
	Enemy( ENEMY_TYPE type, double range, Character::STATUS status );
	virtual ~Enemy( );
public:
	ENEMY_TYPE getEnemyType( );
	void otherUpdate( );
protected:
	void setState( ENEMY_STATE state );
	ENEMY_STATE getState( );
	PlayerWeakPtr getTarget( );
	void onAttack( PlayerPtr player );
	bool isOnDamage( );
	void setAttack( bool is_attack );
private:
	void searchTarget( );
	void switchStatus( );
	void moveToTarget( );
	virtual void animationUpdate( ) = 0;
private:
	PlayerWeakPtr _target;
	ENEMY_STATE _state;
	ENEMY_STATE _before_state;
	ENEMY_TYPE _type;
	bool _is_attack;
	double _range;
	bool _on_damage;
	int _before_hp;
};