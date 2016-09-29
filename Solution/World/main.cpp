#include "Application.h"
#include "App.h"
#include "Viewer.h"
#include "Status.h"
#include "Drawer.h"
#include "Client.h"


void main( ) {
	ApplicationPtr application = Application::getInstance( );
	AppPtr app = AppPtr( new App( ) );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource" ) );
	StatusPtr status = StatusPtr( new Status );
<<<<<<< HEAD
	ViewerPtr viewer = ViewerPtr( new Viewer );

	application->addTask( App::getTag( ), app );
	application->addTask( Drawer::getTag( ), drawer );
	application->addTask( Status::getTag( ), status );
	application->addTask( Viewer::getTag( ), viewer );
=======
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource/" ) );
	ClientPtr client = ClientPtr( new Client );


	app->addTask( Status::getTag( ), status );
	app->addTask( Viewer::getTag( ), viewer );
	app->addTask( Drawer::getTag( ), drawer );
	app->addTask( Client::getTag( ), client );
>>>>>>> f8b8d30751081dca23fa85a8ae9c563109d6bf09
}