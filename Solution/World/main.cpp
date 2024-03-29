#include "Application.h"
#include "App.h"
#include "Viewer.h"
#include "Drawer.h"
#include "Client.h"
#include "Camera.h"


void main( ) {
	ApplicationPtr application = Application::getInstance( );
	AppPtr app = AppPtr( new App( ) );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource" ) );
	ClientPtr client = ClientPtr( new Client );
	ViewerPtr viewer = ViewerPtr( new Viewer );
	CameraPtr camera = CameraPtr( new Camera );

	application->addTask( App::getTag( ), app );
	application->addTask( Drawer::getTag( ), drawer );
	application->addTask( Viewer::getTag( ), viewer );
	application->addTask( Client::getTag( ), client );
	application->addTask( Camera::getTag( ), camera );
}