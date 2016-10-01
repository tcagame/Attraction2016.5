#pragma once

#include "smart_ptr.h"
#include <list>

PTR( Weapon );
PTR( Bullet );

class Weapon {
public:
	Weapon( );
	virtual ~Weapon( );
public:
	void reset( );
	void update( );
	void add( BulletPtr bullet );
private:
	std::list< BulletPtr> _list_bullet;
};

