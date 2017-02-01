#include "EnemyGoblin.h"
#include "Animation.h"

const double ATTACK_TIME = 30;

EnemyGoblin::EnemyGoblin( ENEMY_TYPE type, double range, Character::STATUS status ) :
Enemy( type, range, status ) {
}


EnemyGoblin::~EnemyGoblin( ) {
} 

void EnemyGoblin::animationUpdate( ) {
	AnimationPtr animation = getAnimation( );
	Enemy::ENEMY_STATE state = getState( );
	if ( animation->getMotion( ) == Animation::MV1_GOBLIN_DEAD ) {
		if ( animation->isEndAnimation( ) ) {
			dead( );
		}
		return;
	}
	if ( animation->getMotion( ) == Animation::MV1_GOBLIN_DAMAGE && !animation->isEndAnimation( ) ) {
		setState( ENEMY_STATE_WAIT );
		return;
	}
	if ( state == ENEMY_STATE_WAIT ) {
		if ( animation->getMotion( ) != Animation::MV1_GOBLIN_WAIT ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_GOBLIN, Animation::MV1_GOBLIN_WAIT ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
	if ( state == ENEMY_STATE_WALK ) {
		if ( animation->getMotion( ) != Animation::MV1_GOBLIN_WALK ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_GOBLIN, Animation::MV1_GOBLIN_WALK ) ) );
		} else {
			if ( animation->isEndAnimation( ) ) {
				animation->setAnimationTime( 0 );
			}
		}
	}
	if ( state == ENEMY_STATE_ATTACK ) {
		if ( animation->getMotion( ) != Animation::MV1_GOBLIN_ATTACK ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_GOBLIN, Animation::MV1_GOBLIN_ATTACK ) ) );
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
		if ( animation->getMotion( ) != Animation::MV1_GOBLIN_DAMAGE ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_GOBLIN, Animation::MV1_GOBLIN_DAMAGE ) ) );
		}
	}
	if ( state == ENEMY_STATE_DEAD ) {
		if ( animation->getMotion( ) != Animation::MV1_GOBLIN_DEAD ) {
			setAnimation( AnimationPtr( new Animation( Animation::MV1_GOBLIN, Animation::MV1_GOBLIN_DEAD ) ) );
		}
	}
}
