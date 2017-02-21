#include "Camera.h"
#include "App.h"
#include "Ground.h"
#include "Drawer.h"
#include "Application.h"

const Vector START_CAMERA_POS = Vector( 150, 15, 30 );
const Vector START_TARGET_POS = Vector( 0, 15, 0 );

const Vector BATTRL_CAMERA_POS = Vector( 230, 30, 20 );
const Vector BATTRL_TARGET_POS = Vector( 0, 30, 0 );

const Vector ENEMY_ENTRY_CAMERA_POS = Vector(  );
const Vector ENEMY_ENTRY_TARGET_POS = Vector(  );
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
	switch ( _camera_view_phase ) {
	case CAMERA_VIEW_PHASE_TITLE:
		break;
	case CAMERA_VIEW_PHASE_ENEMY:
		break;
	case CAMERA_VIEW_PHASE_BATTLE:
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

	//�J�����̌��������߂Ă���
	Vector camera_dir = _target - _pos;
	camera_dir.z = 0;
	//�f�o�C�X�̕��p�Ƃ܂������i�ތ����Ƃ̍��p�����߂�
	//���p����]�����]�s�������
	double angle = vec.angle( Vector( 0, -1, 0 ) );
	Vector axis = vec.cross( Vector( 0, -1, 0 ) );
	Matrix mat = Matrix::makeTransformRotation( axis, angle );

	//���p����]������
	Vector move_dir = mat.multiply( camera_dir );
	return move_dir.normalize( );
}