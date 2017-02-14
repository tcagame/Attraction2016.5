#include "BulletFire.h"
#include "App.h"
#include "Ground.h"

const int VANISH_TIME = 60;
const int POWER = 100;
const double SPEED = 1.0;
const double EFFECT_SCALE = 0.3;

BulletFire::BulletFire( const Vector& pos, const Vector& dir, int power )
: Bullet( Bullet::TYPE_FIRE ) {
	_pos = pos + Vector( 0, 0, 0.1 ) * Bullet::BULLET_SCALE;
	_dir = dir.normalize( );
	_power = power;
	_speed = SPEED;
	_exist_time = 0;
}

BulletFire::~BulletFire( ) {
}


bool BulletFire::update( ) {
	// ˆÚ“®
	_exist_time++;
	if ( _exist_time >= VANISH_TIME  ) {
		return true;
	}
	_pos += _dir * _speed;

	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	if ( _pos.x < 0 || _pos.y < 0 ||
		 _pos.x > ground->getWidth( ) * ground->CHIP_WIDTH ||
		 _pos.y > ground->getHeight( ) * ground->CHIP_HEIGHT ) {
		return true;
	}
	return attackEnemy( _pos, _power );
}