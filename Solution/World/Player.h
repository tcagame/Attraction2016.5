#pragma once
#include "smart_ptr.h"

PTR( Player );

class Player {
public:
	Player( );
	virtual ~Player( );
public:
	void update( );
};

