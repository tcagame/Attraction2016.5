#include "Device.h"
#include "mathmatics.h"
#include "Server.h"
#include "DxLib.h"
#include "Application.h"

const int MAX_JOYPAD_USE_NUM = PLAYER_NUM;
const int JOYPADKEY[ MAX_JOYPAD_USE_NUM ] = {
	DX_INPUT_PAD1,
	DX_INPUT_PAD2,
	DX_INPUT_PAD3,
	DX_INPUT_PAD4
};

DevicePtr Device::getTask( ) {
	ApplicationPtr app = Application::getInstance( );
	return std::dynamic_pointer_cast< Device >( app->getTask( Device::getTag( ) ) );
}


Device::Device( ) {
	for ( int i = 0; i < MAX_JOYPAD_USE_NUM; i++ ) {
		_data.player[ i ].x = 0;
		_data.player[ i ].y = 0;
		_data.player[ i ].button = 0;
	}
}

Device::~Device( ) {
}

void Device::resetup( ) {
	ReSetupJoypad( );
}

int Device::getDirX( int i ) const {
	return _data.player[ i ].x;
}

int Device::getDirY( int i ) const {
	return _data.player[ i ].y;
}

unsigned int Device::getButton( int i ) const {
	return _data.player[ i ].button;
}

void Device::update( ) {
	_device_num = GetJoypadNum( );
	for ( int i = 0; i < MAX_JOYPAD_USE_NUM; i++ ) {
		
		int key = GetJoypadInputState( JOYPADKEY[ i ] );
		Vector vec;
		int x = 0, y = 0;
		GetJoypadAnalogInput( &x, &y, JOYPADKEY[ i ] );
		vec.x = x;
		vec.y = y;
		vec.x += +( ( key & PAD_INPUT_RIGHT ) != 0 );
		vec.x += -( ( key & PAD_INPUT_LEFT  ) != 0 );
		vec.y += +( ( key & PAD_INPUT_DOWN  ) != 0 );
		vec.y += -( ( key & PAD_INPUT_UP    ) != 0 );
		vec = vec.normalize( ) * 100;


		_data.player[ i ].x = ( int )vec.x;
		_data.player[ i ].y = ( int )vec.y;

		_data.player[ i ].button = 0;
		if ( ( key & PAD_INPUT_A ) != 0 ) { 
			_data.player[ i ].button |= BUTTON_A;
		}
		if ( ( key & PAD_INPUT_B ) != 0 ) { 
			_data.player[ i ].button |= BUTTON_B;
		}
		if ( ( key & PAD_INPUT_C ) != 0 ) { 
			_data.player[ i ].button |= BUTTON_C;
		}
		if ( ( key & PAD_INPUT_X ) != 0 ) { 
			_data.player[ i ].button |= BUTTON_D;
		}
	}
}

int Device::getDeviceNum( ) {
	return _device_num;
}