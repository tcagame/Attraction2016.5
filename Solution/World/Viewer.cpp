#include "Viewer.h"
<<<<<<< HEAD
=======
#include "Status.h"
#include "Client.h"
>>>>>>> f8b8d30751081dca23fa85a8ae9c563109d6bf09
#include "Application.h"
#include "Status.h"
#include "App.h"
#include "Ground.h"
#include "Drawer.h"

ViewerPtr Viewer::getTask( ) {
	ApplicationPtr app = Application::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( app->getTask( getTag( ) ) );
}

Viewer::Viewer( ) {
}


Viewer::~Viewer( ) {
}

void Viewer::initialize( ) {
	DrawerPtr drawer =Drawer::getTask( );
	drawer->loadMDLModel( 1, "MapModel/floor01.mdl", "MapModel/floor01_DM.jpg" );
}

void Viewer::update( ) {
	drawMap( );
	drawStatus( );
}

void Viewer::drawStatus( ) {
	StatusPtr status = Status::getTask( );
	ClientPtr client = Client::getTask( );
	status->setInput( client->getClientData( ) );
	status->draw( );
}

void Viewer::drawMap( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	int width = ground->getWidth( );
	int height = ground->getHeight( );
	int tex_handle = 0;

	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			int idx = ground->getIdx( i, j );
			int type = ground->getGroundData( idx );
			Drawer::ModelMDL model_mdl = Drawer::ModelMDL( Vector(  i *  Ground::CHIP_WIDTH, j *  Ground::CHIP_HEIGHT, 0 ), type );
			drawer->setModelMDL( model_mdl );
		}
	}
}