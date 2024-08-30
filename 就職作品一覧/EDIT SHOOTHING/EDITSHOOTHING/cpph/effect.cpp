//===========================================================
//
//エフェクトの処理操作
//Author:堀川萩大
//
//===========================================================
#include "game.h"
#include "effect.h"
#include "Player.h"
#include "explosion.h"

//マクロ定義
#define MAX_EFFECT (4056) //エフェクトの最大数

//エフェクトの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;	    //色
	float fRadius;		//半径
	int nLife;			//寿命
	int NumTex;			//テクスチャ番号
	bool bUse;			//使用の有無
}EFFECT;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureEffect[2] = {};		//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//頂点バッファのポインタ
EFFECT g_aEffect[MAX_EFFECT];						//エフェクトの情報数

void CollisionRazer(EFFECT *pEffecet);


//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect001.jpg",
		&g_pTextureEffect[1]);

	//エフェクトの情報の初期化
	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		 g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		 g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		 g_aEffect[nCntEffect].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();

}

//=========================================================================================================
//終了処理
//=========================================================================================================
void UninitEffect(void)
{
	//テクスチャの破棄
	if (g_pTextureEffect[0] != NULL)
	{
		g_pTextureEffect[0]->Release();
		g_pTextureEffect[0] = NULL;
	}
	if (g_pTextureEffect[1] != NULL)
	{
		g_pTextureEffect[1]->Release();
		g_pTextureEffect[1] = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=========================================================================================================
//更新処理
//=========================================================================================================
void UpdataEffect(void)
{
	int nCntEffect;
	VERTEX_2D *pVtx;
	Player *pPlayer = GetPlayer();

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		if ( g_aEffect[nCntEffect].bUse == true)
		{
			if (g_aEffect[nCntEffect].NumTex == 0)
			{
				g_aEffect[nCntEffect].fRadius -= 0.5f;
				g_aEffect[nCntEffect].col.a -= 0.05f;
				pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius,
					g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius,
					g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius,
					g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius,
					g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			}
			else if (g_aEffect[nCntEffect].NumTex == 1)
			{
				g_aEffect[nCntEffect].fRadius -= 0.1f;
				g_aEffect[nCntEffect].col.a -= 0.001f;
				pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 1000.0f,
					g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 25.0f,
					g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 1000.0f,
					g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 25.0f,
					g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			}
			//頂点座標


			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].nLife--;
			if (g_aEffect[nCntEffect].nLife <= 0 || g_aEffect[nCntEffect].fRadius<= 0.0f)
			{
				g_aEffect[nCntEffect].bUse = false;
			}

			if (g_aEffect[nCntEffect].NumTex == 1 && pPlayer->state == PLAYERSTATE_NORMAL)
			{
				CollisionRazer(&g_aEffect[nCntEffect]);
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================
//描画処理
//=========================================================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);



	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		if ( g_aEffect[nCntEffect].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect[g_aEffect[nCntEffect].NumTex]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);  //右から二番目を変えないとまずい！！
		}
	}

	//αブレンディングから戻す
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
}

//=========================================================================================================
//エフェクトの設置処理
//=========================================================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col ,float fRadius,int nLife,int nTex)
{
	int nCntEffect;

	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_2D *pVtx;
  	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		if ( g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].NumTex = nTex;

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius,
				g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius,
				g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius,
				g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius,
				g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

			//頂点カラー
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			 g_aEffect[nCntEffect].bUse = true;
			break; //←重要！！
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}
void CollisionRazer(EFFECT *pEffect)
{
	Player *pPlayer = GetPlayer();

	if (pEffect->pos.x - 1000.0f >= pPlayer->pos.x - 20.0f && pEffect->pos.x + 25.0f <= pPlayer->pos.x + 20.0f  ||
		pEffect->pos.y - pEffect->fRadius >= pPlayer->pos.y - 20.0f && pEffect->pos.y + pEffect->fRadius <= pPlayer->pos.y + 20.0f)
	{

		if (pPlayer->life <= 1)
		{
			SetEnablePause(true);
			HitPlayer(1);

		}
		else
		{
			SetExplosion(pEffect->pos, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
			HitPlayer(1);
		}
	}
}