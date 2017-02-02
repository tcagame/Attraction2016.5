#include "DarkKnight.h"
#include "Animation.h"

const double ATTACK_TIME = 10;
const Character::STATUS DARKKNIGHT_STATUS = Character::STATUS( 500, 10, 0.1 );
const double DARKKNIGHT_RANGE = 1;

DarkKnight::DarkKnight( ):
Enemy( ENEMY_TYPE_DARKKIGHT, DARKKNIGHT_RANGE, DARKKNIGHT_STATUS ) {
	_is_dead = false;
}


DarkKnight::~DarkKnight( ) {
}


bool DarkKnight::isDead( ) {
	return _is_dead;
}


void DarkKnight::resetDeadFlag( ) {
	_is_dead = false;
	setState( ENEMY_STATE_WAIT );
	setMode( ENEMY_MODE_ENTRY );

	setAnimation( AnimationPtr( new Animation( Animation::MV1_DARKKNIGHT, Animation::MV1_DARKKNIGHT_WAIT ) ) );
}

void DarkKnight::animationUpdate( ) {
	AnimationPtr animation = getAnimation( );
	Enemy::ENEMY_STATE state = getState( );
	if ( animation->getMotion( ) == Animation::MV1_DARKKNIGHT_DEAD ) {
		if ( animation->isEndAnimation( ) ) {
			dead( );
			_is_dead = true;
		}
		return;
	}
	if ( animation->getMotion( ) == Animation::MV1_DARKKNIGHT_DAMAGE && !animation->isEndAnimation( ) ) {
		setState( ENEMY_STATE_WAIT );
		return;
	}
	if ( state == ENEMY_STATE_WAIT ) {
		if ( animation->getMotion( ) != Animation::MV1_DARKKNIGHT_WAIT ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_DARKKNIGHT, Animation::MV1_DARKKNIGHT_WAIT ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
	if ( state == ENEMY_STATE_WALK ) {
		if ( animation->getMotion( ) != Animation::MV1_DARKKNIGHT_WALK ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_DARKKNIGHT, Animation::MV1_DARKKNIGHT_WALK ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
	if ( state == ENEMY_STATE_ATTACK ) {
		if ( animation->getMotion( ) != Animation::MV1_DARKKNIGHT_ATTACK ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_DARKKNIGHT, Animation::MV1_DARKKNIGHT_ATTACK ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( animation->getEndAnimTime( ) );
				setAttack( false );
			}
			if ( animation->getAnimTime( ) == ATTACK_TIME ) {
				PlayerWeakPtr target = getTarget( );
				onAttack( target.lock( ) );
			}
		}
	}
	bool on_damage = isOnDamage( );
	if ( on_damage ) {
		if ( animation->getMotion( ) != Animation::MV1_DARKKNIGHT_DAMAGE ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_DARKKNIGHT, Animation::MV1_DARKKNIGHT_DAMAGE ) ) );
		}
	}
	if ( state == ENEMY_STATE_DEAD ) {
		if ( animation->getMotion( ) != Animation::MV1_DARKKNIGHT_DEAD ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_DARKKNIGHT, Animation::MV1_DARKKNIGHT_DEAD ) ) );
		}
	}
}
