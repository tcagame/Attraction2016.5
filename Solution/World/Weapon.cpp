#include "Weapon.h"
#include "Bullet.h"


Weapon::Weapon( ) {
}


Weapon::~Weapon( ) {
}

void Weapon::reset( ) {
	_list_bullet.clear( );
}

void Weapon::update( ) {
	std::list<BulletPtr>::iterator it = _list_bullet.begin( );
	while ( it != _list_bullet.end( ) ) {
		BulletPtr bullet = *it;
		if ( !bullet ) {
			it = _list_bullet.erase( it );
			continue;
		}

		if ( bullet->update( ) ) {
			it = _list_bullet.erase( it );
		} else {
			it++;
		}
	}
}

void Weapon::add( BulletPtr bullet ) {
	_list_bullet.push_back( bullet );
}

int Weapon::getBulletNum( ) {
	return _list_bullet.size( );
}

BulletPtr Weapon::getBullet( int idx ) {
	std::list<BulletPtr>::iterator it = _list_bullet.begin( );
	for ( int i = 0; i < idx; i++ ) {
		it++;
	}
	BulletPtr bullet = *it;
	return bullet;
}