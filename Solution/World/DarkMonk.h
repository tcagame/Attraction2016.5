#pragma once
#include "Enemy.h"
#include "smart_ptr.h"

PTR( DarkMonk );
class DarkMonk : public Enemy {
public:
	DarkMonk( ENEMY_TYPE type, double range, Character::STATUS status );
	virtual ~DarkMonk( );
public:
	bool isDead( );
	void resetDeadFlag( );
	
private:
	virtual void animationUpdate( );
private:
	bool _is_dead;
};

