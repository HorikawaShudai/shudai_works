//=============================================================================
//
//ゲーム画面処理 [game.h]
// Author : 堀川萩大
//
//=============================================================================
#include <stdio.h>
#include "game.h"
#include "bg.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "main.h"
#include "block.h"
//#include "bullet.h"
//#include "enemy.h"
//#include "explosion.h"
//#include "score.h"
#include "sound.h"
//#include "effect.h"
#include "pause.h"
#include "life.h"
#include "Item.h"
#include "DethUi.h"
#include "CreateMap.h"


//グローバル変数宣言
bool g_bPause;
int g_nCntFade;
GAMEMODE g_Gamemode;
void DrawPos(void);
void DrawPBlock(void);

//=========================================================================================================
//ゲーム画面の初期化処理
//=========================================================================================================
void InitGame(void)
{
	g_bPause = false;
	g_nCntFade = 0;
	g_Gamemode = GAMEMODE_NONE; 

	//背景の初期化処理
	InitBg();
	//ブロックの初期化処理
	InitBlock();
	//プレイヤーの初期化処理
	InitPlayer();
	//ライフの初期化処理
	InitLife();
	//アイテムの初期化処理
	InitItem();
	//UIの初期化処理
	InitDethUi();
	InitPause();

	//マップ生成
	LoadMap();


	////弾の初期化処理
	//InitBullet();
	//爆発の初期化処理
	//InitExplosion();
	////敵の初期化処理
	//InitEnemy();
	//////エフェクトの初期化処理
	//InitEffect();


	//InitScore();
	//SetScore(0);

	////サウンドの初期化処理
	PlaySound(SOUND_LABEL_BGM007);
}

//=========================================================================================================
//ゲーム画面の終了処理
//=========================================================================================================
void UninitGame(void)
{
	//背景の終了処理
	UninitBg();
	//ブロックの終了処理
	UninitBlock();
	//プレイヤーの終了処理
	UninitPlayer();
	//ライフの終了処理
	UninitLife();
	//アイテムの終了処理
	UninitItem();
	//ポーズメニューの終了処理
	UninitPause();
	//UIの終了処理
	UninitDethUi();
	////弾の終了処理
	//UninitBullet();
	////敵の終了処理
	//UninitEnemy();
	////爆発の終了処理
	//UninitExplosion();
	////エフェクトの終了処理
	//UninitEffect();
	////スコアの終了処理
	//UninitScore();
	////ポーズメニューの初期化処理
	//InitPause();

	//サウンドの停止
	StopSound();
}

//=========================================================================================================
//ゲーム画面の更新処理
//=========================================================================================================
void UpdateGame(void)
{
	Player aPlayer = *GetPlayer();
	FADE fFade = GetFade();

	if (g_bPause == false)
	{
		//背景の更新処理
		UpdataBg();
		//ブロックの更新処理
		UpdateBlock();
		//プレイヤーの更新処理
		UpdatePlayer();
		//ライフの更新処理
		UpdataLife();
		//アイテムの更新処理
		UpdataItem();
		////UIの更新処理
		UpdataDethUi();

		////弾の更新処理
		//UpdataBullet();
		//敵の更新処理
		//UpdataEnemy();
		//////エフェクトの更新処理
		//UpdataEffect();
		////スコアの更新処理
		//UpdataScore();
		////爆発の更新処理
		//UpdataExplosion();
	}
	//ポーズメニューの更新処理
	UpdataPause();
	//スコアの更新処理
	UpdateFade();

	switch (g_Gamemode)
	{
	case GAMEMODE_NONE :
		break;

	case	GAMEMODE_GAMECLEAR:
		g_nCntFade++;
		if (g_nCntFade == 120)
		{
			SetFade(MODE_RESULT, 0.01f);
		}
		break;
	case GAMEMODE_GAMEOVER:
		g_nCntFade++;
		if (g_nCntFade == 120)
		{
			SetFade(MODE_RESULT, 0.01f);

		}
		break;
	case GAMEMODE_POUSE:
		SetEnablePause(true);

		break;




	}

	if (GetKeyboardTrigger(DIK_P) == true && fFade == FADE_NONE &&g_Gamemode ==GAMEMODE_NONE)
	{
		SetGameMode(GAMEMODE_POUSE);
	}

}

//=========================================================================================================
//ゲーム画面の描画処理
//=========================================================================================================
void DrawGame(void)
{
	Player aPlayer = *GetPlayer();

	//背景の描画処理
	DrawBg();
	//ブロックの描画処理
	DrawBlock();
	//プレイヤーの描画処理
	DrawPlayer();
	//ライフの描画処理
	DrawLife();	
	//アイテムの描画処理
	DrawItem();
	//DrawPos();
	//DrawPBlock();

	//弾の描画処理
	//DrawBullet();
	//敵の描画処理
	//DrawEnemy();
	//爆発の描画処理
	//DrawExplosion();
	////エフェクトの描画処理
	//DrawEffect();
	////スコアの描画処理
	//DrawScore();

	if (aPlayer.nType == PLAYERSTATE_DETH)
	{
		//UIの描画処理
		DrawDethUi();
	}
	if (g_bPause == true)
	{
		//ポーズメニューの描画処理
		DrawPause();
	}
}

void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

bool GetPouse(void)
{
	return g_bPause;
}

void SetGameMode(GAMEMODE mode)
{
	g_Gamemode = mode;
}

GAMEMODE GetGamemode(void)
{
	return g_Gamemode;
}

//=========================================================================================================
//FPSの描画処理
//=========================================================================================================
void DrawPos(void)
{
	LPD3DXFONT pFont = GetFont();
	D3DXVECTOR3 World = GetWorld();
	Player aPlayer = *GetPlayer();


	RECT rect = { 100,100,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[1024];

	//文字列に代入
	//wsprintf(&aStr[0], "%.1f"/*\n y  %f\n Cx  %f\n  Cy%f\n  move.x  %f\n  move.y  %f*/, pos[4]/*, pos[1], pos[2], pos[3], pos[4], pos[5]*/);


	sprintf(&aStr[0], "%.3f \n%.3f", aPlayer.pos.x, aPlayer.pos.y);
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}