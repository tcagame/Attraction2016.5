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
}


AppController::~AppController( ) {
}


void AppController::initialize( ) {
}

void AppController::update( ) {
	DevicePtr device = Device::getTask( );
	ServerPtr server = Server::getTask( );

	CLIENTDATA data;
	for ( int i = 0; i < MAX_MACHINE; i++ ) {
		data.player[ i ].x = device->getDirX( i );
		data.player[ i ].y = device->getDirY( i );
		data.player[ i ].button = device->getButton( i );
	}
	server->sendStatus( data );
}

void AppController::finalize( ) {
}
