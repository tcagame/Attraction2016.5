#include "Application.h"
#include "App.h"
#include "Viewer.h"
#include "Status.h"
#include "Drawer.h"

void main( ) {
	ApplicationPtr application = Application::getInstance( );
	AppPtr app = AppPtr( new App( ) );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource" ) );
	StatusPtr status = StatusPtr( new Status );
	ViewerPtr viewer = ViewerPtr( new Viewer );

	application->addTask( App::getTag( ), app );
	application->addTask( Drawer::getTag( ), drawer );
	application->addTask( Status::getTag( ), status );
	application->addTask( Viewer::getTag( ), viewer );
}