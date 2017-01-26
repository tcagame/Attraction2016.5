#include "Viewer.h"
#include "Status.h"
#include "Client.h"
#include "Cohort.h"
#include "Enemy.h"
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
	drawer->loadMV1Model( Animation::MOTION_PLAYER_WAIT,		"CaracterModel/hunter/player_hunter_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_WAIT,		"EnemyModel/goblin/enemy_goblin_wait.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_WALK,		"EnemyModel/goblin/enemy_goblin_walk.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_ATTACK,	    "EnemyModel/goblin/enemy_goblin_attack.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_DAMAGE,		"EnemyModel/goblin/enemy_goblin_damage.mv1" );
	drawer->loadMV1Model( Animation::MOTION_GOBLIN_DEAD,		"EnemyModel/goblin/enemy_goblin_dead.mv1" );

	drawer->loadGraph( 0, "Billboard/missile.png" );
}

void Viewer::update( ) {
	drawGroundModel( );
	drawPlayer( );
	drawStatus( );
	drawBackGround( );
	drawEnemy( );
	drawBullet( );
	updateCamera( );
}

void Viewer::updateCamera( ) {
	CameraPtr camera = Camera::getTask( );
	Vector camera_pos = camera->getPos( );
	Vector camera_target = camera->getTarget( );
	DrawerPtr drawer = Drawer::getTask( );
	drawer->setCamera( camera_pos, camera_target );
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
	PlayerPtr player = app->getPlayer( );
	if ( !player ) {
		return;
	}
	if ( !player->isExpired( ) ) {
		return;
	}

	AnimationPtr animation = player->getAnimation( );
	int motion = animation->getMotion( );
	double time = animation->getAnimTime( );
	Vector pos = player->getPos( );
	Vector dir = player->getDir( );

	DrawerPtr drawer = Drawer::getTask( );
	Drawer::ModelMV1 model = Drawer::ModelMV1( motion, time );
	drawer->setModelMV1( model );
}

void Viewer::drawEnemy ( ) {
	AppPtr app = App::getTask( );
	CohortPtr cohort = app->getCohort( );
	int num = cohort->getMaxNum( );
	for ( int i = 0; i < num; i++ ) {
		EnemyPtr enemy = cohort->getEnemy( i );
		if ( !enemy ) {
			continue;
		}
		if ( !enemy->isExpired( ) ) {
			continue;
		}

		AnimationPtr animation = enemy->getAnimation( );
		int motion = animation->getMotion( );
		double time = animation->getAnimTime( );
		Vector pos = enemy->getPos( );
		Vector dir = enemy->getDir( );

		DrawerPtr drawer = Drawer::getTask( );
		Drawer::ModelMV1 model = Drawer::ModelMV1( pos, dir, motion, time );
		drawer->setModelMV1( model );
	}
}

void Viewer::drawBullet( ) {
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < weapon->getBulletNum( ); i++ ) {
		BulletPtr bullet = weapon->getBullet( i );
		Drawer::Billboard billboad;
		billboad.res = 0;
		billboad.pos = bullet->getPos( );
		billboad.size = 0.5;
		billboad.blend = Drawer::BLEND_NONE;
		billboad.ratio = 0;
		drawer->setBillboard( billboad );
	}
}