#pragma once
#include "Enemy.h"
class EnemyGoblin : public Enemy {
public:
	EnemyGoblin( ENEMY_TYPE type, double range, Character::STATUS status );
	virtual ~EnemyGoblin( );
private:
	virtual void animationUpdate( );
};

