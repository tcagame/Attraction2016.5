#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"
#include <array>

PTR( GroundModel );
PTR( Model );

class GroundModel {
public:
	GroundModel();
	virtual ~GroundModel();
public:
	void loadModelData( int x, int y, std::string filename );
	void update( );
	bool isCollisionGround( Vector pos );
private:
	static const int MAX_POLYGON_NUM = 6000;
	static const int MAX_MODEL_NUM = 900;
private:
	struct ModelData {
		std::array< Vector, MAX_POLYGON_NUM > pos;
		int polygon_num;
		double max_x;
		double max_y;
		double min_x; 
		double min_y;
		ModelData( );
	};
private:
	void loadModelPos( int x, int y, ModelPtr model );
	bool isCollisionModel( ModelData model, Vector pos_a, Vector pos_b );
	void loadBossModel( );
private:
	std::array< ModelData, MAX_MODEL_NUM > _model_data_ground;
	ModelData _model_data_boss;
	int _model_max_idx;
};

