//=============================================================================
//
//ゲーム画面処理 [game.h]
// Author : 堀川萩大
//
//=============================================================================
#include "game.h"
#include "input.h"
#include "Light.h"
#include "MeshIndex.h"
#include "Camera.h"
#include "Player.h"
#include "Shadow.h"
#include "MeshWall.h"
#include "Item.h"
#include "Bullet.h"
#include "Explosion.h"
#include "effect.h"
#include "MeshIndex.h"
//#include "MeshCylinder.h"
#include "Object.h"
#include "Enemy.h"
#include "Pause.h"
#include "Enagy.h"
#include "LifeGuage.h"
#include "Sound.h"
#include "ModelBullet.h"


//グローバル変数宣言
bool g_bPause;
int g_nCntFade;
GAMEMODE g_Gamemode;

//=========================================================================================================
//ゲーム画面の初期化処理
//=========================================================================================================
void InitGame(void)
{
	//サウンドの初期化処理
	PlaySound(SOUND_LABEL_BGM000);
	g_bPause = false;
	g_nCntFade = 0;
	g_Gamemode = GAMEMODE_NONE;

	//カメラの初期化処理
	InitCamera();
	//ライトの初期化処理
	InitLight();
	//影の初期化処理
	InitShadow();
	//プレイヤーの初期化処理
	InitPlayer();
	//弾の初期化処理
	InitBullet();
	//弾の初期化処理
	InitModBull();
	//爆発の初期化処理
	InitExplosion();
	//敵の初期化処理
	InitEnemy();
	//敵設置
	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\Enemy000.x");
	//エフェクトの初期化処理
	InitEffect();
	//アイテムの初期化処理
	InitItem();
	//筒の初期化処理
	//InitMeshCylinder();
	//地面の初期化処理
	InitMeshIndex();
	//壁の初期化処理
	InitMeshWall();
	//オブジェクトの初期化処理
	InitObject();
	{//オブジェクト設置
		SetObject(D3DXVECTOR3(1100.0f, 50.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(-1100.0f, 50.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(500.0f, 50.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(-500.0f, 50.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(-800.0f, 50.0f, 1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(-800.0f, 50.0f, -1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(800.0f, 50.0f, 1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(800.0f, 50.0f, -1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		//SetObject(D3DXVECTOR3(-1100.0f, 50.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		//SetObject(D3DXVECTOR3(-1200.0f, 50.0f, -1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		//SetObject(D3DXVECTOR3(1200.0f, 50.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");

		SetObject(D3DXVECTOR3(1470.0f, 0.0f, -1470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\WoodBox.x");
		SetObject(D3DXVECTOR3(-1470.0f, 0.0f, -1470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\WoodBox.x");
		SetObject(D3DXVECTOR3(1470.0f, 0.0f, 1470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\WoodBox.x");
		SetObject(D3DXVECTOR3(-1470.0f, 0.0f, 1470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\WoodBox.x");
	}
	//ポーズの初期化処理
	InitPause();
	//エナジーの初期化処理
	InitEnagy();
	//ライフゲージの初期化処理
	InitLifeGuage();
}

//=========================================================================================================
//ゲーム画面の終了処理
//=========================================================================================================
void UninitGame(void)
{
	//カメラの終了処理
	UninitCamera();
	//弾の終了処理
	UninitBullet();
	UninitModBull();
	//敵の終了処理
	UninitEnemy();
	//爆発の終了処理
	UninitExplosion();
	//ポリゴンの終了処理
	UninitPlayer();
	//エフェクトの終了処理
	UninitEffect();
	//アイテムの終了処理
	UninitItem();
	//地面の終了処理
	UninitMeshIndex();
	//壁の終了処理
	UninitMeshWall();
	//筒の終了処理
	//UninitMeshCylinder();
	//ライトの終了処理
	UninitLight();
	//オブジェクトの終了処理
	UninitObject();
	//影の終了処理
	UninitShadow();
	//ポーズの終了処理
	UninitPause();
	//エナジーの終了処理
	UninitEnagy();
	//ライフゲージの終了処理
	UninitLifeGuage();
	//サウンドの停止
	StopSound();
}

//=========================================================================================================
//ゲーム画面の更新処理
//=========================================================================================================
void UpdateGame(void)
{
	UpdatePause();
	if (g_bPause == false)
	{
		UpdateCamera();
		//UpdateMeshCylinder();
		UpdateLight();
		UpdateShadow();
		UpdateBullet();
		UpdateModBull();
		UpdateExplosion();
		UpdateEffect();
		UpdateMeshWall();
		UpdateMeshIndex();
		UpdatePlayer();
		UpdateObject();
		UpdateEnemy();
		UpdateItem();
		UpdateEnagy();
		UpdatePlayerGuage();
		UpdateEnemyGuage();
	}
}

//=========================================================================================================
//ゲーム画面の描画処理
//=========================================================================================================
void DrawGame(void)
{
	SetCamera();
	DrawMeshIndex();
	//DrawMeshCylinder();
	DrawMeshWall();
	DrawEffect();
	DrawBullet();
	DrawModBull();
	DrawExplosion();
	DrawObject();
	DrawPlayer();
	DrawEnemy();
	DrawItem();
	DrawEnagy();
	DrawLifeGuage();
	DrawShadow();

	if (g_bPause == true)
	{
		DrawPause();
	}
}


GAMEMODE GetGamemode(void)
{
	return g_Gamemode;
}

void SetGamemode(GAMEMODE mode)
{
	g_Gamemode = mode;
}

void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

bool GetPouse(void)
{
	return g_bPause;
}