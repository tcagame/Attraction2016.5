#include "Ground.h"
#include <string>

const int Ground::CHIP_WIDTH = 7;
const int Ground::CHIP_HEIGHT = 4;

Ground::Ground(std::string file_name) {
	for ( unsigned int i = 0; i < _ground_data.size( ); i++ ) {
		_ground_data.pop_back( );
	}
	loadMapCSV( file_name.c_str( ) );
}


Ground::~Ground( ) {
}

bool Ground::loadMapCSV( const char* file_name ) {
	//ファイルの読み込み
	FILE* fp;
	errno_t err = fopen_s( &fp, file_name, "r" );
	if ( err != 0 ) {
		return false;
	}
	
	char buf[ 2048 ];

    //　カウントする
	int width = 0;
	int height = 0;
	while ( fgets( buf, 2048, fp ) != NULL ) {
		int w = 0;
		std::string str = buf;
		while ( true ) {
			w++;
			std::string::size_type index = str.find( "," );

			if ( index == std::string::npos ) {
				_ground_data.push_back( atoi( str.c_str( ) ) );
				break;
			}
			std::string substr = str.substr( 0, index );
			_ground_data.push_back( atoi( substr.c_str( ) ) );
			str = str.substr( index + 1 );
		}

		if ( height == 0 ) {
			width = w;
		}
		height++;
	}

	_width = width;
	_height = height;
	return true;
}


int Ground::getWidth( ) const {
	return _width;
}

int Ground::getHeight( ) const {
	return _height;
}

int Ground::getIdx( int x, int y ) {
	return x + y * _width;
}

int Ground::getGroundData( int idx ) const {
	return _ground_data[ idx ];
}
