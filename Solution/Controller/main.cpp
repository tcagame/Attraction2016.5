#include "Framework.h"
#include "Viewer.h"
#include "Server.h"
#include "Drawer.h"

void main( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = ViewerPtr( new Viewer );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resouce/" ) );
	
	fw->addTask( Viewer::getTag( ), viewer );
	fw->addTask( Drawer::getTag( ), drawer );
}