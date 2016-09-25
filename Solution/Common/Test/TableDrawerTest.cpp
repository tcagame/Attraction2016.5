#include "TableDrawerTest.h"
#include "TableDrawer.h"
#include "Application.h"

TableDrawerTestPtr TableDrawerTest::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< TableDrawerTest >( fw->getTask( TableDrawerTest::getTag( ) ) );
}

TableDrawerTest::TableDrawerTest( ) {
	TableDrawer::FORM form;
	form.title = "Status";
	form.x = 10;
	form.y = 10;
	form.rows = 7;
	form.cols = 4;
	form.col[ 0 ] = 200;
	form.col[ 1 ] = 100;
	form.col[ 2 ] = 100;
	form.col[ 3 ] = 150;
	_td_test = TableDrawerPtr( new TableDrawer( form ) );

	_td_test->setCell( 0, 0 , "PLAYER(KNIGHT)" );
	_td_test->setCell( 0, 1 , "PLAYER(HUNTER)" );
	_td_test->setCell( 0, 2 , "PLAYER(MONK)" );
	_td_test->setCell( 0, 3 , "PLAYER(WIDTH)" );
	_td_test->setCell( 0, 4 , "ETUDE(RED)" );
	_td_test->setCell( 0, 5 , "ETUDE(GREEN)" );
	_td_test->setCell( 0, 6 , "ETUDE(BLUE)" );
}


TableDrawerTest::~TableDrawerTest( ) {
}

void TableDrawerTest::update( ) {
	_td_test->draw( );
}
