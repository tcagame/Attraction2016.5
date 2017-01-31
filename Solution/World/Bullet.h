#pragma once
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Bullet );
PTR( Enemy );

class Bullet {
public:
	static const double BULLET_SCALE; 
	enum TYPE {
		TYPE_FIRE,
		TYPE_MAX,
	};
public:
	Bullet( TYPE type );
	virtual ~Bullet( );
public:
	virtual bool update( ) = 0;
public:
	TYPE getType( ) const;
	Vector getPos( ) const;
	Vector getDir( ) const;
protected:
	void attackEnemy( const Vector& pos, int power );
	void attackPlayer( const Vector& pos, int power );
private:
	bool isDeathBlow( );
protected:
	Vector _pos;
	Vector _dir;
	int _power;
	int _effect_handle;
private:
	const TYPE _type;
};