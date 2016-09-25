#include "TableDrawerTest.h"
#include "Status.h"
#include "TableDrawer.h"
#include "Application.h"

TableDrawerTestPtr TableDrawerTest::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< TableDrawerTest >( fw->getTask( TableDrawerTest::getTag( ) ) );
}

TableDrawerTest::TableDrawerTest( ) {
	_status = StatusPtr( new Status( ) );
}


TableDrawerTest::~TableDrawerTest( ) {
}

void TableDrawerTest::update( ) {
	//_td_test->draw( );
	_status->draw( );
}
