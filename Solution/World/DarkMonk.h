#pragma once
#include "Enemy.h"
#include "smart_ptr.h"

PTR( DarkMonk );
class DarkMonk : public Enemy {
public:
	DarkMonk( ENEMY_TYPE type, double range, Character::STATUS status );
	virtual ~DarkMonk( );
private:
	virtual void animationUpdate( );
};

