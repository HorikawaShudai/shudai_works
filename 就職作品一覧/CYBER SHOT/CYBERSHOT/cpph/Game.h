//=============================================================================
//
//ゲーム画面処理 [game.h]
// Author : 堀川萩大
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_


//画面モードの種類
typedef enum
{
	GAMEMODE_NONE = 0,	//タイトル画面
	GAMEMODE_GAMECLEAR,		//攻撃選択画面
	GAMEMODE_GAMEOVER,		//ゲーム画面
	GAMEMODE_POUSE,	//リザルト画面
	GAMEMODE_MAX
}GAMEMODE;

#include "main.h"

//プロタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
GAMEMODE GetGamemode(void);
void SetGamemode(GAMEMODE mode);
void SetEnablePause(bool bPause);
bool GetPouse(void);
#endif