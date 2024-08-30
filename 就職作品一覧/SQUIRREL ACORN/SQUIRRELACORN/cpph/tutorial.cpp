//===========================================================
//
//リザルトの処理操作
//Author:堀川萩大
//
//===========================================================
#include "tutorial.h"
#include "Input.h"
#include "sound.h"
#include "fade.h"

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureTutorial = {}; //リザルトの数のテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;  //リザルトの数の頂点バッファ

 //=========================================================================================================
 //リザルトの初期化処理
 //=========================================================================================================
void InitTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tutrial.jpg",
		&g_pTextureTutorial);


	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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

	//頂点バッファをアンロックする
	g_pVtxBuffTutorial->Unlock();
	PlaySound(SOUND_LABEL_BGM006);
}

//=========================================================================================================
//リザルトの終了処理
//=========================================================================================================
void UninitTutorial(void)
{

	if (g_pTextureTutorial != NULL)
	{
		g_pTextureTutorial->Release();
		g_pTextureTutorial = NULL;
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
//リザルトの更新処理
//=========================================================================================================
void UpdateTutorial(void)
{
	FADE fFade;
	fFade = GetFade();
	if (GetKeyboardTrigger(DIK_RETURN) == true && fFade == FADE_NONE)
	{//spaceのみ押された場合
		SetFade(MODE_GAME, 0.05f);
		return;
	}
}

//=========================================================================================================
//リザルトの描画処理
//=========================================================================================================
void DrawTutorial(void)
{
	PDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_pTextureTutorial);

	//ポリゴン
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}