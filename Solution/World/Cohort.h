#pragma once

#include "smart_ptr.h"
#include "mathmatics.h"
#include <string>
#include <array>
#include <vector>

PTR( Cohort );
PTR( Enemy );
PTR( DarkKnight );
PTR( DarkMonk );
PTR( Character );

class Cohort {
public:
	struct ENEMY_DATA {
		double x;
		double y;
		std::string name;
	};
	typedef std::vector< ENEMY_DATA > BLOCK_ENEMY_DATA;//ブロックごとのエネミー配置データ
public:
	static const int MAX_NUM = 500;	
	static const int MAX_BLOCK_NUM = 10000;
public:
	Cohort( );
	virtual ~Cohort();
public:
	void init( );
	void reset( );
	virtual void update( );
	DarkKnightPtr getDarkKnight( );
	DarkMonkPtr getDarkMonk( );

	EnemyConstPtr getEnemy( int index ) const;
	EnemyPtr getEnemy( int index );
	void add( int type );
	int getMaxNum( );
	void loadBlockEnemyData( int idx, std::string filepath );
private:
	void putBlockEnemy( int idx );
	void putEnemy( const Vector& pos );
private:
	std::array< EnemyPtr, MAX_NUM > _enemy;
	DarkKnightPtr _dark_knight;
	DarkMonkPtr _dark_monk;

	std::array< BLOCK_ENEMY_DATA, MAX_BLOCK_NUM > _enemy_data;
	int _enemy_max;
};

