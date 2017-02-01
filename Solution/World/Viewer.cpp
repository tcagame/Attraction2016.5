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
#include "Party.h"
#include "Player.h"
#include "Weapon.h"
#include "Bullet.h"

const double MODEL_SCALE_2015 = 0.008;
const double MODEL_SCALE_2016 = 0.015;
const double MODEL_SCALE_ALL = 1.0;
const double MODEL_BACK_GROUND_SCALE = 0.01;

const int GRAPH_STRING_X = 1024;
const int GRAPH_STRING_Y = 1024;

const int GRAPH_UI_WINDOW_WIDTH = 160;
const int GRAPH_UI_WINDOW_HEIGHT = 120;

enum MODEL_MDL {
	MODEL_MDL_NONE,
	MODEL_MDL_FLOOR,
	MODEL_MDL_BACK_GROUND
};

enum GRAPH_ID {
	GRAPH_ID_MISSILE,
	GRAPH_ID_CLEAR_STRING,
	GRAPH_ID_GAMEOVER_STRING,
	GRAPH_ID_TITLE_STRING,
	GRAPH_ID_UI_WINDOW,
	GRAPH_ID_UI_LIFE
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
	drawer->loadMDLModel( MODEL_MDL_FLOOR,					  "MapModel/floor_collision.mdl", "MapModel/floor01_DM.jpg" );
	drawer->loadMV1Model( Animation::MV1_PLAYER,			  "CaracterModel/player/player.mv1" );
	drawer->loadMV1Model( Animation::MV1_PLAYER_WAIT,	      "CaracterModel/player/player_idle.mv1" );
	drawer->loadMV1Model( Animation::MV1_PLAYER_WALK,	      "CaracterModel/player/player_run.mv1" );
	drawer->loadMV1Model( Animation::MV1_PLAYER_ATTACK_BEGIN, "CaracterModel/player/player_attack_begin.mv1" );
	drawer->loadMV1Model( Animation::MV1_PLAYER_ATTACK_LOOP,  "CaracterModel/player/player_attack_loop.mv1" );
	drawer->loadMV1Model( Animation::MV1_PLAYER_ATTACK_END,	  "CaracterModel/player/player_attack_end.mv1" );
	drawer->loadMV1Model( Animation::MV1_PLAYER_DAMAGE,	      "CaracterModel/player/player_damage.mv1" );
	drawer->loadMV1Model( Animation::MV1_PLAYER_DEAD,	      "CaracterModel/player/player_dead.mv1" );


	drawer->loadMV1Model( Animation::MV1_BACK_GROUND,	"MapModel/background.mv1" );
	drawer->loadMV1Model( Animation::MV1_GOBLIN_WAIT,	"EnemyModel/goblin/enemy_goblin_wait.mv1" );
	drawer->loadMV1Model( Animation::MV1_MINOTAUR,            "EnemyModel/minotaur/enemy_minotaur.mv1" );
	drawer->loadMV1Model( Animation::MV1_MINOTAUR_WAIT,       "EnemyModel/minotaur/enemy_minotaur_wait.mv1" );
	drawer->loadMV1Model( Animation::MV1_MINOTAUR_WALK,	      "EnemyModel/minotaur/enemy_minotaur_walk.mv1" );
	drawer->loadMV1Model( Animation::MV1_MINOTAUR_SMASH,	  "EnemyModel/minotaur/enemy_minotaur_smash.mv1" );
	drawer->loadMV1Model( Animation::MV1_MINOTAUR_DAMAGE,	  "EnemyModel/minotaur/enemy_minotaur_damage.mv1" );
	drawer->loadMV1Model( Animation::MV1_MINOTAUR_DEAD,	      "EnemyModel/minotaur/enemy_minotaur_dead.mv1" );


	drawer->loadGraph( GRAPH_ID_MISSILE,		"Billboard/missile.png" );
	drawer->loadGraph( GRAPH_ID_CLEAR_STRING,	"Images/clear.png" );
	drawer->loadGraph( GRAPH_ID_GAMEOVER_STRING,"Images/dead.png" );
	drawer->loadGraph( GRAPH_ID_TITLE_STRING,	"Images/title.png" );
	drawer->loadGraph( GRAPH_ID_UI_WINDOW,		"UI/status_window.png" );
	drawer->loadGraph( GRAPH_ID_UI_LIFE,		"UI/lifenumber.png" );
}

void Viewer::update( ) {
	AppPtr app = App::getTask( );
	unsigned scene = app->getScene( );
	switch ( scene ) {
	case SCENE_TITLE:
		drawTitle( );
		break;
	case SCENE_PLAY:
		drawGroundModel( );
		drawPlayer( );
		drawBullet( );
		drawEnemy( );
		drawUI( );
		updateCamera( );
		break;
	case SCENE_CLEAR:
		drawClear( );
		break;
	case SCENE_GAMEOVER:
		drawGameover( );
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

void Viewer::drawEnemy( ) {
	AppPtr app = App::getTask( );
	CohortPtr cohort = app->getCohort( );
	if ( !cohort ) {
		return;
	}
	int max_enemy = cohort->getMaxNum( );
	for ( int i = 0; i < max_enemy; i++ ) {
		EnemyPtr enemy = cohort->getEnemy( i );
		if ( !enemy ) {
			continue;
		}
		AnimationPtr animation = enemy->getAnimation( );
		int motion = animation->getMotion( );
		int mesh = animation->getMesh( );
		int time = ( int )animation->getAnimTime( );
		Vector pos = enemy->getPos( );

		Vector dir = enemy->getDir( );

		double angle = dir.angle( Vector( 0, 1, 0 ) );
		Vector axis = dir.cross( Vector( 0, -1, 0 ) );
		if ( dir == Vector( 0, -1, 0 ) ) {
			axis = Vector( 0, 0, 1 );
		}

		Matrix mat_dir = Matrix::makeTransformRotation( axis, angle );
		Matrix mat_rot = Matrix::makeTransformRotation( Vector( 1.0, 0.0, 0.0 ), PI / 2 );
		Matrix mat_scale = Matrix::makeTransformScaling( Vector( MODEL_SCALE_2016, MODEL_SCALE_2016, MODEL_SCALE_2016 ) );
		Matrix mat_trans = Matrix::makeTransformTranslation( pos );

		Matrix mat = mat_dir * mat_rot * mat_scale;
		mat = mat * mat_trans;

		DrawerPtr drawer = Drawer::getTask( );
		Drawer::ModelMV1 model = Drawer::ModelMV1( mat, mesh, motion, time );
		drawer->setModelMV1( model );
		drawer->drawString( 0, i * 10, "Hp:%d", enemy->getStatus( ).hp );
	}
	
}

void Viewer::drawPlayer( ) {
	AppPtr app = App::getTask( );
	PartyPtr party = app->getParty( );
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		PlayerPtr player = party->getPlayer( i );
		if ( !player ) {
			continue;
		}
		if ( !player->isExpired( ) ) {
			continue;
		}

		AnimationPtr animation = player->getAnimation( );
		int motion = animation->getMotion( );
		int mesh = animation->getMesh( );
		int time = ( int )animation->getAnimTime( );
		Vector pos = player->getPos( );

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

		Matrix mat = mat_dir * mat_rot * mat_scale;
		mat = mat * mat_trans;

		DrawerPtr drawer = Drawer::getTask( );
		Drawer::ModelMV1 model = Drawer::ModelMV1( mat, mesh, motion, time );
		drawer->setModelMV1( model );
	}
}

void Viewer::drawBullet( ) {
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < weapon->getBulletNum( ); i++ ) {
		BulletPtr bullet = weapon->getBullet( i );
		Bullet::TYPE type = bullet->getType( );
		Drawer::Billboard billboad;
		billboad.res = type;
		billboad.pos = bullet->getPos( );
		billboad.size = 1.0;
		billboad.blend = Drawer::BLEND_NONE;
		billboad.ratio = 0;
		drawer->setBillboard( billboad );
	}
}

void Viewer::drawTitle( ) {
	ApplicationPtr app = Application::getInstance( );
	DrawerPtr drawer = Drawer::getTask( );
	//READY文字
	Drawer::Sprite sprite;
	sprite.res = GRAPH_ID_TITLE_STRING;
	sprite.trans.sx = app->getWindowWidth( ) / 2 - GRAPH_STRING_X / 2;
	sprite.trans.sy = app->getWindowHeight( ) / 2 - GRAPH_STRING_Y / 2;
	sprite.trans.tw = -1;
	sprite.blend = Drawer::BLEND_NONE;
	drawer->setSprite( sprite );
}

void Viewer::drawClear( ) {
	ApplicationPtr app = Application::getInstance( );
	DrawerPtr drawer = Drawer::getTask( );
	//READY文字
	Drawer::Sprite sprite;
	sprite.res = GRAPH_ID_CLEAR_STRING;
	sprite.trans.sx = app->getWindowWidth( ) / 2 - GRAPH_STRING_X / 2;
	sprite.trans.sy = app->getWindowHeight( ) / 2 - GRAPH_STRING_Y / 2;
	sprite.trans.tw = -1;
	sprite.blend = Drawer::BLEND_NONE;
	drawer->setSprite( sprite );
}

void Viewer::drawGameover( ) {
	ApplicationPtr app = Application::getInstance( );
	DrawerPtr drawer = Drawer::getTask( );
	//READY文字
	Drawer::Sprite sprite;
	sprite.res = GRAPH_ID_GAMEOVER_STRING;
	sprite.trans.sx = app->getWindowWidth( ) / 2 - GRAPH_STRING_X / 2;
	sprite.trans.sy = app->getWindowHeight( ) / 2 - GRAPH_STRING_Y / 2;
	sprite.trans.tw = -1;
	sprite.blend = Drawer::BLEND_NONE;
	drawer->setSprite( sprite );
}

void Viewer::drawUI( ) {
	ApplicationPtr app = Application::getInstance( );
	AppPtr app_p = App::getTask( );
	PartyPtr party = app_p->getParty( );
	DrawerPtr drawer = Drawer::getTask( );
	int pitch = ( app->getWindowWidth( ) - GRAPH_UI_WINDOW_WIDTH * 4 ) / 5;
	int sy = app->getWindowHeight( ) - GRAPH_UI_WINDOW_HEIGHT;
	int sx = pitch;
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		PlayerPtr playre = party->getPlayer( i );
		{//ウィンドウ
			Drawer::Sprite sprite;
			sprite.res = GRAPH_ID_UI_WINDOW;
			sprite.trans.sx = app->getWindowWidth( ) / 2 - GRAPH_STRING_X / 2;
			sprite.trans.sy = sy;
			sprite.trans.sx = sx;
			sprite.trans.tw = -1;
			sprite.blend = Drawer::BLEND_NONE;
			drawer->setSprite( sprite );
		}
		{//HP文字
			std::string str_num = std::to_string( playre->getStatus( ).hp );
			int string_y = GRAPH_UI_WINDOW_HEIGHT - 92;
			int digits = str_num.size( );
			for ( int i = 0; i < digits; i++ ) {
				const char num_c = str_num[ i ];
				int num = std::atoi( &num_c );
				Drawer::Sprite sprite;
				sprite.res = GRAPH_ID_UI_LIFE;
				sprite.trans.sx = app->getWindowWidth( ) / 2 - GRAPH_STRING_X / 2;
				sprite.trans.sy = sy + string_y;
				sprite.trans.sx = sx + GRAPH_UI_WINDOW_WIDTH - 32 - 20 * ( digits - i );
				sprite.trans.tx = 32 * num;
				sprite.trans.ty = 0;
				sprite.trans.th = 64;
				sprite.trans.tw = 32;
				sprite.blend = Drawer::BLEND_NONE;
				drawer->setSprite( sprite );
			}
		}
		sx += GRAPH_UI_WINDOW_WIDTH + pitch;
	}
}