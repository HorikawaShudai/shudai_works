//===========================================================
//
//ライフの処理操作
//Author:堀川萩大
//
//===========================================================
#include "game.h"
#include "player.h"
#include "life.h"
#include "input.h"

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
LPDIRECT3DTEXTURE9 g_pTexturelife = NULL;		//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufflife = NULL;	//頂点バッファのポインタ
LIFE g_aLife;

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitLife(void)
{
	Player aPlayer = *GetPlayer();

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player.png",
		&g_pTexturelife);

	//ライフの情報の初期化
	//g_aLife.pos = D3DXVECTOR3(190.0f, 10.0f, 0.0f);
	g_aLife.pos = D3DXVECTOR3(-50.0f, 10.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufflife,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBufflife->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aLife.pos.x, g_aLife.pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aLife.pos.x + (2.0f*aPlayer.nLifeFly), g_aLife.pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aLife.pos.x, g_aLife.pos.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aLife.pos.x + (2.0f*aPlayer.nLifeFly), g_aLife.pos.y + 20.0f, 0.0f);
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

		g_aLife.bUse = false;
	
	//頂点バッファをアンロックする
	g_pVtxBufflife->Unlock();

}

//=========================================================================================================
//終了処理
//=========================================================================================================
void UninitLife(void)
{
	//テクスチャの破棄
	if (g_pTexturelife != NULL)
	{
		g_pTexturelife->Release();
		g_pTexturelife = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBufflife != NULL)
	{
		g_pVtxBufflife->Release();
		g_pVtxBufflife = NULL;
	}
}

//=========================================================================================================
//更新処理
//=========================================================================================================
void UpdataLife(void)
{

	Player aPlayer = *GetPlayer();

		VERTEX_2D *pVtx;
		//頂点バッファをロックし頂点情報へのポインタを取得
		g_pVtxBufflife->Lock(0, 0, (void**)&pVtx, 0);
		//頂点座標h
		pVtx[0].pos = D3DXVECTOR3(g_aLife.pos.x+aPlayer.pos.x
			, g_aLife.pos.y + aPlayer.pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aLife.pos.x + (2.0f*aPlayer.nLifeFly)+aPlayer.pos.x
			, g_aLife.pos.y + aPlayer.pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aLife.pos.x+aPlayer.pos.x
			, g_aLife.pos.y + 20.0f + aPlayer.pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aLife.pos.x + (2.0f*aPlayer.nLifeFly)+aPlayer.pos.x
			, g_aLife.pos.y + 20.0f + aPlayer.pos.y, 0.0f);

		//頂点バッファをアンロックする
		g_pVtxBufflife->Unlock();
}

//=========================================================================================================
//描画処理
//=========================================================================================================
void DrawLife(void)
{
	Player aPlayer = *GetPlayer();

	if (GetKeyboardPress(DIK_LSHIFT) == true || GetKeyboardPress(DIK_RSHIFT) == true && aPlayer.bUse == true && aPlayer.bJump == true)
	{
		LPDIRECT3DDEVICE9 pDevice;


		pDevice = GetDevice();
		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBufflife, 0, sizeof(VERTEX_2D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);  //右から二番目を変えないとまずい！！
	}

}