#include "App.h"
#include "Player.h"
#include "Cohort.h"
#include "Ground.h"
#include "GroundModel.h"
#include "Field.h"
#include "Weapon.h"
#include "Device.h"
#include "Application.h"
#include "Client.h"

const std::string DIRECTORY = "../Resource/";
const std::string MODEL_NAME_LIST [] {
	"none",
	"floor01"
};
const int RESET_COUNT = 30;
const int START_COUNT = 60;
const int STRING_BUF = 256;

AppPtr App::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< App >( fw->getTask( App::getTag( ) ) );
}

App::App( ) {
	_ground = GroundPtr( new Ground( DIRECTORY + "CSV/map.csv" ) );
	_ground_model = GroundModelPtr( new GroundModel );
	_ground_model->loadModelData( 0, 0, DIRECTORY + "MapModel/floor01.mdl" );
	_state = STATE_PLAY;//�f�o�b�O�p
}

App::~App( ) {

}

void App::initialize( ) {
	std::string filepath = DIRECTORY + "CSV/";
	_ground = GroundPtr( new Ground( filepath + "map.csv" ) );//�}�b�v�f�[�^
	_ground_model = GroundModelPtr( new GroundModel( ) );
	_field = FieldPtr( new Field( ) );
	_weapon = WeaponPtr( new Weapon( ) );
	Character::STATUS status = Character::STATUS( 100000, 100, 0.5 );
	_player = PlayerPtr( new Player( 2, status ) );
	_player->create( Vector( 0, 0 ) );
	
	_cohort = CohortPtr( new Cohort( ) );
	
	
	loadToGround( ) ;//GroundModel��Cohort�̃f�[�^�ǂݍ���
	if ( _cohort ) {
		_cohort->init( );
	}
}

void App::update( ) {
	updateState( );
	switch ( _state ) {
	case STATE_READY:
		updateStateReady( );
		break;
	case STATE_PLAY:
		updateStatePlay( );
		break;
	case STATE_CLEAR:
		updateStateClear( );
		break;
	case STATE_DEAD:
		updateStateDead( );
		break;
	}
}

void App::updateState( ) {
	ClientPtr client = Client::getTask( );
	CLIENTDATA data = client->getClientData( );
	STATE state;
	switch( data.scene ) {
	case SCENE_TITLE:
		state = STATE_READY;
		break;
	case SCENE_PLAY:
		state = STATE_PLAY;
		break;
	case SCENE_CLEAR:
		state = STATE_CLEAR;
		break;
	case SCENE_GAMEOVER:
		state = STATE_DEAD;
		break;
	default:
		return;
		break;
	}
	//�^�C�g���ɖ߂�Ƃ��ɏ�����
	if ( _state != state ) {
		if ( _state != STATE_READY ) {
			initialize( );
		}
		setState( state );
	}
}

void App::updateStateReady( ) {
}

void App::updateStatePlay( ) {
	_player->update( );
	_cohort->update( );
	_weapon->update( );
}

void App::updateStateClear( ) {
}

void App::updateStateDead( ) {
}

GroundPtr App::getGround( ) const {
	return _ground;
}

GroundModelPtr App::getGroundModel( ) const {
	return _ground_model;
}

PlayerPtr App::getPlayerTarget( const Vector& pos ){
	PlayerPtr target;

	double min = 1000;
	if ( !_player->isExpired( ) ) {
		return target;
	}
	Vector vec = _player->getPos( ) - pos;
	double length = vec.getLength( );
	if ( length < min ) {
		target = _player;
	}
	return target;	
}

void App::loadToGround( ) {
	int width = _ground->getWidth( );
	int height = _ground->getHeight( );

	for ( int i = 0; i < height; i++ ) {
		for ( int j = 0; j < width; j++ ) {
			int idx = _ground->getIdx( j, i );
			int type = _ground->getGroundData( idx );
			
			char idx_string[ STRING_BUF ] = "";
			sprintf_s( idx_string, STRING_BUF,"%d", type );
			
			std::string md_file_path = DIRECTORY + "MapData/";
			md_file_path += idx_string;
			md_file_path += ".md";

			//�t�@�C���̓ǂݍ���
			FILE* fp;
			errno_t err = fopen_s( &fp, md_file_path.c_str( ), "r" );
			if ( err != 0 ) {
				continue;
			}
			
			char buf[ 1024 ];
			std::string name[ 2 ];
			for( int k = 0; k < 2; k++ ) {
				fscanf_s( fp,"%s", buf, 1024 );
				name[ k ] = buf;
			}
			fclose( fp );
			int model_type = 0;
			for ( int k = 0; k < 5; k++ ) {
				if( name[ 0 ] == MODEL_NAME_LIST[ k ] ) {
					model_type = k;
				}
			}
			_map_convert[ type ] = model_type;

			if ( _cohort ) {
				std::string enemy_file_path = DIRECTORY + "EnemyData/" + name[ 1 ] + ".ene";
				_cohort->loadBlockEnemyData( idx, enemy_file_path );
			}
			if ( model_type == 0 ) {
				continue;
			}

			std::string model_file_path = DIRECTORY + "MapModel/" + MODEL_NAME_LIST[ model_type ] + ".mdl";
			_ground_model->loadModelData( j, i, model_file_path );

		}
	}
}

int App::convertCSVtoMap( int type ) {
	return _map_convert[ type ];
}

App::STATE App::getState( ) const {
	return _state;
}

void App::setState( STATE state ) {
	_state = state;
}

FieldPtr App::getField( ) const {
	return _field;
}

WeaponPtr App::getWeapon( ) const {
	return _weapon;
}

CohortPtr App::getCohort( ) const{
	return _cohort;
}

PlayerPtr App::getPlayer( ) const {
	return _player;
}