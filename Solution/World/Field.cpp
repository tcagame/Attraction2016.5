#include "Field.h"
#include "Ground.h"
#include "App.h"

Field::Field( ) {
	initialize( );
}


Field::~Field( ) {

}

void Field::reset( ) {
	initialize( );
}

void Field::initialize(  ) {
	for ( int i = 0; i < MAX_MAP_CHIP_NUM; i++ ) {
		_target_board[ i ].reset( );
	}
}

void Field::delTarget( int x, int y, ObjectPtr object ) {
	int idx = getIndexTargetBoard( x, y );
	ObjectPtr target = _target_board[ idx ].lock( );
	if ( target == object ) {
		_target_board[ idx ].reset( );
	}
}

void Field::setTarget(int x, int y, ObjectPtr object) {
	int idx = getIndexTargetBoard( x, y );
	_target_board[ idx ] = object;
}

ObjectPtr Field::getTarget( int x, int y ) {
	int idx = getIndexTargetBoard( x, y );
	return _target_board[ idx ].lock( );
}

int Field::getIndexTargetBoard( int x, int y ) {
	int ret = 0;
	int map_x = x; 
	int map_y = y;
	if ( map_x < 0 ) {
		map_x = 0;
	}
	if ( map_y < 0 ) {
		map_y = 0;
	}
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	int map_width = ground->getWidth( ) * 10;
	int map_height = ground->getHeight( ) * 10;
	ret = map_x + map_y * map_width ;
	return ret;
}