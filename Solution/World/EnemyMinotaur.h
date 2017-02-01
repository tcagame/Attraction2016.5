#pragma once
#include "Enemy.h"
class EnemyMinotaur : public Enemy {
public:
	EnemyMinotaur( ENEMY_TYPE type, double range, Character::STATUS status );
	virtual ~EnemyMinotaur( );
private:
	virtual void animationUpdate( );
};

