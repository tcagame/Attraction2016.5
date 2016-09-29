#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( Character );

class Character {
public:
	struct STATUS {
		
	};
public:
	Character( );
	virtual ~Character( );
public:
	void update( );
	Vector getPos( ) const;
	Vector getDir( ) const;
private:
	Vector _pos;
	Vector _dir;
};