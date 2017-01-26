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
	setAnimation( AnimationPtr( new Animation( Animation::MOTION_GOBLIN_WAIT ) ) );
}

Player::~Player( ) {
}

void Player::otherUpdate( ) {
	_player_state = PLAYER_STATE_WAIT;
	
	CONTROLL controll = makeControll( );

	animationUpdate( );
	_before_state = _player_state;
}

Player::CONTROLL Player::makeControll( ) {
	CONTROLL controll;
	// ネットから動かす
	ClientPtr client = Client::getTask( );
	CLIENTDATA data = client->getClientData( );

	Vector vec;
	vec.x = data.player[ _player_id ].x;
	vec.y = data.player[ _player_id ].y;
	CameraPtr camera = Camera::getTask( );
	Vector move_vec = camera->getConvertDeviceVec( vec );
	Character::STATUS status = getStatus( );
	move_vec = move_vec.normalize( ) * status.speed;//プレイヤーの進行ベクトル
	controll.move = move_vec;

	unsigned char action = data.player[ _player_id ].action;
	if ( action & ACTION_ATTACK ) {
		controll.action = CONTROLL::ATTACK;
	} else {
		controll.action = CONTROLL::NONE;
	}
	return controll;
}

void Player::animationUpdate( ) {
	AnimationPtr animation = getAnimation( );

	if ( _player_state == PLAYER_STATE_WAIT ) {
		if ( animation->getMotion( ) != Animation::MOTION_PLAYER_WAIT ) {
			setAnimation( AnimationPtr( new Animation( Animation::MOTION_PLAYER_WAIT ) ) );
		} else {
			if( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
}