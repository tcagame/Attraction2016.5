#include "Player.h"
#include "App.h"
#include "Animation.h"
#include "Camera.h"
#include "Field.h"
#include "mathmatics.h"
#include "GroundModel.h"
#include "Ground.h"
#include "Client.h"
#include "BulletFire.h"
#include "Weapon.h"

Player::Player( unsigned char player_id, Character::STATUS status ) :
Character( status ),
_player_id( player_id ) {
}

Player::~Player( ) {
}

void Player::otherUpdate( ) {
	_player_state = PLAYER_STATE_WAIT;
	
	CONTROLL controll = makeControll( );
	walk( controll );
	attack( controll );

	if ( getStatus( ).hp <= 0 ) {
		_player_state = PLAYER_STATE_DEAD;
	}
	_before_state = _player_state;
}

void Player::walk( const CONTROLL& controll ) {
	if ( _before_state != PLAYER_STATE_ATTACK &&
		 _before_state != PLAYER_STATE_DEAD ) {

		if ( controll.move.getLength( ) > 0.0 ) {
			//�i�߂�ꍇ�ړ�
			move( controll.move );
			_player_state = PLAYER_STATE_WALK;
		}
	}
}

void Player::attack( const CONTROLL& controll ) {
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	BulletPtr bullet;
	AnimationPtr animation = getAnimation( );
	int power = getStatus(  ).power;

	//�U���ɓ���u��
	bool in_attack = controll.action == CONTROLL::ATTACK && _before_state != PLAYER_STATE_ATTACK;
	if ( in_attack ) {
		_player_state = PLAYER_STATE_ATTACK;
	}
	//�U����
	if ( animation->getMotion( ) == Animation::MOTION_PLAYER_ATTACK_FIRE ) {
		if ( !animation->isEndAnimation( ) ) {
			if ( animation->getAnimTime( ) == 30.0 ) {
				bullet = BulletFirePtr( new BulletFire( getPos( ), getDir( ), power ) );
				weapon->add( bullet );
				_player_state = PLAYER_STATE_ATTACK;
			}
		}
	}
}

Player::CONTROLL Player::makeControll( ) {
	CONTROLL controll;
	// �l�b�g���瓮����
	ClientPtr client = Client::getTask( );
	CLIENTDATA data = client->getClientData( );

	Vector vec;
	vec.x = data.player[ _player_id ].x;
	vec.y = data.player[ _player_id ].y;
	CameraPtr camera = Camera::getTask( );
	Vector move_vec = camera->getConvertDeviceVec( vec );
	Character::STATUS status = getStatus( );
	move_vec = move_vec.normalize( ) * status.speed;//�v���C���[�̐i�s�x�N�g��
	controll.move = move_vec;

	unsigned char button = data.player[ _player_id ].button;
	if ( button & BUTTON_A ) {
		controll.action = CONTROLL::ATTACK;
	} else {
		controll.action = CONTROLL::NONE;
	}
	return controll;
}