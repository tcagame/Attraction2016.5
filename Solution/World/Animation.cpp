#include "Animation.h"
#include "Drawer.h"

Animation::Animation( MV1 mesh, MV1 motion, double anim_speed ) {
	DrawerPtr drawer = Drawer::getTask( );//描画ではなくアニメ―ションタイムの取得用
	_mesh = mesh;
	_motion = motion;
	_anim_time = 0;
	_anim_speed = anim_speed;
	_max_anim_time = drawer->getEndAnimTime( _motion );
}

Animation::~Animation( ) {
}

void Animation::update( ) {
	_anim_time += _anim_speed;
}

bool Animation::isEndAnimation( ) const {
	bool result = false;
	if ( _anim_time > _max_anim_time ) {
		result = true;
	}
	return result;
}

int Animation::getMotion( ) const {
	return _motion;
}

int Animation::getMesh( ) const {
	return _mesh;
}

double Animation::getAnimTime( ) const {
	return _anim_time;
}

double Animation::getEndAnimTime( ) const {
	return _max_anim_time;
}

void Animation::setAnimationTime( double anim_time ) {
	_anim_time = anim_time;
}