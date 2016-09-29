#pragma once
#include "Task.h"
#include <string>

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
	void update( );
	GroundPtr getGround( ) const;
	GroundModelPtr getGroundModel( ) const;
	void setState( STATE state );
	STATE getState( ) const;
	int getStartCount( ) const;
	int getStartCountMax( ) const;
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
};