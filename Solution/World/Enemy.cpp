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
	/*
	PlayerPtr player = app->getPlayerTarget( pos );
	if ( !player ) {
		_target.reset( );
	} else if ( player->isExpired( ) ) {
		_target = player;
	} else {
		_target.reset( );
	}
	*/
	_target.reset( );
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

void Enemy::setAttack( bool is_attack ) {
	_is_attack = is_attack;
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
		setAttack( true );
	}
	//UŒ‚’†
	if ( _is_attack ) {
		_state = ENEMY_STATE_ATTACK;
	}

	if ( _before_hp > getStatus( ).hp ) {
		_on_damage = true;
	}

	if ( getStatus( ).hp <= 0 ) {
		_state = ENEMY_STATE_DEAD;
	}
}


void Enemy::setState( Enemy::ENEMY_STATE state ) {
	_state = state;
}

Enemy::ENEMY_STATE Enemy::getState( ) {
	return _state;
}

PlayerWeakPtr Enemy::getTarget( ) {
	return _target;
}

bool Enemy::isOnDamage( ) {
	return _on_damage;
}

void Enemy::onAttack( PlayerPtr player ) {
	AppPtr app = App::getTask( );
	
	Vector player_pos = player->getPos( );
	Vector vec = player_pos - getPos( );
	Vector dir = vec.normalize( );
	Vector attack_pos = getPos( ) +  dir * 1.0;
	Vector smash_dis = attack_pos - player_pos;

	if ( smash_dis.getLength( ) < _range ) {
		player->damage( getStatus( ).power );
	}
}