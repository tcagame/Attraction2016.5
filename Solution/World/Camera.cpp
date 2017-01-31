#include "Camera.h"
#include "App.h"
#include "Ground.h"
#include "Drawer.h"
#include "Application.h"

const Vector START_CAMERA_POS = Vector( 60, 0, 500 );
const Vector START_TARGET_POS = Vector( 0, 0, 0 );

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
}


Camera::~Camera( ) {
}

void Camera::initialize( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->setCameraUp( Vector( 0, 0, 1 ) );
}

void Camera::update( ) {
	/*Vector vec = _pos - _target;
	vec.z = 0;

	if( vec.getLength( ) > MAX_LENGTH ) {
		vec = vec.normalize( ) * MAX_LENGTH;
	}
	if ( vec.getLength( ) < MIN_LENGTH ) {
		vec = vec.normalize( ) * MIN_LENGTH;
	}
	vec.z = 15;

	// _camera_posを変更
	_pos = _target + vec;*/
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
	double length = ( _target - pos ).getLength( );
	return length < SCREEN_LENGTH;
}

Vector Camera::getConvertDeviceVec( const Vector& vec ) {

	//カメラの向きを求めている
	Vector camera_dir = _target - _pos;
	camera_dir.z = 0;
	//デバイスの方角とまっすぐ進む向きとの差角を求める
	//差角分回転する回転行列をつくる
	double angle = vec.angle( Vector( 0, -1, 0 ) );
	Vector axis = vec.cross( Vector( 0, -1, 0 ) );
	Matrix mat = Matrix::makeTransformRotation( axis, angle );

	//差角分回転させる
	Vector move_dir = mat.multiply( camera_dir );
	return move_dir.normalize( );
}