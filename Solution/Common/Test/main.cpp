#include "Application.h"
#include "Drawer.h"
#include "TableDrawerTest.h"

void main( ) {
	ApplicationPtr fw = Application::getInstance ( );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource" ) );
	TableDrawerTestPtr td_test = TableDrawerTestPtr( new TableDrawerTest );

	fw->addTask( Drawer::getTag( ), drawer );
	fw->addTask( TableDrawerTest::getTag( ), td_test );
}