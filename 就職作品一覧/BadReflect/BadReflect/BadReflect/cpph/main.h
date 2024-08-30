#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include "d3dx9.h"

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")	//システム時刻の取得
#include "xaudio2.h"
#include <assert.h>		// アサート処理に必要



#define SCREEN_HEIGHT			(1280)	 //ウィンドウサイズ（幅）
#define SCREEN_WIDTH			(720)	 //ウィンドウサイズ（高さ）
#define FVF_VERTEX_2D (D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_TEX1) //頂点フォーマット
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)


typedef struct
{
	D3DXVECTOR3 pos; //頂点座標	
	float rhw;		 //座標変換用係数(1.0fで固定)
	D3DCOLOR col;	 //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	D3DXVECTOR3 nor;		//法線ベクトル
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
}VERTEX_3D;

//前方宣言
class  CRenderer;
class  CObject;
class  CKeyboard;
class CManager;
class CBullet;
class CFade;
//プロタイプ宣言
//CRenderer *GetRenderer(void);
//CObject  **GetObject(void);


//メモリリーク出力用マクロ
#define _CRTCBG_MAP_ALLOC
#include <crtdbg.h>	//メモリリーク検出に必要

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif
#endif