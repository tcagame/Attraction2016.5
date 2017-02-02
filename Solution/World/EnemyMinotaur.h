#pragma once
#include "Enemy.h"
class EnemyMinotaur : public Enemy {
public:
	EnemyMinotaur( );
	virtual ~EnemyMinotaur( );
private:
	virtual void animationUpdate( );
};

