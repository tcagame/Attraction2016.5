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
	walk( controll );
	attack( controll );

	if ( getStatus( ).hp <= 0 ) {
		_player_state = PLAYER_STATE_DEAD;
	}
	animationUpdate( );
	_before_state = _player_state;
}

void Player::walk( const CONTROLL& controll ) {
	if ( _before_state != PLAYER_STATE_ATTACK &&
		 _before_state != PLAYER_STATE_DEAD ) {

		if ( controll.move.getLength( ) > 0.0 ) {
			//進める場合移動
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

	//攻撃に入る瞬間
	bool in_attack = controll.action == CONTROLL::ATTACK && _before_state != PLAYER_STATE_ATTACK;
	if ( in_attack ) {
		_player_state = PLAYER_STATE_ATTACK;
	}
	//攻撃中
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

	unsigned char button = data.player[ _player_id ].button;
	if ( button & BUTTON_A ) {
		controll.action = CONTROLL::ATTACK;
	} else {
		controll.action = CONTROLL::NONE;
	}
	return controll;
}

void Player::animationUpdate( ) {
	AnimationPtr animation = getAnimation( );
	if ( _player_state == PLAYER_STATE_DEAD && animation->isEndAnimation( ) ) {
		dead( );
		return;
	}

	if ( _player_state == PLAYER_STATE_WAIT ) {
		if ( animation->getMotion( ) != Animation::MOTION_PLAYER_WAIT ) {
			setAnimation( AnimationPtr( new Animation( Animation::MOTION_PLAYER_WAIT ) ) );
		} else {
			if( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_WALK ) {
		if ( animation->getMotion( ) != Animation::MOTION_PLAYER_WALK ) {
			setAnimation( AnimationPtr( new Animation( Animation::MOTION_PLAYER_WALK ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_ATTACK ) {
		if ( animation->getMotion( ) != Animation::MOTION_PLAYER_ATTACK_FIRE ) {
			setAnimation( AnimationPtr( new Animation( Animation::MOTION_PLAYER_ATTACK_FIRE ) ) );
			animation->setAnimationTime( 20 );
		}
	}
	if ( _player_state == PLAYER_STATE_DEAD ) {
		if ( animation->getMotion( ) != Animation::MOTION_PLAYER_DEAD ) {
			setAnimation( AnimationPtr( new Animation( Animation::MOTION_PLAYER_DEAD ) ) );
		}
	}
}