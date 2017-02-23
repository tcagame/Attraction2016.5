#pragma once
#include "smart_ptr.h"
#include <array>

PTR( Field );
PTR( Object );

class Field {
public:
	Field( );
	virtual ~Field( );
public:
	static const int MAX_MAP_CHIP_NUM = 10000;
public:
	void initialize( );
	void reset( );
	void setTarget( int x, int y, ObjectPtr object );
	void delTarget( int x, int y, ObjectPtr object );
	ObjectPtr getTarget( int x, int y );
	ObjectPtr getTarget( int idx );
	bool isExistenceEnemy( );
private:
	int getIndexTargetBoard( int x, int y );
private:
	std::array< ObjectWeakPtr, MAX_MAP_CHIP_NUM > _target_board;
};

