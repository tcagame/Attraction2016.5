#include "App.h"
#include "Party.h"
#include "Cohort.h"
#include "Ground.h"
#include "GroundModel.h"
#include "Field.h"
#include "Weapon.h"
#include "Device.h"
#include "Application.h"
#include "Client.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyMinotaur.h"
#include "EnemyGoblin.h"
#include "DarkKnight.h"
#include "DarkMonk.h"


const std::string DIRECTORY = "../Resource/";
const std::string MODEL_NAME_LIST [] {
	"none",
	"floor01"
};
const int RESET_COUNT = 30;
const int START_COUNT = 60;
const int STRING_BUF = 256;
const int SEND_MESSAGE_COUNT_MAX = 10;

AppPtr App::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< App >( fw->getTask( App::getTag( ) ) );
}

App::App( ) {
	_ground = GroundPtr( new Ground( DIRECTORY + "CSV/map.csv" ) );
	_ground_model = GroundModelPtr( new GroundModel );
	_ground_model->loadModelData( 0, 0, DIRECTORY + "MapModel/floor01.mdl" );
}

App::~App( ) {

}

void App::initialize( ) {
	std::string filepath = DIRECTORY + "CSV/";
	_ground = GroundPtr( new Ground( filepath + "map.csv" ) );//マップデータ
	_ground_model = GroundModelPtr( new GroundModel( ) );
	_field = FieldPtr( new Field( ) );
	_weapon = WeaponPtr( new Weapon( ) );
	_party = PartyPtr( new Party( ) );
	std::string floor_model_path = DIRECTORY + "MapModel/floor_collision.mdl";
	_ground_model->loadModelData( 100, 30, floor_model_path );
	_cohort = CohortPtr( new Cohort( ) );
	_dark_knight = DarkKnightPtr ( new DarkKnight( ) );
	_dark_monk = DarkMonkPtr ( new DarkMonk( ) );


	_dark_monk->create( Vector( 0, 10, 0 ) );
	_dark_knight->create( Vector( 0, 10, 0 ) );
	_dark_knight->resetDeadFlag( );
	_dark_monk->resetDeadFlag( );
	//EnemyPtr enemy = EnemyPtr( new EnemyGoblin( Enemy::ENEMY_TYPE_GOBLIN, 2, Character::STATUS( 10, 10, 0.4 ) ) );
	//_cohort->add( enemy );

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
	// だめ！！initialize( );]


	_dark_knight->reset( );
	_dark_monk->reset( );
	_dark_monk->create( Vector( 0, 10, 0 ) );
	_dark_knight->create( Vector( 0, 10, 0 ) );
	_dark_knight->resetDeadFlag( );
	_dark_monk->resetDeadFlag( );
	
	_is_send_dark_knight_dead_data = false;
	_is_send_dark_monk_dead_data = false;

	_sever_send_message_count = 60;
}

void App::initScenePlay( ) {
	_party->reset( );
}

void App::initSceneClear( ) {
}

void App::initSceneGameover( ) {
}

void App::updateSceneTitle( ) {
}

void App::updateScenePlay( ) {
	_party->update( );
	_cohort->update( );
	_weapon->update( );
	_dark_knight->update( );
	_dark_monk->update( );
	sendBossDeadMessage( );
	decreasePlayerHp( );
}

void App::sendBossDeadMessage( ) {
	if ( _dark_knight->isDead( ) && !_is_send_dark_knight_dead_data ) {
		ClientPtr client = Client::getTask( );
		SERVERDATA sever_data;
		sever_data.command = COMMAND_BOSS_DEAD;
		sever_data.value[ 0 ] = BOSS_1;
		client->send( sever_data );
		_is_send_dark_knight_dead_data = true;
	}
	if ( _dark_monk->isDead( ) && !_is_send_dark_monk_dead_data ) {
		ClientPtr client = Client::getTask( );
		SERVERDATA sever_data;
		sever_data.command = COMMAND_BOSS_DEAD;
		sever_data.value[ 0 ] = BOSS_2;
		client->send( sever_data );
		_is_send_dark_monk_dead_data = true;

	}
}

void App::decreasePlayerHp( ) {
	_sever_send_message_count++;
	if ( _sever_send_message_count < SEND_MESSAGE_COUNT_MAX ) {
		return;
	}
	ClientPtr client = Client::getTask( );
	CLIENTDATA data = client->getClientData( );

	for ( int i = 0; i < MAX_MACHINE; i++ ) {
		PlayerPtr player = _party->getPlayer( i );
		if ( !player ) {
			continue;
		}
		if ( !player->isExpired( ) ) {
			continue;
		}
		int diff_hp = player->getTotaldamage( );
		SERVERDATA sever_data;
		sever_data.command = COMMAND_STATUS_DAMAGE;
		sever_data.value[ 0 ] = i;
		sever_data.value[ 1 ] = diff_hp;
		sever_data.value[ 2 ] = 1;
		client->send( sever_data );
	}
	_sever_send_message_count = 0;
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

PartyPtr App::getParty( ) const {
	return _party;
}

DarkKnightPtr App::getDarkKnight( ) const{
	return _dark_knight;
}

DarkMonkPtr App::getDarkMonk( ) const{
	return _dark_monk;
}