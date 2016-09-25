#include "Application.h"
#include "Viewer.h"
#include "Log.h"
#include "Command.h"
#include "Drawer.h"

void main( ) {
	ApplicationPtr app = Application::getInstance( );
	app->setWindowSize( 640, 480 );
	ViewerPtr viewer = ViewerPtr( new Viewer );
	CommandPtr command = CommandPtr( new Command );
	LogPtr log = LogPtr( new Log );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resouce/" ) );

	app->addTask( Viewer::getTag( ), viewer );
	app->addTask( Command::getTag( ), command );
	app->addTask( Log::getTag( ), log );
	app->addTask( Drawer::getTag( ), drawer );
}