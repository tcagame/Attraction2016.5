#include "Bullet.h"
#include "App.h"
#include "Enemy.h"
#include "mathmatics.h"
#include "Player.h"
#include "Cohort.h"

const double BULLET_HIT_LENGTH = 1.5;
const double Bullet::BULLET_SCALE( 0.05 );//ƒ‚ƒfƒ‹‚Ì‘å‚«‚³‚É‡‚í‚¹‚éB

Bullet::Bullet( TYPE type )
: _type( type ) {
}

Bullet::~Bullet( ) {
}

Bullet::TYPE Bullet::getType( ) const {
	return _type;
}

Vector Bullet::getPos( ) const {
	return _pos;
}

Vector Bullet::getDir( ) const {
	return _dir;
}

bool Bullet::attackEnemy( const Vector& pos, int power ) {
	AppPtr app = App::getTask( );
	CohortPtr cohort = app->getCohort( );
	int enemy_max_num = cohort->getMaxNum( );
	for ( int i = 0; i < enemy_max_num; i++ ) {
		EnemyPtr enemy = cohort->getEnemy( i );
		if ( !enemy ) {
			continue;
		}
		Vector enemy_pos = enemy->getPos( );
		Vector dist = pos - enemy_pos;
		double length = dist.getLength( );
		if ( length < BULLET_HIT_LENGTH ) {
			enemy->damage( power );
			return true;
		}
	}
	return false;
}
