#include "Command.h"
#include "Application.h"
#include "Keyboard.h"
#include "Server.h"
#include "Device.h"
#include "log.h"

const char * COM_IP     = "ip";
const char * COM_DEVICE = "device";
const char * COM_SCENE = "scene";

const char * COM_SCENE_TITLE	= "title";
const char * COM_SCENE_PLAY		= "play";
const char * COM_SCENE_CLEAR	= "clear";
const char * COM_SCENE_GAMEOVER = "gameover";

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

	// IP�A�h���X�擾
	if ( _word[ 0 ] == COM_IP ) {
		ServerPtr server = Server::getTask( );
		server->saveIP( );
		log->send( "IP.ini�t�@�C���𐶐����܂���" );
		return;
	}

	// IP�A�h���X�擾
	if ( _word[ 0 ] == COM_DEVICE ) {
		DevicePtr device = Device::getTask( );
		device->resetup( );
		log->send( "device�̍ēǂݍ��݂����܂����B" );
		return;
	}

	//���Z�b�g
	if ( _word[ 0 ] == COM_SCENE && _word.size( ) >= 2 ) {
		ServerPtr server = Server::getTask( );
		std::string string = "scene��";
		if ( _word[ 1 ] == COM_SCENE_TITLE ) {
			server->setScene( SCENE_TITLE );
			string += "�^�C�g���ɕύX���܂����B";
		}
		if ( _word[ 1 ] == COM_SCENE_PLAY ) {
			server->setScene( SCENE_PLAY );
			string += "�v���C�ɕύX���܂����B";
		}
		if ( _word[ 1 ] == COM_SCENE_CLEAR ) {
			server->setScene( SCENE_CLEAR );
			string += "�N���A�ɕύX���܂����B";
		}
		if ( _word[ 1 ] == COM_SCENE_GAMEOVER ) {
			server->setScene( SCENE_GAMEOVER );
			string += "�Q�[���I�[�o�[�ɕύX���܂����B";
		}
		log->send( string.c_str( ) );
		return;
	}

	// �R�}���h�G���[
	log->send( "[�G���[]���̃R�}���h�͓o�^����Ă��܂���(%s)", com.c_str( ) );
}

