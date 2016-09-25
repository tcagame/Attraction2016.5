#include "Drawer.h"
#include "Application.h"
#include "Model.h"
#include "DxLib.h"
#include <assert.h>

static const int REFRESH_COUNT = 60;	//平均を取るサンプル数
static const int FPS = 30;
static const double SHADOW_RADIUS = 0.5;

const char* SHADOW_TEXTURE_PATH = "../Resource/Images/Shadow/shadow.png";

Drawer::Transform::Transform( ) :
sx( 0 ),
sy( 0 ),
tx( 0 ),
ty( 0 ),
tw( 0 ),
th( -1 ) {
}

Drawer::Transform::Transform( int sx_, int sy_, int tx_, int ty_, int tw_, int th_, int sx2_, int sy2_ ) :
sx( sx_ ),
sy( sy_ ),
tx( tx_ ),
ty( ty_ ),
tw( tw_ ),
th( th_ ),
sx2( sx2_ ),
sy2( sy2_ ) {
}

Drawer::ModelMV1::ModelMV1( ) :
motion( -1 ),
time( 0 ){
}

Drawer::ModelMV1::ModelMV1( Vector pos_, Vector dir_, int motion_, double time_ ) :
pos( pos_ ),
dir( dir_ ),
motion( motion_ ),
time( time_ ) {
}

Drawer::ModelMDL::ModelMDL( ) :
type( -1 ){
}

Drawer::ModelMDL::ModelMDL( Vector pos_, int type_ ) :
pos( pos_ ),
type( type_ ) {

}


Drawer::Sprite::Sprite( ) :
res( -1 ),
blend( BLEND_NONE ) {

}

Drawer::Sprite::Sprite( Transform trans_ ,int res_, BLEND blend_, double ratio_ ) :
trans( trans_ ),
res( res_ ),
blend( blend_ ),
ratio( ratio_ ) {

}

Drawer::PlayingEffect::PlayingEffect( ) :
playing_handle( -1 ),
scale( Vector( 1, 1, 1 ) ),
pos( Vector( 0, 0, 0 ) ),
dir( Vector( 0, 0, 0 ) ) {

}

Drawer::PlayingEffect::PlayingEffect( int playing_handle_, Vector scale_,Vector pos_, Vector dir_ ) :
playing_handle ( playing_handle_ ),
scale( scale_ ),
pos( pos_ ),
dir( dir_ ) {

}

Drawer::Billboard::Billboard( ) :
size( 0 ),
res( 0 ),
blend( BLEND_NONE ),
ratio( 0.0 ) {

}

Drawer::Billboard::Billboard( Vector pos_, double size_, int res_, BLEND blend_, double ratio_ ) :
pos( pos_ ),
size( size_ ),
res( res_ ),
blend( blend_ ),
ratio( ratio_ ) {

}

DrawerPtr Drawer::getTask( ) {
	ApplicationPtr fw = Application::getInstance( );
	return std::dynamic_pointer_cast< Drawer >( fw->getTask( getTag( ) ) );
}

Drawer::Drawer( const char * directory ) :
_directory( directory ){
}

Drawer::~Drawer( ) {
}

void Drawer::initialize( ) {
	for ( int i = 0; i < MODEL_ID_NUM; i++ ) {
		_model_id[ i ].body = -1;
	}
	_sprite_idx = 0;
	_model_mv1_idx = 0;
	_billboard_idx = 0;
	_effect_idx = 0;

	_shadow_model = ModelPtr( new Model );
	_shadow_model->alloc( SHADOW_NUM * 2 );
	_shadow_handle = _shadow_model->getTextureHandle( SHADOW_TEXTURE_PATH );
	_refresh_count = 0;
	_fps = FPS;
	_start_time = 0;

}

void Drawer::update( ) {
	
	flip( );

	drawShadow( );
	drawModelMV1( );
	drawModelMDL( );
	drawBillboard( );
	drawSprite( );
	
}

void Drawer::drawModelMDL( ) {
	for ( int i = 0; i < _model_mdl_idx; i++ ) {
		int type = _model_mdl[ i ].type;
		Vector pos = _model_mdl[ i ].pos;
		_model[ type ]->setPos( pos );
		_model[ type ]->draw( );
	}
	_model_mdl_idx = 0;
}


void Drawer::drawShadow( ) {
	_shadow_model->setPolygonNum( _shadow_idx * 2 );
	_shadow_model->draw( _shadow_handle, true );
	_shadow_idx = 0;
}

void Drawer::drawModelMV1( ) {
	for ( int i = 0; i < _model_mv1_idx; i++ ) {
		int id = _model_id[ _model_mv1[ i ].motion ].body;
		int anim = _model_id[ _model_mv1[ i ].motion ].body_anim;
		double time = _model_mv1[ i ].time;
		Vector pos = _model_mv1[ i ].pos;
		Vector dir = _model_mv1[ i ].dir;
		if ( ( float )dir.x == 0 ) {
			dir.x = 0.001;
		}
		MATRIX matrix = MGetIdent( );
		//上をZにするための回転
		matrix = MMult( matrix, MGetRotX( ( float )( PI / 2 ) ) );
		matrix = MMult( matrix, MGetRotY( ( float )( PI2 ) ) );
		//回転
		float angle = ( float )dir.angle( Vector( 0, 1, 0 ) );
		Vector axis = dir.cross( Vector( 0, -1, 0 ) );
		matrix = MMult( matrix, MGetRotAxis( VGet( ( float )axis.x, ( float )axis.y, ( float )axis.z ), angle ) );
		//サイズ変換
		float scale = ( float )_model_id[ _model_mv1[ i ].motion ].scale;
		matrix = MMult( matrix, MGetScale( VGet( scale, scale, scale ) ) );
		// 座標変換
		matrix = MMult( matrix, MGetTranslate( VGet( ( float )pos.x, ( float )pos.y, ( float )pos.z ) ) );
		MV1SetMatrix( id, matrix );

		// アニメーション時間設定
		MV1SetAttachAnimTime( id, anim, ( float )time );

		// ３Ｄモデルの描画
		MV1DrawModel( id ) ;
	}
	_model_mv1_idx = 0;
}

void Drawer::drawSprite( ) {
	if ( _back ) {
		ApplicationPtr fw = Application::getInstance( );
		DrawBox( 0, 0,
			fw->getWindowWidth( ),
			fw->getWindowHeight( ),
			GetColor( 0, 0, 0 ), TRUE );
	}
	_back = false;

	for ( int i = 0; i < _sprite_idx; i++ ) {
		const Sprite& sprite = _sprite[ i ];

		switch ( sprite.blend ) {
		case BLEND_ALPHA:
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, ( int )( 255 * sprite.ratio ) );
			break;
		case BLEND_ADD:
			SetDrawBlendMode( DX_BLENDMODE_ADD  , ( int )( 255 * sprite.ratio ) );
			break;
		}

		if ( sprite.trans.tw < 0 ) {
			DrawGraph( sprite.trans.sx, sprite.trans.sy, _graphic_id[ sprite.res ], TRUE );
		} else if ( sprite.trans.sy2 < 0 ) {
			DrawRectGraph( sprite.trans.sx, sprite.trans.sy, sprite.trans.tx, sprite.trans.ty, sprite.trans.tw, sprite.trans.th, _graphic_id[ sprite.res ], TRUE, FALSE );
		} else {
			DrawRectExtendGraph(
				sprite.trans.sx , sprite.trans.sy ,
				sprite.trans.sx2, sprite.trans.sy2,
				sprite.trans.tx , sprite.trans.ty ,
				sprite.trans.tw , sprite.trans.th , _graphic_id[ sprite.res ], TRUE );
		}

		if ( sprite.blend != BLEND_NONE ) {
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
		}
	}
	_sprite_idx = 0;
}

void Drawer::drawBillboard( ) {
	for ( int i = 0; i < _billboard_idx; i++ ) {
		const Billboard& billboard = _billboard[ i ];
		switch( billboard.blend ) {
		case BLEND_ALPHA:
			SetDrawBlendMode( DX_BLENDMODE_ALPHA, ( int )( 255 * billboard.ratio ) );
			break;
		case BLEND_ADD:
			SetDrawBlendMode( DX_BLENDMODE_ADD, ( int )( 255 * billboard.ratio ) );
			break;
		}

		int cheak = DrawBillboard3D( VGet( ( float )billboard.pos.x, ( float )billboard.pos.y, ( float )billboard.pos.z ), 0.5f, 0.5f, ( float )billboard.size, 0.0f, _graphic_id[ billboard.res ], TRUE );
		
		if ( billboard.blend != BLEND_NONE ) {
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
		}
	}
	_billboard_idx = 0;
}

void Drawer::loadMV1Model( int motion, const char* filename, double scale ) {
	std::string path = _directory;
	path += "/";
	path += filename;
	assert( motion < MODEL_ID_NUM );
	int& id = _model_id[ motion ].body;
	id = MV1LoadModel( path.c_str( ) );
	assert( id > 0 );
	int num = MV1GetMaterialNum( id ) ;
	for ( int i = 0; i < num; i++ ) {
		MV1SetMaterialEmiColor( id, i, GetColorF( 1.0f, 1.0f, 1.0f, 1.0f ) );
	}
	int& anim = _model_id[ motion ].body_anim;
	anim = MV1AttachAnim( id, 0, -1, FALSE );
	_model_id[ motion ].scale = scale;
}

void Drawer::loadMDLModel( int type, const char* model_filename, const char* texture_filename, Matrix matrix ) {
	assert( type < MODEL_NUM );
	std::string path = _directory;
	path += "/";
	std::string tex_path = path;
	path += model_filename;
	tex_path += texture_filename;
	
	_model[ type ] = ModelPtr( new Model );
	_model[ type ]->load( path.c_str( ) );
	_model[ type ]->setTexture( tex_path.c_str( ) );
	_model[ type ]->multiply( matrix );
}

void Drawer::loadGraph( int res, const char * filename ) {
	std::string path = _directory;
	path += "/";
	path +=  filename;
	assert( res < GRAPHIC_ID_NUM );
	_graphic_id[ res ] = LoadGraph( path.c_str( ) );
	if ( _graphic_id[ res ] < 0 ) {
		path = "../" + path;
		_graphic_id[ res ] = LoadGraph( path.c_str( ) );
		assert( _graphic_id[ res ] >= 0 );
	}
}

void Drawer::setSprite( const Sprite& sprite ) {
	assert( _sprite_idx < SPRITE_NUM );
	_sprite[ _sprite_idx ] = sprite;
	_sprite_idx++;
}

void Drawer::setModelMV1( const ModelMV1& model ) {
	assert( _model_mv1_idx < MODEL_MV1_NUM );
	_model_mv1[ _model_mv1_idx ] = model;
	_model_mv1_idx++;
}

void Drawer::setShadow( const Vector& pos ){
	assert( _shadow_idx < SHADOW_NUM );
	Model::VERTEX vertex[ 4 ];
	for ( int i = 0; i < 4; i++ ) {
		vertex[ i ].pos = Vector( i / 2 * SHADOW_RADIUS - SHADOW_RADIUS / 2, i % 2 * SHADOW_RADIUS - SHADOW_RADIUS / 2, 0 ) + pos;
		vertex[ i ].u = i % 2;
		vertex[ i ].v = i / 2;
	}
		
	_shadow_model->set( _shadow_idx * 6 + 0, vertex[ 0 ] ); 
	_shadow_model->set( _shadow_idx * 6 + 1, vertex[ 2 ] ); 
	_shadow_model->set( _shadow_idx * 6 + 2, vertex[ 1 ] ); 
	_shadow_model->set( _shadow_idx * 6 + 3, vertex[ 1 ] ); 
	_shadow_model->set( _shadow_idx * 6 + 4, vertex[ 2 ] ); 
	_shadow_model->set( _shadow_idx * 6 + 5, vertex[ 3 ] ); 

	_shadow_idx++;
}

void Drawer::setModelMDL( const ModelMDL& model_mdl ) {
	assert( _model_mdl_idx < MODEL_MDL_NUM );
	_model_mdl[ _model_mdl_idx ] = model_mdl;
	_model_mdl_idx++;
}

void Drawer::setBillboard( const Billboard& billboard ) {
	assert( _billboard_idx < GRAPHIC_ID_NUM );
	_billboard[ _billboard_idx ] = billboard;
	_billboard_idx++;
}

void Drawer::flip( ) {
	if ( _refresh_count == 0 ) {
		_start_time = GetNowCount( );
	}
	if ( _refresh_count == REFRESH_COUNT ){ //60フレーム目なら平均を計算する
		int frame_time_sum = GetNowCount( ) - _start_time;//かかった時間
		double frame_time_avg = frame_time_sum / REFRESH_COUNT;//平均
		if ( frame_time_avg != 0.0 ) {
			_fps = 1000.0 / frame_time_avg;
		}
		_refresh_count = 0;
		_start_time = GetNowCount( );
	}
	_refresh_count++;

	int took_time = GetNowCount( ) - _start_time;	//かかった時間
	int wait_time = _refresh_count * 1000 / FPS - took_time;	//待つべき時間
	if ( wait_time > 0 ) {
		Sleep( wait_time );	//待機
	}
	

	ScreenFlip( );
	ClearDrawScreen( );
}

double Drawer::getEndAnimTime( int motion ) {
	return MV1GetAnimTotalTime( _model_id[ motion ].body, _model_id[ motion ].body_anim );
}

void Drawer::drawLine( int x1, int y1, int x2, int y2 ) {
	DrawLine( x1, y1, x2, y2, 0xFFFFFF ) ;
}

void Drawer::drawString( int x, int y, const char* string, ... ) {
	char buf[ 1024 ];
	va_list ap;
	unsigned int color = 0xFFFFFF;
	va_start( ap, string );
	vsprintf_s( buf, 1024, string, ap );
	DrawString( x, y, buf, color );
	va_end( ap );
}
