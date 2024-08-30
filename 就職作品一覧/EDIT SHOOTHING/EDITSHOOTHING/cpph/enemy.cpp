//===========================================================
//
//敵の処理操作
//Author:堀川萩大
//
//===========================================================
#include "game.h"
#include "enemy.h"
#include "Input.h"
#include "Bullet.h"
#include "explosion.h"
#include "score.h"
#include "sound.h"
#include "fade.h"
#include "Item.h"
#include "effect.h"
#include "Player.h"

//マクロ定義
#define NUM_ENEMY  (128)				//敵の最大数

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_apTextureEnemy[4] = {};	//敵の種類のテクスチャ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//敵の種類の頂点バッファ
Enemy g_aEnemy[MAX_ENEMY];								//敵の種類
int g_nNumEnemy;										//敵の数
float g_aEnemySixe[MAX_ENEMY] = {};										//敵のサイズ
D3DXVECTOR3 g_fpos = D3DXVECTOR3(1000.0f, 360.0f, 0.0f);
D3DXVECTOR3 g_fmove = D3DXVECTOR3(0.0f, 200.0f, 0.0f);
int g_killNum;
int g_nCntShot;

//=========================================================================================================
//敵の初期化処理
//=========================================================================================================
void InitEnemy(void)
{
	int nCntEnemy;
	g_nNumEnemy = 0;
	g_killNum = 0;

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ENEMY\\enemy004.png",
		&g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ENEMY\\enemy003.png",
		&g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ENEMY\\enemy001.png",
		&g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ENEMY\\boss.png",
		&g_apTextureEnemy[3]);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy <NUM_ENEMY ; nCntEnemy++)
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].EneBullet = 0;
		g_aEnemy[nCntEnemy].EneBtCnt = 0;
		g_aEnemy[nCntEnemy].nLifeHarf = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

	//敵の設定処理
	SetEnemy(D3DXVECTOR3(1300.0f, 220.0f, 0.0f), 1, 27.0f); //0
	SetEnemy(D3DXVECTOR3(1350.0f, 220.0f, 0.0f), 1, 27.0f); //1
	SetEnemy(D3DXVECTOR3(1400.0f, 220.0f, 0.0f), 1, 27.0f); //2
	SetEnemy(D3DXVECTOR3(1450.0f, 220.0f, 0.0f), 2, 27.0f); //3
	//敵の設定処理								 
	SetEnemy(D3DXVECTOR3(2100.0f, 500.0f, 0.0f), 1, 27.0f); //4
	SetEnemy(D3DXVECTOR3(2150.0f, 500.0f, 0.0f), 1, 27.0f); //5
	SetEnemy(D3DXVECTOR3(2200.0f, 500.0f, 0.0f), 1, 27.0f); //6
	SetEnemy(D3DXVECTOR3(2250.0f, 500.0f, 0.0f), 2, 27.0f); //7
	//敵の設定処理								 
	SetEnemy(D3DXVECTOR3(2900.0f, 100.0f, 0.0f), 1, 27.0f); //8
	SetEnemy(D3DXVECTOR3(2900.0f, 200.0f, 0.0f), 0, 27.0f); //9
	SetEnemy(D3DXVECTOR3(2900.0f, 400.0f, 0.0f), 0, 27.0f); //10
	SetEnemy(D3DXVECTOR3(2900.0f, 500.0f, 0.0f), 1, 27.0f); //11
	//敵の設定処理								 
	SetEnemy(D3DXVECTOR3(3700.0f, 100.0f, 0.0f), 1, 27.0f); //12
	SetEnemy(D3DXVECTOR3(3800.0f, 200.0f, 0.0f), 0, 27.0f);//13
	SetEnemy(D3DXVECTOR3(3900.0f, 300.0f, 0.0f), 1, 27.0f); //14
	SetEnemy(D3DXVECTOR3(3800.0f, 400.0f, 0.0f), 0, 27.0f);//15
	SetEnemy(D3DXVECTOR3(3700.0f, 500.0f, 0.0f), 1, 27.0f); //16
	//敵の設定処理								 
	SetEnemy(D3DXVECTOR3(4700.0f, 100.0f, 0.0f), 1, 27.0f); //17
	SetEnemy(D3DXVECTOR3(4600.0f, 200.0f, 0.0f), 0, 27.0f); //18
	SetEnemy(D3DXVECTOR3(4500.0f, 300.0f, 0.0f), 1, 27.0f); //19
	SetEnemy(D3DXVECTOR3(4600.0f, 400.0f, 0.0f), 0, 27.0f); //20
	SetEnemy(D3DXVECTOR3(4700.0f, 500.0f, 0.0f), 1, 27.0f); //21

}

//=========================================================================================================
//敵の終了処理
//=========================================================================================================
void UninitEnemy(void)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].bUse = false;
		}
	}
	for (nCntEnemy = 0; nCntEnemy < 4; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

		if (g_pVtxBuffEnemy != NULL)
		{
			g_pVtxBuffEnemy->Release();
			g_pVtxBuffEnemy = NULL;
		}
}

//=========================================================================================================
//敵の更新処理
//=========================================================================================================
void UpdataEnemy(void)
{
	int nCntEnemy;
	FADE fFade = GetFade();
	int nNumEnemy = *GetNumEnemy();
	Enemy aEnemy = *GetEnemy();
	Player aPlayer = *GetPlayer();
	GAMEMODE aMode = GetGamemode();

	//ボス召喚
	if ( nNumEnemy <= 0 && aMode == GAMEMODE_NONE)
	{//敵がいなくなった場合

		SetEnemy(D3DXVECTOR3(1400.0f, 350.0f, 0.0f), 3, 100.0f);

	}

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (g_aEnemy[nCntEnemy].nType == 3)
			{//ボスの場合
				if (g_aEnemy[nCntEnemy].pos.x > 900.0f  && g_aEnemy[nCntEnemy].state == ENEMYSTATE_MAX)
				{
					g_aEnemy[nCntEnemy].pos.x -= 1.0f;
				}
				if (g_aEnemy[nCntEnemy].pos.x == 1000.0f  && g_aEnemy[nCntEnemy].state == ENEMYSTATE_MAX )
				{
					//サウンドの停止
					StopSound();
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					//サウンドの初期化処理
					PlaySound(SOUND_LABEL_BGM001);
				}

				if (g_aEnemy[nCntEnemy].state != ENEMYSTATE_MAX)
				{
					if (g_aEnemy[nCntEnemy].pos.y < g_fpos.y)
					{
						g_aEnemy[nCntEnemy].pos.y += 1.0f;
					}
					else if (g_aEnemy[nCntEnemy].pos.y > g_fpos.y)
					{
						g_aEnemy[nCntEnemy].pos.y -= 1.0f;
					}

					if (g_aEnemy[nCntEnemy].pos.y == g_fpos.y)
					{
						g_fpos.y += g_fmove.y;

						if (750.0f <= g_fpos.y + g_fmove.y)
						{
							g_fmove.y *= -1.0f;
						}
						else if (10.0f >= g_fpos.y + g_fmove.y)
						{
							g_fmove.y *= -1.0f;
						}
					}
				}
			}
			else
			{//ボス以外

				g_aEnemy[nCntEnemy].pos.x -= 1.0f;

				if (nCntEnemy <= 3 && nCntEnemy >= 0)
				{
					if (g_aEnemy[nCntEnemy].pos.x <900.0f)
					{
						if (g_aEnemy[nCntEnemy].Farstpos.y > 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y += 2.0f;
						}
						else if (g_aEnemy[nCntEnemy].Farstpos.y < 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y -= 2.0f;
						}
						else
						{
							g_aEnemy[nCntEnemy].pos.x -= 2.0f;
						}
					}
				}
				else if (nCntEnemy <=7 && nCntEnemy >= 4)
				{
					if (g_aEnemy[nCntEnemy].pos.x <900.0f)
					{
						if (g_aEnemy[nCntEnemy].Farstpos.y > 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y += 2.0f;
						}
						else if (g_aEnemy[nCntEnemy].Farstpos.y < 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y -= 2.0f;
						}
						else
						{
							g_aEnemy[nCntEnemy].pos.x -= 2.0f;
						}
					}
				}
				else if (nCntEnemy <=11 && nCntEnemy >= 8)
				{
					if (g_aEnemy[nCntEnemy].pos.x <1000.0f)
					{
						if (g_aEnemy[nCntEnemy].Farstpos.y > 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y -= 1.0f;
						}
						else if (g_aEnemy[nCntEnemy].Farstpos.y < 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y += 1.0f;
						}
						else
						{
							g_aEnemy[nCntEnemy].pos.x -= 1.0f;
						}
					}
				}
				else if (nCntEnemy <=16 && nCntEnemy >= 12)
				{
					if (g_aEnemy[nCntEnemy].pos.x <900.0f)
					{
						if (g_aEnemy[nCntEnemy].Farstpos.y > 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y -= 1.0f;
						}
						else if (g_aEnemy[nCntEnemy].Farstpos.y < 360.f)
						{

							g_aEnemy[nCntEnemy].pos.y += 1.0f;
						}
						else
						{
							g_aEnemy[nCntEnemy].pos.x -= 1.0f;
						}
					}
				}
				else if (nCntEnemy <=21 && nCntEnemy >= 17)
				{
					if (g_aEnemy[nCntEnemy].pos.x <900.0f)
					{
						if (g_aEnemy[nCntEnemy].Farstpos.y > 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y -= 1.0f;
						}
						else if (g_aEnemy[nCntEnemy].Farstpos.y < 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y += 1.0f;
						}
						else
						{
							g_aEnemy[nCntEnemy].pos.x -= 1.0f;
						}
					}
				}

				//範囲外に出た場合
					if (g_aEnemy[nCntEnemy].pos.x < 0.0f || g_aEnemy[nCntEnemy].pos.y < 0.0f || g_aEnemy[nCntEnemy].pos.y > 720.0f)
					{
						g_aEnemy[nCntEnemy].bUse = false;
						g_nNumEnemy--;
						g_killNum++;
					}
			}


			if (g_aEnemy[nCntEnemy].pos.x > 0.0f && g_aEnemy[nCntEnemy].pos.x < 1280.0f)
			{

				g_aEnemy[nCntEnemy].EneBullet++;
				if (g_aEnemy[nCntEnemy].nType == 1 || g_aEnemy[nCntEnemy].nType == 2)
				{
					if ((g_aEnemy[nCntEnemy].EneBullet % g_aEnemy[nCntEnemy].EneBtCnt) == 0)
					{
						SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y, 0.0f),
							D3DXVECTOR3(-5.5f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), BULLETTYPE_ENEMY, D3DXCOLOR(0.8f, 0.4f, 0.4f, 1.0f));
					}
				}
				else if (g_aEnemy[nCntEnemy].nType == 0)
				{
					if ((g_aEnemy[nCntEnemy].EneBullet % g_aEnemy[nCntEnemy].EneBtCnt) == 0)
					{
  						SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y, 0.0f),
							D3DXVECTOR3(-6.5f, -6.5f, 0.0f),
							D3DXVECTOR3(0.0f, 0.0f, atan2f((g_aEnemy[nCntEnemy].pos.x -20.0f) - aPlayer.pos.x, (g_aEnemy[nCntEnemy].pos.y) - aPlayer.pos.y))
							, BULLETTYPE_ENEMY, D3DXCOLOR(0.8f, 0.4f, 0.4f, 1.0f));
					}
				}
				else if (g_aEnemy[nCntEnemy].nType == 3  && g_aEnemy[nCntEnemy].state != ENEMYSTATE_MAX)
				{
					if ((g_aEnemy[nCntEnemy].EneBullet % g_aEnemy[nCntEnemy].EneBtCnt) == 0)
					{
						SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y, 0.0f),
							D3DXVECTOR3(-7.2f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), BULLETTYPE_ENEMY, D3DXCOLOR(0.8f, 0.4f, 0.4f, 1.0f));
						if (g_aEnemy[nCntEnemy].nLife < g_aEnemy[nCntEnemy].nLifeHarf)
						{
							SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 40.0f, g_aEnemy[nCntEnemy].pos.y + 80.0f, 0.0f),
								D3DXVECTOR3(-6.5f, -8.5f, 0.0f), 
								D3DXVECTOR3(0.0f, 0.0f, atan2f((g_aEnemy[nCntEnemy].pos.x + 40.0f)- aPlayer.pos.x, (g_aEnemy[nCntEnemy].pos.y + 80.0f) - aPlayer.pos.y))
								, BULLETTYPE_ENEMY, D3DXCOLOR(0.8f, 0.4f, 0.4f, 1.0f));
							SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 40.0f, g_aEnemy[nCntEnemy].pos.y - 80.0f, 0.0f),
								D3DXVECTOR3(-6.5f, -8.5f, 0.0f), 
								D3DXVECTOR3(0.0f, 0.0f,atan2f((g_aEnemy[nCntEnemy].pos.x + 40.0f)- aPlayer.pos.x, (g_aEnemy[nCntEnemy].pos.y - 80.0f) - aPlayer.pos.y))
								, BULLETTYPE_ENEMY, D3DXCOLOR(0.8f, 0.4f, 0.4f, 1.0f));
							g_nCntShot++;
							if (g_nCntShot % 5 == 0)
							{
								SetEffect(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, 0.0f),
									D3DXCOLOR(0.0f, 8.0f, 0.0f, 1.0f), 10.0f, 1000, 1);
							}
						}
					}
				}
			}
			if (g_aEnemy[nCntEnemy].nType == 3 && g_aEnemy[nCntEnemy].nLife <= g_aEnemy[nCntEnemy].nLifeHarf)
			{
				g_aEnemy[nCntEnemy].EneBtCnt = 50;
				pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			}
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterstate--;
				if (g_aEnemy[nCntEnemy].nCounterstate <= 0)
				{
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
				}
				break;
			}

			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fsize, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fsize, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fsize, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fsize, 0.0f);
		}
		pVtx += 4;

	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();


}

//=========================================================================================================
//敵の描画処理
//=========================================================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy <NUM_ENEMY ; nCntEnemy++)
	{

		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			//ポリゴン
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//=========================================================================================================
//敵の設置処理
//=========================================================================================================
void SetEnemy(D3DXVECTOR3 pos,int Type , float size)
{
	int nCntEnemy;
	Player aPlayer = *GetPlayer();

	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{

			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].Farstpos = pos;	

			g_aEnemy[nCntEnemy].fsize = size;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3( g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y -g_aEnemy[nCntEnemy].fsize, 0.0f);
			pVtx[1].pos = D3DXVECTOR3( g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y -g_aEnemy[nCntEnemy].fsize, 0.0f);
			pVtx[2].pos = D3DXVECTOR3( g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y +g_aEnemy[nCntEnemy].fsize, 0.0f);
			pVtx[3].pos = D3DXVECTOR3( g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y +g_aEnemy[nCntEnemy].fsize, 0.0f);

			g_aEnemy[nCntEnemy].nType = Type;
			switch (Type)
			{
			case 0:
				g_aEnemy[nCntEnemy].EneBtCnt = 95;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
				g_aEnemy[nCntEnemy].nLife = 8;

				break;
			case 1:
				g_aEnemy[nCntEnemy].EneBtCnt = 75;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
				g_aEnemy[nCntEnemy].nLife = 5;

				break;
			case 2:
				g_aEnemy[nCntEnemy].EneBtCnt = 85;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
				g_aEnemy[nCntEnemy].nLife = 5;

				break;
			case 3:
				g_aEnemy[nCntEnemy].EneBtCnt = 60;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_MAX;
				g_aEnemy[nCntEnemy].nLife = (80 + (aPlayer.Attackpt[0] * 20));

				break;
			}
			g_aEnemy[nCntEnemy].bUse = true;
			g_nNumEnemy++;

			if (g_aEnemy[nCntEnemy].nLife % 2 == 1)
			{
				g_aEnemy[nCntEnemy].nLifeHarf = ((g_aEnemy[nCntEnemy].nLife - 1) / 2);
			}
			else
			{
				g_aEnemy[nCntEnemy].nLifeHarf = (g_aEnemy[nCntEnemy].nLife / 2);
			}

			break; //←重要！！
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================
//敵の状態遷移処理
//=========================================================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	FADE fFade = GetFade();
	Player aPlayer = *GetPlayer();


	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_NORMAL)
	{
		g_aEnemy[nCntEnemy].nLife -= nDamage;
	}
	if (g_aEnemy[nCntEnemy].nLife < 1)
	{
		g_nNumEnemy--;
		g_killNum++;

		if (g_aEnemy[nCntEnemy].nType == 3 && fFade == FADE_NONE)
		{
			SetGameMode(GAMEMODE_GAMECLEAR);
			AddScore(16000-(aPlayer.Attackpt[0] * 2000));
		}
		else 
		{
			if (g_aEnemy[nCntEnemy].nType == 2 || g_aEnemy[nCntEnemy].nType == 0)
			{
				DropItem(g_aEnemy[nCntEnemy].pos);
			}
			AddScore(450 - (aPlayer.Attackpt[0] * 50));
		}
		SetExplosion(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 40.0f, g_aEnemy[nCntEnemy].pos.y, 0.0f)
			, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_aEnemy[nCntEnemy].bUse = false;
	}
	else
	{
		pVtx += (4 * nCntEnemy);

		if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_NORMAL)
		{

			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
			g_aEnemy[nCntEnemy].nCounterstate = 5;
			PlaySound(SOUND_LABEL_SE_HIT);
		}
		else if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_MAX)
		{
			PlaySound(SOUND_LABEL_SE_NOHIT);
		}
	}
	g_pVtxBuffEnemy->Unlock();

}

//=========================================================================================================
//敵の情報取得処理
//=========================================================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//=========================================================================================================
//敵数の取得処理
//=========================================================================================================
int *GetNumEnemy(void)
{
	return &g_nNumEnemy;
}

//=========================================================================================================
//kill数の取得処理
//=========================================================================================================
int *Getg_killNum(void)
{
	return &g_killNum;
}