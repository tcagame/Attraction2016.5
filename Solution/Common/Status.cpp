#include "Status.h"
#include "TableDrawer.h"
#include "Application.h"
#include "Device.h"
#include "Server.h"

Status::Status( ) {
	TableDrawer::FORM form;
	form.title = "Status";
	form.x = 10;
	form.y = 10;
	form.rows = 5;
	form.cols = 6;
	form.col[ 0 ] = 150;
	form.col[ 1 ] = 150;
	form.col[ 2 ] = 100;
	form.col[ 3 ] = 100;
	form.col[ 4 ] = 100;
	form.col[ 5 ] = 150;
	_td = TableDrawerPtr( new TableDrawer( form ) );

	_td->setCell( 0, 0 , "PLAYER_NUM" );
	_td->setCell( 1, 0 , "CONNECT_DEVICE" );
	_td->setCell( 2, 0 , "HP" );
	_td->setCell( 3, 0 , "DIR_X" );
	_td->setCell( 4, 0 , "DIR_Y" );
	_td->setCell( 5, 0 , "BUTTON" );

	_td->setCell( 0, 1 , "PLAYER:1" );
	_td->setCell( 0, 2 , "PLAYER:2" );
	_td->setCell( 0, 3 , "PLAYER:3" );
	_td->setCell( 0, 4 , "PLAYER:4" );
}

StatusPtr Status::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< Status >( fw->getTask( Status::getTag( ) ) );
}

Status::~Status( ) {

}

void Status::draw( ) {
	_td->draw( );
}

void Status::update( ) {
	DevicePtr device = Device::getTask( );
	ServerPtr server = Server::getTask( );
	CLIENTDATA data = server->getData( );
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		if ( i < device->getDeviceNum( ) ) {
			_td->setCell( 1, i + 1, "CONNECTING" );
		} else {
			_td->setCell( 1, i + 1, "DISCONNECT" );
		}
		_td->setCell( 2, i + 1, std::to_string( data.player[ i ].hp ) );
		_td->setCell( 3, i + 1, std::to_string( data.player[ i ].x ) );
		_td->setCell( 4, i + 1, std::to_string( data.player[ i ].y ) );
		_td->setCell( 5, i + 1, getButtonBinary( data.player[ i ].button ) );
	}
}

std::string Status::getButtonBinary( unsigned char button_key ) {
	std::string res; 
	for ( int i = 0; i < 8; i++ ) {
		if ( ( button_key & 1 << ( 7 - i ) ) > 0 ) {
			res += "1";
		} else {
			res += "0";
		}
	}
	return res;
}