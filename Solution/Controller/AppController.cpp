#include "AppController.h"
#include "Device.h"
#include "Server.h"
#include "Network.h"
#include "Application.h"

const int PLAYER_START_HP = 1000;

AppControllerPtr AppController::getTask( ) {
	ApplicationPtr app = Application::getInstance( );
	return std::dynamic_pointer_cast< AppController >( app->getTask( getTag( ) ) );
}

AppController::AppController( ) {
	_scene = SCENE_CLEAR;
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
		data.player[ i ].exist = server->getData( ).player[ i ].exist;
	}
	if ( _scene != server->getData( ).scene ) {
		if ( server->getData( ).scene == SCENE_TITLE ){
			//ƒŠƒZƒbƒg
			for ( int i = 0; i < PLAYER_NUM; i++ ) {
				data.player[ i ].hp = PLAYER_START_HP;
				data.player[ i ].exist = NOT_EXIST;
			}
		}
		_scene = server->getData( ).scene;
	}

	switch ( _scene ) {
	case SCENE_TITLE:
		updateTitle( );
		break;
	case SCENE_PLAY:
		for ( int i = 0; i < PLAYER_NUM; i++ ) {
			if ( device->getPush( i ) > 0 && data.player[ i ].exist == NOT_EXIST ) {
				data.player[ i ].exist = EXIST;
			}
		}
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
	int exist_coiunt = 0;
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		if ( data.player[ i ].hp > 0 && data.player[ i ].exist == EXIST ) {
			is_alive = true;
		}
		if ( data.player[ i ].exist == EXIST ) {
			exist_coiunt++;
		}
	}
	if ( !is_alive && exist_coiunt > 0 ) {
		_scene = SCENE_GAMEOVER;
	}
}
