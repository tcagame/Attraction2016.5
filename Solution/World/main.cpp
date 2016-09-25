#include "Application.h"
#include "Viewer.h"
#include "Status.h"
#include "Drawer.h"

void main( ) {
	ApplicationPtr app = Application::getInstance( );
	ViewerPtr viewer = ViewerPtr( new Viewer );
	StatusPtr status = StatusPtr( new Status );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource/" ) );

	app->addTask( Status::getTag( ), status );
	app->addTask( Viewer::getTag( ), viewer );
	app->addTask( Drawer::getTag( ), drawer );
}