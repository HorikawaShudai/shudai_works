//===========================================================
//
//アイテムの処理操作
//Author:堀川萩大
//
//===========================================================
#include "game.h"
//#include "main.h"
#include "Item.h"
#include "Input.h"
#include "enemy.h"
#include "player.h"

//マクロ定義
#define NUM_ITEM (80)				//アイテムの最大数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureItem = NULL; //アイテムの数のテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;  //アイテムの数の頂点バッファ
float g_TexV;                        //アイテムの移動量V値
float g_TexU;                        //アイテムの移動量U値
ITEM g_aItem[NUM_ITEM];



 //=========================================================================================================
 //アイテムの初期化処理
 //=========================================================================================================
void InitItem(void)
{
	int nCntItem;

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\dropitem.png",
		&g_pTextureItem);

	//テクスチャ移動速度の初期化
	g_TexV = 0.5f;	//アイテムの移動量V値
	g_TexU = 0.000f;	//アイテムの移動量U値

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f ,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f ,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f ,1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f ,1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=========================================================================================================
//アイテムの終了処理
//=========================================================================================================
void UninitItem(void)
{
	int nCntItem;

	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			g_aItem[nCntItem].bUse = false;
		}
	}
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//アイテムの更新処理
void UpdataItem(void)
{
	int nCntItem;

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			g_aItem[nCntItem].pos.x -= g_TexV;
			g_aItem[nCntItem].pos.y -= g_TexU;
		//テクスチャ座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y - 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y - 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y + 20.0f, 0.0f);

		if (g_aItem[nCntItem].pos.x <= 0)
		{
			g_aItem[nCntItem].bUse = false;
		}

		//アイテムの取得判定
		CollisionItem(&g_aItem[nCntItem]);

		}
		pVtx += 4;

	}
	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=========================================================================================================
//アイテムの描画処理
//=========================================================================================================
void DrawItem(void)
{
	int nCntItem;

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_pTextureItem);

	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			//ポリゴン
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4* nCntItem, 2);
		}
	}
}

//=========================================================================================================
//ドロップアイテムの処理
//=========================================================================================================
void DropItem(D3DXVECTOR3 pos)
{
	int nCntItem;

	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_2D *pVtx;
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].pos = pos;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x -10.0f,g_aItem[nCntItem].pos.y - 10.0f,0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x +10.0f,g_aItem[nCntItem].pos.y - 10.0f,0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x -10.0f,g_aItem[nCntItem].pos.y + 10.0f,0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x +10.0f,g_aItem[nCntItem].pos.y + 10.0f,0.0f);

			g_aItem[nCntItem].bUse = true;
			break; //←重要！！
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}

//=========================================================================================================
//アイテムの取得判定
//=========================================================================================================
void CollisionItem(ITEM *pItem)
{
	Player *pPlayer = GetPlayer();

	if (pItem->pos.x >= pPlayer->pos.x - 20.0f && pItem->pos.x <= pPlayer->pos.x + 20.0f  &&
		pItem->pos.y >= pPlayer->pos.y - 20.0f && pItem->pos.y <= pPlayer->pos.y + 20.0f)
	{
		GetItem(1);

		pItem->bUse = false;
	}
}
