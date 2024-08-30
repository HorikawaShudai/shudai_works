//===========================================================
//
//エフェクトの処理操作
//Author:堀川萩大
//
//===========================================================
#include "effect.h"
#include "explosion.h"

//マクロ定義
#define MAX_EFFECT (4096) //エフェクトの最大数

//エフェクトの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;	    //色
	EFFECTKIND type;
	float fRadius;		//半径
	int nLife;			//寿命
	bool bUse;			//使用の有無
}EFFECT;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureEffect = {};		//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//頂点バッファのポインタ
EFFECT g_aEffect[MAX_EFFECT];						//エフェクトの情報数
D3DXMATRIX g_mtxWorldEffect;


//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitEffect(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEffect;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);

	//エフェクトの情報の初期化
	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		 g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		 g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		 g_aEffect[nCntEffect].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(-50.0f, 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f, 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
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
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
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
void UpdateEffect(void)
{
	int nCntEffect;
	VERTEX_3D *pVtx;

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		if ( g_aEffect[nCntEffect].bUse == true)
		{
			if (g_aEffect[nCntEffect].type == EFFECT_KIND_BULLET)
			{
				g_aEffect[nCntEffect].fRadius -= 0.5f;
				g_aEffect[nCntEffect].col.a -= 0.05f;
				pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius,
					+g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius,
					+g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius,
					-g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius,
					-g_aEffect[nCntEffect].fRadius, 0.0f);

				g_aEffect[nCntEffect].nLife--;
				if (g_aEffect[nCntEffect].nLife <= 0 || g_aEffect[nCntEffect].fRadius <= 0.0f)
				{
					g_aEffect[nCntEffect].bUse = false;
				}
			}
			else if(g_aEffect[nCntEffect].type == EFFECT_KIND_SANDDUST)
			{
				g_aEffect[nCntEffect].pos.y +=1.0f;
				g_aEffect[nCntEffect].fRadius += 1.0f;
				g_aEffect[nCntEffect].col.a -= 0.05f;
				pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius,g_aEffect[nCntEffect].pos.y+g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius,g_aEffect[nCntEffect].pos.y+g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius,g_aEffect[nCntEffect].pos.y-g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius,g_aEffect[nCntEffect].pos.y-g_aEffect[nCntEffect].fRadius, 0.0f);

				g_aEffect[nCntEffect].nLife--;
				if (g_aEffect[nCntEffect].nLife <= 0 || g_aEffect[nCntEffect].fRadius <= 0.0f)
				{
					g_aEffect[nCntEffect].bUse = false;
				}
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			D3DXMATRIX mtxTrans;	//計算用マトリックス
			D3DXMATRIX mtxView;		//ビューマトリックスの取得用

									//Zテストを有効にする
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//αテストを有効
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldEffect);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_mtxWorldEffect, NULL, &mtxView);
			g_mtxWorldEffect._41 = 0.0f;
			g_mtxWorldEffect._42 = 0.0f;
			g_mtxWorldEffect._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEffect);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);


			pDevice->SetTexture(0, g_pTextureEffect);

			//ビルボード
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);

			//αテストを有効
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

			//Zテストを有効にする
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
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
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col ,float fRadius,int nLife, EFFECTKIND type)
{
	int nCntEffect;

	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_3D *pVtx;
  	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		if ( g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].type = type;
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