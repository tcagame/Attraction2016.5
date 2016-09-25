#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"
#include <string>
#include <array>
#include <vector>

PTR( TableDrawer );

class TableDrawer {
public:
	struct FORM {
		std::string title;
		int x;
		int y;
		int rows;
		int cols;
		std::array< int, 100 > col;
		bool inner_line;
		FORM( ) : inner_line( true ) { }
	};
public:
	TableDrawer( const FORM& form );
	virtual ~TableDrawer( );
public:
	void draw( );
	void setCell( int x, int y, std::string str );
	std::string getCell( int x, int y ) const;
private:
	const FORM _form;
	std::vector< std::string > _cell;
};
