#pragma once
#include "smart_ptr.h"
#include "Network.h"
#include <array>

PTR( Party );
PTR( Player );

class Party {
public:
	Party( );
	virtual ~Party( );
	void update( );
	PlayerPtr getPlayer( int id ) const;
	int getPlayerNum( ) const;
public:
	std::array< PlayerPtr, PLAYER_NUM > _party;
};
