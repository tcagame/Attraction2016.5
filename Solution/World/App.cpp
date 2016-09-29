#include "App.h"
#include "Player.h"
#include "GroundModel.h"
#include "Ground.h"
#include "Device.h"
#include "Application.h"
#include "Client.h"

const std::string DIRECTORY = "../Resource/";
const int RESET_COUNT = 30;
const int START_COUNT = 60;

AppPtr App::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< App >( fw->getTask( App::getTag( ) ) );
}

App::App( ) {
	_ground = GroundPtr( new Ground( DIRECTORY + "CSV/map.csv" ) );
	_ground_model = GroundModelPtr( new GroundModel );
	_ground_model->loadModelData( 0, 0, DIRECTORY + "MapModel/floor01.mdl" );
	reset( );
}

App::~App( ) {

}

void App::reset( ) {
	//_state = STATE_READY;
	_state = STATE_PLAY;//デバック用にプレイスタート
	_push_reset_count = 0;
	_push_start_count = 0;
}

void App::update( ) {
	updateReset( );
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

void App::updateReset( ) {
	DevicePtr device = Device::getTask( );
	if ( !device ) {
		return;
	}
	if ( device->getButton( ) == BUTTON_A + BUTTON_B + BUTTON_C + BUTTON_D ) {
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
	DevicePtr device = Device::getTask( );
	if ( device->getButton( ) > 0 ) {
		_push_start_count += 1;
	} else {
		_push_start_count = 0;
	}
	if ( _push_start_count < START_COUNT ) {
		return;
	}

	setState( STATE_PLAY );
	_push_start_count = 0;
}

void App::updateStatePlay( ) {
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

App::STATE App::getState( ) const {
	return _state;
}

void App::setState( STATE state ) {
	_state = state;
}

int App::getStartCount( ) const {
	return _push_start_count;
}

int App::getStartCountMax( ) const {
	return START_COUNT;
}