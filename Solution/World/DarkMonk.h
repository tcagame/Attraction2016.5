#pragma once
#include "Enemy.h"
#include "smart_ptr.h"

PTR( DarkMonk );
class DarkMonk : public Enemy {
public:
	DarkMonk( );
	virtual ~DarkMonk( );
public:
	bool isDead( );
	void resetDeadFlag( );
	
private:
	virtual void animationUpdate( );
private:
	bool _is_dead;
};

