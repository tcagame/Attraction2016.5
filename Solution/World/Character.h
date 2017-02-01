#pragma once
#include "Object.h"
#include "smart_ptr.h"
#include "mathmatics.h"
#include <string>

PTR( Character );
PTR( Behavior );
PTR( Animation );

class Character : public Object {
public:
	struct STATUS {
		int hp;
		unsigned int power;
		double speed;
		double width;
		STATUS( ) {
			hp = 0;
			power = 0;
			speed = 0;
			width = 0.5;
		}
		STATUS( int hp_, unsigned int power_, double speed_, double width_ = 0.5 ) {
			hp = hp_;
			power = power_;
			speed = speed_;
			width = width_;
		}
	};
public:
	Character( STATUS status );
	virtual ~Character( );
public:
	void update( );

	void reset( );
	void create( const Vector& pos );
	void dead( );
	void damage( unsigned int power );

	Vector getPos( ) const;
	Vector getDir( ) const;
	bool isExpired( ) const;

	STATUS getStatus( ) const;
	int getMaxHp( ) const;

	AnimationPtr getAnimation( ) const;
protected:
	bool move( const Vector& vec, bool is_entry_mode = false );
	void setAnimation( AnimationPtr animation );
	void setDir( Vector dir );
	void setHP( unsigned int hp );
	virtual void otherUpdate( ) = 0;
private:
	Vector _pos;
	Vector _dir;
	bool _expired;

	STATUS _status;
	const STATUS _origin_status;
	int _max_hp;

	AnimationPtr _animation;
};

