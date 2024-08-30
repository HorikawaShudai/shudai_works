//===========================================================
//
//リザルトの処理操作
//Author:堀川萩大
//
//===========================================================
#include "result.h"
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
#include "Shadow.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureResult[2] = {}; //リザルトの数のテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffresult = NULL;  //リザルトの数の頂点バッファ

//=========================================================================================================
//リザルトの初期化処理
//=========================================================================================================
void InitResult(void)
{
	InitLight();
	InitCamera();
	InitMeshIndex();
	InitShadow();

	GAMEMODE aMode = GetGamemode();

	if (aMode == GAMEMODE_GAMEOVER)
	{
		//サウンドの初期化処理
		PlaySound(SOUND_LABEL_SE_LOSE);
		InitEndPlayer();
	}
	else if (aMode == GAMEMODE_GAMECLEAR)
	{
		//サウンドの初期化処理
		PlaySound(SOUND_LABEL_SE_WIN);
		InitClearPlayer();
	}

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffresult,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\end_001.png",
		&g_pTextureResult[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\clear.png",
		&g_pTextureResult[1]);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffresult->Lock(0, 0, (void**)&pVtx, 0);
	for (int nResCnt = 0; nResCnt < 2; nResCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(300.0f, 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1040.0f, 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1040.0f, 300.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffresult->Unlock();
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetPosCamera(D3DXVECTOR3(300.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 50.0f, 0.0f));
}

//=========================================================================================================
//リザルトの終了処理
//=========================================================================================================
void UninitResult(void)
{
	UninitLight();
	UninitCamera();
	UninitPlayer();
	UninitMeshIndex();
	UninitShadow();
	for (int nResCnt = 0; nResCnt < 2; nResCnt++)
	{
		if (g_pTextureResult[nResCnt] != NULL)
		{
			g_pTextureResult[nResCnt]->Release();
			g_pTextureResult[nResCnt] = NULL;
		}
	}
	if (g_pVtxBuffresult != NULL)
	{
		g_pVtxBuffresult->Release();
		g_pVtxBuffresult = NULL;
	}
	//サウンドの停止
	StopSound();
}

//=========================================================================================================
//リザルトの更新処理
//=========================================================================================================
void UpdateResult(void)
{
	//UpdateLight();
	UpdateShadow();
	EndCamera();
	FADE fFade;
	fFade = GetFade();
	if (GetKeyboardTrigger(DIK_RETURN) == true && fFade == FADE_NONE)
	{//spaceのみ押された場合
		SetFade(MODE_TITLE,0.05f);
		return;
	}
}

//=========================================================================================================
//リザルトの描画処理
//=========================================================================================================
void DrawResult(void)
{
	SetEndCam();
	DrawPlayer();
	DrawMeshIndex();
	DrawShadow();
	PDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffresult, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	GAMEMODE aMode = GetGamemode();

	if (aMode == GAMEMODE_GAMEOVER)
	{
		pDevice->SetTexture(0, g_pTextureResult[0]);
	}
	else if (aMode == GAMEMODE_GAMECLEAR)
	{
		pDevice->SetTexture(0, g_pTextureResult[1]);
	}

	//ポリゴン
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}