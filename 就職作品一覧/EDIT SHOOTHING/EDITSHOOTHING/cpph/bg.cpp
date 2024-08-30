//===========================================================
//
//背景の処理操作
//Author:堀川萩大
//
//===========================================================
#include "Bg.h"
#include "game.h"
#include "Input.h"

//マクロ定義
#define NUM_BG (3)				//背景の最大数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBg[NUM_BG] = {}; //背景の数のテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;  //背景の数の頂点バッファ
float g_aTexV[NUM_BG];                        //背景の移動量V値
float g_aTexU[NUM_BG];                        //背景の移動量U値

//=========================================================================================================
//背景の初期化処理
//=========================================================================================================
void InitBg(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4*NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG\\bg200.jpg",
		&g_pTextureBg[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG\\bg100.png",
		&g_pTextureBg[1]);	
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG\\bg102.png",
		&g_pTextureBg[2]);

	//テクスチャ座標（3枚分）の開始位置の初期化
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aTexV[nCntBG] = 0.0f;
	}

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
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
		pVtx[0].tex = D3DXVECTOR2(0.0f - g_aTexU[nCntBG], g_aTexV[nCntBG]);
		pVtx[1].tex = D3DXVECTOR2(1.0f - g_aTexU[nCntBG], g_aTexV[nCntBG]);
		pVtx[2].tex = D3DXVECTOR2(0.0f - g_aTexU[nCntBG], g_aTexV[nCntBG] + 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f - g_aTexU[nCntBG], g_aTexV[nCntBG] + 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBg->Unlock();
}

//=========================================================================================================
//背景の終了処理
//=========================================================================================================
void UninitBg(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (g_pTextureBg[nCntBG] != NULL)
		{
			g_pTextureBg[nCntBG]->Release();
			g_pTextureBg[nCntBG] = NULL;
		}
	}
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
}

//背景の更新処理
void UpdataBg(void)
{
	int nCntBG;

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);
	
	g_aTexV[0] -= 0.000f;
	g_aTexV[1] -= 0.000f;
	g_aTexV[2] -= 0.000f;
	g_aTexU[0] -= 0.0001f;
	g_aTexU[1] -= 0.003f;
	g_aTexU[2] -= 0.002f;
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{	
		
		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f- g_aTexU[nCntBG], g_aTexV[nCntBG]);
		pVtx[1].tex = D3DXVECTOR2(1.0f- g_aTexU[nCntBG], g_aTexV[nCntBG]);
		pVtx[2].tex = D3DXVECTOR2(0.0f- g_aTexU[nCntBG], g_aTexV[nCntBG] + 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f- g_aTexU[nCntBG], g_aTexV[nCntBG] + 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBg->Unlock();
}

//=========================================================================================================
//背景の描画処理
//=========================================================================================================
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBG;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		pDevice->SetTexture(0, g_pTextureBg[nCntBG]);

		//ポリゴン
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCntBG, 2);
	}
}