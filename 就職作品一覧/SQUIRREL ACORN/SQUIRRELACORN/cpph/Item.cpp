//===========================================================
//
//アイテムの処理操作
//Author:堀川萩大
//
//===========================================================
#include "game.h"
//#include "main.h"
#include "Item.h"
#include "block.h"
#include "Input.h"
#include "player.h"

//マクロ定義
#define NUM_ITEM (80)				//アイテムの最大数
#define NUM_TEX (2)


//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureItem[NUM_TEX] = {}; //アイテムの数のテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;  //アイテムの数の頂点バッファ
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
		"data\\TEXTURE\\acorn.png",
		&g_pTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Key.png",
		&g_pTextureItem[1]);


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
	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			g_aItem[nCntItem].bUse = false;
		}
	}
	for (int nCntTex = 0; nCntTex < NUM_TEX; nCntTex++)
	{
		if (g_pTextureItem[nCntTex] != NULL)
		{
			g_pTextureItem[nCntTex]->Release();
			g_pTextureItem[nCntTex] = NULL;
		}
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
	D3DXVECTOR3 Worldpos = GetWorld();

	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_2D *pVtx;
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			g_aItem[nCntItem].pos = g_aItem[nCntItem].posworld + Worldpos;
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 50.0f, g_aItem[nCntItem].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 50.0f, g_aItem[nCntItem].pos.y + 50.0f, 0.0f);
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


	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].nType]);

			//ポリゴン
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4* nCntItem, 2);
		}
	}
}

//=========================================================================================================
//ドロップアイテムの処理
//=========================================================================================================
void SetItem(D3DXVECTOR3 pos, ITEM_KIND ntype)
{
	int nCntItem;
	D3DXVECTOR3 Worldpos = GetWorld();

	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_2D *pVtx;
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].pos = pos+ Worldpos;
			g_aItem[nCntItem].posworld = pos+ Worldpos;
			g_aItem[nCntItem].nType = ntype;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x,       g_aItem[nCntItem].pos.y ,0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x +50.0f,g_aItem[nCntItem].pos.y ,0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x,       g_aItem[nCntItem].pos.y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 50.0f, g_aItem[nCntItem].pos.y + 50.0f,0.0f);

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
bool CollisionItem(D3DXVECTOR3 pPos, float fWidth, float fHeight)
{
	bool bCatch =false;
	Player *pPlayer = GetPlayer();

	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			float flength[3];
			flength[0] = (pPlayer->pos.x - ((g_aItem[nCntItem].pos.x + (50.0f / 2.0f)))) * (pPlayer->pos.x - ((g_aItem[nCntItem].pos.x + (50.0f / 2.0f))));
			flength[1] = (pPlayer->pos.y - fHeight - g_aItem[nCntItem].pos.y)* (pPlayer->pos.y - fHeight - g_aItem[nCntItem].pos.y);
			flength[2] = (fWidth + (50.0f / 2.0f)) * (fWidth + (50.0f / 2.0f));
			if (flength[0] + flength[1] <= flength[2])
			{//当たり判定
				if (g_aItem[nCntItem].nType == ITEM_KEY)
				{
					DleatBlock(BLOCKTYPE_ORI);
					g_aItem[nCntItem].bUse = false;
				}
				if (g_aItem[nCntItem].nType == ITEM_GOAL)
				{
					bCatch = true;
					g_aItem[nCntItem].bUse = false;
				}
			}
		}
	}
	return bCatch;
}
