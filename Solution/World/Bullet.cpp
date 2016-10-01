#include "Bullet.h"
#include "App.h"
#include "Enemy.h"
#include "mathmatics.h"
#include "Player.h"
#include "Field.h"

const double Bullet::BULLET_SCALE( 1.0 );//���f���̑傫���ɍ��킹��B

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

void Bullet::attackEnemy( const Vector& pos, int power ) {
	AppPtr app = App::getTask( );
	FieldPtr field = app->getField( );
	ObjectPtr object = field->getTarget( ( int )pos.x, ( int )pos.y );
	EnemyPtr enemy = std::dynamic_pointer_cast< Enemy >( object );
	if ( !enemy ) {
		return;
	}
	Character::STATUS status = enemy->getStatus();
	enemy->damage( power );
}