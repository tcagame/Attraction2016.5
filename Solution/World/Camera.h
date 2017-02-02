#pragma once

#include "smart_ptr.h"
#include "mathmatics.h"
#include "Task.h"
#include <string>

PTR( Camera );

class Camera : public Task {
public:
	enum CAMERA_VIEW_PHASE {
		CAMERA_VIEW_PHASE_TITLE,
		CAMERA_VIEW_PHASE_ENEMY,
		CAMERA_VIEW_PHASE_BATTLE,
	};
public:
	static std::string getTag( ) { return "CAMERA"; }
	static CameraPtr getTask( );
public:
	Camera( );
	virtual ~Camera( );
public:
	void update( );
	Vector getPos( ) const;
	Vector getTarget( ) const;
	void setTarget( Vector target );
	virtual void initialize( );
	bool isInScreen( Vector pos );
	Vector getConvertDeviceVec( const Vector& vec );
protected:
	Vector getStartPos( ) const;
	Vector getStartTargetPos( ) const;
protected:
	Vector _pos;
	CAMERA_VIEW_PHASE _camera_view_phase;
	Vector _target;
};

