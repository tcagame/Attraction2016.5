#include "Party.h"
#include "Player.h"
#include "Client.h"

const int POWER = 10;
const double SPEED = 0.5;

const Vector PLAYER_START_POS [ PLAYER_NUM ] = {
	Vector( 0, 0 ),
	Vector( 0, 0 ),
	Vector( 0, 0 ),
	Vector( 0, 0 )
};

Party::Party( ) {
	ClientPtr client = Client::getTask( );
	CLIENTDATA data = client->getClientData( );
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		Character::STATUS status = Character::STATUS( data.player[ i ].hp, POWER, SPEED );
		_party[ i ] = PlayerPtr( new Player( i, status ) );
	}
}

Party::~Party( ) {
}

void Party::update( ) {
	//‚±‚±‚ÅXV
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		if ( _party[ i ]->isExpired( ) ) {
			_party[ i ]->update( );
		}
	}

	//‚±‚±‚ÅoŒ»
	ClientPtr client = Client::getTask( );
	CLIENTDATA data = client->getClientData( );
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		if ( !_party[ i ]->isExpired( ) && data.player[ i ].button > 0 ) {
			_party[ i ]->create( PLAYER_START_POS[ i ] );
		}
	}
}

PlayerPtr Party::getPlayer( int id ) const {
	return _party[ id ];
}

int Party::getPlayerNum( ) const {
	int num = 0;
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		if ( _party[ i ]->isExpired( ) ) {
			num++;
		}
	}
	return num;
}