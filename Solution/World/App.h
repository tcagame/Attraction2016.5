#pragma once
#include "Task.h"
#include <string>
#include <array>
#include "mathmatics.h"
#include "Network.h"

PTR( App );
PTR( Ground );
PTR( Field );
PTR( Weapon );
PTR( Player );
PTR( Cohort );
PTR( GroundModel );

class App : public Task {
public:
	static std::string getTag( ) { return "APP"; }
	static AppPtr getTask( );
public:
	App( );
	virtual ~App( );
public:
	enum STATE {
		STATE_READY,
		STATE_PLAY,
		STATE_CLEAR,
		STATE_DEAD,
		STATE_MAX
	};
public:
	void initialize( );
	void update( );
	GroundPtr getGround( ) const;
	GroundModelPtr getGroundModel( ) const;
	FieldPtr getField( ) const;
	WeaponPtr getWeapon( ) const;
	CohortPtr getCohort( ) const;

	PlayerPtr getPlayer( unsigned char player_id ) const;
	void setState( STATE state );
	PlayerPtr getPlayerTarget( const Vector& pos );
	STATE getState( ) const;
	int getStartCount( ) const;
	int getStartCountMax( ) const;
	int convertCSVtoMap( int type );
	void loadToGround( );
private:
	static const int MAX_MAP_DATA_NUM = 12;
private:
	void reset( );
	void updateReset( );
	void updateStateReady( );
	void updateStatePlay( );
	void updateStateClear( );
	void updateStateDead( );
private:
	GroundPtr _ground;
	GroundModelPtr _ground_model;
	FieldPtr _field;
	CohortPtr _cohort;
	WeaponPtr _weapon;
	std::array< PlayerPtr, PLAYER_NUM > _player;
	STATE _state;
	int _push_reset_count;
	int _push_start_count;
	std::array< int, MAX_MAP_DATA_NUM > _map_convert;
};