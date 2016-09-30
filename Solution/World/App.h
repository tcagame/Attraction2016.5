#pragma once
#include "Task.h"
#include <string>
#include <array>

PTR( App );
PTR( Ground );
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
	void setState( STATE state );
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
	STATE _state;
	int _push_reset_count;
	int _push_start_count;
	std::array< int, MAX_MAP_DATA_NUM > _map_convert;
};