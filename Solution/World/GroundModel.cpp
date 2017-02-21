#include "GroundModel.h"
#include "App.h"
#include "Ground.h"
#include "Model.h"
#include "MapType.h"
#include "Drawer.h"


GroundModel::ModelData::ModelData( ) :
polygon_num( 0 ) {
	
}

GroundModel::GroundModel() {
	_model_max_idx  = 0;
}

GroundModel::~GroundModel()
{
}

void GroundModel::loadModelData( int x, int y, std::string filename ) {
	ModelPtr model = ModelPtr( new Model( ) );
	model->load( filename );
	loadModelPos( x, y, model );
}

void GroundModel::loadModelPos( int x, int y, ModelPtr model ) {
	int polygon_num = model->getPolygonNum( );
	_model_data_ground.polygon_num = polygon_num;
	model->translate( Vector( x , y ) );
	int num = 0;
	for ( int i = 0; i < polygon_num * 3; i++ ) {
		Vector pos = model->getPoint( i );
		_model_data_ground.pos[ num ] = Vector( pos.x / 2, pos.y / 2, pos.z / 2 );
		num++;
	}
}

Vector GroundModel::HitGroundPos( Vector head_pos, Vector foot_pos ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );

	Vector ret = Vector( -100, -100, -100 );
	int polygon_idx = 0;
	Vector pos_a = head_pos;
	Vector pos_b = foot_pos;

	for ( int i = 0; i < _model_data_ground.polygon_num; i++ ) {
		polygon_idx = i * 3;
		
		Vector plane_point_a = _model_data_ground.pos[ polygon_idx ];
		Vector plane_point_b = _model_data_ground.pos[ polygon_idx + 1 ];
		Vector plane_point_c = _model_data_ground.pos[ polygon_idx + 2 ];
		
		Vector normal_plane = ( plane_point_b - plane_point_a ).cross( plane_point_c - plane_point_b );
		normal_plane = normal_plane.normalize( );
		
		
		Vector plane_to_pos_a = plane_point_a - pos_a;
		Vector plane_to_pos_b = plane_point_a - pos_b;
		double dot_a = normal_plane.dot( plane_to_pos_a );
		double dot_b = normal_plane.dot( plane_to_pos_b );
		
		if ( normal_plane.z != 1 ) {
			int a = 0;	
		}
		if( dot_a == 0 && dot_b == 0 ) {
			continue;
		} 
		if ( ( dot_a <= 0 || dot_b >= 0 ) &&
			 ( dot_a >= 0 || dot_b <= 0 ) ) {
			continue;

		} 
		if ( normal_plane.z != 1 ) {
			int a = 0;
		}
		Vector pos_a_to_b = pos_b - pos_a;
		double ratio =  abs( dot_a ) / ( abs( dot_a ) + abs( dot_b ) );
		Vector cross_pos = pos_a + ( pos_a_to_b * ratio );
		

		Vector ab_cross_bcroos_pos = ( plane_point_b - plane_point_a ).cross( cross_pos - plane_point_b );
		Vector ca_cross_acroos_pos = ( plane_point_a - plane_point_c ).cross( cross_pos - plane_point_a );
		Vector bc_cross_ccroos_pos = ( plane_point_c - plane_point_b ).cross( cross_pos - plane_point_c );
	
		if ( ab_cross_bcroos_pos != normal_plane ||
			 ca_cross_acroos_pos != normal_plane || 
			 bc_cross_ccroos_pos != normal_plane ) {
			continue;
		}
		
		if ( ( cross_pos - head_pos ).getLength( ) < ( ret - head_pos ).getLength( ) ) {
			ret = cross_pos;
		}
	}
	return ret;
}

void GroundModel::draw( ) {
	DrawerPtr drawer = Drawer::getTask( );

	for ( int i = 0; i < _model_data_ground.polygon_num; i++ ) {
		Vector pos0 = _model_data_ground.pos[ i * 3 + 0 ];
		Vector pos1 = _model_data_ground.pos[ i * 3 + 1 ];
		Vector pos2 = _model_data_ground.pos[ i * 3 + 2 ];
		drawer->drawLine( pos0, pos1 );
		drawer->drawLine( pos1, pos2 );
		drawer->drawLine( pos2, pos0 );
	}
}
