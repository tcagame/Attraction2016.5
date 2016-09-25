#include "Viewer.h"
#include "Framework.h"
#include "Server.h"
#include "Drawer.h"

const int PITCH = 20;
const int COLOR = 0xffffff;

const int MAX_PLAYER = 4;//プレイヤーの数

const int FRAME_STATUS_R = 7;
const int FRAME_STATUS_X = PITCH;
const int FRAME_STATUS_Y = PITCH;
const int FRAME_STATUS_W = 640 - PITCH - PITCH;
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
const int FRAME_CONNECT_R = MAX_PLAYER + 1;
const int FRAME_CONNECT_X = PITCH;
const int FRAME_CONNECT_Y = FRAME_STATUS_X + FRAME_STATUS_H + PITCH;
const int FRAME_CONNECT_W = 200;
const int FRAME_CONNECT_H = 480 - FRAME_CONNECT_Y - PITCH;
const int FRAME_COMMAND_X = FRAME_CONNECT_X + FRAME_CONNECT_W + PITCH;
const int FRAME_COMMAND_W = 640 - FRAME_COMMAND_X - PITCH;
const int FRAME_COMMAND_H = 30; // 固定値
const int FRAME_COMMAND_Y = 480 - PITCH - FRAME_COMMAND_H;
const int FRAME_COMMAND_TITLE_W = 80;
const int FRAME_LOG_X = FRAME_CONNECT_X + FRAME_CONNECT_W + PITCH;
const int FRAME_LOG_Y = FRAME_STATUS_Y + FRAME_STATUS_H + PITCH;
const int FRAME_LOG_W = 640 - FRAME_LOG_X - PITCH;
const int FRAME_LOG_H = FRAME_COMMAND_Y - FRAME_LOG_Y - PITCH;

ViewerPtr Viewer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( fw->getTask( getTag( ) ) );
}

Viewer::Viewer( ) {
}

Viewer::~Viewer( ) {
}

void Viewer::update( ) {
	drawLog( );
	drawCommand( );
}

void Viewer::drawLog( ) {
	{
		int x1 = FRAME_LOG_X;
		int y1 = FRAME_LOG_Y;
		int x2 = x1 + FRAME_LOG_W;
		int y2 = y1 + FRAME_LOG_H;
		drawBox( x1, y1, x2, y2 );
	}

	// ログ
	DrawerPtr drawer = Drawer::getTask( );
	/*
	LogPtr log = Log::getTask( );
	for ( int i = 0; i < Log::MESSAGE_COUNT; i++ ) {
		int x = FRAME_LOG_X + 10;
		int y = FRAME_LOG_Y + FRAME_LOG_H / Log::MESSAGE_COUNT * i;
		drawer->drawString( x, y, "%s", log->get( i ).c_str( ) );
	}
	*/
}

void Viewer::drawCommand( ) {
	{
		int x1 = FRAME_COMMAND_X;
		int y1 = FRAME_COMMAND_Y;
		int x2 = x1 + FRAME_COMMAND_W;
		int y2 = y1 + FRAME_COMMAND_H;
		drawBox( x1, y1, x2, y2 );
	}

	DrawerPtr drawer = Drawer::getTask( );
	// 中の枠
	{
		int x1 = FRAME_COMMAND_X + FRAME_COMMAND_TITLE_W;
		int y1 = FRAME_COMMAND_Y;
		int x2 = x1;
		int y2 = y1 + FRAME_COMMAND_H;
		drawer->drawLine( x1, y1, x2, y2 );
	}

	// タイトル
	{
		int x = FRAME_COMMAND_X + 3;
		int y = FRAME_COMMAND_Y + 5;
		drawer->drawString( x, y, "Command" );
	}
	/*
	// コマンド
	{
		CommandPtr command = Command::getTask( );
		int x = FRAME_COMMAND_X + FRAME_COMMAND_TITLE_W + 3;
		int y = FRAME_COMMAND_Y + 5;
		drawer->drawString( x, y, command->get( ).c_str( ) );
	}
	*/
}

void Viewer::drawBox( int x1, int y1, int x2, int y2 ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->drawLine( x1, y1, x1, y2 );//左の縦線
	drawer->drawLine( x2, y1, x2, y2 );//右の縦線
	drawer->drawLine( x1, y1, x2, y1 );//上の横線
	drawer->drawLine( x1, y2, x2, y2 );//下の横線
}