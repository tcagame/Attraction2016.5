#pragma once
#include "Enemy.h"
#include "smart_ptr.h"

PTR( DarkKnight );

class DarkKnight : public Enemy{
public:
	DarkKnight( );
	virtual ~DarkKnight();
public:
	bool isDead( );
	void resetDeadFlag( );
private:
	virtual void animationUpdate( );
private:
	bool _is_dead;
};



