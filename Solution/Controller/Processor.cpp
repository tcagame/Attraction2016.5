#include "Processor.h"
#include "Application.h"
#include "Status.h"
#include "Device.h"
#include "Server.h"

const int PLAYER_START_HP = 1000;//‚Æ‚è‚ ‚¦‚¸‚±‚±‚Å’è‹`

ProcessorPtr Processor::getTask( ) {
	ApplicationPtr app = Application::getInstance( );
	return std::dynamic_pointer_cast< Processor >( app->getTask( getTag( ) ) );
}

Processor::Processor( ) {
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		_data.player[ i ].hp = PLAYER_START_HP;
		_data.player[ i ].x = 0;
		_data.player[ i ].y = 0;
		_data.player[ i ].button = 0;
	}
}


Processor::~Processor( ) {
}

void Processor::update( ) {
	setInputDevice( );
	ServerPtr server = Server::getTask( );
	server->setData( _data );
}

void Processor::setInputDevice( ) {
	DevicePtr device = Device::getTask( );

	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		_data.player[ i ].x = device->getDirX( i );
		_data.player[ i ].y = device->getDirY( i );
		_data.player[ i ].button = device->getButton( i );
	}
	StatusPtr status = Status::getTask( );
	status->setInput( _data );
}