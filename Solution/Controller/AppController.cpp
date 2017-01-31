#include "AppController.h"
#include "Device.h"
#include "Server.h"
#include "Network.h"
#include "Application.h"


AppControllerPtr AppController::getTask( ) {
	ApplicationPtr app = Application::getInstance( );
	return std::dynamic_pointer_cast< AppController >( app->getTask( getTag( ) ) );
}

AppController::AppController( ) {
	_scene = SCENE_TITLE;
}


AppController::~AppController( ) {
}


void AppController::initialize( ) {
}

void AppController::update( ) {
	DevicePtr device = Device::getTask( );
	ServerPtr server = Server::getTask( );
	CLIENTDATA data;
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		data.player[ i ].x = device->getDirX( i );
		data.player[ i ].y = device->getDirY( i );
		data.player[ i ].hp = server->getData( ).player[ i ].hp;
		data.player[ i ].button = device->getButton( i );
	}
	_scene = server->getData( ).scene;
	switch ( _scene ) {
	case SCENE_TITLE:
		updateTitle( );
		break;
	case SCENE_PLAY:
		updatePlay( data );
		break;
	case SCENE_CLEAR:
	case SCENE_GAMEOVER:
		break;
	}
	data.scene = _scene;
	server->sendStatus( data );
}

void AppController::finalize( ) {
}

void AppController::updateTitle( ) {
	DevicePtr device = Device::getTask( );
	bool input_button = false;
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		if ( device->getPush( i ) > 0 ) {
			input_button = true;
		}
	}
	if ( input_button ) {
		_scene = SCENE_PLAY;
	}
}

void AppController::updatePlay( CLIENTDATA data ) {
	bool is_alive = false;
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		if ( data.player[ i ].hp > 0 ) {
			is_alive = true;
		}
	}
	if ( !is_alive ) {
		_scene = SCENE_GAMEOVER;
	}
}
