//===========================================================
//
//敵の処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Enemy.h"
#include "Camera.h"
#include "Shadow.h"
#include "Bullet.h"
#include "MeshWall.h"
#include "Game.h"
#include "Fade.h"
#include "Sound.h"
#include "ModelBullet.h"
#include "Player.h"

#define ENEMY_MAX (25)

//グローバル変数宣言
ENEMY g_Enemy[ENEMY_MAX];
LPD3DXBUFFER	g_pVtxBuffMatEnemy[ENEMY_MAX] = {};
int g_NumEnemy;
int g_MaxHp[ENEMY_MAX];

void SetEnemySize(int nNumEnemy);
void HitEnemy(int nCntEnemy, int nDamage);
//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitEnemy(void)
{
	g_NumEnemy= 0;
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nEnemy = 0; nEnemy < ENEMY_MAX; nEnemy++)
	{
		g_Enemy[nEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nEnemy].Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nEnemy].Destrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nEnemy].nIdxShadow = 0;
		g_Enemy[nEnemy].pTEXtureEnemy[250] = {};
		g_Enemy[nEnemy].bUse = false;
		g_Enemy[nEnemy].dwNumMatEnemy = 0;
		g_Enemy[nEnemy].pMeshEnemy = NULL;
		g_Enemy[nEnemy].VtxMinEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Enemy[nEnemy].VtxMaxEnemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f); 
		g_Enemy[nEnemy].state = ENEMYSTATE_NORMAL;
		g_Enemy[nEnemy].col[256] = {};
		g_Enemy[nEnemy].AttackPatarn = BOSSMODE_FIRST;
		g_Enemy[nEnemy].nCntAttack = 0;
		//g_Enemy[nEnemy].aEnemyModel[2] = {};
	}


}

//=========================================================================================================
//敵の終了処理
//=========================================================================================================
void UninitEnemy(void)
{
	for (int nEnemy = 0; nEnemy < ENEMY_MAX; nEnemy++)
	{
		if (g_Enemy[nEnemy].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < 50; nCntMat++)
			{
				if (g_Enemy[nEnemy].pTEXtureEnemy[nCntMat] != NULL)
				{
					g_Enemy[nEnemy].pTEXtureEnemy[nCntMat]->Release();
					g_Enemy[nEnemy].pTEXtureEnemy[nCntMat] = NULL;
				}

			}
			if (g_Enemy[nEnemy].pMeshEnemy != NULL)
			{
				g_Enemy[nEnemy].pMeshEnemy->Release();
				g_Enemy[nEnemy].pMeshEnemy = NULL;
			}
			if (g_pVtxBuffMatEnemy[nEnemy] != NULL)
			{
				g_pVtxBuffMatEnemy[nEnemy]->Release();
				g_pVtxBuffMatEnemy[nEnemy] = NULL;
			}
			g_Enemy[nEnemy].bUse = false;
		}
	}


}

//=========================================================================================================
//敵の更新処理
//=========================================================================================================
void UpdateEnemy(void)
{
	for (int nEnemy = 0; nEnemy < ENEMY_MAX; nEnemy++)
	{
		if (g_Enemy[nEnemy].bUse == true)
		{
			if (g_Enemy[nEnemy].type == ENEMY_BOSS)
			{
				AttackPart();

				if ((g_MaxHp[nEnemy] / BOSSMODE_MAX) * 2 < g_Enemy[nEnemy].nLife)
				{
					g_Enemy[nEnemy].AttackPatarn = BOSSMODE_FIRST;
				}
				else if ((g_MaxHp[nEnemy] / BOSSMODE_MAX) * 2 >= g_Enemy[nEnemy].nLife && (g_MaxHp[nEnemy] / BOSSMODE_MAX) * 1 <= g_Enemy[nEnemy].nLife)
				{
					g_Enemy[nEnemy].AttackPatarn = BOSSMODE_SECOND;
				}
				else if ((g_MaxHp[nEnemy] / BOSSMODE_MAX) * 1 > g_Enemy[nEnemy].nLife)
				{
					g_Enemy[nEnemy].AttackPatarn = BOSSMODE_FINAL;
				}
			}

			else if (g_Enemy[nEnemy].type == ENEMY_MOB)
			{
				AttackMob(nEnemy);
			}

			switch (g_Enemy[nEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				D3DXMATERIAL *pMat;

				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pVtxBuffMatEnemy[nEnemy]->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_Enemy[nEnemy].dwNumMatEnemy; nCntMat++,pMat++)
				{
					pMat->MatD3D.Diffuse = g_Enemy[nEnemy].col[nCntMat];
				}
				break;

			case ENEMYSTATE_DAMAGE:
				g_Enemy[nEnemy].nCntState--;
				if (g_Enemy[nEnemy].nCntState <= 0)
				{
					g_Enemy[nEnemy].state = ENEMYSTATE_NORMAL;
				}
				break;
			}
			SetPositionShadow(g_Enemy[nEnemy].nIdxShadow, g_Enemy[nEnemy].pos);
		}
	}
	
}

//=========================================================================================================
//敵の描画処理
//=========================================================================================================
void DrawEnemy(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nEnemy = 0; nEnemy < ENEMY_MAX; nEnemy++)
	{
		if (g_Enemy[nEnemy].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
			D3DMATERIAL9 matDef;
			D3DXMATERIAL *pMat;

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[nEnemy].mtxWorldEnemy);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nEnemy].rot.y, g_Enemy[nEnemy].rot.x, g_Enemy[nEnemy].rot.z);
			D3DXMatrixMultiply(&g_Enemy[nEnemy].mtxWorldEnemy, &g_Enemy[nEnemy].mtxWorldEnemy, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nEnemy].pos.x, g_Enemy[nEnemy].pos.y, g_Enemy[nEnemy].pos.z);
			D3DXMatrixMultiply(&g_Enemy[nEnemy].mtxWorldEnemy, &g_Enemy[nEnemy].mtxWorldEnemy, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nEnemy].mtxWorldEnemy);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pVtxBuffMatEnemy[nEnemy]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nEnemy].dwNumMatEnemy; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			
				//テクスチャの設定
				pDevice->SetTexture(0, g_Enemy[nEnemy].pTEXtureEnemy[nCntMat]);

				//モデル（パーツ）の描画
				g_Enemy[nEnemy].pMeshEnemy->DrawSubset(nCntMat);
			}
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=========================================================================================================
//敵の設置処理
//=========================================================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pEnemyename)
{

	for (int nEnemy = 0; nEnemy < ENEMY_MAX; nEnemy++)
	{
		if (g_Enemy[nEnemy].bUse == false)
		{
			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			g_Enemy[nEnemy].pos = pos;
			g_Enemy[nEnemy].rot = rot;
			if (pEnemyename == "data\\MODEL\\Enemy000.x")
			{
				g_Enemy[nEnemy].type = ENEMY_BOSS;
				g_Enemy[nEnemy].nLife = 100;

			}
			else
			{
				g_Enemy[nEnemy].type = ENEMY_MOB;
				g_Enemy[nEnemy].nLife = 1;

			}
			g_MaxHp[nEnemy] = g_Enemy[nEnemy].nLife;

			//Xファイルの読み込み
			D3DXLoadMeshFromX(pEnemyename,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pVtxBuffMatEnemy[nEnemy],
				NULL,
				&g_Enemy[nEnemy].dwNumMatEnemy,
				&g_Enemy[nEnemy].pMeshEnemy);

			D3DXMATERIAL *pMat;

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pVtxBuffMatEnemy[nEnemy]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nEnemy].dwNumMatEnemy; nCntMat++)
			{
				g_Enemy[nEnemy].col[nCntMat] = pMat[nCntMat].MatD3D.Diffuse ;
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_Enemy[nEnemy].pTEXtureEnemy[nCntMat]);
				}
			}

			SetEnemySize(nEnemy);
			if (pEnemyename == "data\\MODEL\\Enemy000.x")
			{
				g_Enemy[nEnemy].nIdxShadow = SetShadow(200.0f, g_Enemy[nEnemy].pos);
			}
			else
			{
				g_Enemy[nEnemy].nIdxShadow = SetShadow(30.0f, g_Enemy[nEnemy].pos);
			}

			g_Enemy[nEnemy].bUse = true;
			g_NumEnemy += 1;
			break;
		}
	}
}

//=========================================================================================================
//サイズの計算処理
//=========================================================================================================
void SetEnemySize(int nNumEnemy)
{
	int nNumVtx;

	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	//頂点数の取得
	nNumVtx = g_Enemy[nNumEnemy].pMeshEnemy->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(g_Enemy[nNumEnemy].pMeshEnemy->GetFVF());

	//頂点バッファをロック
	g_Enemy[nNumEnemy].pMeshEnemy->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (vtx.x > g_Enemy[nNumEnemy].VtxMaxEnemy.x)
		{
			g_Enemy[nNumEnemy].VtxMaxEnemy.x = vtx.x;
		}
		if (vtx.x < g_Enemy[nNumEnemy].VtxMinEnemy.x)
		{
			g_Enemy[nNumEnemy].VtxMinEnemy.x = vtx.x;
		}
		if (vtx.z > g_Enemy[nNumEnemy].VtxMaxEnemy.z)
		{
			g_Enemy[nNumEnemy].VtxMaxEnemy.z = vtx.z;
		}
		if (vtx.z < g_Enemy[nNumEnemy].VtxMinEnemy.z)
		{
			g_Enemy[nNumEnemy].VtxMinEnemy.z = vtx.z;
		}
		pVtxBuff += dwSizeFVF;
	}
}

//=========================================================================================================
//敵の当たり判定
//=========================================================================================================
D3DXVECTOR3 ColissionEnemy(D3DXVECTOR3 possize, D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *pMove)
{
	bool bHit = false;
	D3DXVECTOR3 RPos;
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecTopos;
	D3DXVECTOR3 vecmove;
	RPos = pos;
	vecmove = pos - posOld;

	for (int nEnemy = 0; nEnemy < ENEMY_MAX; nEnemy++)
	{
		if (g_Enemy[nEnemy].bUse == true)
		{
			{//交点処理
			 //vecLine.x = g_Enemy[nEnemy].VtxMaxEnemy.x - g_Enemy[nEnemy].VtxMinEnemy.x;
			 //vecLine.z = g_Enemy[nEnemy].VtxMaxEnemy.z - g_Enemy[nEnemy].VtxMaxEnemy.z;
			 //vecTopos = pos - D3DXVECTOR3(g_Enemy[nEnemy].VtxMinEnemy.x, 0.0f, g_Enemy[nEnemy].VtxMaxEnemy.z);


			 //Enemypos[0] = (vecTopos.z*vecmove.x) - (vecTopos.x*vecmove.z);
			 //Enemypos[1] = (vecLine.z*vecmove.x) - (vecLine.x*vecmove.z);
			 //Enemypos[2] = Enemypos[0] / Enemypos[1];
			 //if (Enemypos[2] >= 0.0f&&Enemypos[2] <= 1.0f)
			 //{
			 //	RPos = D3DXVECTOR3(0.0f, 300.0f, 500.0f);
			 //}
			}

			//if (pos.x > (g_Enemy[nEnemy].pos.x+g_Enemy[nEnemy].VtxMinEnemy.x) && pos.z < (g_Enemy[nEnemy].pos.z + g_Enemy[nEnemy].VtxMaxEnemy.z) &&
			//	pos.x < (g_Enemy[nEnemy].pos.x+g_Enemy[nEnemy].VtxMaxEnemy.x) && pos.z >(g_Enemy[nEnemy].pos.z + g_Enemy[nEnemy].VtxMinEnemy.z))
			//{
			//		RPos = posOld;
			//	
			//}
			if (possize.x >(g_Enemy[nEnemy].pos.x + g_Enemy[nEnemy].VtxMinEnemy.x) && possize.z < (g_Enemy[nEnemy].pos.z + g_Enemy[nEnemy].VtxMaxEnemy.z) &&
				possize.x < (g_Enemy[nEnemy].pos.x + g_Enemy[nEnemy].VtxMaxEnemy.x) && possize.z >(g_Enemy[nEnemy].pos.z + g_Enemy[nEnemy].VtxMinEnemy.z))
			{
				if (posOld.x >= (g_Enemy[nEnemy].pos.x + g_Enemy[nEnemy].VtxMaxEnemy.x))
				{
					RPos.x = posOld.x;
					pMove->x = 0.0f;
				}
				else if (posOld.x <= (g_Enemy[nEnemy].pos.x + g_Enemy[nEnemy].VtxMinEnemy.x))
				{
					RPos.x = posOld.x;
					pMove->x = 0.0f;


				}
				else if (posOld.z <= (g_Enemy[nEnemy].pos.z + g_Enemy[nEnemy].VtxMinEnemy.z))
				{
					RPos.z = posOld.z;

					pMove->z = 0.0f;
				}
				else if (posOld.z >= (g_Enemy[nEnemy].pos.z + g_Enemy[nEnemy].VtxMaxEnemy.z))
				{
					RPos.z = posOld.z;

					pMove->z = 0.0f;
				}
			}
		}
	}
	return RPos;
}

bool ColissionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 pMove)
{
	bool bHit = false;
	D3DXVECTOR3 RPos;
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecTopos;
	D3DXVECTOR3 vecmove;
	RPos = pos;
	vecmove = pos - posOld;




	for (int nEnemy = 0; nEnemy < ENEMY_MAX; nEnemy++)
	{
		if (g_Enemy[nEnemy].bUse == true)
		{
			{//交点処理
			 //vecLine.x = g_Enemy[nEnemy].VtxMaxEnemy.x - g_Enemy[nEnemy].VtxMinEnemy.x;
			 //vecLine.z = g_Enemy[nEnemy].VtxMaxEnemy.z - g_Enemy[nEnemy].VtxMaxEnemy.z;
			 //vecTopos = pos - D3DXVECTOR3(g_Enemy[nEnemy].VtxMinEnemy.x, 0.0f, g_Enemy[nEnemy].VtxMaxEnemy.z);


			 //Enemypos[0] = (vecTopos.z*vecmove.x) - (vecTopos.x*vecmove.z);
			 //Enemypos[1] = (vecLine.z*vecmove.x) - (vecLine.x*vecmove.z);
			 //Enemypos[2] = Enemypos[0] / Enemypos[1];
			 //if (Enemypos[2] >= 0.0f&&Enemypos[2] <= 1.0f)
			 //{
			 //	RPos = D3DXVECTOR3(0.0f, 300.0f, 500.0f);
			 //}
			}

			if (pos.x >= (g_Enemy[nEnemy].pos.x + g_Enemy[nEnemy].VtxMinEnemy.x) && pos.z <= (g_Enemy[nEnemy].pos.z + g_Enemy[nEnemy].VtxMaxEnemy.z) &&
				pos.x <= (g_Enemy[nEnemy].pos.x + g_Enemy[nEnemy].VtxMaxEnemy.x) && pos.z >= (g_Enemy[nEnemy].pos.z + g_Enemy[nEnemy].VtxMinEnemy.z))
			{
				HitEnemy(nEnemy, 1);
				bHit = true;
			}
		}
	}
	return bHit;
}

//=========================================================================================================
//敵の状態遷移処理
//=========================================================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (g_Enemy[nCntEnemy].state == ENEMYSTATE_NORMAL)
	{
		PlaySound(SOUND_LABEL_SE_HIT);

		g_Enemy[nCntEnemy].nLife -= nDamage;
	}
	if (g_Enemy[nCntEnemy].nLife < 1)
	{
		g_Enemy[nCntEnemy].bUse = false;
		FinishShadow(g_Enemy[nCntEnemy].nIdxShadow);
		g_Enemy[nCntEnemy].nIdxShadow = -1;
		g_NumEnemy -= 1;

		MODE aMode = GetMode();
		if (aMode== MODE_GAME)
		{
			FADE fFade = GetFade();
			if (g_NumEnemy <= 0 && fFade == FADE_NONE)
			{
				SetGamemode(GAMEMODE_GAMECLEAR);
				//PlaySound(SOUND_LABEL_SE_DECISION);
				SetFade(MODE_RESULT, 0.05f);
			}
		}
	}
	else
	{

		if (g_Enemy[nCntEnemy].state == ENEMYSTATE_NORMAL)
		{
			g_Enemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;

			D3DXMATERIAL *pMat;

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pVtxBuffMatEnemy[nCntEnemy]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCntEnemy].dwNumMatEnemy; nCntMat++,pMat++)
			{
				pMat->MatD3D.Diffuse = { 1.0f,0.0f,0.0f,1.0f };
			}
			g_Enemy[nCntEnemy].nCntState = 5;
		}

	}

}

ENEMY GetEnemy(void)
{
	return g_Enemy[0];
}

void AttackPart(void)
{
	for (int nEnemy = 0; nEnemy < ENEMY_MAX; nEnemy++)
	{
		if (g_Enemy[nEnemy].bUse == true)
		{
			g_Enemy[nEnemy].nCntAttack++;
			if (g_Enemy[nEnemy].AttackPatarn == BOSSMODE_FIRST)
			{
				if (g_Enemy[nEnemy].nCntAttack % 5 == 0)
				{
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), g_Enemy[nEnemy].rot, BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

				}
				g_Enemy[nEnemy].rot.y += 0.01f;
				if (g_Enemy[nEnemy].rot.y > D3DX_PI)
				{
					g_Enemy[nEnemy].rot.y = -D3DX_PI;
				}
			}
			else if (g_Enemy[nEnemy].AttackPatarn == BOSSMODE_SECOND)
			{
				if (g_Enemy[nEnemy].nCntAttack % 3 == 0)
				{
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), -g_Enemy[nEnemy].rot, BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), g_Enemy[nEnemy].rot, BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), -(g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f)), BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), (g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f)), BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					if (g_Enemy[nEnemy].nCntAttack % 60 == 0)
					{
						SetModBull(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), g_Enemy[nEnemy].rot, D3DXVECTOR3(0.0f, 0.0f, 20.0f), "data\\MODEL\\Model_Bullet.x");
						SetModBull(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 20.0f), "data\\MODEL\\Model_Bullet.x");
						SetModBull(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 20.0f), "data\\MODEL\\Model_Bullet.x");
						SetModBull(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 20.0f), "data\\MODEL\\Model_Bullet.x");
					}
				}
				g_Enemy[nEnemy].rot.y += 0.02f;
				if (g_Enemy[nEnemy].rot.y > D3DX_PI)
				{
					g_Enemy[nEnemy].rot.y = -D3DX_PI;
				}
			}
			if (g_Enemy[nEnemy].AttackPatarn == BOSSMODE_FINAL)
			{
				if (g_Enemy[nEnemy].nCntAttack % 4 == 0)
				{
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), g_Enemy[nEnemy].rot, BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*0.25f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*0.75f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI *-0.25f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					SetBullet(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*-0.75f, 0.0f), BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					if (g_Enemy[nEnemy].nCntAttack % 60 == 0)
					{
						SetModBull(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), g_Enemy[nEnemy].rot, D3DXVECTOR3(0.0f, 0.0f, 20.0f), "data\\MODEL\\Model_Bullet.x");
						SetModBull(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 20.0f), "data\\MODEL\\Model_Bullet.x");
						SetModBull(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 20.0f), "data\\MODEL\\Model_Bullet.x");
						SetModBull(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 20.0f), "data\\MODEL\\Model_Bullet.x");						
						SetModBull(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*0.25f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 20.0f), "data\\MODEL\\Model_Bullet.x");
						SetModBull(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*-0.25f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 20.0f), "data\\MODEL\\Model_Bullet.x");						
						SetModBull(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*0.75f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 20.0f), "data\\MODEL\\Model_Bullet.x");
						SetModBull(D3DXVECTOR3(g_Enemy[nEnemy].pos.x, 40.0f, g_Enemy[nEnemy].pos.z), g_Enemy[nEnemy].rot + D3DXVECTOR3(0.0f, D3DX_PI*-0.75f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 20.0f), "data\\MODEL\\Model_Bullet.x");
					}
			
				}
				g_Enemy[nEnemy].rot.y += 0.03f;
				if (g_Enemy[nEnemy].rot.y > D3DX_PI)
				{
					g_Enemy[nEnemy].rot.y = -D3DX_PI;
				}
			}
		}
	}
}

void AttackMob(int nNum)
{
	g_Enemy[nNum].nCntAttack++;
	//PLAYER aPlayer = GetPlayer();
	//MODE aMode = GetMode();
	//if (aMode == MODE_TUTORIAL)
	//{
	//	g_Enemy[nNum].move = aPlayer.pos - g_Enemy[nNum].pos;
	//	g_Enemy[nNum].pos += g_Enemy[nNum].move*0.001f;
	//	g_Enemy[nNum].Destrot.y = -atan2f((aPlayer.pos.x) - g_Enemy[nNum].pos.x, (aPlayer.pos.z) - g_Enemy[nNum].pos.z);

	//	g_Enemy[nNum].Destrot.y = g_Enemy[nNum].Destrot.y + g_Enemy[nNum].rot.y;

	//	if (g_Enemy[nNum].Destrot.y > D3DX_PI)
	//	{
	//		g_Enemy[nNum].Destrot.y -= D3DX_PI * 2;
	//	}
	//	else if (g_Enemy[nNum].Destrot.y < -D3DX_PI)
	//	{
	//		g_Enemy[nNum].Destrot.y += D3DX_PI * 2;

	//	}

	//	g_Enemy[nNum].rot.y -= (g_Enemy[nNum].Destrot.y)*0.05f;

	//	if (g_Enemy[nNum].rot.y > D3DX_PI)
	//	{
	//		g_Enemy[nNum].rot.y -= D3DX_PI * 2;
	//	}
	//	else if (g_Enemy[nNum].rot.y < -D3DX_PI)
	//	{
	//		g_Enemy[nNum].rot.y += D3DX_PI * 2;
	//	}
	//}
	if (g_Enemy[nNum].nCntAttack % 60 == 0)
	{
		SetBullet(D3DXVECTOR3(g_Enemy[nNum].pos.x, 40.0f, g_Enemy[nNum].pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.1f), g_Enemy[nNum].rot, BULLETTYPE_ENEMY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
	
//=========================================================================================================
//プレイヤーとの当たり判定
//=========================================================================================================
bool ColPlayEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 posOld)
{
	bool bHit = false;

	for (int enemy = 0; enemy < ENEMY_MAX; enemy++)
	{
		if (g_Enemy[enemy].bUse == true)
		{

			if (pos.x >= (g_Enemy[enemy].pos.x + g_Enemy[enemy].VtxMinEnemy.x) && pos.z <= (g_Enemy[enemy].pos.z + g_Enemy[enemy].VtxMaxEnemy.z) &&
				pos.x <= (g_Enemy[enemy].pos.x + g_Enemy[enemy].VtxMaxEnemy.x) && pos.z >= (g_Enemy[enemy].pos.z + g_Enemy[enemy].VtxMinEnemy.z))
			{
				bHit = true;
			}
		}
	}
	return bHit;
}