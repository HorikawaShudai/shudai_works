//===========================================================
//
//スコアの処理操作
//Author:堀川萩大
//
//===========================================================
#include "game.h"
#include "score.h"
#include "input.h"

//マクロ定義
#define NUM_PLACE (8) //スコアの最大数

//スコアの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;	    //色
}score;

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturescore = NULL;		//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffscore = NULL;	//頂点バッファのポインタ
D3DXVECTOR3 g_posScore;							//スコアの位置
int g_nScore;									//スコアの値

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntscore;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&g_pTexturescore);

	//スコアの情報の初期化
	g_posScore = D3DXVECTOR3(1000.0f, 10.0f, 0.0f);
	g_nScore = 0;


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffscore,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffscore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntscore = 0; nCntscore < NUM_PLACE; nCntscore++)
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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffscore->Unlock();

}

//=========================================================================================================
//終了処理
//=========================================================================================================
void UninitScore(void)
{
	//テクスチャの破棄
	if (g_pTexturescore != NULL)
	{
		g_pTexturescore->Release();
		g_pTexturescore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffscore != NULL)
	{
		g_pVtxBuffscore->Release();
		g_pVtxBuffscore = NULL;
	}
}

//=========================================================================================================
//更新処理
//=========================================================================================================
void UpdataScore(void)
{
	//if (GetKeyboardPress(DIK_1) == true)
	//{//Aのみ押された場合
	//	AddScore(10000000);
	//}
	//if (GetKeyboardPress(DIK_2) == true)
	//{//Aのみ押された場合
	//	AddScore(1000000);
	//}	
	//if (GetKeyboardPress(DIK_3) == true)
	//{//Aのみ押された場合
	//	AddScore(100000);
	//}	
	//if (GetKeyboardPress(DIK_4) == true)
	//{//Aのみ押された場合
	//	AddScore(10000);
	//}	
	//if (GetKeyboardPress(DIK_5) == true)
	//{//Aのみ押された場合
	//	AddScore(1000);
	//}
	//if (GetKeyboardPress(DIK_6) == true)
	//{//Aのみ押された場合
	//	AddScore(100);
	//}
	//if (GetKeyboardPress(DIK_7) == true)
	//{//Aのみ押された場合
	//	AddScore(10);
	//}
	//if (GetKeyboardPress(DIK_8) == true)
	//{//Aのみ押された場合
	//	AddScore(1);
	//}
	//if (GetKeyboardPress(DIK_0) == true)
	//{//Aのみ押された場合
	//	AddScore(-99999999);
	//}
}

//=========================================================================================================
//描画処理
//=========================================================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntscore;

	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffscore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturescore);

	for (nCntscore = 0; nCntscore < NUM_PLACE; nCntscore++)
	{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntscore * 4, 2);  //右から二番目を変えないとまずい！！
	}
}

//=========================================================================================================
//スコアの設定処理
//=========================================================================================================
void SetScore(int nScore)
{
	int nCntscore;
	int aTexU[NUM_PLACE];
	int Max;
	int Min;
	int nCount;
	g_nScore += nScore;
	
	for (nCount = 0,Max = 100000000,Min = 10000000; nCount < NUM_PLACE; nCount++,Max/=10,Min/=10)
	{
		aTexU[nCount] = g_nScore % Max / Min;
	}

	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_2D *pVtx;
	g_pVtxBuffscore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntscore = 0; nCntscore < NUM_PLACE; nCntscore++)
	{
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x + (20.0f*nCntscore)
			, g_posScore.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + 20.0f + (20.0f*nCntscore)
			, g_posScore.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x + (20.0f*nCntscore)
			, g_posScore.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + 20.0f + (20.0f*nCntscore)
			, g_posScore.y + 20.0f, 0.0f);
		
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f , 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f , 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f , 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f , 1.0f);

		//break; //←重要！！

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffscore->Unlock();
}

//=========================================================================================================
//スコアの計算処理
//=========================================================================================================
void AddScore(int nValue)
{
	int aTexU[NUM_PLACE];
	int nCntscore;
	int Max;
	int Min;
	int nCount;

	g_nScore += nValue;

	if (g_nScore > 99999999)
	{
		g_nScore = 99999999;
	}
	if (g_nScore < 0)
	{
		g_nScore = 0;
	}

	for (nCount = 0, Max = 100000000, Min = 10000000; nCount < NUM_PLACE; nCount++, Max /= 10, Min /= 10)
	{
		aTexU[nCount] = g_nScore % Max / Min;
	}

	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_2D *pVtx;
	g_pVtxBuffscore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntscore = 0; nCntscore < NUM_PLACE; nCntscore++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f*aTexU[nCntscore]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f*aTexU[nCntscore]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f*aTexU[nCntscore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f*aTexU[nCntscore]), 1.0f);

		//break; //←重要！！

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffscore->Unlock();
}