#pragma once
#include "Enemy.h"
class EnemyGoblin : public Enemy {
public:
	EnemyGoblin( );
	virtual ~EnemyGoblin( );
private:
	virtual void animationUpdate( );
};

