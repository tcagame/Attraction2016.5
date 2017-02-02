#include "DarkMonk.h"
#include "Animation.h"

const double ATTACK_TIME = 10;
const Character::STATUS DARKMONK_STATUS = Character::STATUS( 500, 10, 0.1 );
const double DARKMONK_RANGE = 1;

DarkMonk::DarkMonk( ):
Enemy( ENEMY_TYPE_DARKMONK, DARKMONK_RANGE, DARKMONK_STATUS ) {
	_is_dead = false;
}


DarkMonk::~DarkMonk( ) {
}

bool DarkMonk::isDead( ) {
	return _is_dead;
}

void DarkMonk::resetDeadFlag( ) {
	_is_dead = false;
	setState( ENEMY_STATE_WAIT );
	setMode( ENEMY_MODE_ENTRY );
	setAnimation( AnimationPtr( new Animation( Animation::MV1_DARKMONK, Animation::MV1_DARKMONK_WAIT ) ) );
}

void DarkMonk::animationUpdate( ) {
	AnimationPtr animation = getAnimation( );
	Enemy::ENEMY_STATE state = getState( );
	if ( animation->getMotion( ) == Animation::MV1_DARKMONK_DEAD ) {
		if ( animation->isEndAnimation( ) ) {
			dead( );
			_is_dead = true;
		}
		return;
	}
	if ( animation->getMotion( ) == Animation::MV1_DARKMONK_DAMAGE && !animation->isEndAnimation( ) ) {
		setState( ENEMY_STATE_WAIT );
		return;
	}
	if ( state == ENEMY_STATE_WAIT ) {
		if ( animation->getMotion( ) != Animation::MV1_DARKMONK_WAIT ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_DARKMONK, Animation::MV1_DARKMONK_WAIT ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
	if ( state == ENEMY_STATE_WALK ) {
		if ( animation->getMotion( ) != Animation::MV1_DARKMONK_WALK ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_DARKMONK, Animation::MV1_DARKMONK_WALK ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
	if ( state == ENEMY_STATE_ATTACK ) {
		if ( animation->getMotion( ) != Animation::MV1_DARKMONK_ATTACK ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_DARKMONK, Animation::MV1_DARKMONK_ATTACK ) ) );
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
		if ( animation->getMotion( ) != Animation::MV1_DARKMONK_DAMAGE ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_DARKMONK, Animation::MV1_DARKMONK_DAMAGE ) ) );
		}
	}
	if ( state == ENEMY_STATE_DEAD ) {
		if ( animation->getMotion( ) != Animation::MV1_DARKMONK_DEAD ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_DARKMONK, Animation::MV1_DARKMONK_DEAD ) ) );
		}
	}
}
