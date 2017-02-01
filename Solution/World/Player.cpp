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

const int MOVE_SPEED = 1;
const int ATTACK_TIME = 1;

const Vector BULLET_OFFSET = Vector( 0.0, 0.0, 1.7 );

Player::Player( unsigned char player_id, Character::STATUS status ) :
Character( status ),
_player_id( player_id ) {
	setAnimation( AnimationPtr( new Animation( Animation::MV1_PLAYER_WAIT ) ) );
	_attack_loop = false;
	_attack_end = true;
}

Player::~Player( ) {
}

void Player::otherUpdate( ) {
	_player_state = PLAYER_STATE_WAIT;
	_attack = ATTACK_NONE;
	
	CONTROLL controll = makeControll( );

	swicthState( controll );
	walk( controll );
	attack( controll );
	animationUpdate( );
	_before_state = _player_state;
	_before_attack = _attack;
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

	unsigned char action = data.player[ _player_id ].button;
	if ( action & BUTTON_A ) {
		controll.action = CONTROLL::ATTACK;
	} else {
		controll.action = CONTROLL::NONE;
	}
	return controll;
}

void Player::animationUpdate( ) {
	AnimationPtr animation = getAnimation( );
	if ( animation->getMotion( ) == Animation::MV1_PLAYER_ATTACK_END && animation->isEndAnimation( ) ) {
		_attack_end = true;
	}

	if ( _player_state == PLAYER_STATE_WAIT && _attack_end ) {
		if ( animation->getMotion( ) != Animation::MV1_PLAYER_WAIT ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_PLAYER, Animation::MV1_PLAYER_WAIT ) ) );
		} else {
			if( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _player_state == PLAYER_STATE_WALK ) {
		if ( animation->getMotion( ) != Animation::MV1_PLAYER_WALK ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_PLAYER, Animation::MV1_PLAYER_WALK ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}

	if ( _player_state == PLAYER_STATE_ATTACK || _before_state == PLAYER_STATE_ATTACK ) {
		switch( _attack ) {
			case ATTACK_BRGIN:
				if ( animation->getMotion( ) != Animation::MV1_PLAYER_ATTACK_BEGIN ) {
					setAnimation( AnimationPtr( new Animation( Animation::MV1_PLAYER, Animation::MV1_PLAYER_ATTACK_BEGIN ) ) );
				} else {
					if ( animation->isEndAnimation( ) ) {
						animation->setAnimationTime( 0 );
					}
				}
			break;
			case ATTACK_LOOP:
				if ( animation->getMotion( ) != Animation::MV1_PLAYER_ATTACK_LOOP ) {
					setAnimation( AnimationPtr( new Animation( Animation::MV1_PLAYER, Animation::MV1_PLAYER_ATTACK_LOOP ) ) );
				} else {
					if ( animation->isEndAnimation( ) ) {
						animation->setAnimationTime( 0 );
					}
				}
			break;
			case ATTACK_END:
				if ( animation->getMotion( ) != Animation::MV1_PLAYER_ATTACK_END ) {
					setAnimation( AnimationPtr( new Animation( Animation::MV1_PLAYER, Animation::MV1_PLAYER_ATTACK_END ) ) );
				} else {
					if ( animation->isEndAnimation( ) ) {
						animation->setAnimationTime( 0 );
					}
				}
			break;
		}

	}
}

void Player::walk( Player::CONTROLL controll ) {
	if ( controll.action == CONTROLL::ATTACK ) {
		return;
	}

	Vector speed = Vector( );
	if ( controll.move.getLength( ) > 0.0 ) {
		Vector vec = controll.move.normalize( );
		speed = vec;
		move( speed );
		setDir( vec );
	}
}

void Player::swicthState( Player::CONTROLL controll ) {
	_player_state = PLAYER_STATE_WAIT;

	if ( controll.move.getLength( ) > 0.0 ) {
		_player_state = PLAYER_STATE_WALK;
	}
	if ( controll.action == CONTROLL::ATTACK ) {
		_player_state = PLAYER_STATE_ATTACK;
	}
}

void Player::attack( Player::CONTROLL controll ) {
	if ( _player_state == PLAYER_STATE_ATTACK && _before_state != PLAYER_STATE_ATTACK ) {
		_attack = ATTACK_BRGIN;
	}
	AnimationPtr animation = getAnimation( );
	if ( animation->getMotion( ) == Animation::MV1_PLAYER_ATTACK_BEGIN ) {
		if ( animation->isEndAnimation( ) ) {
			_attack_loop = true;
		}
	}
	if ( _attack_loop ) {
		_attack = ATTACK_LOOP;
		AnimationPtr anim = getAnimation( );
		int time = ( int )anim->getAnimTime( );
		if ( time == ATTACK_TIME ) {
			onAttack( );
		}
	}

	if ( _player_state != PLAYER_STATE_ATTACK && _before_state == PLAYER_STATE_ATTACK ) {
		_attack_loop = false;
		_attack_end = false;
		_attack = ATTACK_END;
	}
}

void Player::onAttack( ) {
	Vector pos = getPos( );
	Vector dir = getDir( );

	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	weapon->add( BulletPtr( new BulletFire( pos + BULLET_OFFSET + dir * 2, dir, getStatus( ).power ) ) );
}