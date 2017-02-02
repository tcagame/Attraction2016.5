#pragma once

#include "Enemy.h"
#include "smart_ptr.h"
#include <vector>

PTR( Schedule );
PTR( Cohort );

class Schedule {
public:
	Schedule();
	virtual ~Schedule();
public:
	void update( CohortPtr cohort );
private:
	std::vector< Enemy::ENEMY_TYPE > _enemies;
	int _count;
};

