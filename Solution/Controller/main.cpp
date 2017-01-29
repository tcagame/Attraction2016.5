#include "Application.h"
#include "Viewer.h"
#include "Log.h"
#include "Keyboard.h"
#include "Device.h"
#include "Command.h"
#include "Drawer.h"
#include "Status.h"
#include "Server.h"
#include "AppController.h"

void main( ) {
	ApplicationPtr app = Application::getInstance( );
	ViewerPtr viewer = ViewerPtr( new Viewer );
	KeyboardPtr keyboard = KeyboardPtr( new Keyboard );
	DevicePtr device = DevicePtr( new Device );
	CommandPtr command = CommandPtr( new Command );
	LogPtr log = LogPtr( new Log );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource/" ) );
	StatusPtr status = StatusPtr( new Status );
	ServerPtr server = ServerPtr( new Server );
	AppControllerPtr app_controller = AppControllerPtr( new AppController );

	app->addTask( Viewer::getTag( ), viewer );
	app->addTask( Keyboard::getTag( ), keyboard );
	app->addTask( Device::getTag( ), device );
	app->addTask( Command::getTag( ), command );
	app->addTask( Log::getTag( ), log );
	app->addTask( Drawer::getTag( ), drawer );
	app->addTask( Status::getTag( ), status );
	app->addTask( Server::getTag( ), server );
	app->addTask( AppController::getTag( ), app_controller );
}