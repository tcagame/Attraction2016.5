#include "App.h"
#include "Player.h"
#include "Cohort.h"
#include "Ground.h"
#include "GroundModel.h"
#include "Field.h"
#include "Weapon.h"
#include "Device.h"
#include "Application.h"
#include "Client.h"

const std::string DIRECTORY = "../Resource/";
const std::string MODEL_NAME_LIST [] {
	"none",
	"floor01"
};
const int RESET_COUNT = 30;
const int START_COUNT = 60;
const int STRING_BUF = 256;

AppPtr App::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< App >( fw->getTask( App::getTag( ) ) );
}

App::App( ) {
<<<<<<< HEAD
	_ground = GroundPtr( new Ground( DIRECTORY + "CSV/map.csv" ) );
	_ground_model = GroundModelPtr( new GroundModel );
	_ground_model->loadModelData( 0, 0, DIRECTORY + "MapModel/floor01.mdl" );
=======
	_state = STATE_PLAY;//デバッグ用
>>>>>>> 09fc67b1d228f45e0935b1a75a9a6724dc0dba28
}

App::~App( ) {

}

void App::initialize( ) {
	std::string filepath = DIRECTORY + "CSV/";
	_ground = GroundPtr( new Ground( filepath + "map.csv" ) );//マップデータ
	_ground_model = GroundModelPtr( new GroundModel( ) );
	_field = FieldPtr( new Field( ) );
	_weapon = WeaponPtr( new Weapon( ) );
	Character::STATUS status = Character::STATUS( 100000, 100, 0.5 );
	_player = PlayerPtr( new Player( 2, status ) );
	_player->create( Vector( 0, 0 ) );
	std::string floor_model_path = DIRECTORY + "MapModel/floor_collision.mdl";
	_ground_model->loadModelData( 0, 0, floor_model_path );
	_cohort = CohortPtr( new Cohort( ) );

	
}

void App::update( ) {
	changeScene( );

	switch ( _scene ) {
	case SCENE_TITLE:
		updateSceneTitle( );
		break;
	case SCENE_PLAY:
		updateScenePlay( );
		break;
	case SCENE_CLEAR:
		updateSceneClear( );
		break;
	case SCENE_GAMEOVER:
		updateSceneGameover( );
		break;
	}
}

void App::changeScene( ) {
	ClientPtr client = Client::getTask( );
	CLIENTDATA data = client->getClientData( );

	if ( _scene == data.scene ) {
		return;
	}

	// 各シーンの初期化をおこなう
	switch( data.scene ) {
	case SCENE_TITLE:
		initSceneTitle( );
		break;
	case SCENE_PLAY:
		initScenePlay( );
		break;
	case SCENE_CLEAR:
		initSceneClear( );
		break;
	case SCENE_GAMEOVER:
		initSceneGameover( );
		break;
	default:
		return;
		break;
	}

	_scene = data.scene;
}

void App::initSceneTitle( ) {
	// だめ！！initialize( );
}

void App::initScenePlay( ) {
}

void App::initSceneClear( ) {
}

void App::initSceneGameover( ) {
}

void App::updateSceneTitle( ) {
}

void App::updateScenePlay( ) {
	_player->update( );
	_cohort->update( );
	_weapon->update( );
}

void App::updateSceneClear( ) {
}

void App::updateSceneGameover( ) {
}

GroundPtr App::getGround( ) const {
	return _ground;
}

GroundModelPtr App::getGroundModel( ) const {
	return _ground_model;
}

PlayerPtr App::getPlayerTarget( const Vector& pos ){
	PlayerPtr target;

	double min = 1000;
	if ( !_player->isExpired( ) ) {
		return target;
	}
	Vector vec = _player->getPos( ) - pos;
	double length = vec.getLength( );
	if ( length < min ) {
		target = _player;
	}
	return target;	
}



int App::convertCSVtoMap( int type ) {
	return _map_convert[ type ];
}

unsigned char App::getScene( ) const {
	return _scene;
}

FieldPtr App::getField( ) const {
	return _field;
}

WeaponPtr App::getWeapon( ) const {
	return _weapon;
}

CohortPtr App::getCohort( ) const{
	return _cohort;
}

PlayerPtr App::getPlayer( ) const {
	return _player;
}