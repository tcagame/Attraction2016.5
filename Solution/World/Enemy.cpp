#include "Enemy.h"
#include "App.h"
#include "Player.h"
#include "Animation.h"
#include "Party.h"

const double ATTACK_RANGE = 2.0;
const double MOVE_RANGE = 15;
const double MV1_SPEED = 1.0;
const double MAX_PLAYER_NUM = 4;
const double ATTACK_TIME = 10;
const Vector ENEMY_ENTRY_TARGET_POS[ ] = {
	Vector( 0, 30, 0 ),
	Vector( 10, 30, 0 )
};
const int ENEMY_ENTRY_TARGET_NUM = 2;

Enemy::Enemy( ENEMY_TYPE type, double range, Character::STATUS status ) :
_type( type ),
_range( range ),
Character( status ) {
	_state = ENEMY_STATE_WAIT;
	_before_state = ENEMY_STATE_WAIT;
	setAnimation( AnimationPtr( new Animation( Animation::MV1_PLAYER, Animation::MV1_GOBLIN_WAIT, MV1_SPEED ) ) );
	_on_damage = false;
	_enemy_mode = Enemy::ENEMY_MODE_ENTRY;
	_entry_target_num = 0;
}

Enemy::~Enemy( ) {

}



void Enemy::otherUpdate( ) {
	switch ( _enemy_mode ) {
	case ENEMY_MODE_ENTRY:
		moveToEntryTarget( );
		animationUpdate( );
		break;
	case ENEMY_MODE_COMBAT:
		searchTarget( );
		moveToTarget( );
		animationUpdate( );
		switchStatus( );
		_before_state = _state;
		break;
	default:
		break;
	}

	
}

void Enemy::moveToEntryTarget( ) {
	Vector distance = ENEMY_ENTRY_TARGET_POS[ _entry_target_num ] - getPos( );
	move( distance, true );
	_state = ENEMY_STATE_WALK;
	if ( distance.getLength( ) < 2 ) {
		_entry_target_num++;
	}
	if ( _entry_target_num >= ENEMY_ENTRY_TARGET_NUM ) {
		_enemy_mode = ENEMY_MODE_COMBAT;
		_entry_target_num = 0;
	}
}


void Enemy::searchTarget( ) {
	_target.reset( );
	AppPtr app = App::getTask( );
	Vector pos = getPos( );
	double length = 1000;
	PartyPtr party = app->getParty( );
	for ( int i = 0; i < MAX_PLAYER_NUM; i++ ) {
		PlayerPtr player = party->getPlayer( i );
		if ( !player ) {
			continue;
		}
		if ( !player->isExpired( ) ) {
			continue;
		}
		if ( ( pos - player->getPos( ) ).getLength( ) < length ) {
			length = ( pos - player->getPos( ) ).getLength( );
			_target = player;
		}
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
		move( distance );
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

	if ( getBeforeHp( ) > getStatus( ).hp ) {
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

void Enemy::setMode( Enemy::ENEMY_MODE mode ) {
	_enemy_mode = mode;
}

bool Enemy::isOnDamage( ) {
	return _on_damage;
}

Enemy::ENEMY_TYPE Enemy::getEnemyType( ) {
	return _type;
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