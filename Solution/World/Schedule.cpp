#include "Schedule.h"
#include "Cohort.h"
#include <string>
static const int GENERATE_COUNT = 100;
const char* FILENAME = "../Resource/Schedule/schedule.txt";

Schedule::Schedule( ) {
	FILE* fp;
	if ( fopen_s( &fp, FILENAME, "r" ) != 0 ) {
		return;
	}
	char str[ 1024 ];
	while ( fgets( str, 1024, fp ) != NULL ) {
		std::string string = str;
		string = string.substr( 0, string.size( ) -1 );
		if ( string == "NONE" ) {
			_enemies.push_back( Enemy::ENEMY_TYPE_NONE );
		}
		if ( string == "GOBLIN" ){
			_enemies.push_back( Enemy::ENEMY_TYPE_GOBLIN );
		}
		if ( string == "MINOTAUR" ){
			_enemies.push_back( Enemy::ENEMY_TYPE_MINOTAUR );
		}
		if ( string == "DARKKNIGHT" ){
			_enemies.push_back( Enemy::ENEMY_TYPE_DARKKIGHT );
		}
		if ( string == "DARKMONK" ){
			_enemies.push_back( Enemy::ENEMY_TYPE_DARKMONK );
		}
	}

	fclose( fp );

	_count = 0;
}


Schedule::~Schedule( ) {
}

void Schedule::update( CohortPtr cohort ) {
	_count++; 
	if ( _count % GENERATE_COUNT != 0 ) {
		return;
	}
	int idx = ( _count / GENERATE_COUNT ) - 1;
	if ( idx  >= ( int )_enemies.size( ) ) {
		return;
	}
	cohort->add( _enemies[ idx ] );
}
