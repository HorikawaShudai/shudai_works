//===========================================================
//
//ライフの処理操作
//Author:堀川萩大
//
//===========================================================
#include "game.h"
#include "player.h"
#include "Enemy.h"
#include "LifeGuage.h"
#include "input.h"

//マクロ定義
#define NUM_LIFE (4) //ライフの最大数
#define GUAGE_HEIGHT (400.0f)

//ライフの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;	    //色
	LPDIRECT3DTEXTURE9 TexNum;
	int MaxLife;
}LIFE;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturelife = NULL;		//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufflife = NULL;	//頂点バッファのポインタ
LIFE g_aLifeGuage[NUM_LIFE];
//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitLifeGuage(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\gage.png",
		&g_pTexturelife);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufflife,
		NULL);
	PLAYER aPlayer = GetPlayer();
	ENEMY aEnemy = GetEnemy();

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBufflife->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < NUM_LIFE; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			g_aLifeGuage[nCnt].pos = D3DXVECTOR3(140.0f, 10.0f, 0.0f);
			g_aLifeGuage[nCnt].MaxLife = aPlayer.nLife;
			g_aLifeGuage[nCnt].TexNum = NULL;
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x + ((GUAGE_HEIGHT / g_aLifeGuage[nCnt].MaxLife)*aPlayer.nLife), g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y + 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x + ((GUAGE_HEIGHT / g_aLifeGuage[nCnt].MaxLife)*aPlayer.nLife), g_aLifeGuage[nCnt].pos.y + 20.0f, 0.0f);
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			break;
		case 1:
			g_aLifeGuage[nCnt].pos = D3DXVECTOR3(1140.0f, 10.0f, 0.0f);
			g_aLifeGuage[nCnt].MaxLife = aEnemy.nLife;
			g_aLifeGuage[nCnt].TexNum = NULL;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x - ((GUAGE_HEIGHT/ g_aLifeGuage[nCnt].MaxLife)*aEnemy.nLife), g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y + 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x - ((GUAGE_HEIGHT/ g_aLifeGuage[nCnt].MaxLife)*aEnemy.nLife), g_aLifeGuage[nCnt].pos.y + 20.0f, 0.0f);
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			break;

		case 2:

			g_aLifeGuage[nCnt].pos = D3DXVECTOR3(135.0f, 5.0f, 0.0f);
			g_aLifeGuage[nCnt].MaxLife = aPlayer.nLife;
			g_aLifeGuage[nCnt].TexNum = g_pTexturelife;
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x + 410.0f, g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y + 30.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x + 410.0f, g_aLifeGuage[nCnt].pos.y + 30.0f, 0.0f);
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case 3:
			g_aLifeGuage[nCnt].pos = D3DXVECTOR3(735.0f, 5.0f, 0.0f);
			g_aLifeGuage[nCnt].MaxLife = aEnemy.nLife;
			g_aLifeGuage[nCnt].TexNum = g_pTexturelife;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x + 410.0f, g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y + 30.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x + 410.0f, g_aLifeGuage[nCnt].pos.y + 30.0f, 0.0f);
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;


		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBufflife->Unlock();

}

//=========================================================================================================
//終了処理
//=========================================================================================================
void UninitLifeGuage(void)
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
void UpdatePlayerGuage(void)
{

	PLAYER aPlayer = GetPlayer();

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBufflife->Lock(0, 0, (void**)&pVtx, 0);


	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_aLifeGuage[0].pos.x, 
		g_aLifeGuage[0].pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aLifeGuage[0].pos.x + ((GUAGE_HEIGHT / g_aLifeGuage[0].MaxLife)*aPlayer.nLife), 
		g_aLifeGuage[0].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aLifeGuage[0].pos.x, 
		g_aLifeGuage[0].pos.y + 20.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aLifeGuage[0].pos.x + ((GUAGE_HEIGHT / g_aLifeGuage[0].MaxLife)*aPlayer.nLife), 
		g_aLifeGuage[0].pos.y + 20.0f, 0.0f);
	if (aPlayer.nLife <= 3)
	{
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else 
	{
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	}
	//頂点バッファをアンロックする
	g_pVtxBufflife->Unlock();
}
//=========================================================================================================
//更新処理
//=========================================================================================================
void UpdateEnemyGuage(void)
{

	ENEMY aEnemy = GetEnemy();

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBufflife->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;
	//頂点座標h
	pVtx[0].pos = D3DXVECTOR3(g_aLifeGuage[1].pos.x - ((GUAGE_HEIGHT / g_aLifeGuage[1].MaxLife)*aEnemy.nLife),
		g_aLifeGuage[1].pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aLifeGuage[1].pos.x, 
		g_aLifeGuage[1].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aLifeGuage[1].pos.x - ((GUAGE_HEIGHT / g_aLifeGuage[1].MaxLife)*aEnemy.nLife),
		g_aLifeGuage[1].pos.y + 20.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aLifeGuage[1].pos.x,
		g_aLifeGuage[1].pos.y + 20.0f, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBufflife->Unlock();
}

//=========================================================================================================
//描画処理
//=========================================================================================================
void DrawLifeGuage(void)
{

	LPDIRECT3DDEVICE9 pDevice;


	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBufflife, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	MODE aMode = GetMode();
	if (aMode == MODE_TUTORIAL)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_aLifeGuage[0].TexNum);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);  //右から二番目を変えないとまずい！！
																   //テクスチャの設定
		pDevice->SetTexture(0, g_aLifeGuage[2].TexNum);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * 2, 2);  //右から二番目を変えないとまずい！！
	}
	else if (aMode == MODE_GAME)
	{
		for (int nCnt = 0; nCnt < NUM_LIFE; nCnt++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_aLifeGuage[nCnt].TexNum);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);  //右から二番目を変えないとまずい！！
		}
	}

}

//=========================================================================================================
//描画処理
//=========================================================================================================
void DrawPlayerGuage(void)
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