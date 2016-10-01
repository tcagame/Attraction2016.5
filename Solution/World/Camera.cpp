#include "Camera.h"
#include "App.h"
#include "Ground.h"
#include "Application.h"

const Vector START_CAMERA_POS = Vector( 10, 5, 20 );
const Vector START_TARGET_POS = Vector( 5, 10, 0 );

const double SCREEN_LENGTH = 800.0;

const int MAX_LENGTH = 40;
const int MIN_LENGTH = 35;

CameraPtr Camera::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< Camera >( fw->getTask( Camera::getTag( ) ) );
}

Camera::Camera( ) :
_pos( START_CAMERA_POS ),
_target( START_TARGET_POS ) {
	ApplicationPtr fw = Application::getInstance( );
	fw->setCameraUp( Vector( 0, 0, 1 ) );
}


Camera::~Camera( ) {
}

void Camera::update( ) {
Vector vec = _pos - _target;
	vec.z = 0;

	if( vec.getLength( ) > MAX_LENGTH) {
		vec = vec.normalize( ) * MAX_LENGTH;
	}
	if ( vec.getLength( ) < MIN_LENGTH ) {
		vec = vec.normalize( ) * MIN_LENGTH;
	}
	vec.z = 15;

	// _camera_pos‚ð•ÏX
	_pos = _target + vec;
}

Vector Camera::getPos( ) const {
	return _pos;
}

Vector Camera::getTarget( ) const {
	return _target;
}

void Camera::setTarget( Vector target ) {
	_target = target;
}

Vector Camera::getStartPos( ) const {
	return START_CAMERA_POS;
}

Vector Camera::getStartTargetPos( ) const {
	return START_TARGET_POS;
}

bool Camera::isInScreen( Vector pos ) {
	double length = ( _target - pos ).getLength2( );
	return length < SCREEN_LENGTH;
}

Vector Camera::getConvertDeviceVec( const Vector& vec ) {

	//ƒJƒƒ‰‚ÌŒü‚«‚ð‹‚ß‚Ä‚¢‚é
	Vector camera_dir = _target - _pos;
	camera_dir.z = 0;
	//ƒfƒoƒCƒX‚Ì•ûŠp‚Æ‚Ü‚Á‚·‚®i‚ÞŒü‚«‚Æ‚Ì·Šp‚ð‹‚ß‚é
	//·Šp•ª‰ñ“]‚·‚é‰ñ“]s—ñ‚ð‚Â‚­‚é
	double angle = vec.angle( Vector( 0, -1, 0 ) );
	Vector axis = vec.cross( Vector( 0, -1, 0 ) );
	Matrix mat = Matrix::makeTransformRotation( axis, angle );

	//·Šp•ª‰ñ“]‚³‚¹‚é
	Vector move_dir = mat.multiply( camera_dir );
	return move_dir.normalize( );
}