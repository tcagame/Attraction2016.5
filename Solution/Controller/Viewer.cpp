#include "Viewer.h"
#include "Application.h"
#include "Server.h"
#include "Drawer.h"
#include "Log.h"
#include "Command.h"
#include "Network.h"
#include "TableDrawer.h"

const int MAX_PLAYER = 4;//プレイヤーの数

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const int PITCH = 20;

const int FRAME_STATUS_R = 7;
const int FRAME_STATUS_X = PITCH;
const int FRAME_STATUS_Y = PITCH;
const int FRAME_STATUS_W = WINDOW_WIDTH - PITCH - PITCH;
const int FRAME_STATUS_H = 150;
const int FRAME_STATUS_DEVICE_X = FRAME_STATUS_X;
const int FRAME_STATUS_DEVICE_W = 60;
const int FRAME_STATUS_DIR_X = FRAME_STATUS_DEVICE_X + FRAME_STATUS_DEVICE_W;
const int FRAME_STATUS_DIR_W = 100;
const int FRAME_STATUS_BUTTON_X = FRAME_STATUS_DIR_X + FRAME_STATUS_DIR_W;
const int FRAME_STATUS_BUTTON_W = 80;
const int FRAME_STATUS_STATE_X = FRAME_STATUS_BUTTON_X + FRAME_STATUS_BUTTON_W;
const int FRAME_STATUS_STATE_W = 60;
const int FRAME_STATUS_WEAPON_X = FRAME_STATUS_STATE_X + FRAME_STATUS_STATE_W;
const int FRAME_STATUS_WEAPON_W = 70;
const int FRAME_STATUS_LIFE_X = FRAME_STATUS_WEAPON_X + FRAME_STATUS_WEAPON_W;
const int FRAME_STATUS_LIFE_W = 100;
const int FRAME_STATUS_AREA_X = FRAME_STATUS_LIFE_X + FRAME_STATUS_LIFE_W;

const int FRAME_CONNECT_R = MAX_MACHINE;
const int FRAME_CONNECT_Y = FRAME_STATUS_Y + FRAME_STATUS_H + PITCH;
const int FRAME_CONNECT_W = 200;
const int FRAME_CONNECT_X = WINDOW_WIDTH - FRAME_CONNECT_W;

const int FRAME_COMMAND_X = PITCH;
const int FRAME_COMMAND_W = WINDOW_WIDTH - PITCH * 2 - FRAME_CONNECT_W;
const int FRAME_COMMAND_Y = WINDOW_HEIGHT - PITCH + 60;

const int FRAME_LOG_X = FRAME_COMMAND_X;
const int FRAME_LOG_Y = FRAME_STATUS_Y + FRAME_STATUS_H + PITCH;
const int FRAME_LOG_W = FRAME_COMMAND_W;

ViewerPtr Viewer::getTask( ) {
	ApplicationPtr app = Application::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( app->getTask( getTag( ) ) );
}

Viewer::Viewer( ) {
}

Viewer::~Viewer( ) {
}

void Viewer::initialize( ) {
	makeTableLog( );
	makeTableCommand( );
	makeTableConnect( );
}

void Viewer::update( ) {
	drawConnect( );
	drawLog( );
	drawCommand( );
}

void Viewer::makeTableLog( ) {
	TableDrawer::FORM form;
	form.x = FRAME_LOG_X;
	form.y = FRAME_LOG_Y;
	form.title = "Log";
	form.rows = Log::MESSAGE_COUNT;
	form.cols = 1;
	form.col[ 0 ] = FRAME_LOG_W;

	form.inner_line = false;
	_log = TableDrawerPtr( new TableDrawer( form ) );
}

void Viewer::makeTableCommand( ) {
	TableDrawer::FORM form;
	form.x = FRAME_COMMAND_X;
	form.y = FRAME_COMMAND_Y;
	form.title = "Command";
	form.rows = 1;
	form.cols = 1;
	form.col[ 0 ] = FRAME_COMMAND_W;
	form.inner_line = true;
	_command = TableDrawerPtr( new TableDrawer( form ) );
}

void Viewer::makeTableConnect( ) {
	TableDrawer::FORM form;
	form.x = FRAME_CONNECT_X;
	form.y = FRAME_CONNECT_Y;
	form.title = "Connect";
	form.rows = FRAME_CONNECT_R;
	form.cols = 1;
	form.col[ 0 ] = FRAME_CONNECT_W;
	form.inner_line = true;
	_connect = TableDrawerPtr( new TableDrawer( form ) );
}

void Viewer::drawConnect( ) {
	ServerPtr server = Server::getTask( );

	for ( int i = 0; i < MAX_MACHINE; i++ ) {
		std::string str = server->getMachineIPStr( i );
		_connect->setCell( 0, i, str );
	}

	_connect->draw( );
}

void Viewer::drawLog( ) {
	// ログ
	LogPtr log = Log::getTask( );
	for ( int i = 0; i < Log::MESSAGE_COUNT; i++ ) {
		std::string str = log->get( i );
		_log->setCell( 0, i, str );
	}

	_log->draw( );
}

void Viewer::drawCommand( ) {
	CommandPtr command = Command::getTask( );
	_command->setCell( 0, 0, command->get( ) );

	_command->draw( );
}