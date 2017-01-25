#include "Command.h"
#include "Application.h"
#include "Keyboard.h"
#include "Server.h"
#include "log.h"

const char * COM_IP     = "ip";
const char * COM_DEVICE = "device";

CommandPtr Command::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< Command >( fw->getTask( Command::getTag( ) ) );
}

Command::Command( ) {
}

Command::~Command( ) {
}

void Command::update( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	char single_ch = keyboard->getInputChar( );

	if ( single_ch == 0 ) {
		return;
	}

	if ( single_ch == CTRL_CODE_CR ) {
		execute( );
	} else if ( single_ch == CTRL_CODE_BS && !_command.empty( ) ) {
		_command.pop_back( );
	} else {
		_command += single_ch;
	}
}

std::string Command::get( ) {
	return _command;
}

void Command::parser( ) {
	_word.clear( );
	
	std::string command = _command;
	command += " ";
	std::transform( command.cbegin( ), command.cend( ), command.begin( ), tolower );
	_command.clear( );

	int pos = 0;
	while ( true ) {
		int p = command.find( ' ', pos );
		std::string tmp = command.substr( pos, ( p - pos ) );

		if ( tmp.empty( ) ) {
			break;
		}

		_word.push_back( tmp );
		pos = p + 1;
	}
}

void Command::execute( ) {
	LogPtr log = Log::getTask( );

	std::string com = _command;

	parser( );

	if ( _word.empty( ) ) {
		_word.push_back( "" );
	}

	// IPアドレス取得
	if ( _word[ 0 ] == COM_IP ) {
		ServerPtr server = Server::getTask( );
		server->saveIP( );
		log->send( "IP.iniファイルを生成しました" );
		return;
	}

	// IPアドレス取得
	if ( _word[ 0 ] == COM_DEVICE ) {
		ReSetupJoypad( );
		log->send( "deviceの再読み込みをしました。" );
		return;
	}

	// コマンドエラー
	log->send( "[エラー]このコマンドは登録されていません(%s)", com.c_str( ) );
}

