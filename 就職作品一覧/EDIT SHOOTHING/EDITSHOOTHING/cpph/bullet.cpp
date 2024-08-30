//===========================================================
//
//弾の処理操作
//Author:堀川萩大
//
//===========================================================
#include "game.h"
#include "bullet.h"
#include "explosion.h"
#include "input.h"
#include "enemy.h"
#include "player.h"
#include "sound.h"
#include "effect.h"

//マクロ定義
#define MAX_BULLET (512) //弾の最大数
#define BULLET_SIZE (10.0f) //弾の最大数
#define BULLET_WIDTH (20.0f) //弾の最大数
#define BULLET_HEIGHT (20.0f) //弾の最大数

//弾の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 frot;		   //弾の向き
	D3DXCOLOR col;
	BULLETTYPE type;	//弾の種類
	bool bUse;			//使用の有無
}Bullet;//弾

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//頂点バッファのポインタ
Bullet g_aBullet[MAX_BULLET];						//弾の情報数
float g_fAngleBullet;
float g_fLengthBullet;

//プロトタイプ宣言
void CollisionEnemy(Bullet *pBullet);
void CollisionPlayer(Bullet *pBullet);

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitBullet(void)
{

	g_fLengthBullet = sqrtf((BULLET_WIDTH *BULLET_WIDTH)+ (BULLET_HEIGHT*BULLET_HEIGHT))*0.5f;
	g_fAngleBullet = atan2f(BULLET_WIDTH, BULLET_HEIGHT);
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player_shot.png",
		&g_pTextureBullet);

	//弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].frot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標
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

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

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
void UpdataBullet(void)
{
	int nCntBullet;
	//int nCntEnemy;
	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].pos.x += sinf(g_aBullet[nCntBullet].frot.z) * g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += cosf(g_aBullet[nCntBullet].frot.z) * g_aBullet[nCntBullet].move.y;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x +sinf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z +(D3DX_PI + g_fAngleBullet)) * g_fLengthBullet, 
				                      g_aBullet[nCntBullet].pos.y +cosf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z + (D3DX_PI + g_fAngleBullet)) * g_fLengthBullet,
				                      0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + sinf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z + (D3DX_PI - g_fAngleBullet)) * g_fLengthBullet,
				                      g_aBullet[nCntBullet].pos.y + cosf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z + (D3DX_PI - g_fAngleBullet)) * g_fLengthBullet,
				                      0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + sinf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z  - g_fAngleBullet) * g_fLengthBullet,
				                      g_aBullet[nCntBullet].pos.y + cosf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z - g_fAngleBullet) * g_fLengthBullet,
				                      0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + sinf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z + g_fAngleBullet) * g_fLengthBullet,
				                      g_aBullet[nCntBullet].pos.y + cosf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z + g_fAngleBullet) * g_fLengthBullet,
				                      0.0f);
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{

				SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 20.0f, 3,0);
			}
			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{

				SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos), D3DXCOLOR(0.0f, 8.0f, 0.0f, 1.0f), 20.0f, 3,0);
			}
			//弾が画面外に行ったとき
			if (g_aBullet[nCntBullet].pos.y <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			else if (g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			else if (g_aBullet[nCntBullet].pos.x <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			else if (g_aBullet[nCntBullet].pos.x >= SCREEN_WIDTH)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			Player *pPlayer = GetPlayer();
			GAMEMODE aMode = GetGamemode();
			
			if (aMode == GAMEMODE_NONE)
			{
				//弾との当たり判定
				if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
				{//自分の弾が相手に当たった時
					CollisionEnemy(&g_aBullet[nCntBullet]);
				}
				else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY && pPlayer->state == PLAYERSTATE_NORMAL)
				{//敵の弾が自分に当たった時
					CollisionPlayer(&g_aBullet[nCntBullet]);
				}
			}
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
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0 ; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);  //右から二番目を変えないとまずい！！
		}
	}
}

//=========================================================================================================
//弾の設定処理
//=========================================================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot,BULLETTYPE type , D3DXCOLOR col)
{
	int nCntBullet;
	Player aPlayer = *GetPlayer();

	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].col = col;
			g_aBullet[nCntBullet].frot.z = rot.z;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE , g_aBullet[nCntBullet].pos.y - BULLET_SIZE , 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE , g_aBullet[nCntBullet].pos.y - BULLET_SIZE , 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE , g_aBullet[nCntBullet].pos.y + BULLET_SIZE , 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE , g_aBullet[nCntBullet].pos.y + BULLET_SIZE , 0.0f);
			
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(g_aBullet[nCntBullet].col);
			pVtx[1].col = D3DXCOLOR(g_aBullet[nCntBullet].col);
			pVtx[2].col = D3DXCOLOR(g_aBullet[nCntBullet].col);
			pVtx[3].col = D3DXCOLOR(g_aBullet[nCntBullet].col);

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].bUse = true;

			break; //←重要！！
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//=========================================================================================================
//敵の当たり判定
//=========================================================================================================
void CollisionEnemy(Bullet *pBullet)
{
	Enemy *pEnemy = GetEnemy();
	Player *pPlayer = GetPlayer();
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy <= MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			if (pEnemy->nType == 0 || pEnemy->nType == 1 || pEnemy->nType == 2)
			{
				if (pBullet->pos.x >= pEnemy->pos.x - pEnemy->fsize && pBullet->pos.x <= pEnemy->pos.x + pEnemy->fsize  &&
					pBullet->pos.y >= pEnemy->pos.y - pEnemy->fsize && pBullet->pos.y <= pEnemy->pos.y + pEnemy->fsize)
				{
					HitEnemy(nCntEnemy, 1 + pPlayer->Attackpt[0]);
					pBullet->bUse = false;
				}
			}
			else if (pEnemy->nType == 3)
			{
				if (pBullet->pos.x >= (pEnemy->pos.x - (pEnemy->fsize-50.0f)) && 
					pBullet->pos.x <= (pEnemy->pos.x + pEnemy->fsize)  &&
					pBullet->pos.y >= (pEnemy->pos.y - pEnemy->fsize +BULLET_SIZE) && 
					pBullet->pos.y <= (pEnemy->pos.y + pEnemy->fsize-BULLET_SIZE) )
				{
					HitEnemy(nCntEnemy, 1 + pPlayer->Attackpt[0]);
					pBullet->bUse = false;
				}

				 else if (pBullet->pos.x >= (pEnemy->pos.x - pEnemy->fsize) &&
					pBullet->pos.x <= pEnemy->pos.x &&
					pBullet->pos.y >= (pEnemy->pos.y - pEnemy->fsize + (BULLET_SIZE+60.0f)) &&
					pBullet->pos.y <= (pEnemy->pos.y + pEnemy->fsize - (BULLET_SIZE+60.0f)))
				{
					HitEnemy(nCntEnemy, 1 + pPlayer->Attackpt[0]);
					pBullet->bUse = false;
				}
			}
		}
	}
}

//=========================================================================================================
//プレイヤーの当たり判定
//=========================================================================================================
void CollisionPlayer(Bullet *pBullet)
{
	int nCntEnemy;
	Enemy *pEnemy = GetEnemy();
	Player *pPlayer = GetPlayer();

	if (pBullet->pos.x >= pPlayer->pos.x - 20.0f && pBullet->pos.x <= pPlayer->pos.x + 20.0f  &&
		pBullet->pos.y >= pPlayer->pos.y - 20.0f && pBullet->pos.y <= pPlayer->pos.y + 20.0f)
	{
		if (pPlayer->life <= 1)
		{
			SetEnablePause(true);
			HitPlayer(1);

		}
		else
		{
			SetExplosion(pBullet->pos, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
			HitPlayer(1);
		}
		pBullet->bUse = false;
	}
	for (nCntEnemy = 0; nCntEnemy <= MAX_ENEMY; nCntEnemy++, pEnemy++)

	{
		if (pEnemy->bUse == true)
		{
			if (pPlayer->pos.x - 20.0f >= pEnemy->pos.x - pEnemy->fsize &&  pPlayer->pos.x + 20.0f <= pEnemy->pos.x + pEnemy->fsize  &&
				pPlayer->pos.y - 20.0f >= pEnemy->pos.y - pEnemy->fsize &&  pPlayer->pos.y + 20.0f <= pEnemy->pos.y + pEnemy->fsize)
			{
				HitPlayer(1);
				pBullet->bUse = false;
			}
		}
	}
}

