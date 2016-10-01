#include "Viewer.h"
#include "Status.h"
#include "Client.h"
#include "Ground.h"
#include "Camera.h"
#include "App.h"
#include "Drawer.h"
#include "Application.h"
#include "Animation.h"
#include "Player.h"
#include "Weapon.h"
#include "Bullet.h"

const double MODEL_SCALE_2015 = 0.008;
const double MODEL_SCALE_2016 = 0.06;
const double MODEL_SCALE_ALL = 1.0;

enum MODEL_MDL {
	MODEL_MDL_NONE,
	MODEL_MDL_FLOOR,
	MODEL_MDL_BACK_GROUND
};

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
	drawer->loadMDLModel( MODEL_MDL_FLOOR, "MapModel/floor01.mdl", "MapModel/floor01_DM.jpg" );
	drawer->loadMDLModel( MODEL_MDL_BACK_GROUND, "MapModel/bg.mdl", "MapModel/bg01_DM.jpg" );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WAIT,		"CaracterModel/hunter/player_hunter_wait.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WALK,		"CaracterModel/hunter/player_hunter_walk.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_ATTACK_FIRE,	"CaracterModel/hunter/player_hunter_attack_fire.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
	drawer->loadMV1Model( Animation::MOTION_PLAYER_DEAD,		"CaracterModel/hunter/player_hunter_dead.mv1", MODEL_SCALE_2016 * MODEL_SCALE_ALL );
}

void Viewer::update( ) {
	drawGroundModel( );
	drawPlayer( );
	drawStatus( );
	drawBackGround( );
	updateCamera( );
}

void Viewer::updateCamera( ) {
	CameraPtr camera = Camera::getTask( );
	Vector camera_pos = camera->getPos( );
	Vector camera_target = camera->getTarget( );
	ApplicationPtr fw = Application::getInstance( );
	fw->setCamera( camera_pos, camera_target );
}

void Viewer::drawGroundModel( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	DrawerPtr drawer = Drawer::getTask( );
	int width = ground->getWidth( );
	int height = ground->getHeight( );
	int tex_handle = 0;
	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			int idx = ground->getIdx( i, j );
			int csv_type = ground->getGroundData( idx );
			int type = app->convertCSVtoMap( csv_type );
			if ( type == MODEL_MDL_NONE ) {
				continue;
			}
			Vector pos =  Vector( i *  Ground::CHIP_WIDTH, j *  Ground::CHIP_HEIGHT, 0 );
			Vector max_pos = pos + Vector( Ground::CHIP_WIDTH, Ground::CHIP_HEIGHT, 0 );
			Vector min_pos = pos - Vector( Ground::CHIP_WIDTH, Ground::CHIP_HEIGHT, 0 );
			CameraPtr camera = Camera::getTask( );
			if ( !camera->isInScreen( max_pos ) && !camera->isInScreen( min_pos ) ) {
				continue;
			}
			Drawer::ModelMDL model_mdl = Drawer::ModelMDL( Vector(  i *  Ground::CHIP_WIDTH, j *  Ground::CHIP_HEIGHT, 0 ), type );
			drawer->setModelMDL( model_mdl );
		}
	}
}

void Viewer::drawStatus( ) {
	StatusPtr status = Status::getTask( );
	ClientPtr client = Client::getTask( );
	status->setInput( client->getClientData( ) );
	status->draw( );
}

void Viewer::drawBackGround( ) {
	AppPtr app = App::getTask( );
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::ModelMDL model_mdl = Drawer::ModelMDL( Vector(  0, 0, 0 ), MODEL_MDL_BACK_GROUND );
	drawer->setModelMDL( model_mdl );
}

void Viewer::drawPlayer( ) {
	AppPtr app = App::getTask( );
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		PlayerPtr player = app->getPlayer( i );
		if ( !player ) {
			continue;
		}
		if ( !player->isExpired( ) ) {
			continue;
		}

		AnimationPtr animation = player->getAnimation( );
		int motion = animation->getMotion( );
		double time = animation->getAnimTime( );
		Vector pos = player->getPos( );
		Vector dir = player->getDir( );

		DrawerPtr drawer = Drawer::getTask( );
		Drawer::ModelMV1 model = Drawer::ModelMV1( pos, dir, motion, time );
		drawer->setModelMV1( model );
	}
}
