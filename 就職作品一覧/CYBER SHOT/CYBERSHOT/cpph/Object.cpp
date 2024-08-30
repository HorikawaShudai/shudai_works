//===========================================================
//
//オブジェクトの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Object.h"
#include "Camera.h"
#include "Bullet.h"
#include "MeshWall.h"
#include "Item.h"

#define OBJECT_MAX (20)

//グローバル変数宣言
OBJECT g_Object[OBJECT_MAX];
LPD3DXBUFFER	g_pVtxBuffMatObject[OBJECT_MAX] = {};

void SetObjectSize(int nNumObject);

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitObject(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nObject = 0; nObject < OBJECT_MAX; nObject++)
	{
		g_Object[nObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nObject].pTEXtureObject[50] = {};
		g_Object[nObject].bUse = false;
		g_Object[nObject].dwNumMatObject = 0;
		g_Object[nObject].pMeshObject = NULL;
		g_Object[nObject].VtxMinObject =  D3DXVECTOR3 (0.0f, 0.0f, 0.0f);
		g_Object[nObject].VtxMaxObject =  D3DXVECTOR3 (0.0f, 0.0f, 0.0f);
	}
}

//=========================================================================================================
//オブジェクトの終了処理
//=========================================================================================================
void UninitObject(void)
{
	for (int nObject = 0; nObject < OBJECT_MAX; nObject++)
	{
		if (g_Object[nObject].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < 50; nCntMat++)
			{
				if (g_Object[nObject].pTEXtureObject[nCntMat] != NULL)
				{
					g_Object[nObject].pTEXtureObject[nCntMat]->Release();
					g_Object[nObject].pTEXtureObject[nCntMat] = NULL;
				}

			}
			if (g_Object[nObject].pMeshObject != NULL)
			{
				g_Object[nObject].pMeshObject->Release();
				g_Object[nObject].pMeshObject = NULL;
			}
			if (g_pVtxBuffMatObject[nObject] != NULL)
			{
				g_pVtxBuffMatObject[nObject]->Release();
				g_pVtxBuffMatObject[nObject] = NULL;
			}
			g_Object[nObject].bUse = false;
		}
	}


}

//=========================================================================================================
//オブジェクトの更新処理
//=========================================================================================================
void UpdateObject(void)
{

}

//=========================================================================================================
//オブジェクトの描画処理
//=========================================================================================================
void DrawObject(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nObject = 0; nObject < OBJECT_MAX; nObject++)
	{
		if (g_Object[nObject].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
			D3DMATERIAL9 matDef;
			D3DXMATERIAL *pMat;

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Object[nObject].mtxWorldObject);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object[nObject].rot.y, g_Object[nObject].rot.x, g_Object[nObject].rot.z);
			D3DXMatrixMultiply(&g_Object[nObject].mtxWorldObject, &g_Object[nObject].mtxWorldObject, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Object[nObject].pos.x, g_Object[nObject].pos.y, g_Object[nObject].pos.z);
			D3DXMatrixMultiply(&g_Object[nObject].mtxWorldObject, &g_Object[nObject].mtxWorldObject, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Object[nObject].mtxWorldObject);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pVtxBuffMatObject[nObject]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Object[nObject].dwNumMatObject; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_Object[nObject].pTEXtureObject[nCntMat]);

				//モデル（パーツ）の描画
				  g_Object[nObject].pMeshObject->DrawSubset(nCntMat);
			}
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=========================================================================================================
//オブジェクトの設置処理
//=========================================================================================================
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pObjectename)
{

	for (int nObject = 0; nObject < OBJECT_MAX; nObject++)
	{
		if (g_Object[nObject].bUse == false)
		{
			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			g_Object[nObject].pos = pos;
			g_Object[nObject].rot = rot;
			if (pObjectename == "data\\MODEL\\WoodBox.x")
			{
				g_Object[nObject].ObjectCode = OBJECT_KIND_001;
			}
			else 
			{
				g_Object[nObject].ObjectCode = OBJECT_KIND_000;
			}

			//Xファイルの読み込み
			D3DXLoadMeshFromX(pObjectename,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pVtxBuffMatObject[nObject],
				NULL,
				&g_Object[nObject].dwNumMatObject,
				&  g_Object[nObject].pMeshObject);

			D3DXMATERIAL *pMat;

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pVtxBuffMatObject[nObject]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat <(int)g_Object[nObject].dwNumMatObject; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_Object[nObject].pTEXtureObject[nCntMat]);
				}
			}

			SetObjectSize(nObject);

			g_Object[nObject].bUse = true;
			break;
		}
	}
}

//=========================================================================================================
//サイズの計算処理
//=========================================================================================================
void SetObjectSize(int nNumObject)
{
	int nNumVtx;

	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	//頂点数の取得
	nNumVtx = g_Object[nNumObject].pMeshObject->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(g_Object[nNumObject].pMeshObject->GetFVF());

	//頂点バッファをロック
	g_Object[nNumObject].pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (vtx.x > g_Object[nNumObject].VtxMaxObject.x)
		{
			g_Object[nNumObject].VtxMaxObject.x = vtx.x;
		}
		if (vtx.x < g_Object[nNumObject].VtxMinObject.x )
		{
			g_Object[nNumObject].VtxMinObject.x = vtx.x;
		}
		if (vtx.z > g_Object[nNumObject].VtxMaxObject.z )
		{
			g_Object[nNumObject].VtxMaxObject.z = vtx.z;
		}
		if (vtx.z < g_Object[nNumObject].VtxMinObject.z )
		{
			g_Object[nNumObject].VtxMinObject.z = vtx.z;
		}
		if (vtx.y> g_Object[nNumObject].VtxMaxObject.y)
		{
			g_Object[nNumObject].VtxMaxObject.y = vtx.y;
		}
		if (vtx.y < g_Object[nNumObject].VtxMinObject.y)
		{
			g_Object[nNumObject].VtxMinObject.y = vtx.y;
		}
		pVtxBuff += dwSizeFVF;
	}
}

//=========================================================================================================
//オブジェクトの当たり判定
//=========================================================================================================
D3DXVECTOR3 ColissionObject(D3DXVECTOR3 possize, D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *pMove)
{
	bool bHit = false;
	D3DXVECTOR3 RPos;
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecTopos;
	D3DXVECTOR3 vecmove;
	RPos = pos;
	vecmove = pos - posOld;

	for (int nObject = 0; nObject < OBJECT_MAX; nObject++)
	{
		if (g_Object[nObject].bUse == true)
		{
			{//交点処理
				//vecLine.x = g_Object[nObject].VtxMaxObject.x - g_Object[nObject].VtxMinObject.x;
				//vecLine.z = g_Object[nObject].VtxMaxObject.z - g_Object[nObject].VtxMaxObject.z;
				//vecTopos = pos - D3DXVECTOR3(g_Object[nObject].VtxMinObject.x, 0.0f, g_Object[nObject].VtxMaxObject.z);


				//Objectpos[0] = (vecTopos.z*vecmove.x) - (vecTopos.x*vecmove.z);
				//Objectpos[1] = (vecLine.z*vecmove.x) - (vecLine.x*vecmove.z);
				//Objectpos[2] = Objectpos[0] / Objectpos[1];
				//if (Objectpos[2] >= 0.0f&&Objectpos[2] <= 1.0f)
				//{
				//	RPos = D3DXVECTOR3(0.0f, 300.0f, 500.0f);
				//}
			}

			//if (pos.x > (g_Object[nObject].pos.x+g_Object[nObject].VtxMinObject.x) && pos.z < (g_Object[nObject].pos.z + g_Object[nObject].VtxMaxObject.z) &&
			//	pos.x < (g_Object[nObject].pos.x+g_Object[nObject].VtxMaxObject.x) && pos.z >(g_Object[nObject].pos.z + g_Object[nObject].VtxMinObject.z))
			//{
			//		RPos = posOld;
			//	
			//}
			if (possize.x >=(g_Object[nObject].pos.x + g_Object[nObject].VtxMinObject.x) && possize.z <= (g_Object[nObject].pos.z + g_Object[nObject].VtxMaxObject.z) &&
				possize.x <= (g_Object[nObject].pos.x + g_Object[nObject].VtxMaxObject.x) && possize.z >=(g_Object[nObject].pos.z + g_Object[nObject].VtxMinObject.z) &&
				possize.y >=(g_Object[nObject].pos.y + g_Object[nObject].VtxMinObject.y)&& possize.y <=(g_Object[nObject].pos.y + g_Object[nObject].VtxMaxObject.y))
			{
				if (posOld.x >(g_Object[nObject].pos.x + g_Object[nObject].VtxMaxObject.x) )
				{
					RPos.x = posOld.x ;
					pMove->x = 0.0f;
				}
				else if (posOld.x <(g_Object[nObject].pos.x + g_Object[nObject].VtxMinObject.x))
				{
					RPos.x = posOld.x;
					pMove->x = 0.0f;


				}
				else if (posOld.z <(g_Object[nObject].pos.z + g_Object[nObject].VtxMinObject.z))
				{
					RPos.z = posOld.z;

					pMove->z = 0.0f;
				}
				else if (posOld.z >(g_Object[nObject].pos.z + g_Object[nObject].VtxMaxObject.z))
				{
					RPos.z = posOld.z;

					pMove->z = 0.0f;
				}
				if (posOld.y <(g_Object[nObject].pos.y + g_Object[nObject].VtxMinObject.y))
				{
					RPos.y = posOld.y;

					pMove->y = 0.0f;
				}
				else if (posOld.y >= (g_Object[nObject].pos.y + g_Object[nObject].VtxMaxObject.y))
				{
					RPos.y = posOld.y;

					pMove->y = 0.0f;
				}

			}
		}
	}
	return RPos;
}

//=========================================================================================================
//弾との当たり判定
//=========================================================================================================
bool ColissionBullet(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 pMove,BULLETTYPE nType)
{
	bool bHit = false;
	D3DXVECTOR3 RPos;

	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecTopos;
	D3DXVECTOR3 vecmove;
	RPos = pos;
	vecmove = pos - posOld;

	for (int nObject = 0; nObject < OBJECT_MAX; nObject++)
	{
		if (g_Object[nObject].bUse == true)
		{
			{//交点処理
			 //vecLine.x = g_Object[nObject].VtxMaxObject.x - g_Object[nObject].VtxMinObject.x;
			 //vecLine.z = g_Object[nObject].VtxMaxObject.z - g_Object[nObject].VtxMaxObject.z;
			 //vecTopos = pos - D3DXVECTOR3(g_Object[nObject].VtxMinObject.x, 0.0f, g_Object[nObject].VtxMaxObject.z);


			 //Objectpos[0] = (vecTopos.z*vecmove.x) - (vecTopos.x*vecmove.z);
			 //Objectpos[1] = (vecLine.z*vecmove.x) - (vecLine.x*vecmove.z);
			 //Objectpos[2] = Objectpos[0] / Objectpos[1];
			 //if (Objectpos[2] >= 0.0f&&Objectpos[2] <= 1.0f)
			 //{
			 //	RPos = D3DXVECTOR3(0.0f, 300.0f, 500.0f);
			 //}
			}

			//if (pos.x > (g_Object[nObject].pos.x+g_Object[nObject].VtxMinObject.x) && pos.z < (g_Object[nObject].pos.z + g_Object[nObject].VtxMaxObject.z) &&
			//	pos.x < (g_Object[nObject].pos.x+g_Object[nObject].VtxMaxObject.x) && pos.z >(g_Object[nObject].pos.z + g_Object[nObject].VtxMinObject.z))
			//{
			//		RPos = posOld;
			//	
			//}
			if (pos.x >=(g_Object[nObject].pos.x + g_Object[nObject].VtxMinObject.x) && pos.z <= (g_Object[nObject].pos.z + g_Object[nObject].VtxMaxObject.z) &&
				pos.x <= (g_Object[nObject].pos.x + g_Object[nObject].VtxMaxObject.x) && pos.z >=(g_Object[nObject].pos.z + g_Object[nObject].VtxMinObject.z))
			{
				if (nType == BULLETTYPE_PLAYER)
				{
					if (g_Object[nObject].ObjectCode == OBJECT_KIND_001)
					{

						g_Object[nObject].bUse = false;
						SetItem(g_Object[nObject].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\Heart.x");
					}
				}
				bHit = true;
			}
		}
	}
	return bHit;
}
