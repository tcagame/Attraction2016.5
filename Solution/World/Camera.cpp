#include "Camera.h"
#include "App.h"
#include "Ground.h"
#include "Drawer.h"
#include "Application.h"
#include "Field.h"

const Vector START_CAMERA_POS = Vector( 100, 15, 4 );
const Vector START_TARGET_POS = Vector( 0, 15, 0 );

const Vector BATTRL_CAMERA_POS = Vector( 230, 30, 20 );
const Vector BATTRL_TARGET_POS = Vector( 0, 30, 0 );

const Vector ENEMY_ENTRY_CAMERA_POS = Vector( 20, 15, 43 );
const Vector ENEMY_ENTRY_TARGET_POS = Vector( 5, 15, 0 );
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

Camera::CAMERA_VIEW_PHASE Camera::checkPhase( ) {
	AppPtr app = App::getTask( );
	FieldPtr field = app->getField( );

	if ( field->isExistenceEnemy( ) ) {
		return CAMERA_VIEW_PHASE_ENEMY;
	}
	return CAMERA_VIEW_PHASE_NORMAL;
}


void Camera::updatePhaseEnemy( ) {
	_pos = ENEMY_ENTRY_CAMERA_POS;
	_target = ENEMY_ENTRY_TARGET_POS;
}

void Camera::updatePhaseBattle( ) {
	AppPtr app = App::getTask( );
}

void Camera::updatePhaseNormal( ) {
	_pos = START_CAMERA_POS;
	_target = START_TARGET_POS;
}