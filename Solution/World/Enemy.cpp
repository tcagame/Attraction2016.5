#include "Enemy.h"
#include "App.h"
#include "Player.h"
#include "Animation.h"

const double ATTACK_RANGE = 2.0;
const double MOVE_RANGE = 7.5;
const double MV1_SPEED = 1.0;
const double ATTACK_TIME = 10;


Enemy::Enemy( ENEMY_TYPE type, double range, Character::STATUS status ) :
_type( type ),
_range( range ),
Character( status ) {
	_state = ENEMY_STATE_WAIT;
	_before_state = ENEMY_STATE_WAIT;
	setAnimation( AnimationPtr( new Animation( Animation::MV1_PLAYER, Animation::MV1_GOBLIN_WAIT, MV1_SPEED ) ) );
	_on_damage = false;
	_before_hp = status.hp;
}

Enemy::~Enemy( ) {

}

void Enemy::otherUpdate( ) {
	searchTarget( );
	moveToTarget( );
	switchStatus( );
	animationUpdate( );
	_before_state = _state;
	_before_hp = getStatus( ).hp;
}


void Enemy::searchTarget( ) {
	AppPtr app = App::getTask( );
	Vector pos = getPos( );
	PlayerPtr player = app->getPlayerTarget( pos );
	if ( !player ) {
		_target.reset( );
	} else if ( player->isExpired( ) ) {
		_target = player;
	} else {
		_target.reset( );
	}
}


void Enemy::moveToTarget( ) {
	if ( _target.expired( ) ) {
		return;
	}
	PlayerPtr player = _target.lock( );
	Vector target_pos = player->getPos( );
	
	Vector distance = target_pos - getPos( );
	double length = distance.getLength( );
	if ( _state == ENEMY_STATE_WALK ) {
		move( distance * getStatus( ).speed );
	}
}


void Enemy::switchStatus( ) {
	_state = ENEMY_STATE_WAIT;
	_on_damage = false;

	if ( _target.expired( ) ) {
		return;
	}
	PlayerPtr player = _target.lock( );
	Vector target_pos = player->getPos( );
	Vector stance = target_pos - getPos( );
	double range = stance.getLength( );
	if ( range <= MOVE_RANGE ) {
		_state = ENEMY_STATE_WALK;
	}

	if ( range <= ATTACK_RANGE && _before_state != ENEMY_STATE_ATTACK ) {
		_state = ENEMY_STATE_ATTACK;
	}
	AnimationPtr animation = getAnimation( );
	//UŒ‚’†
	if ( animation->getMotion( ) == Animation::MV1_GOBLIN_ATTACK && !animation->isEndAnimation( ) ) {
		_state = ENEMY_STATE_ATTACK;
	}

	if ( _before_hp > getStatus( ).hp ) {
		_on_damage = true;
	}

	if ( getStatus( ).hp <= 0 ) {
		_state = ENEMY_STATE_DEAD;
	}
}


void Enemy::animationUpdate( ) {
	AnimationPtr animation = getAnimation( );
	if ( animation->getMotion( ) == Animation::MV1_GOBLIN_DEAD ) {
		if ( animation->isEndAnimation( ) ) {
			dead( );
		}
		return;
	}
	if ( animation->getMotion( ) == Animation::MV1_GOBLIN_DAMAGE && !animation->isEndAnimation( ) ) {
		_state = ENEMY_STATE_WAIT;
		return;
	}
	if ( _state == ENEMY_STATE_WAIT ) {
		if ( animation->getMotion( ) != Animation::MV1_GOBLIN_WAIT ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_GOBLIN_WAIT ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _state == ENEMY_STATE_WALK ) {
		if ( animation->getMotion( ) != Animation::MV1_GOBLIN_WALK ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_GOBLIN_WALK ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _state == ENEMY_STATE_ATTACK ) {
		if ( animation->getMotion( ) != Animation::MV1_GOBLIN_ATTACK ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_GOBLIN_ATTACK ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
			if ( animation->getAnimTime( ) == ATTACK_TIME ) {
				onAttack( _target.lock( ) );
			}
		}
	}
	if ( _on_damage ) {
		if ( animation->getMotion( ) != Animation::MV1_GOBLIN_DAMAGE ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_GOBLIN_DAMAGE ) ) );
		}
	}
	if ( _state == ENEMY_STATE_DEAD ) {
		if ( animation->getMotion( ) != Animation::MV1_GOBLIN_DEAD ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_GOBLIN_DEAD ) ) );
		}
	}
}



void Enemy::onAttack( PlayerPtr player ) {
	AppPtr app = App::getTask( );
	
	Vector player_pos = player->getPos( );
	Vector vec = player_pos - getPos( );
	Vector dir = vec.normalize( );
	Vector attack_pos = getPos( ) +  dir * 1.0;
	Vector smash_dis = attack_pos - player_pos;

	if ( smash_dis.getLength( ) < 2.0 ) {
		player->damage( getStatus( ).power );
	}
}