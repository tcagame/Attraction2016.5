#include "TableDrawer.h"
#include "drawer.h" 

const int COL_PITCH = 30;
const int OFFSET_ROW = 12;
const int OFFSET_CAL = 0;
const int OFFSET_X = 5;
const int OFFSET_Y = 8;

TableDrawer::TableDrawer( const FORM& form ) :
_form( form ),
_cell( form.rows * form.cols ) {
}


TableDrawer::~TableDrawer( ) {

}

void TableDrawer::draw( ) {
	DrawerPtr drawer = Drawer::getTask( );

	// タイトル描画
	drawer->drawString( _form.x, _form.y, _form.title.c_str( ) );

	// テーブル基準位置
	int origin_x = _form.x; 
	int origin_y = _form.y + COL_PITCH;

	int max_cal = COL_PITCH * _form.rows;
	
	int x = origin_x;
	int y = origin_y;

	// 縦線
	int height = _form.rows * COL_PITCH;
	int col_x = origin_x;
	drawer->drawLine( origin_x, origin_y, origin_x, origin_y + height );
	for ( int i = 0; i < _form.cols; i++ ) {
		col_x += _form.col[ i ];
		drawer->drawLine( col_x, origin_y, col_x, origin_y + height );
	}

	// 横線
	int col_y = origin_y;
	for ( int i = 0; i < _form.rows + 1; i++ ) {
		if ( _form.inner_line || ( i == 0 || i == _form.rows ) ) {
			drawer->drawLine( origin_x, col_y, col_x, col_y );
		}
		col_y += COL_PITCH;
	}

	// セル描画
	int sx = origin_x + OFFSET_X;
	for ( int i = 0; i < _form.cols; i++ ) {
		for ( int j = 0; j < _form.rows; j++ ) {
			std::string str = _cell[ i + j * _form.cols ];
			int sy = j * COL_PITCH + origin_y + OFFSET_Y;
			drawer->drawString( sx, sy, str.c_str( ) );
		}
		sx += _form.col[ i ];
	}
}

void TableDrawer::setCell( int x, int y, std::string str ) {
	_cell[ x + y * _form.cols ] = str;
}

std::string TableDrawer::getCell( int x, int y ) const {
	return _cell[ x + y * _form.cols ];
}
