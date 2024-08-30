//===========================================================
//
//ライフの処理操作
//Author:堀川萩大
//
//===========================================================
#include "game.h"
#include "player.h"
#include "Enagy.h"

//マクロ定義
#define NUM_LIFE (20) //ライフの最大数

//ライフの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;	    //色
	bool bUse;
}LIFE;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureEnagy = NULL;		//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnagy = NULL;	//頂点バッファのポインタ
D3DXVECTOR3 g_posEnagy;							//ライフの位置
LIFE g_aEnagy[NUM_LIFE];

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitEnagy(void)
{


	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnagy;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enagy.png",
		&g_pTextureEnagy);

	//ライフの情報の初期化
	g_posEnagy = D3DXVECTOR3(190.0f, 40.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnagy,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffEnagy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnagy = 0; nCntEnagy < NUM_LIFE; nCntEnagy++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_posEnagy.x + (40.0f*nCntEnagy)
			, g_posEnagy.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posEnagy.x + 40.0f + (40.0f*nCntEnagy)
			, g_posEnagy.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posEnagy.x + (40.0f*nCntEnagy)
			, g_posEnagy.y + 40.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posEnagy.x + 40.0f + (40.0f*nCntEnagy)
			, g_posEnagy.y + 40.0f, 0.0f);
		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_aEnagy[nCntEnagy].bUse = false;

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnagy->Unlock();

	PLAYER aPlayer = GetPlayer();
	for (int nCnt = 0; nCnt < aPlayer.nEnagy; nCnt++)
	{
		g_aEnagy[nCnt].bUse = true;
	}

}

//=========================================================================================================
//終了処理
//=========================================================================================================
void UninitEnagy(void)
{
	//テクスチャの破棄
	if (g_pTextureEnagy != NULL)
	{
		g_pTextureEnagy->Release();
		g_pTextureEnagy = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEnagy != NULL)
	{
		g_pVtxBuffEnagy->Release();
		g_pVtxBuffEnagy = NULL;
	}
}

//=========================================================================================================
//更新処理
//=========================================================================================================
void UpdateEnagy(void)
{
	PLAYER aPlayer = GetPlayer();
	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffEnagy->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntEnagy = 0; nCntEnagy < NUM_LIFE; nCntEnagy++)
	{
		if (g_aEnagy[nCntEnagy].bUse == true)
		{
			if (aPlayer.nEnagy > nCntEnagy)
			{
				g_aEnagy[nCntEnagy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else if (aPlayer.nEnagy <= nCntEnagy)
			{
				g_aEnagy[nCntEnagy].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			}

			//頂点カラー
			pVtx[0].col =g_aEnagy[nCntEnagy].col;
			pVtx[1].col =g_aEnagy[nCntEnagy].col;
			pVtx[2].col =g_aEnagy[nCntEnagy].col;
			pVtx[3].col =g_aEnagy[nCntEnagy].col;

			pVtx += 4;
		}
	}
}

//=========================================================================================================
//描画処理
//=========================================================================================================
void DrawEnagy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnagy;

	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnagy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureEnagy);

	for (nCntEnagy = 0; nCntEnagy < NUM_LIFE; nCntEnagy++)
	{
		if (g_aEnagy[nCntEnagy].bUse == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnagy * 4, 2);  //右から二番目を変えないとまずい！！
		}
	}
}