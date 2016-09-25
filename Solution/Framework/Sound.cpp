#include "Sound.h"
#include "Application.h"
#include "Dxlib.h"
#include <string>

const char* DIRECTORY = "../Resource/Sound/";

const char* SE_FILE_PATH[ Sound::SE_MAX ] {	
	"SE/DD_SE_start_harada.mp3",	
	"SE/DD_SE_gameclear=hatakeyama.mp3",
	"SE/DD_SE_gameover_harada.mp3",
	"SE/magicstart2.mp3",
	"SE/landing.wav",
	"SE/dead.wav",
	"SE/player_damage.wav",

	"SE/sword-slash3.mp3",
	"SE/sword-slash4.mp3",
	"SE/katana-slash4.mp3",
	"SE/iainuki1.mp3",
	"SE/sword-clash3.mp3",

	"SE/punch-middle2.mp3",
	"SE/punch-high1.mp3",
	"SE/kick-middle1.mp3",
	"SE/punch-high2.mp3",

	"SE/gun2.mp3",
	"SE/tm2r_bom34.wav",
	"SE/tm2r_bom31_b.wav",
	"SE/machinegun1.mp3",

	"SE/se_maoudamashii_element_ice05.wav",
	"SE/se_maoudamashii_element_ice01.wav",
	"SE/se_maoudamashii_element_ice04.wav",
	"SE/beamgun3.mp3",

	"SE/sen_ge_panchi06.mp3",
	"SE/enemy_damage.wav",

	"SE/kick-high1.mp3",

	"SE/hito_ge_beta.mp3",
	"SE/sword-slash3.mp3",
	"SE/down1.mp3",

	"SE/monster-growl1.mp3",
	"SE/nori_ge_jet_sukuran01.mp3",
	"SE/magic-flame2.mp3",
	"SE/sen_ge_taoreru06.mp3",
	"SE/wing1.mp3",
	"SE/sen_ge_bom16.mp3",
	"SE/sen_ge_bom17.mp3",

	"SE/sceneswitch2.mp3"
};
const char* BGM_FILE_PATH[ Sound::BGM_MAX ] {
	"",
	"BGM/DD_BGM_dotyu_1_harada.mp3",
	"BGM/DD_bgm_camp_imin.mp3",
	"BGM/takeuchiBGM2.wav",
	"BGM/DD_BGM_boss_1_harada.mp3",
	"BGM/DD_BGM_boss_2_harada"
};
const char* VOICE_FILE_PATH[ Sound::VOICE_MAX ] {
	"VOICE/KNI0010.wav",
	"VOICE/KNI0020.wav",
	"VOICE/KNI0030.wav",
	"VOICE/KNI0040.wav",
	"VOICE/KNI0050.wav",
	"VOICE/KNI0060.wav",
	"VOICE/KNI0070.wav",
	"VOICE/KNI0080.wav",
	"VOICE/KNI0090.wav",
	"VOICE/KNI0100.wav",
	"VOICE/KNI0110.wav",
	"VOICE/KNI0120.wav",

	"VOICE/MON0010.wav",
	"VOICE/MON0020.wav",
	"VOICE/MON0030.wav",
	"VOICE/MON0040.wav",
	"VOICE/MON0050.wav",
	"VOICE/MON0060.wav",
	"VOICE/MON0070.wav",
	"VOICE/MON0080.wav",
	"VOICE/MON0090.wav",
	"VOICE/MON0100.wav",
	"VOICE/MON0110.wav",
	"VOICE/MON0120.wav",

	"VOICE/HUN0010.wav",
	"VOICE/HUN0020.wav",
	"VOICE/HUN0030.wav",
	"VOICE/HUN0040.wav",
	"VOICE/HUN0050.wav",
	"VOICE/HUN0060.wav",
	"VOICE/HUN0070.wav",
	"VOICE/HUN0080.wav",
	"VOICE/HUN0090.wav",
	"VOICE/HUN0100.wav",
	"VOICE/HUN0110.wav",
	"VOICE/HUN0120.wav",

	"VOICE/WIT0010.wav",
	"VOICE/WIT0020.wav",
	"VOICE/WIT0030.wav",
	"VOICE/WIT0040.wav",
	"VOICE/WIT0050.wav",
	"VOICE/WIT0060.wav",
	"VOICE/WIT0070.wav",
	"VOICE/WIT0080.wav",
	"VOICE/WIT0090.wav",
	"VOICE/WIT0100.wav",
	"VOICE/WIT0110.wav",
	"VOICE/WIT0120.wav",

	"VOICE/MIN0010.wav",
	"VOICE/MIN0020.wav",
	"VOICE/MIN0030.wav",
	"VOICE/MIN0040.wav",
	"VOICE/MIN0050.wav",
	"VOICE/MIN0060.wav",
	"VOICE/MIN0070.wav",
	"VOICE/MIN0080.wav",
	"VOICE/MIN0090.wav",
	"VOICE/MIN0100.wav",
	"VOICE/MIN0110.wav",
	"VOICE/MIN0120.wav",

	"VOICE/DRA0010.wav",
	"VOICE/DRA0020.wav",
	"VOICE/DRA0030.wav",
	"VOICE/DRA0040.wav",
	"VOICE/DRA0050.wav",
	"VOICE/DRA0060.wav",
	"VOICE/DRA0070.wav",
	"VOICE/DRA0080.wav",
	"VOICE/DRA0090.wav",
	"VOICE/DRA0100.wav",
	"VOICE/DRA0110.wav",
	"VOICE/DRA0120.wav",
	"VOICE/DRA0130.wav",
	"VOICE/DRA0140.wav",
	"VOICE/DRA0150.wav",
	"VOICE/DRA0160.wav",
	"VOICE/DRA0170.wav",

	"VOICE/FAI0010.wav",
	"VOICE/FAI0020.wav",
	"VOICE/FAI0030.wav",
	"VOICE/FAI0040.wav",
	"VOICE/FAI0050.wav",
	"VOICE/FAI0060.wav",
	"VOICE/FAI0070.wav",
	"VOICE/FAI0080.wav",
	"VOICE/FAI0090.wav",
	"VOICE/FAI0100.wav",
	"VOICE/FAI0110.wav",
	"VOICE/FAI0120.wav",
	"VOICE/FAI0130.wav",
	"VOICE/FAI0140.wav",
	"VOICE/FAI0150.wav",
	"VOICE/FAI0160.wav",
	"VOICE/FAI0170.wav",
	"VOICE/FAI0180.wav",
	"VOICE/FAI0190.wav",
	"VOICE/FAI0200.wav",
	"VOICE/FAI0210.wav",
	"VOICE/FAI0220.wav",
	"VOICE/FAI0230.wav",
	"VOICE/FAI0240.wav",
	"VOICE/FAI0250.wav",
	"VOICE/FAI0260.wav",
	"VOICE/FAI0270.wav",
	"VOICE/FAI0280.wav",
	"VOICE/FAI0290.wav",
	"VOICE/FAI0300.wav",
	"VOICE/FAI0310.wav",
	"VOICE/FAI0320.wav",
	"VOICE/FAI0330.wav",
	"VOICE/FAI0340.wav",
	"VOICE/FAI0350.wav",
	"VOICE/FAI0360.wav",

};

SoundPtr Sound::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< Sound >( fw->getTask( Sound::getTag( ) ) );
}

Sound::Sound( ) {
	
}

void Sound::initialize( ) {
	//‚r‚d
	for ( int i = 0; i < SE_MAX; i++ ) {
		std::string file_path = DIRECTORY;
		file_path += SE_FILE_PATH[ i ];
		_id[ i ] = LoadSoundMem( file_path.c_str( ) );
	}
	
	//‚a‚f‚l
	for ( int i = 0; i < BGM_MAX; i++ ) {
		_bgm_file_path[ i ] = DIRECTORY;
		_bgm_file_path[ i ] += BGM_FILE_PATH[ i ];
	}
	_playing_bgm = BGM_NONE;
	

	//VOICE
	for ( int i = 0; i < VOICE_MAX; i++ ) {
		_voice_file_path[ i ] = DIRECTORY;
		_voice_file_path[ i ] += VOICE_FILE_PATH[ i ];
	}

	for ( int i = 0; i < SE_MAX; i++ ) {
		_se_play[ i ] = false;
	}

	_bgm_handle = -1;
	_voice_handle = -1;
}

void Sound::finalize( ) {
	for ( int i = 0; i < SE_MAX; i++ ) {
		StopSoundMem( _id[ i ] );
		DeleteSoundMem( _id[ i ] );

	}
	StopSoundMem( _bgm_handle );
	DeleteSoundMem( _bgm_handle );
	StopSoundMem( _voice_handle );
	DeleteSoundMem( _voice_handle );
}

Sound::~Sound( ) {
	
}

void Sound::update( ) {
	for ( int i = 0; i < SE_MAX; i++ ) {
		if ( _se_play[ i ] ) {
			StopSoundMem( _id[ i ] );
			PlaySoundMem( _id[ i ], DX_PLAYTYPE_BACK );
		}
		_se_play[ i ] = false;
	}
}

void Sound::playSE( SE tag ) {
	_se_play[ tag ] = true;
}

void Sound::playBGM( BGM tag ) {
	// ‚·‚Å‚ÉÄ¶’†
	if ( _playing_bgm == tag ) {
		return;
	}

	// ‘O‰ñ‚Ì‚a‚f‚l‚ðíœ
	if ( _bgm_handle > -1 ) {
		StopSoundMem( _bgm_handle );
		DeleteSoundMem( _bgm_handle );
	}

	// V‚µ‚¢‚a‚f‚l‚ðÄ¶
	_playing_bgm = tag;
	if ( tag != BGM_NONE ) {
		_bgm_handle = LoadSoundMem( _bgm_file_path[ tag ].c_str( ) );
		PlaySoundMem( _bgm_handle, DX_PLAYTYPE_LOOP );
	}
}


void Sound::playVoice( VOICE tag ) {
	if ( _voice_handle > -1 ) {
		StopSoundMem( _voice_handle );
		DeleteSoundMem( _voice_handle );
	}
	_voice_handle = LoadSoundMem( _voice_file_path[ tag ].c_str( ) );
	PlaySoundMem( _voice_handle, DX_PLAYTYPE_BACK );
}

bool Sound::isPlayingVoice( ) {
	if ( _voice_handle < -1 ) {
		return false;
	}
	return CheckSoundMem( _voice_handle ) == 1;
}
