#pragma once
#include "Task.h"
#include "mathmatics.h"
#include <string>
#include <array>

PTR( Drawer );
PTR( Model );

class Drawer : public Task {
public:
	static DrawerPtr getTask( );
	static std::string getTag( ) { return "DRAWER"; }
public:
	Drawer( const char* directory );
	virtual ~Drawer( );
public:
	enum BLEND {
		BLEND_NONE,
		BLEND_ALPHA,
		BLEND_ADD,
		MAX_BLEND,
	};
	struct Transform {
		int sx;
		int sy;
		int tx;
		int ty;
		int tw;
		int th;
		int sx2;
		int sy2;
		Transform( );
		Transform( int sx_, int sy_, int tx_ = -1, int ty_ = -1, int tw_ = -1, int th_ = -1, int sx2 = -1, int sy2 = -1 );
	};
	struct Sprite {
		Transform trans;
		int res;
		BLEND blend;
		double ratio;
		Sprite( );
		Sprite( Transform trans_, int res_, BLEND blend_, double ratio_ );
	};
	struct ModelMV1 {
		Vector pos;
		Vector dir;
		int motion;
		double time;
		ModelMV1( );
		ModelMV1( Vector pos_, Vector dir_, int motion_, double time_ );
	};
	struct ModelMDL {
		Vector pos;
		int type;
		ModelMDL( );
		ModelMDL( Vector pos_, int type_ );
	};
	struct MV1_ID {
		int body;
		int body_anim;
		double scale;
	};
	struct Billboard {
		Vector pos;
		double size;
		int res;
		BLEND blend;
		double ratio;
		Billboard( );
		Billboard( Vector pos_, double size_, int res, BLEND blend_, double ratio_ );
	};
	struct PlayingEffect {
		int playing_handle;
		Vector scale;
		Vector pos;
		Vector dir;
		PlayingEffect( );
		PlayingEffect( int playing_effect_, Vector scale_, Vector pos_, Vector dir_ );
	};
	
public:
	void initialize( );
	void update( );
	void loadMV1Model( int motion, const char* filename, double scale );
	void loadMDLModel( int type, const char* filename, const char* texture_filename, Matrix matrix = Matrix( ) );
	void loadGraph( int res, const char* filename );
	void loadEffect( int res,  const char* filename );
	double getEndAnimTime( int res );
	void setSprite( const Sprite& sprite );
	void setModelMV1( const ModelMV1& model );
	void setModelMDL( const ModelMDL& model_mdl );
	void setShadow( const Vector& pos );
	void setBillboard( const Billboard& billboard );
	void drawString( int x, int y, const char* string, ... );
	void drawLine( int x1, int y1, int x2, int y2 );

	bool _back;
	void setBack( ) { _back = true; };
private:
	void drawModelMV1( );
	void drawModelMDL( );
	void drawSprite( );
	void drawBillboard( );
	void drawShadow( );
	void flip( );
private:
	const char* _directory;

	static const int MODEL_MV1_NUM = 10000;
	std::array< ModelMV1, MODEL_MV1_NUM > _model_mv1; 
	int _model_mv1_idx;

	static const int SPRITE_NUM = 10000;
	std::array< Sprite, SPRITE_NUM > _sprite; 
	int _sprite_idx;

	static const int MODEL_ID_NUM = 1000;
	std::array< MV1_ID, MODEL_ID_NUM > _model_id;

	static const int GRAPHIC_ID_NUM = 1000;
	std::array< int, GRAPHIC_ID_NUM > _graphic_id;

	static const int EFFECT_ID_NUM = 1000;
	std::array< int, EFFECT_ID_NUM > _effect_id;

	static const int BILLBOARD_NUM = 1000;
	std::array< Billboard, BILLBOARD_NUM > _billboard;
	int _billboard_idx;

	std::array< PlayingEffect, EFFECT_ID_NUM > _effect;
	int _effect_idx;

	static const int MODEL_MDL_NUM = 500;
	std::array< ModelMDL, MODEL_MDL_NUM > _model_mdl;
	int _model_mdl_idx;

	static const int MODEL_NUM = 20;
	std::array< ModelPtr, MODEL_NUM > _model;

	static const int SHADOW_NUM = 1000;
	ModelPtr _shadow_model;
	int _shadow_idx;


	int _refresh_count;
	int _shadow_handle;
	int _start_time;
	double _fps;
};
