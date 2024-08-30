//===========================================================
//
//メイン処理
//Author:堀川萩大
//
//===========================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800) //ビルド時の警告対処用ビルド
#include "dinput.h"
#include "xaudio2.h"

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")	//システム時刻の取得
#pragma comment(lib,"dinput8.lib")

#define SCREEN_WIDTH			(1280)	 //ウィンドウサイズ（幅）
#define SCREEN_HEIGHT			(720)	 //ウィンドウサイズ（高さ）
#define FVF_VERTEX_2D (D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_TEX1) //頂点フォーマット

typedef struct
{
	D3DXVECTOR3 pos; //頂点座標	
	float rhw;		 //座標変換用係数(1.0fで固定)
	D3DCOLOR col;	 //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
}VERTEX_2D;

//画面モードの種類
typedef enum
{
	MODE_TITLE = 0,	//タイトル画面
	MODE_EDIT,		//攻撃選択画面
	MODE_GAME,		//ゲーム画面
	MODE_RESULT,	//リザルト画面
	MODE_MAX
}MODE;

//プロタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
#endif

