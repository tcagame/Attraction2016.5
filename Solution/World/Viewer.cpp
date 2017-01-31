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
const double MODEL_BACK_GROUND_SCALE = 0.01;

const int GRAPH_STRING_X = 1024;
const int GRAPH_STRING_Y = 1024;

enum MODEL_MDL {
	MODEL_MDL_NONE,
	MODEL_MDL_FLOOR,
	MODEL_MDL_BACK_GROUND
};

enum GRAPH_ID {
	GRAPH_ID_CLEAR_STRING,
	GRAPH_ID_GAMEOVER_STRING,
	GRAPH_ID_TITLE_STRING,
	GRAPH_ID_MISSILE
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
	drawer->loadMDLModel( MODEL_MDL_FLOOR,				"MapModel/floor.mdl", "MapModel/floor01_DM.jpg" );
	drawer->loadMV1Model( Animation::MV1_PLAYER,		"CaracterModel/player/player.mv1" );
	drawer->loadMV1Model( Animation::MV1_PLAYER_WAIT,	"CaracterModel/player/player_idle.mv1" );
	drawer->loadMV1Model( Animation::MV1_PLAYER_WALK,	"CaracterModel/player/player_run.mv1" );
	drawer->loadMV1Model( Animation::MV1_BACK_GROUND,	"MapModel/background.mv1" );
	drawer->loadMV1Model( Animation::MV1_GOBLIN_WAIT,	"EnemyModel/goblin/enemy_goblin_wait.mv1" );

	drawer->loadGraph( GRAPH_ID_MISSILE,		"Billboard/missile.png" );
	drawer->loadGraph( GRAPH_ID_CLEAR_STRING,	"Images/clear.png" );
	drawer->loadGraph( GRAPH_ID_GAMEOVER_STRING,"Images/dead.png" );
	drawer->loadGraph( GRAPH_ID_TITLE_STRING,	"Images/title.png" );
}

void Viewer::update( ) {
	AppPtr app = App::getTask( );
	unsigned scene = app->getScene( );
	switch ( scene ) {
	case SCENE_TITLE:
		drawTitle( );
		break;
	case SCENE_PLAY:
		//drawGroundModel( );
		drawPlayer( );
		drawBackGround( );
		drawBullet( );
		updateCamera( );
		break;
	case SCENE_CLEAR:

		break;
	case SCENE_GAMEOVER:

		break;
	}
}

void Viewer::updateCamera( ) {
	CameraPtr camera = Camera::getTask( );
	Vector camera_pos = camera->getPos( );
	Vector camera_target = camera->getTarget( );
	DrawerPtr drawer = Drawer::getTask( );
	drawer->setCamera( camera_pos, camera_target );
}

void Viewer::drawGroundModel( ) {
	//AppPtr app = App::getTask( );
	//GroundPtr ground = app->getGround( );
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::ModelMDL model_mdl = Drawer::ModelMDL( Vector( 0, 0, 0 ), MODEL_MDL_FLOOR );
	drawer->setModelMDL( model_mdl );
	/*int width = ground->getWidth( );
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
	}*/
}

void Viewer::drawBackGround( ) {
	AppPtr app = App::getTask( );
	DrawerPtr drawer = Drawer::getTask( );

	Vector pos = Vector( 0, 0, 0 );
//	Matrix mat_dir = Matrix::makeTransformRotation( Vector( 0.0, 0.0, 1.0 ), );
	Matrix mat_rot = Matrix::makeTransformRotation( Vector( 1.0, 0.0, 0.0 ), PI / 2 );
	Matrix mat_scale = Matrix::makeTransformScaling( Vector( MODEL_BACK_GROUND_SCALE, MODEL_BACK_GROUND_SCALE, MODEL_BACK_GROUND_SCALE ) );
	Matrix mat_trans = Matrix::makeTransformTranslation( pos );

	Matrix mat = mat_trans * mat_rot * mat_scale;

	Drawer::ModelMV1 model = Drawer::ModelMV1( mat, Animation::MV1_BACK_GROUND, Animation::MV1_BACK_GROUND, 0 );
	drawer->setModelMV1( model );
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
	int mesh = animation->getMesh( );
	int time = ( int )animation->getAnimTime( );
	Vector pos = player->getPos( );
	double z = pos.y;
	pos.y = pos.z;
	pos.z = z;
	Vector dir = player->getDir( );

	double angle = dir.angle( Vector( 0, 1, 0 ) );
	Vector axis = dir.cross( Vector( 0, -1, 0 ) );
	if ( dir == Vector( 0, -1, 0 ) ) {
		axis = Vector( 0, 0, 1 );
	}

	Matrix mat_dir = Matrix::makeTransformRotation( axis, angle );
	Matrix mat_rot = Matrix::makeTransformRotation( Vector( 1.0, 0.0, 0.0 ), PI / 2 );
	Matrix mat_scale = Matrix::makeTransformScaling( Vector( 0.1, 0.1, 0.1 ) );
	Matrix mat_trans = Matrix::makeTransformTranslation( pos );

	Matrix mat = mat_dir * mat_trans * mat_rot * mat_scale;

	DrawerPtr drawer = Drawer::getTask( );
	Drawer::ModelMV1 model = Drawer::ModelMV1( mat, mesh, motion, time );
	drawer->setModelMV1( model );
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

void Viewer::drawTitle( ) {
	ApplicationPtr app = Application::getInstance( );
	DrawerPtr drawer = Drawer::getTask( );
	//READY•¶Žš
	Drawer::Sprite sprite;
	sprite.res = GRAPH_ID_TITLE_STRING;
	sprite.trans.sx = app->getWindowWidth( ) / 2 - GRAPH_STRING_X / 2;
	sprite.trans.sy = app->getWindowHeight( ) / 2 - GRAPH_STRING_Y / 2;
	sprite.trans.tw = -1;
	sprite.blend = Drawer::BLEND_NONE;
	drawer->setSprite( sprite );
}