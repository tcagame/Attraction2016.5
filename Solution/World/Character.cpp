#include "Character.h"
#include "Player.h"
#include "App.h"
#include "Field.h"
#include "GroundModel.h"
#include "Camera.h"
#include "Animation.h"

const Vector START_DIR = Vector( 1, -1, 0 );

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
	if ( !camera->isInScreen( getPos( ) ) ) {
		return;
	}
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
	FieldPtr field = app->getField( );
	
	field->delTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );

	Vector store = _pos;
	Vector move_pos = _pos + vec;
	ObjectPtr object = field->getTarget( ( int )move_pos.x, ( int )move_pos.y );
	if ( !object ) {
		GroundModelPtr ground_model = app->getGroundModel( );
		bool is_ground = ground_model->isCollisionGround( move_pos );//’n–Ê‚Æ‚Ì”»’è
		if ( is_ground ) {
			_pos = move_pos;
		}
	}

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

std::string Character::getCharacterName( ) const {
	return _character_name;
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