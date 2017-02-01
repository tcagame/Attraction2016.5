#pragma once
#include "Enemy.h"
#include "smart_ptr.h"

PTR( DarkKnight );

class DarkKnight : public Enemy{
public:
	DarkKnight( ENEMY_TYPE type, double range, Character::STATUS status );
	virtual ~DarkKnight();
private:
	virtual void animationUpdate( );
};



