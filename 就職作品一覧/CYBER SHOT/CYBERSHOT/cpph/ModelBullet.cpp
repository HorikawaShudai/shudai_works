//===========================================================
//
//モデル弾の処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "ModelBullet.h"
#include "Camera.h"
//#include "Shadow.h"
#include "Bullet.h"
#include "MeshWall.h"
#include "Game.h"
#include "Fade.h"
#include "Sound.h"
#include "Player.h"
#include "Object.h"

#define MODBULL_MAX (40)

//グローバル変数宣言
MODBULL g_ModBull[MODBULL_MAX];
LPD3DXBUFFER	g_pVtxBuffMatModBull[MODBULL_MAX] = {};

void SetModBullSize(int nNumModBull);
void ColisionOBWALL(int nCnt);
//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitModBull(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nModBull = 0; nModBull < MODBULL_MAX; nModBull++)
	{
		g_ModBull[nModBull].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ModBull[nModBull].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ModBull[nModBull].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ModBull[nModBull].nIdxShadow = -1;
		g_ModBull[nModBull].pTEXtureModBull[250] = {};
		g_ModBull[nModBull].bUse = false;
		g_ModBull[nModBull].dwNumMatModBull = 0;
		g_ModBull[nModBull].pMeshModBull = NULL;
		g_ModBull[nModBull].VtxMinModBull = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ModBull[nModBull].VtxMaxModBull = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ModBull[nModBull].col[256] = {};
		g_ModBull[nModBull].type = BULLETTYPE_ENEMY;
		//g_ModBull[nModBull].aModBullModel[2] = {};
	}


}

//=========================================================================================================
//敵の終了処理
//=========================================================================================================
void UninitModBull(void)
{
	for (int nModBull = 0; nModBull < MODBULL_MAX; nModBull++)
	{
		if (g_ModBull[nModBull].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < 50; nCntMat++)
			{
				if (g_ModBull[nModBull].pTEXtureModBull[nCntMat] != NULL)
				{
					g_ModBull[nModBull].pTEXtureModBull[nCntMat]->Release();
					g_ModBull[nModBull].pTEXtureModBull[nCntMat] = NULL;
				}

			}
			if (g_ModBull[nModBull].pMeshModBull != NULL)
			{
				g_ModBull[nModBull].pMeshModBull->Release();
				g_ModBull[nModBull].pMeshModBull = NULL;
			}
			if (g_pVtxBuffMatModBull[nModBull] != NULL)
			{
				g_pVtxBuffMatModBull[nModBull]->Release();
				g_pVtxBuffMatModBull[nModBull] = NULL;
			}
			g_ModBull[nModBull].bUse = false;
		}
	}


}

//=========================================================================================================
//敵の更新処理
//=========================================================================================================
void UpdateModBull(void)
{
	for (int nModBull = 0; nModBull < MODBULL_MAX; nModBull++)
	{
		if (g_ModBull[nModBull].bUse == true)
		{
			g_ModBull[nModBull].posOld = g_ModBull[nModBull].pos;
			if (g_ModBull[nModBull].rot.y > 0)
			{
				g_ModBull[nModBull].pos.z -= sinf(g_ModBull[nModBull].rot.y)* g_ModBull[nModBull].move.z;
				g_ModBull[nModBull].pos.x += cosf(g_ModBull[nModBull].rot.y)* g_ModBull[nModBull].move.z;
			}
			if (g_ModBull[nModBull].rot.y <= 0)
			{
				g_ModBull[nModBull].pos.z -= sinf(g_ModBull[nModBull].rot.y)* g_ModBull[nModBull].move.z;
				g_ModBull[nModBull].pos.x += cosf(g_ModBull[nModBull].rot.y)* g_ModBull[nModBull].move.z;
			}

			ColisionOBWALL(nModBull);


		}
	}

}

//=========================================================================================================
//敵の描画処理
//=========================================================================================================
void DrawModBull(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nModBull = 0; nModBull < MODBULL_MAX; nModBull++)
	{
		if (g_ModBull[nModBull].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
			D3DMATERIAL9 matDef;
			D3DXMATERIAL *pMat;

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_ModBull[nModBull].mtxWorldModBull);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ModBull[nModBull].rot.y, g_ModBull[nModBull].rot.x, g_ModBull[nModBull].rot.z);
			D3DXMatrixMultiply(&g_ModBull[nModBull].mtxWorldModBull, &g_ModBull[nModBull].mtxWorldModBull, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_ModBull[nModBull].pos.x, g_ModBull[nModBull].pos.y, g_ModBull[nModBull].pos.z);
			D3DXMatrixMultiply(&g_ModBull[nModBull].mtxWorldModBull, &g_ModBull[nModBull].mtxWorldModBull, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_ModBull[nModBull].mtxWorldModBull);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pVtxBuffMatModBull[nModBull]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ModBull[nModBull].dwNumMatModBull; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_ModBull[nModBull].pTEXtureModBull[nCntMat]);

				//モデル（パーツ）の描画
				g_ModBull[nModBull].pMeshModBull->DrawSubset(nCntMat);
			}
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=========================================================================================================
//敵の設置処理
//=========================================================================================================
void SetModBull(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, char *pModBullename)
{

	for (int nModBull = 0; nModBull < MODBULL_MAX; nModBull++)
	{
		if (g_ModBull[nModBull].bUse == false)
		{
			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			g_ModBull[nModBull].pos = pos;
			g_ModBull[nModBull].rot = rot;
			g_ModBull[nModBull].move = move;

			//Xファイルの読み込み
			D3DXLoadMeshFromX(pModBullename,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pVtxBuffMatModBull[nModBull],
				NULL,
				&g_ModBull[nModBull].dwNumMatModBull,
				&g_ModBull[nModBull].pMeshModBull);

			D3DXMATERIAL *pMat;

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pVtxBuffMatModBull[nModBull]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ModBull[nModBull].dwNumMatModBull; nCntMat++)
			{
				g_ModBull[nModBull].col[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_ModBull[nModBull].pTEXtureModBull[nCntMat]);
				}
			}
			//g_ModBull[nModBull].nIdxShadow = SetShadow(20.0f,g_ModBull[nModBull].pos);

			SetModBullSize(nModBull);

			g_ModBull[nModBull].bUse = true;
			break;
		}
	}
}

//=========================================================================================================
//サイズの計算処理
//=========================================================================================================
void SetModBullSize(int nNumModBull)
{
	int nNumVtx;

	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	//頂点数の取得
	nNumVtx = g_ModBull[nNumModBull].pMeshModBull->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(g_ModBull[nNumModBull].pMeshModBull->GetFVF());

	//頂点バッファをロック
	g_ModBull[nNumModBull].pMeshModBull->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (vtx.x > g_ModBull[nNumModBull].VtxMaxModBull.x)
		{
			g_ModBull[nNumModBull].VtxMaxModBull.x = vtx.x;
		}
		if (vtx.x < g_ModBull[nNumModBull].VtxMinModBull.x)
		{
			g_ModBull[nNumModBull].VtxMinModBull.x = vtx.x;
		}
		if (vtx.z > g_ModBull[nNumModBull].VtxMaxModBull.z)
		{
			g_ModBull[nNumModBull].VtxMaxModBull.z = vtx.z;
		}
		if (vtx.z < g_ModBull[nNumModBull].VtxMinModBull.z)
		{
			g_ModBull[nNumModBull].VtxMinModBull.z = vtx.z;
		}
		pVtxBuff += dwSizeFVF;
	}
}

//=========================================================================================================
//プレイヤーとの当たり判定
//=========================================================================================================
bool ColissionModBull(D3DXVECTOR3 pos, D3DXVECTOR3 posOld)
{
	bool bHit = false;

	for (int nModBull = 0; nModBull < MODBULL_MAX; nModBull++)
	{
		if (g_ModBull[nModBull].bUse == true)
		{
		
			if (pos.x >= (g_ModBull[nModBull].pos.x + g_ModBull[nModBull].VtxMinModBull.x) && pos.z <= (g_ModBull[nModBull].pos.z + g_ModBull[nModBull].VtxMaxModBull.z) &&
				pos.x <= (g_ModBull[nModBull].pos.x + g_ModBull[nModBull].VtxMaxModBull.x) && pos.z >= (g_ModBull[nModBull].pos.z + g_ModBull[nModBull].VtxMinModBull.z))
			{
				g_ModBull[nModBull].bUse = false;
				bHit = true;
			}
		}
	}
	return bHit;
}



//=========================================================================================================
//モデルバレットとオブジェクトまたは壁の判定
//=========================================================================================================
void ColisionOBWALL(int nCnt)
{

	//オブジェクトとの当たり判定
	{
		if (ColissionBullet(D3DXVECTOR3((g_ModBull[nCnt].pos.x + (cosf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMaxModBull.x)), g_ModBull[nCnt].pos.y, (g_ModBull[nCnt].pos.z + (sinf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMaxModBull.z))),g_ModBull[nCnt].posOld, g_ModBull[nCnt].move, g_ModBull[nCnt].type)==true)
		{																																																																					  
			//FinishShadow(g_ModBull[nCnt].nIdxShadow);		
			//g_ModBull[nCnt].nIdxShadow = -1;
			g_ModBull[nCnt].bUse = false;																																																													  
		}																																																																					  
		if (ColissionBullet(D3DXVECTOR3((g_ModBull[nCnt].pos.x + (cosf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMinModBull.x)), g_ModBull[nCnt].pos.y, (g_ModBull[nCnt].pos.z + (sinf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMaxModBull.z))),g_ModBull[nCnt].posOld, g_ModBull[nCnt].move, g_ModBull[nCnt].type)==true)
		{																																																																					  
			//FinishShadow(g_ModBull[nCnt].nIdxShadow);																																																										  
			//g_ModBull[nCnt].nIdxShadow = -1;
			g_ModBull[nCnt].bUse = false;
		}																																																																					  
		if (ColissionBullet(D3DXVECTOR3((g_ModBull[nCnt].pos.x + (cosf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMaxModBull.x)), g_ModBull[nCnt].pos.y, (g_ModBull[nCnt].pos.z + (sinf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMinModBull.z))),g_ModBull[nCnt].posOld, g_ModBull[nCnt].move, g_ModBull[nCnt].type)==true)
		{																																																																					  
			//FinishShadow(g_ModBull[nCnt].nIdxShadow);																																																										  
			//g_ModBull[nCnt].nIdxShadow = -1;
			g_ModBull[nCnt].bUse = false;
		}																																																																					  
		if (ColissionBullet(D3DXVECTOR3((g_ModBull[nCnt].pos.x + (cosf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMinModBull.x)), g_ModBull[nCnt].pos.y, (g_ModBull[nCnt].pos.z + (sinf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMinModBull.z))),g_ModBull[nCnt].posOld, g_ModBull[nCnt].move, g_ModBull[nCnt].type)==true)
		{
			//FinishShadow(g_ModBull[nCnt].nIdxShadow);
			//g_ModBull[nCnt].nIdxShadow = -1;
			g_ModBull[nCnt].bUse = false;
		}
	}

	{
		if (g_ModBull[nCnt].pos.x  > 1700.0f)
		{
			//FinishShadow(g_ModBull[nCnt].nIdxShadow);
			//g_ModBull[nCnt].nIdxShadow = -1;
			g_ModBull[nCnt].bUse = false;
		}
		if (g_ModBull[nCnt].pos.x  < -1700.0f)
		{
/*			FinishShadow(g_ModBull[nCnt].nIdxShadow);
			g_ModBull[nCnt].nIdxShadow = -1*/;
			g_ModBull[nCnt].bUse = false;
		}
		if (g_ModBull[nCnt].pos.z  > 1700.0f)
		{
			//FinishShadow(g_ModBull[nCnt].nIdxShadow);
			//g_ModBull[nCnt].nIdxShadow = -1;
			g_ModBull[nCnt].bUse = false;
		}
		if (g_ModBull[nCnt].pos.z  < -1700.0f)
		{
		/*	FinishShadow(g_ModBull[nCnt].nIdxShadow);
			g_ModBull[nCnt].nIdxShadow = -1;*/
			g_ModBull[nCnt].bUse = false;
		}
	}
}
