//===========================================================
//
//弾の処理操作
//Author:堀川萩大
//
//===========================================================
#include "bullet.h"
#include "explosion.h"
#include "input.h"
#include "model.h"
#include "shadow.h"
#include "effect.h"
#include "MeshWall.h"
#include "Object.h"
#include "Enemy.h"
#include "Player.h"
//#include "sound.h"

//マクロ定義
#define MAX_BULLET (4048) //弾の最大数
#define BULLET_WIDTH (10.0f) //弾の高さ
#define BULLET_HEIGHT (10.0f) //弾の幅

//弾の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//現在位置
	D3DXVECTOR3 posOld;	//現在位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 frot;	//弾の向き
	float Length;
	int nIdxShadow;
	D3DXCOLOR col;
	BULLETTYPE type;	//弾の種類
	bool bUse;			//使用の有無
}Bullet;//弾

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//頂点バッファのポインタ
Bullet g_aBullet[MAX_BULLET];						//弾の情報数
D3DXMATRIX g_mtxWorldBullet;
int g_UseBullet;

float g_fAngleBullet;
float g_fLengthBullet;

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitBullet(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_UseBullet= 0;


	//弾の情報の初期化
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].frot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].Length = 0.0f;
		g_aBullet[nCntBullet].nIdxShadow = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player_shot.png",
		&g_pTextureBullet);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-BULLET_HEIGHT, BULLET_WIDTH, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+BULLET_HEIGHT, BULLET_WIDTH, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_HEIGHT, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+BULLET_HEIGHT, 0.0f, 0.0f); 

		//norの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//=========================================================================================================
//終了処理
//=========================================================================================================
void UninitBullet(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].bUse = false;
			g_UseBullet -= 1;
		}
	}
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=========================================================================================================
//更新処理
//=========================================================================================================
void UpdateBullet(void)
{
	int nCntBullet;
	//int nCntEnemy;
	VERTEX_3D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].posOld = g_aBullet[nCntBullet].pos;

			g_aBullet[nCntBullet].Length += g_aBullet[nCntBullet].move.z;
			if (g_aBullet[nCntBullet].frot.y > 0)
			{
				g_aBullet[nCntBullet].pos.z = g_aBullet[nCntBullet].pos.z - sinf(g_aBullet[nCntBullet].frot.y)* g_aBullet[nCntBullet].Length;
				g_aBullet[nCntBullet].pos.x = g_aBullet[nCntBullet].pos.x + cosf(g_aBullet[nCntBullet].frot.y)* g_aBullet[nCntBullet].Length;
			}
			if (g_aBullet[nCntBullet].frot.y <= 0)
			{
				g_aBullet[nCntBullet].pos.z = g_aBullet[nCntBullet].pos.z - sinf(g_aBullet[nCntBullet].frot.y)* g_aBullet[nCntBullet].Length;
				g_aBullet[nCntBullet].pos.x = g_aBullet[nCntBullet].pos.x + cosf(g_aBullet[nCntBullet].frot.y)* g_aBullet[nCntBullet].Length;
			}

			
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				if (ColissionEnemy(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].posOld, g_aBullet[nCntBullet].move))
				{
					SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
					FinishShadow(g_aBullet[nCntBullet].nIdxShadow);
					g_aBullet[nCntBullet].nIdxShadow = -1;
					g_aBullet[nCntBullet].bUse = false;
					g_UseBullet -= 1;
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				if (ColissionPlayer(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].posOld, g_aBullet[nCntBullet].move))
				{
					SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
					FinishShadow(g_aBullet[nCntBullet].nIdxShadow);
					g_aBullet[nCntBullet].nIdxShadow = -1;
					g_aBullet[nCntBullet].bUse = false;
					g_UseBullet -= 1;
				}
			}

			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 20.0f, 7, EFFECT_KIND_BULLET);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 20.0f, 7, EFFECT_KIND_BULLET);
			}
			
			BulletFalse();

			SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.0f, g_aBullet[nCntBullet].pos.z));

		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();

}

//=========================================================================================================
//描画処理
//=========================================================================================================
void DrawBullet(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			D3DXMATRIX mtxTrans;	//計算用マトリックス
			D3DXMATRIX mtxView;		//ビューマトリックスの取得用

									//Zテストを有効にする
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldBullet);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_mtxWorldBullet, NULL, &mtxView);
			g_mtxWorldBullet._41 = 0.0f;
			g_mtxWorldBullet._42 = 0.0f;
			g_mtxWorldBullet._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldBullet, &g_mtxWorldBullet, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);


			pDevice->SetTexture(0, g_pTextureBullet);

			//ビルボード
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);

			//Zテストを有効にする
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}
	}
}

//=========================================================================================================
//弾の設定処理
//=========================================================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot,BULLETTYPE type , D3DXCOLOR col)
{
	int nCntBullet;

	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_3D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].col = col;
			g_aBullet[nCntBullet].frot= rot;
			g_aBullet[nCntBullet].Length = 10.0f;
			
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(g_aBullet[nCntBullet].col);
			pVtx[1].col = D3DXCOLOR(g_aBullet[nCntBullet].col);
			pVtx[2].col = D3DXCOLOR(g_aBullet[nCntBullet].col);
			pVtx[3].col = D3DXCOLOR(g_aBullet[nCntBullet].col);

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].nIdxShadow = SetShadow(15.0f, g_aBullet[nCntBullet].pos);

			g_aBullet[nCntBullet].bUse = true;
			g_UseBullet +=1;

			break; //←重要！！
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//{
////=========================================================================================================
////敵の当たり判定
////=========================================================================================================
//void CollisionEnemy(Bullet *pBullet)
//{
//	Enemy *pEnemy = GetEnemy();
//	Player *pPlayer = GetPlayer();
//	int nCntEnemy;
//
//	for (nCntEnemy = 0; nCntEnemy <= MAX_ENEMY; nCntEnemy++, pEnemy++)
//	{
//		if (pEnemy->bUse == true)
//		{
//			if (pEnemy->nType == 0 || pEnemy->nType == 1 || pEnemy->nType == 2)
//			{
//				if (pBullet->pos.x >= pEnemy->pos.x - pEnemy->fsize && pBullet->pos.x <= pEnemy->pos.x + pEnemy->fsize  &&
//					pBullet->pos.y >= pEnemy->pos.y - pEnemy->fsize && pBullet->pos.y <= pEnemy->pos.y + pEnemy->fsize)
//				{
//					HitEnemy(nCntEnemy, 1 + pPlayer->Attackpt[0]);
//					pBullet->bUse = false;
//				}
//			}
//			else if (pEnemy->nType == 3)
//			{
//				if (pBullet->pos.x >= (pEnemy->pos.x - (pEnemy->fsize-50.0f)) && 
//					pBullet->pos.x <= (pEnemy->pos.x + pEnemy->fsize)  &&
//					pBullet->pos.y >= (pEnemy->pos.y - pEnemy->fsize +BULLET_SIZE) && 
//					pBullet->pos.y <= (pEnemy->pos.y + pEnemy->fsize-BULLET_SIZE) )
//				{
//					HitEnemy(nCntEnemy, 1 + pPlayer->Attackpt[0]);
//					pBullet->bUse = false;
//				}
//
//				 else if (pBullet->pos.x >= (pEnemy->pos.x - pEnemy->fsize) &&
//					pBullet->pos.x <= pEnemy->pos.x &&
//					pBullet->pos.y >= (pEnemy->pos.y - pEnemy->fsize + (BULLET_SIZE+60.0f)) &&
//					pBullet->pos.y <= (pEnemy->pos.y + pEnemy->fsize - (BULLET_SIZE+60.0f)))
//				{
//					HitEnemy(nCntEnemy, 1 + pPlayer->Attackpt[0]);
//					pBullet->bUse = false;
//				}
//			}
//		}
//	}
//}
//
////=========================================================================================================
////プレイヤーの当たり判定
////=========================================================================================================
//void CollisionPlayer(Bullet *pBullet)
//{
//	int nCntEnemy;
//	Enemy *pEnemy = GetEnemy();
//	Player *pPlayer = GetPlayer();
//
//	if (pBullet->pos.x >= pPlayer->pos.x - 20.0f && pBullet->pos.x <= pPlayer->pos.x + 20.0f  &&
//		pBullet->pos.y >= pPlayer->pos.y - 20.0f && pBullet->pos.y <= pPlayer->pos.y + 20.0f)
//	{
//		if (pPlayer->life <= 1)
//		{
//			SetEnablePause(true);
//			HitPlayer(1);
//
//		}
//		else
//		{
//			SetExplosion(pBullet->pos, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
//			HitPlayer(1);
//		}
//		pBullet->bUse = false;
//	}
//	for (nCntEnemy = 0; nCntEnemy <= MAX_ENEMY; nCntEnemy++, pEnemy++)
//
//	{
//		if (pEnemy->bUse == true)
//		{
//			if (pPlayer->pos.x - 20.0f >= pEnemy->pos.x - pEnemy->fsize &&  pPlayer->pos.x + 20.0f <= pEnemy->pos.x + pEnemy->fsize  &&
//				pPlayer->pos.y - 20.0f >= pEnemy->pos.y - pEnemy->fsize &&  pPlayer->pos.y + 20.0f <= pEnemy->pos.y + pEnemy->fsize)
//			{
//				HitPlayer(1);
//				pBullet->bUse = false;
//			}
//		}
//	}
//}
//}

void BulletFalse(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			if (g_aBullet[nCntBullet].Length > 50.0f)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				FinishShadow(g_aBullet[nCntBullet].nIdxShadow);
				g_aBullet[nCntBullet].nIdxShadow = -1;
				g_aBullet[nCntBullet].bUse = false;
				g_UseBullet -= 1;

			}
			else if (g_aBullet[nCntBullet].pos.x >= 1700.0f || g_aBullet[nCntBullet].pos.x <= -1700.0f || g_aBullet[nCntBullet].pos.z >= 1700.0f || g_aBullet[nCntBullet].pos.z <= -1700.0f)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				FinishShadow(g_aBullet[nCntBullet].nIdxShadow);
				g_aBullet[nCntBullet].nIdxShadow = -1;
				g_aBullet[nCntBullet].bUse = false;
				g_UseBullet -= 1;
			}
			else if (ColissionBullet(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].posOld, g_aBullet[nCntBullet].move, g_aBullet[nCntBullet].type))
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
				FinishShadow(g_aBullet[nCntBullet].nIdxShadow);
				g_aBullet[nCntBullet].nIdxShadow = -1;
				g_aBullet[nCntBullet].bUse = false;
				g_UseBullet -= 1;
			}
		}
	}
}

int GetUseBullet(void)
{
	return g_UseBullet;
}

