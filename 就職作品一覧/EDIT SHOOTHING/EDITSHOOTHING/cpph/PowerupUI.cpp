//===========================================================
//
//UIの処理操作
//Author:堀川萩大
//
//===========================================================
#include "PowerupUI.h"
#include "game.h"
//#include "main.h"
#include "Input.h"
#include "Player.h"

//マクロ定義
#define NUM_UI (4)				//UIの最大数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePwUi = NULL; //UIの数のテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPwUi = NULL;  //UIの数の頂点バッファ


 //=========================================================================================================
 //UIの初期化処理
 //=========================================================================================================
void InitPwUi(void)
{
	int nCntUI;

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_UI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		& g_pVtxBuffPwUi ,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\PW_UI.png",
		&g_pTexturePwUi);


	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	 g_pVtxBuffPwUi ->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntUI = 0; nCntUI < NUM_UI; nCntUI++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(300.0f+(100.0f*nCntUI), 650.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(400.0f+(100.0f*nCntUI), 650.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(300.0f+(100.0f*nCntUI), 700.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(400.0f+(100.0f*nCntUI), 700.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.001f +(0.25f*nCntUI),0.01f);
		pVtx[1].tex = D3DXVECTOR2(0.25f+(0.25f*nCntUI),0.01f);
		pVtx[2].tex = D3DXVECTOR2(0.001f +(0.25f*nCntUI),1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f+(0.25f*nCntUI),1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	 g_pVtxBuffPwUi ->Unlock();
}

//=========================================================================================================
//UIの終了処理
//=========================================================================================================
void UninitPwUi(void)
{
	if (g_pTexturePwUi != NULL)
	{
		g_pTexturePwUi->Release();
		g_pTexturePwUi = NULL;
	}

	if (g_pVtxBuffPwUi != NULL)
	{
		g_pVtxBuffPwUi->Release();
		g_pVtxBuffPwUi = NULL;
	}
}

//UIの更新処理
void UpdataPwUi(void)
{
	D3DXCOLOR ColSelect = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Player aPlayer = *GetPlayer();


	if (aPlayer.nPoint > 0)
	{
		VERTEX_2D *pVtx;
		//頂点バッファをロックし頂点情報へのポインタを取得
		g_pVtxBuffPwUi->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCnt = 0; nCnt < aPlayer.nPoint; nCnt++)
		{
			//頂点座標の設定
			pVtx[0].col = D3DXCOLOR(ColSelect);
			pVtx[1].col = D3DXCOLOR(ColSelect);
			pVtx[2].col = D3DXCOLOR(ColSelect);
			pVtx[3].col = D3DXCOLOR(ColSelect);
			pVtx += 4;

		}
		//頂点バッファをアンロックする
		g_pVtxBuffPwUi->Unlock();
	}

	if (GetKeyboardPress(DIK_B) == true)
	{
		ResetUI();
	}

}

//=========================================================================================================
//UIの描画処理
//=========================================================================================================
void DrawPwUi(void)
{
	int nCntUI;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPwUi, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);


	pDevice->SetTexture(0, g_pTexturePwUi);

	for (nCntUI = 0; nCntUI < NUM_UI; nCntUI++)
	{
		//ポリゴン
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntUI * 4, 2);
	}
}

//=========================================================================================================
//UIのリセット処理
//=========================================================================================================
void ResetUI(void)
{
	D3DXCOLOR ColNoSelect = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffPwUi->Lock(0, 0, (void**)&pVtx, 0);
	for (int nUiCnt = 0; nUiCnt < 4; nUiCnt++)
	{
		//頂点座標の設定
		pVtx[0].col = D3DXCOLOR(ColNoSelect);
		pVtx[1].col = D3DXCOLOR(ColNoSelect);
		pVtx[2].col = D3DXCOLOR(ColNoSelect);
		pVtx[3].col = D3DXCOLOR(ColNoSelect);
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPwUi->Unlock();
}