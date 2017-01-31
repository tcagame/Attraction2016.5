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
	void initialize( );
	void update( );
	GroundPtr getGround( ) const;
	GroundModelPtr getGroundModel( ) const;
	FieldPtr getField( ) const;
	WeaponPtr getWeapon( ) const;
	CohortPtr getCohort( ) const;

	PlayerPtr getPlayer( ) const;
	PlayerPtr getPlayerTarget( const Vector& pos );
	unsigned char getScene( ) const;
	int convertCSVtoMap( int type );
private:
	static const int MAX_MAP_DATA_NUM = 12;
private:
	void reset( );
	void changeScene( );
	void initSceneTitle( );
	void initScenePlay( );
	void initSceneClear( );
	void initSceneGameover( );
	void updateSceneTitle( );
	void updateScenePlay( );
	void updateSceneClear( );
	void updateSceneGameover( );
private:
	GroundPtr _ground;
	GroundModelPtr _ground_model;
	FieldPtr _field;
	CohortPtr _cohort;
	WeaponPtr _weapon;
	PlayerPtr _player;
	unsigned char _scene;
	std::array< int, MAX_MAP_DATA_NUM > _map_convert;
};