#include "EnemyMinotaur.h"
#include "Animation.h"

const double ATTACK_TIME = 10;

EnemyMinotaur::EnemyMinotaur( ENEMY_TYPE type, double range, Character::STATUS status ) :
Enemy( type, range, status ) {
}


EnemyMinotaur::~EnemyMinotaur( ) {
}

void EnemyMinotaur::animationUpdate( ) {
	AnimationPtr animation = getAnimation( );
	Enemy::ENEMY_STATE state = getState( );
	if ( animation->getMotion( ) == Animation::MV1_MINOTAUR_DEAD ) {
		if ( animation->isEndAnimation( ) ) {
			dead( );
		}
		return;
	}
	if ( animation->getMotion( ) == Animation::MV1_MINOTAUR_DAMAGE && !animation->isEndAnimation( ) ) {
		setState( ENEMY_STATE_WAIT );
		return;
	}
	if ( state == ENEMY_STATE_WAIT ) {
		if ( animation->getMotion( ) != Animation::MV1_MINOTAUR_WAIT ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_MINOTAUR, Animation::MV1_MINOTAUR_WAIT ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
	if ( state == ENEMY_STATE_WALK ) {
		if ( animation->getMotion( ) != Animation::MV1_MINOTAUR_WALK ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_MINOTAUR, Animation::MV1_MINOTAUR_WALK ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
	if ( state == ENEMY_STATE_ATTACK ) {
		if ( animation->getMotion( ) != Animation::MV1_MINOTAUR_SMASH ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_MINOTAUR, Animation::MV1_MINOTAUR_SMASH ) ) );
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
		if ( animation->getMotion( ) != Animation::MV1_MINOTAUR_DAMAGE ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_MINOTAUR, Animation::MV1_MINOTAUR_DAMAGE ) ) );
		}
	}
	if ( state == ENEMY_STATE_DEAD ) {
		if ( animation->getMotion( ) != Animation::MV1_MINOTAUR_DEAD ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_MINOTAUR, Animation::MV1_MINOTAUR_DEAD ) ) );
		}
	}
}