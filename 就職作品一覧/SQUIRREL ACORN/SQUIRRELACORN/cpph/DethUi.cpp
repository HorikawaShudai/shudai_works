//===========================================================
//
//UIの処理操作
//Author:堀川萩大
//
//===========================================================
#include "DethUi.h"
#include "game.h"

//マクロ定義

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureDethUi = NULL; //UIの数のテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDethUi = NULL;  //UIの数の頂点バッファ


//=========================================================================================================
//UIの初期化処理
//=========================================================================================================
void InitDethUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDethUi,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\DETH.png",
		&g_pTextureDethUi);


	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffDethUi->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(320.0f, 200.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(960.0f, 200.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(320.0f, 550.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(960.0f, 550.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffDethUi->Unlock();
}

//=========================================================================================================
//UIの終了処理
//=========================================================================================================
void UninitDethUi(void)
{
	if (g_pTextureDethUi != NULL)
	{
		g_pTextureDethUi->Release();
		g_pTextureDethUi = NULL;
	}

	if (g_pVtxBuffDethUi != NULL)
	{
		g_pVtxBuffDethUi->Release();
		g_pVtxBuffDethUi = NULL;
	}
}

//UIの更新処理
void UpdataDethUi(void)
{

}

//=========================================================================================================
//UIの描画処理
//=========================================================================================================
void DrawDethUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffDethUi, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);


	pDevice->SetTexture(0, g_pTextureDethUi);

	//ポリゴン
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}