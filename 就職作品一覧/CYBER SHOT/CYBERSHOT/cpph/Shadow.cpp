//===========================================================
//
//影の処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Shadow.h"

//マクロ変数
#define MAX_SHADOW (720)

typedef struct
{
	D3DXVECTOR3 posShadow;
	D3DXVECTOR3 rotShadow;
	D3DXMATRIX  mtxWorldShadow;
	float fLength;
	bool bUse;
}SHADOW;

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//頂点バッファポイント
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;			//テクスチャポインタ
SHADOW g_shadow[MAX_SHADOW];

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitShadow(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4*MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_shadow[nCntShadow].posShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCntShadow].rotShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCntShadow].bUse = false;

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-15.0f, 0.0f, +15.0f);
		pVtx[1].pos = D3DXVECTOR3(+15.0f, 0.0f, +15.0f);
		pVtx[2].pos = D3DXVECTOR3(-15.0f, 0.0f, -15.0f);
		pVtx[3].pos = D3DXVECTOR3(+15.0f, 0.0f, -15.0f);

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
	g_pVtxBuffShadow->Unlock();
}

//=========================================================================================================
//影の終了処理
//=========================================================================================================
void UninitShadow(void)
{
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == true)
		{
			g_shadow[nCntShadow].bUse = false;
		}
	}
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=========================================================================================================
//影の更新処理
//=========================================================================================================
void UpdateShadow(void)
{

}

//=========================================================================================================
//影の描画処理
//=========================================================================================================
void DrawShadow(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == true)
		{


			D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

			//減算合成の設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_shadow[nCntShadow].mtxWorldShadow);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_shadow[nCntShadow].rotShadow.y, g_shadow[nCntShadow].rotShadow.x, g_shadow[nCntShadow].rotShadow.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorldShadow, &g_shadow[nCntShadow].mtxWorldShadow, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_shadow[nCntShadow].posShadow.x, g_shadow[nCntShadow].posShadow.y, g_shadow[nCntShadow].posShadow.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorldShadow, &g_shadow[nCntShadow].mtxWorldShadow, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_shadow[nCntShadow].mtxWorldShadow);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);


			pDevice->SetTexture(0, g_pTextureShadow);

			//影の描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4* nCntShadow, 2);

		}
	}
	//通常合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=========================================================================================================
//影の使用番号を取得
//=========================================================================================================
int SetShadow(float fLength, D3DXVECTOR3 pos)
{
	int nCntShadow;
	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == false)
		{
			g_shadow[nCntShadow].posShadow = pos;
			g_shadow[nCntShadow].rotShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-fLength, 1.0f, +fLength);
			pVtx[1].pos = D3DXVECTOR3(+fLength, 1.0f, +fLength);
			pVtx[2].pos = D3DXVECTOR3(-fLength, 1.0f, -fLength);
			pVtx[3].pos = D3DXVECTOR3(+fLength, 1.0f, -fLength);
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
			g_shadow[nCntShadow].bUse = true;
			break;
		}
		pVtx += 4;

	}
	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();
	return nCntShadow;
}

//=========================================================================================================
//影の設置処理
//=========================================================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_shadow[nIdxShadow].posShadow = pos;
	
}


//=========================================================================================================
//影の消去処理
//=========================================================================================================
void FinishShadow(int nIdxShadow)
{
 	g_shadow[nIdxShadow].bUse = false;
}