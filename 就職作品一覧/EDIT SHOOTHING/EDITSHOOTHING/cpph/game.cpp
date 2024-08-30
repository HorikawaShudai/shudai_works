//=============================================================================
//
//ゲーム画面処理 [game.h]
// Author : 堀川萩大
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "effect.h"
#include "pause.h"
#include "main.h"
#include "life.h"
#include "Item.h"
#include "PowerupUI.h"


//グローバル変数宣言
bool g_bPause;
int g_nCntFade;
GAMEMODE g_Gamemode;

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
	//プレイヤーの初期化処理
	InitPlayer();
	//弾の初期化処理
	InitBullet();
	//爆発の初期化処理
	InitExplosion();
	//敵の初期化処理
	InitEnemy();
	////エフェクトの初期化処理
	InitEffect();
	//ライフの初期化処理
	InitLife();
	//アイテムの初期化処理
	InitItem();
	//UIの初期化処理

	InitPwUi();
	InitPause();

	InitScore();
	SetScore(0);

	//サウンドの初期化処理
	PlaySound(SOUND_LABEL_BGM005);
}

//=========================================================================================================
//ゲーム画面の終了処理
//=========================================================================================================
void UninitGame(void)
{
	//背景の終了処理
	UninitBg();
	//弾の終了処理
	UninitBullet();
	//敵の終了処理
	UninitEnemy();
	//爆発の終了処理
	UninitExplosion();
	//ポリゴンの終了処理
	UninitPlayer();
	//ライフの終了処理
	UninitLife();
	////エフェクトの終了処理
	UninitEffect();
	//スコアの終了処理
	UninitScore();
	//アイテムの終了処理
	UninitItem();
	//ポーズメニューの初期化処理
	InitPause();
	//ポーズメニューの終了処理
	UninitPause();
	//UIの終了処理
	UninitPwUi();

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
	/*int nNumEnemy = *GetNumEnemy();
	Enemy aEnemy = *GetEnemy();*/

	if (g_bPause == false)
	{
		//背景の更新処理
		UpdataBg();
		//プレイヤーの更新処理
		UpdataPlayer();
		//ライフの更新処理
		UpdataLife();
		//弾の更新処理
		UpdataBullet();
		//敵の更新処理
		UpdataEnemy();
		////エフェクトの更新処理
		UpdataEffect();
		//スコアの更新処理
		UpdataScore();
		//アイテムの更新処理
		UpdataItem();
		//爆発の更新処理
		UpdataExplosion();
		//UIの更新処理
		UpdataPwUi();
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

	if (GetKeyboardTrigger(DIK_P) == true && fFade == FADE_NONE && aPlayer.life > 0  &&g_Gamemode ==GAMEMODE_NONE)
	{
		SetGameMode(GAMEMODE_POUSE);
	}

}

//=========================================================================================================
//ゲーム画面の描画処理
//=========================================================================================================
void DrawGame(void)
{
	//背景の描画処理
	DrawBg();
	//弾の描画処理
	DrawBullet();
	//プレイヤーの描画処理
	DrawPlayer();
	//ライフの描画処理
	DrawLife();	
	//敵の描画処理
	DrawEnemy();
	//爆発の描画処理
	DrawExplosion();
	////エフェクトの描画処理
	DrawEffect();
	//スコアの描画処理
	DrawScore();
	//アイテムの描画処理
	DrawItem();
	DrawPwUi();

	Player aPlayer = *GetPlayer();

	if (g_bPause == true && aPlayer.life > 0)
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