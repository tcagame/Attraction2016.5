#include "Status.h"
#include "TableDrawer.h"
#include "Application.h"

Status::Status( ) {
	TableDrawer::FORM form;
	form.title = "Status";
	form.x = 10;
	form.y = 10;
	form.rows = 4;
	form.cols = 4;
	form.col[ 0 ] = 200;
	form.col[ 1 ] = 100;
	form.col[ 2 ] = 100;
	form.col[ 3 ] = 150;
	_td = TableDrawerPtr( new TableDrawer( form ) );

	_td->setCell( 0, 0 , "PLAYER:1" );
	_td->setCell( 0, 1 , "PLAYER:2" );
	_td->setCell( 0, 2 , "PLAYER:3" );
	_td->setCell( 0, 3 , "PLAYER:4" );
	for ( int i = 0; i < 4; i++ ) {
		_data.player[ i ].x = 0;
		_data.player[ i ].y = 0;
	}
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
	for ( int i = 0; i < 4; i++ ) {
		_td->setCell( 1, i, "x:" + std::to_string( _data.player[ i ].x ) );
		_td->setCell( 2, i, "y:" + std::to_string( _data.player[ i ].y ) );
	}
	for ( int i = 0; i < 4; i++ ) {
		_data.player[ i ].x = 0;
		_data.player[ i ].y = 0;
	}
}
void Status::setInput( CLIENTDATA data ) {
	_data = data;
}