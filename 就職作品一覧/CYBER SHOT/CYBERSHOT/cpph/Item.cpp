//===========================================================
//
//アイテムの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Item.h"
#include "Camera.h"
#include "Shadow.h"
#include "Bullet.h"
#include "MeshWall.h"
#include "Player.h"

#define ITEM_MAX (20)

//グローバル変数宣言
ITEM g_Item[ITEM_MAX];
LPD3DXBUFFER	g_pVtxBuffMatItem[ITEM_MAX] = {};

void SetItemSize(int nNumItem);

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitItem(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nItem = 0; nItem < ITEM_MAX; nItem++)
	{
		g_Item[nItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nItem].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nItem].nIdxShadow = -1;
		g_Item[nItem].pTEXtureItem[50] = {};
		g_Item[nItem].bUse = false;
		g_Item[nItem].dwNumMatItem = 0;
		g_Item[nItem].pMeshItem = NULL;
		g_Item[nItem].VtxMinItem = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item[nItem].VtxMaxItem = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}


	//SetItem(D3DXVECTOR3(300.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\Heart.x");


}

//=========================================================================================================
//アイテムの終了処理
//=========================================================================================================
void UninitItem(void)
{
	for (int nItem = 0; nItem < ITEM_MAX; nItem++)
	{
		if (g_Item[nItem].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < 50; nCntMat++)
			{
				if (g_Item[nItem].pTEXtureItem[nCntMat] != NULL)
				{
					g_Item[nItem].pTEXtureItem[nCntMat]->Release();
					g_Item[nItem].pTEXtureItem[nCntMat] = NULL;
				}

			}
			if (g_Item[nItem].pMeshItem != NULL)
			{
				g_Item[nItem].pMeshItem->Release();
				g_Item[nItem].pMeshItem = NULL;
			}
			if (g_pVtxBuffMatItem[nItem] != NULL)
			{
				g_pVtxBuffMatItem[nItem]->Release();
				g_pVtxBuffMatItem[nItem] = NULL;
			}
			g_Item[nItem].bUse = false;
		}
	}


}

//=========================================================================================================
//アイテムの更新処理
//=========================================================================================================
void UpdateItem(void)
{
	for (int nItem = 0; nItem < ITEM_MAX; nItem++)
	{
		if (g_Item[nItem].bUse == true)
		{
			SetPositionShadow(g_Item[nItem].nIdxShadow, D3DXVECTOR3(g_Item[nItem].pos.x, 0.0f, g_Item[nItem].pos.z));
		}
	}
}

//=========================================================================================================
//アイテムの描画処理
//=========================================================================================================
void DrawItem(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nItem = 0; nItem < ITEM_MAX; nItem++)
	{
		if (g_Item[nItem].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
			D3DMATERIAL9 matDef;
			D3DXMATERIAL *pMat;

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Item[nItem].mtxWorldItem);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Item[nItem].rot.y, g_Item[nItem].rot.x, g_Item[nItem].rot.z);
			D3DXMatrixMultiply(&g_Item[nItem].mtxWorldItem, &g_Item[nItem].mtxWorldItem, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Item[nItem].pos.x, g_Item[nItem].pos.y, g_Item[nItem].pos.z);
			D3DXMatrixMultiply(&g_Item[nItem].mtxWorldItem, &g_Item[nItem].mtxWorldItem, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Item[nItem].mtxWorldItem);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pVtxBuffMatItem[nItem]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Item[nItem].dwNumMatItem; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_Item[nItem].pTEXtureItem[nCntMat]);

				//モデル（パーツ）の描画
				g_Item[nItem].pMeshItem->DrawSubset(nCntMat);
			}
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=========================================================================================================
//アイテムの設置処理
//=========================================================================================================
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pItemename)
{

	for (int nItem = 0; nItem < ITEM_MAX; nItem++)
	{
		if (g_Item[nItem].bUse == false)
		{
			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			g_Item[nItem].pos = pos;
			g_Item[nItem].rot = rot;
			g_Item[nItem].nType = ITEM_KIND_000;

			//Xファイルの読み込み
			D3DXLoadMeshFromX(pItemename,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pVtxBuffMatItem[nItem],
				NULL,
				&g_Item[nItem].dwNumMatItem,
				&g_Item[nItem].pMeshItem);

			D3DXMATERIAL *pMat;

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pVtxBuffMatItem[nItem]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Item[nItem].dwNumMatItem; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_Item[nItem].pTEXtureItem[nCntMat]);
				}
			}
			g_Item[nItem].nIdxShadow = SetShadow(15.0f, g_Item[nItem].pos);

			SetItemSize(nItem);

			g_Item[nItem].bUse = true;
			break;
		}
	}
}

//=========================================================================================================
//サイズの計算処理
//=========================================================================================================
void SetItemSize(int nNumItem)
{
	int nNumVtx;

	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	//頂点数の取得
	nNumVtx = g_Item[nNumItem].pMeshItem->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(g_Item[nNumItem].pMeshItem->GetFVF());

	//頂点バッファをロック
	g_Item[nNumItem].pMeshItem->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (vtx.x > g_Item[nNumItem].VtxMaxItem.x)
		{
			g_Item[nNumItem].VtxMaxItem.x = vtx.x;
		}
		if (vtx.x < g_Item[nNumItem].VtxMinItem.x)
		{
			g_Item[nNumItem].VtxMinItem.x = vtx.x;
		}
		if (vtx.z > g_Item[nNumItem].VtxMaxItem.z)
		{
			g_Item[nNumItem].VtxMaxItem.z = vtx.z;
		}
		if (vtx.z < g_Item[nNumItem].VtxMinItem.z)
		{
			g_Item[nNumItem].VtxMinItem.z = vtx.z;
		}
		pVtxBuff += dwSizeFVF;
	}
}

//=========================================================================================================
//アイテムの当たり判定
//=========================================================================================================
D3DXVECTOR3 ColissionItem(D3DXVECTOR3 possize, D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *pMove)
{
	bool bHit = false;
	D3DXVECTOR3 RPos;
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecTopos;
	D3DXVECTOR3 vecmove;
	RPos = pos;
	vecmove = pos - posOld;

	for (int nItem = 0; nItem < ITEM_MAX; nItem++)
	{
		if (g_Item[nItem].bUse == true)
		{
			{//交点処理
			 //vecLine.x = g_Item[nItem].VtxMaxItem.x - g_Item[nItem].VtxMinItem.x;
			 //vecLine.z = g_Item[nItem].VtxMaxItem.z - g_Item[nItem].VtxMaxItem.z;
			 //vecTopos = pos - D3DXVECTOR3(g_Item[nItem].VtxMinItem.x, 0.0f, g_Item[nItem].VtxMaxItem.z);


			 //Itempos[0] = (vecTopos.z*vecmove.x) - (vecTopos.x*vecmove.z);
			 //Itempos[1] = (vecLine.z*vecmove.x) - (vecLine.x*vecmove.z);
			 //Itempos[2] = Itempos[0] / Itempos[1];
			 //if (Itempos[2] >= 0.0f&&Itempos[2] <= 1.0f)
			 //{
			 //	RPos = D3DXVECTOR3(0.0f, 300.0f, 500.0f);
			 //}
			}

			//if (pos.x > (g_Item[nItem].pos.x+g_Item[nItem].VtxMinItem.x) && pos.z < (g_Item[nItem].pos.z + g_Item[nItem].VtxMaxItem.z) &&
			//	pos.x < (g_Item[nItem].pos.x+g_Item[nItem].VtxMaxItem.x) && pos.z >(g_Item[nItem].pos.z + g_Item[nItem].VtxMinItem.z))
			//{
			//		RPos = posOld;
			//	
			//}
			if (possize.x >(g_Item[nItem].pos.x + g_Item[nItem].VtxMinItem.x) && possize.z < (g_Item[nItem].pos.z + g_Item[nItem].VtxMaxItem.z) &&
				possize.x < (g_Item[nItem].pos.x + g_Item[nItem].VtxMaxItem.x) && possize.z >(g_Item[nItem].pos.z + g_Item[nItem].VtxMinItem.z))
			{
				if (posOld.x >= (g_Item[nItem].pos.x + g_Item[nItem].VtxMaxItem.x))
				{
					RPos.x = posOld.x;
					pMove->x = 0.0f;
				}
				else if (posOld.x <= (g_Item[nItem].pos.x + g_Item[nItem].VtxMinItem.x))
				{
					RPos.x = posOld.x;
					pMove->x = 0.0f;


				}
				else if (posOld.z <= (g_Item[nItem].pos.z + g_Item[nItem].VtxMinItem.z))
				{
					RPos.z = posOld.z;

					pMove->z = 0.0f;
				}
				else if (posOld.z >= (g_Item[nItem].pos.z + g_Item[nItem].VtxMaxItem.z))
				{
					RPos.z = posOld.z;

					pMove->z = 0.0f;
				}
			}
		}
	}
	return RPos;
}


void ColissionItem(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 pMove)
{
	D3DXVECTOR3 RPos;

	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecTopos;
	D3DXVECTOR3 vecmove;
	RPos = pos;
	vecmove = pos - posOld;




	for (int nItem = 0; nItem < ITEM_MAX; nItem++)
	{
		if (g_Item[nItem].bUse == true)
		{
			{//交点処理
			 //vecLine.x = g_Item[nItem].VtxMaxItem.x - g_Item[nItem].VtxMinItem.x;
			 //vecLine.z = g_Item[nItem].VtxMaxItem.z - g_Item[nItem].VtxMaxItem.z;
			 //vecTopos = pos - D3DXVECTOR3(g_Item[nItem].VtxMinItem.x, 0.0f, g_Item[nItem].VtxMaxItem.z);


			 //Itempos[0] = (vecTopos.z*vecmove.x) - (vecTopos.x*vecmove.z);
			 //Itempos[1] = (vecLine.z*vecmove.x) - (vecLine.x*vecmove.z);
			 //Itempos[2] = Itempos[0] / Itempos[1];
			 //if (Itempos[2] >= 0.0f&&Itempos[2] <= 1.0f)
			 //{
			 //	RPos = D3DXVECTOR3(0.0f, 300.0f, 500.0f);
			 //}
			}

			if (pos.x >= (g_Item[nItem].pos.x + g_Item[nItem].VtxMinItem.x) && pos.z <= (g_Item[nItem].pos.z + g_Item[nItem].VtxMaxItem.z) &&
				pos.x <= (g_Item[nItem].pos.x + g_Item[nItem].VtxMaxItem.x) && pos.z >= (g_Item[nItem].pos.z + g_Item[nItem].VtxMinItem.z))
			{
				HitItem(g_Item[nItem]);
				g_Item[nItem].bUse = false;
				FinishShadow(g_Item[nItem].nIdxShadow);
				g_Item[nItem].nIdxShadow = -1;
			}
		}
	}
}