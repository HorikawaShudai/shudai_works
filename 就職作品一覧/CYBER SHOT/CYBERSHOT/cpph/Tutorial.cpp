//===========================================================
//
//チュートリアルの処理操作
//Author:堀川萩大
//
//===========================================================
#include "Tutorial.h"
#include "Input.h"
#include "sound.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"
#include "Game.h"
#include "Light.h"
#include "Camera.h"
#include "Player.h"
#include "MeshIndex.h"
#include "Bullet.h"
#include "LifeGuage.h"
#include "Enemy.h"
#include "Object.h"
#include "Item.h"
#include "Effect.h"
#include "Shadow.h"
#include "Explosion.h"
#include "MeshWall.h"
#include "Enagy.h"


#define NUM_TUTORIAL (3)

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureTutorial[NUM_TUTORIAL] = {}; //チュートリアルの数のテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;  //チュートリアルの数の頂点バッファ
TEXT g_Text[NUM_TUTORIAL] = {};
D3DXCOLOR g_TextCol;
D3DXCOLOR g_TextFade;

//プロトタイプ宣言
void DrawCntroll(void);
void TutorialCntrol(void);
void FadeText(void);

//=========================================================================================================
//チュートリアルの初期化処理
//=========================================================================================================
void InitTutorial(void)
{
	InitCamera();
	InitMeshIndex();
	InitLight();
	InitItem();
	InitObject();
	InitShadow();
	InitPlayer();
	InitEnemy();
	InitBullet();
	InitLifeGuage();
	InitObject();
	InitItem();
	InitEffect();
	InitExplosion();
	InitMeshWall();
	InitEnagy();

	PlaySound(SOUND_LABEL_BGM002);


	g_TextCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_TextFade = D3DXCOLOR (0.0f,0.0f,0.0f,0.01f);
	g_Text[0].nCntText = 0;
	g_Text[1].nCntText = 0;
	g_Text[2].nCntText = 0;
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TUTORIAL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\TextWindow.png",
		&g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Text_Tutorial.png",
		&g_pTextureTutorial[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Skip_Text.png",
		&g_pTextureTutorial[2]);


	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt <NUM_TUTORIAL; nCnt++)
	{
		if (nCnt == 1)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(250.0f, 500.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1090.0f, 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(250.0f, 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1090.0f, 600.0f, 0.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 0.125f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.125f);
		}
		else if( nCnt == 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(200.0f, 500.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1140.0f, 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(200.0f, 630.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1140.0f, 630.0f, 0.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		else
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(1000.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1240.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1000.0f, 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1240.0f, 50.0f, 0.0f);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = g_TextCol;
		pVtx[1].col = g_TextCol;
		pVtx[2].col = g_TextCol;
		pVtx[3].col = g_TextCol;


		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();

	g_Text[0].bUse = true;
	g_Text[1].bUse = true;
	g_Text[2].bUse = true;
}

//=========================================================================================================
//チュートリアルの終了処理
//=========================================================================================================
void UninitTutorial(void)
{
	UninitLight();
	UninitCamera();
	UninitPlayer();
	UninitMeshIndex();
	UninitBullet();
	UninitEnemy();
	UninitLifeGuage();
	UninitObject();
	UninitItem();
	UninitShadow();
	UninitEffect();
	UninitExplosion();
	UninitMeshWall();
	UninitEnagy();


	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (g_pTextureTutorial[nCnt] != NULL)
		{
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
	//サウンドの停止
	StopSound();
}

//=========================================================================================================
//チュートリアルの更新処理
//=========================================================================================================
void UpdateTutorial(void)
{
	UpdateLight();
	UpdateCamera();
	UpdateMeshWall();
	UpdatePlayer();
	UpdateMeshIndex();
	UpdateBullet();
	UpdateEnemy();
	UpdatePlayerGuage();
	UpdateEnemyGuage();
	UpdateObject();
	UpdateItem();
	UpdateText();
	UpdateEffect();
	UpdateShadow();
	UpdateExplosion();
	UpdateEnagy();
	
}

//=========================================================================================================
//チュートリアルの描画処理
//=========================================================================================================
void DrawTutorial(void)
{
	SetCamera();
	DrawMeshIndex();
	DrawMeshWall();
	DrawShadow();
	DrawEffect();
	DrawBullet();
	DrawExplosion();
	DrawPlayer();
	DrawPlayerGuage();
	DrawEnagy();
	DrawEnemy();
	DrawObject();
	DrawItem();
	DrawLifeGuage();
	FadeText();
	TutorialCntrol();
	if (g_Text[0].bUse == false)
	{
		DrawCntroll();
	}
	for (int nCnt = 0; nCnt < NUM_TUTORIAL; nCnt++)
	{
		if (g_Text[nCnt].bUse == true)
		{
			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

			pDevice->SetFVF(FVF_VERTEX_2D);

			GAMEMODE aMode = GetGamemode();

			pDevice->SetTexture(0, g_pTextureTutorial[nCnt]);

			//ポリゴン
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt*4, 2);
		}
	}
}
//=========================================================================================================
//チュートリアルの操作処理
//=========================================================================================================
void TutorialCntrol(void)
{
	FADE fFade;
	fFade = GetFade();
	PLAYER aPlayer = GetPlayer();

	if (GetKeyboardTrigger(DIK_1) == true && fFade == FADE_NONE)
	{
		SetEnemy(aPlayer.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\Enemy001.x");

	}
	if (GetKeyboardTrigger(DIK_3) == true && fFade == FADE_NONE)
	{
		SetObject(D3DXVECTOR3(aPlayer.pos.x + 50.0f, 0.0f, aPlayer.pos.z + 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\WoodBox.x");

	}

	if (GetKeyboardTrigger(DIK_9) == true && fFade == FADE_NONE)
	{//spaceのみ押された場合
		SetFade(MODE_GAME, 0.05f);
		return;
	}
}


//=========================================================================================================
//テキストのフェード処理
//=========================================================================================================
void FadeText(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);
	//pVtx += 8;
	g_TextCol.a -= g_TextFade.a;

	pVtx[0].col = g_TextCol;
	pVtx[1].col = g_TextCol;
	pVtx[2].col = g_TextCol;
	pVtx[3].col = g_TextCol;

	if (g_TextCol.a < 0.0f || g_TextCol.a > 1.0f)
	{
		g_TextFade *= -1.0f;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();
}

//=========================================================================================================
//テキストの更新処理
//=========================================================================================================
void UpdateText(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_Text[1].nCntText++;
		if (g_Text[1].nCntText == 1)
		{
			SetEnemy(D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), "data\\MODEL\\Enemy001.x");
		}
		if (g_Text[1].nCntText == 4)
		{
			SetObject(D3DXVECTOR3(400.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\WoodBox.x");
		}
		if (g_Text[1].nCntText >= 8)
		{
			g_Text[0].bUse = false;
			g_Text[1].bUse = false;
			g_Text[2].bUse = false;
		}
	}
	VERTEX_2D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f+(0.125f*g_Text[1].nCntText));
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f+(0.125f*g_Text[1].nCntText));
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.125f + (0.125f*g_Text[1].nCntText));
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.125f + (0.125f*g_Text[1].nCntText));

	//頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();
}

//=========================================================================================================
//視点操作方法の描画処理
//=========================================================================================================
void DrawCntroll (void)
{
	LPD3DXFONT pFont = GetFont();

	RECT rect = { 0,20,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "====モデル操作====\nWASD:移動\nK:回避ダッシュ\nSPACE:攻撃\n\n====注視点操作====\nI:向き固定\nJL:カメラ旋回\n\n----チュートリアル限定----\n1:敵設置\n3:木箱設置\n8:HP回復\n\n9:ゲームスタート\nスタート後Pでポーズメニューへ");


	pFont->DrawText(NULL, &aStr[0], -5, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}