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

	_td->setCell( 0, 0 , "PLAYER(KNIGHT)" );
	_td->setCell( 0, 1 , "PLAYER(HUNTER)" );
	_td->setCell( 0, 2 , "PLAYER(MONK)" );
	_td->setCell( 0, 3 , "PLAYER(WIDTH)" );
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

}