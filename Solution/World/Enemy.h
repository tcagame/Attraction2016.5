#pragma once
#include "Character.h"
#include "smart_ptr.h"

PTR( Enemy );
PTR( Player );

class Enemy : public Character {
public:
	enum ENEMY_MODE {
		ENEMY_MODE_ENTRY,
		ENEMY_MODE_COMBAT,
	};
	enum ENEMY_STATE {
		ENEMY_STATE_WAIT,
		ENEMY_STATE_WALK,
		ENEMY_STATE_ATTACK,
		ENEMY_STATE_DEAD,
	};
	enum ENEMY_TYPE {
		ENEMY_TYPE_MINOTAUR,
		ENEMY_TYPE_DARKKIGHT,
		ENEMY_TYPE_DARKMONK,
		ENEMY_TYPE_GOBLIN,
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
	void setMode( ENEMY_MODE mode );
	PlayerWeakPtr getTarget( );
	void onAttack( PlayerPtr player );
	bool isOnDamage( );
	void setAttack( bool is_attack );
private:
	void moveToEntryTarget( );
	void searchTarget( );
	void switchStatus( );
	void moveToTarget( );
	virtual void animationUpdate( ) = 0;
private:
	PlayerWeakPtr _target;
	ENEMY_STATE _state;
	ENEMY_STATE _before_state;
	ENEMY_MODE _enemy_mode;
	ENEMY_TYPE _type;
	bool _is_attack;
	double _range;
	bool _on_damage;
	int _before_hp;
	int _entry_target_num;
};