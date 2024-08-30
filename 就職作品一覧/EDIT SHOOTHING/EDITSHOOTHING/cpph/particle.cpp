////===========================================================
////
////エフェクトの処理操作
////Author:堀川萩大
////
////===========================================================
//#include "game.h"
//#include "particle.h"
//
////マクロ定義
//#define MAX_PARTICLE (4056) //エフェクトの最大数
//
////エフェクトの構造体の定義
//typedef struct
//{
//	D3DXVECTOR3 pos;	//位置
//	D3DXCOLOR col;	    //色
//	float fRadius;		//半径
//	int nLife;			//寿命
//	bool bUse;			//使用の有無
//}PARTICLE;
//
////グローバル変数宣言
//PARTICLE g_aParticle[MAX_PARTICLE];						//エフェクトの情報数
//
////=========================================================================================================
////初期化処理
////=========================================================================================================
//void InitParticle(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	int nCntPARTICLE;
//
//	//デバイスの取得
//	pDevice = GetDevice();
//
//	//エフェクトの情報の初期化
//	for (nCntPARTICLE = 0; nCntPARTICLE <MAX_PARTICLE; nCntPARTICLE++)
//	{
//		g_aParticle[nCntPARTICLE].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aParticle[nCntPARTICLE].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//		g_aParticle[nCntPARTICLE].bUse = false;
//	}
//
//	//頂点バッファの生成
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PARTICLE,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffPARTICLE,
//		NULL);
//
//	VERTEX_2D *pVtx;
//	//頂点バッファをロックし頂点情報へのポインタを取得
//	g_pVtxBuffPARTICLE->Lock(0, 0, (void**)&pVtx, 0);
//	for (nCntPARTICLE = 0; nCntPARTICLE <MAX_PARTICLE; nCntPARTICLE++)
//	{
//		//頂点座標
//		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		//rhwの設定
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//		//頂点カラー
//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//テクスチャ座標
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffPARTICLE->Unlock();
//
//}
//
////=========================================================================================================
////終了処理
////=========================================================================================================
//void UninitParticle(void)
//{
//	//テクスチャの破棄
//	if (g_pTexturePARTICLE != NULL)
//	{
//		g_pTexturePARTICLE->Release();
//		g_pTexturePARTICLE = NULL;
//	}
//
//	//頂点バッファの破棄
//	if (g_pVtxBuffPARTICLE != NULL)
//	{
//		g_pVtxBuffPARTICLE->Release();
//		g_pVtxBuffPARTICLE = NULL;
//	}
//}
//
////=========================================================================================================
////更新処理
////=========================================================================================================
//void UpdataParticle(void)
//{
//	int nCntPARTICLE;
//	VERTEX_2D *pVtx;
//	g_pVtxBuffPARTICLE->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntPARTICLE = 0; nCntPARTICLE <MAX_PARTICLE; nCntPARTICLE++)
//	{
//		if (g_aParticle[nCntPARTICLE].bUse == true)
//		{
//			g_aParticle[nCntPARTICLE].fRadius -= 0.5f;
//			g_aParticle[nCntPARTICLE].col.a -= 0.05f;
//			//頂点座標
//			pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x - g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y - g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x + g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y - g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x - g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y + g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x + g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y + g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//
//			pVtx[0].col = g_aParticle[nCntPARTICLE].col;
//			pVtx[1].col = g_aParticle[nCntPARTICLE].col;
//			pVtx[2].col = g_aParticle[nCntPARTICLE].col;
//			pVtx[3].col = g_aParticle[nCntPARTICLE].col;
//
//			g_aParticle[nCntPARTICLE].nLife--;
//			if (g_aParticle[nCntPARTICLE].nLife == 0)
//			{
//				g_aParticle[nCntPARTICLE].bUse = false;
//			}
//
//		}
//		pVtx += 4;
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffPARTICLE->Unlock();
//}
//
////=========================================================================================================
////描画処理
////=========================================================================================================
//void DrawParticle(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	int nCntPARTICLE;
//
//	pDevice = GetDevice();
//	//頂点バッファをデータストリームに設定
//	pDevice->SetStreamSource(0, g_pVtxBuffPARTICLE, 0, sizeof(VERTEX_2D));
//
//	//頂点フォーマットの設定
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//テクスチャの設定
//	pDevice->SetTexture(0, g_pTexturePARTICLE);
//
//	//αブレンディングを加算合成に設定
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
//
//	int nCntParticle;
//	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
//	{
//		if (g_aParticle[MAX_PARTICLE].bUse == true)
//		{
//
//		}
//	}
//
//	//αブレンディングから戻す
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//}
//
////=========================================================================================================
////エフェクトの設置処理
////=========================================================================================================
//void SetParticle(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
//{
//	int nCntPARTICLE;
//
//	//頂点バッファをロックし頂点情報へのポインタを取得
//	VERTEX_2D *pVtx;
//	g_pVtxBuffPARTICLE->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntPARTICLE = 0; nCntPARTICLE <MAX_PARTICLE; nCntPARTICLE++)
//	{
//		if (g_aParticle[nCntPARTICLE].bUse == false)
//		{
//			g_aParticle[nCntPARTICLE].pos = pos;
//			g_aParticle[nCntPARTICLE].col = col;
//			g_aParticle[nCntPARTICLE].fRadius = fRadius;
//			g_aParticle[nCntPARTICLE].nLife = nLife;
//
//			//頂点座標
//			pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x - g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y - g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x + g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y - g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x - g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y + g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x + g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y + g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//
//			//頂点カラー
//			pVtx[0].col = col;
//			pVtx[1].col = col;
//			pVtx[2].col = col;
//			pVtx[3].col = col;
//
//			g_aParticle[nCntPARTICLE].bUse = true;
//			break; //←重要！！
//		}
//		pVtx += 4;
//	}
//	//頂点バッファをアンロックする
//	g_pVtxBuffPARTICLE->Unlock();
//}