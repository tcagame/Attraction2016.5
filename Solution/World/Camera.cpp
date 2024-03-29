#include "Camera.h"
#include "App.h"
#include "Ground.h"
#include "Drawer.h"
#include "Application.h"
#include "Field.h"

const Vector START_CAMERA_POS = Vector( 95, 15, 0 );
const Vector START_TARGET_POS = Vector( 0, 15, 10 );

const Vector BATTRL_CAMERA_POS = Vector( 230, 30, 20 );
const Vector BATTRL_TARGET_POS = Vector( 0, 30, 0 );

const Vector ENEMY_ENTRY_CAMERA_POS = Vector( 103, 15, 20 );
const Vector ENEMY_ENTRY_TARGET_POS = Vector( 40, 15, 0 );
const double SCREEN_LENGTH = 800.0;

const int MAX_LENGTH = 40;
const int MIN_LENGTH = 35;

const int CAMERA_MOVE_SPEED = 1;

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
	switch ( checkPhase( ) ) {
	case CAMERA_VIEW_PHASE_TITLE:
		break;
	case CAMERA_VIEW_PHASE_NORMAL:
		updatePhaseNormal( );
		break;
	case CAMERA_VIEW_PHASE_ENEMY:
		updatePhaseEnemy( );
		break;
	case CAMERA_VIEW_PHASE_BATTLE:
		//updatePhaseBattle( );
		break;
	default:
		break;
	}
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

Camera::CAMERA_VIEW_PHASE Camera::checkPhase( ) {
	AppPtr app = App::getTask( );
	FieldPtr field = app->getField( );

	if ( field->isExistenceEnemy( ) ) {
		return CAMERA_VIEW_PHASE_ENEMY;
	}
	return CAMERA_VIEW_PHASE_NORMAL;
}


void Camera::updatePhaseEnemy( ) {
	Vector vec_pos = ENEMY_ENTRY_CAMERA_POS - _pos;
	Vector vec_target = ENEMY_ENTRY_TARGET_POS - _target;
	if ( vec_pos.getLength( ) > CAMERA_MOVE_SPEED ) {
		vec_pos = vec_pos.normalize( ) * CAMERA_MOVE_SPEED;
		vec_target = vec_target.normalize( ) * CAMERA_MOVE_SPEED;
	}
	_pos += vec_pos;
	_target += vec_target;
}

void Camera::updatePhaseBattle( ) {
	AppPtr app = App::getTask( );
}

void Camera::updatePhaseNormal( ) {
	Vector vec_pos = START_CAMERA_POS - _pos;
	Vector vec_target = START_TARGET_POS - _target;
	if ( vec_pos.getLength( ) > CAMERA_MOVE_SPEED ) {
		vec_pos = vec_pos.normalize( ) * CAMERA_MOVE_SPEED;
		vec_target = vec_target.normalize( ) * CAMERA_MOVE_SPEED;
	}
	_pos += vec_pos;
	_target += vec_target;
}