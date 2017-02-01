#include "Character.h"
#include "Player.h"
#include "App.h"
#include "Field.h"
#include "GroundModel.h"
#include "Camera.h"
#include "Animation.h"

const Vector START_DIR = Vector( 0, 1, 0 );
const double CHARACTER_HEIGHT = 2.0;

Character::Character( Character::STATUS status ) :
_origin_status( status ) {
	_status = status;
	_expired = false;
	_max_hp = status.hp;
}

Character::~Character( ) {
	
}

void Character::update( ) {
	CameraPtr camera = Camera::getTask( );
	if ( !_expired ) {
		return;
	}
	/*if ( !camera->isInScreen( getPos( ) ) ) {
		return;
	}*/
	otherUpdate( );
	_animation->update( );
}


void Character::reset( ){
	_status = _origin_status;
	_expired = false;
	AppPtr app = App::getTask( );
	FieldPtr field = app->getField( );
	field->delTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
}

bool Character::move( const Vector& vec ) {
	if ( vec.getLength( ) > 0 ) {
		_dir = vec.normalize( );
	}
	AppPtr app = App::getTask( );
	GroundModelPtr ground_model = app->getGroundModel( );
	FieldPtr field = app->getField( );
	field->delTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
	Vector store = _pos;
	Vector move_pos = _pos + vec.normalize( ) * _status.speed;
	Vector head_pos = move_pos;
	Vector foot_pos = move_pos;
	head_pos.z += CHARACTER_HEIGHT / 2;
	foot_pos.z -= CHARACTER_HEIGHT / 2;
	Vector ground_pos;

	ObjectPtr object = field->getTarget( ( int )move_pos.x, ( int )move_pos.y );
	if ( !object ) {
		GroundModelPtr ground_model = app->getGroundModel( );
		ground_pos = ground_model->HitGroundPos( head_pos, foot_pos );//’n–Ê‚Æ‚Ì”»’è
		if ( ground_pos.y < -50 ) {
			ground_pos = _pos;
		}
	} else {
		ground_pos = _pos;
	}

	_pos = ground_pos;
	field->setTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );

	return
		( int )_pos.x == ( int )store.x &&
		( int )_pos.y == ( int )store.y;   
}

void Character::create( const Vector& pos ) {
	_pos = pos;
	_dir = START_DIR;
	_expired = true;
	AppPtr App = App::getTask( );
	FieldPtr field = App->getField( );
	field->setTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
}

void Character::damage( unsigned int power ) {
	_status.hp -= power;
	if ( _status.hp < 0 ) {
	_status.hp = 0;
	}
}

Vector Character::getPos( ) const {
	return _pos;
}

Vector Character::getDir( ) const {
	return _dir;
}

Character::STATUS Character::getStatus( ) const {
	return _status;
}

int Character::getMaxHp( ) const {
	return _max_hp;
}

AnimationPtr Character::getAnimation( ) const {
	return _animation;
}

bool Character::isExpired( ) const {
	return _expired;
}

void Character::dead( ) {
	if ( !_expired ) {
		return;
	}
	AppPtr app = App::getTask( );
	FieldPtr field = app->getField( );
	field->delTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
	_expired = false;
}

void Character::setAnimation( AnimationPtr animation ) {
	_animation = animation;
}

void Character::setDir( Vector dir ) {
	_dir = dir;
}

void Character::setHP( unsigned int hp ) {
	_status.hp = hp;
}