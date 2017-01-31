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
	Vector HitGroundPos( Vector head_pos, Vector foot_pos );
private:
	static const int MAX_POLYGON_NUM = 6000;
	static const int MAX_MODEL_NUM = 900;
private:
	struct ModelData {
		std::array< Vector, MAX_POLYGON_NUM > pos;
		int polygon_num;
		ModelData( );
	};
private:
	void loadModelPos( int x, int y, ModelPtr model );
private:
	ModelData _model_data_ground;
	int _model_max_idx;
};

