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

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureResult = {}; //リザルトの数のテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffresult = NULL;  //リザルトの数の頂点バッファ

//=========================================================================================================
//リザルトの初期化処理
//=========================================================================================================
void InitResult(void)
{
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
		"data\\TEXTURE\\clear.jpg",
		&g_pTextureResult);


	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffresult->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffresult->Unlock();
	PlaySound(SOUND_LABEL_BGM008);
}

//=========================================================================================================
//リザルトの終了処理
//=========================================================================================================
void UninitResult(void)
{

	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
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
	PDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffresult, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

		pDevice->SetTexture(0, g_pTextureResult);

	//ポリゴン
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}