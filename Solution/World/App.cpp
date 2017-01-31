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
	reset( );
}

App::~App( ) {

}

void App::initialize( ) {
	std::string filepath = DIRECTORY + "CSV/";
	_ground = GroundPtr( new Ground( filepath + "map.csv" ) );//マップデータ
	_ground_model = GroundModelPtr( new GroundModel( ) );
	_field = FieldPtr( new Field( ) );
	_weapon = WeaponPtr( new Weapon( ) );
	Character::STATUS status = Character::STATUS( 100000, 100, 0.5 );
	_player = PlayerPtr( new Player( 2, status ) );
	_player->create( Vector( 0, 0 ) );
	std::string floor_model_path = DIRECTORY + "MapModel/floor_collision.mdl";
	_ground_model->loadModelData( 0, 0, floor_model_path );
	_cohort = CohortPtr( new Cohort( ) );

	
}


void App::reset( ) {
	_state = STATE_PLAY;
	//_state = STATE_PLAY;//デバック用にプレイスタート
	_push_reset_count = 0;
	_push_start_count = 0;
}

void App::update( ) {
	updateReset( );
	switch ( _state ) {
	case STATE_READY:
	//	updateStateReady( );
	//	break;
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

void App::updateReset( ) {
	DevicePtr device = Device::getTask( );
	if ( !device ) {
		return;
	}
	if ( device->getButton( 0 ) == BUTTON_A + BUTTON_B + BUTTON_C + BUTTON_D ) {
		_push_reset_count += 1;
	} else  {
		_push_reset_count = 0;
	}
	if ( _push_reset_count < RESET_COUNT ) {
		return;
	}
	reset( );
}

void App::updateStateReady( ) {

	ClientPtr client = Client::getTask( );
	CLIENTDATA data = client->getClientData( );
	bool next = false;
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		if ( data.player[ i ].button > 0 ) {
			next = true;
		}
	}
	if ( next ) {
		setState( STATE_PLAY );
	}
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

int App::getStartCount( ) const {
	return _push_start_count;
}

int App::getStartCountMax( ) const {
	return START_COUNT;
}

PlayerPtr App::getPlayer( ) const {
	return _player;
}