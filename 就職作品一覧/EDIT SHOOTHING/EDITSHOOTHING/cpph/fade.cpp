//===========================================================
//
//フェードの処理操作
//Author:堀川萩大
//
//===========================================================
#include "fade.h"
#include "main.h"
#include "game.h"
#include "sound.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;  //フェードの数の頂点バッファ
FADE g_Fade;
float g_FadeCount;
MODE g_ModeNext;
D3DXCOLOR g_ColorFade;

//=========================================================================================================
//フェードの初期化処理
//=========================================================================================================
void InitFade(MODE ModeNext)
{
	g_Fade = FADE_IN;
	g_ModeNext = ModeNext;
	g_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

	//頂点バッファをアンロックする
	g_pVtxBuffFade->Unlock();

	SetMode(g_ModeNext);
}

//=========================================================================================================
//フェードの終了処理
//=========================================================================================================
void UninitFade(void)
{
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//フェードの更新処理
void UpdateFade(void)
{
	if (g_Fade != FADE_NONE)
	{
		if (g_Fade == FADE_IN)
		{
			g_ColorFade.a -= 0.05f;
			if (g_ColorFade.a <= 0.0f)
			{
				g_ColorFade.a = 0.0f;
				g_Fade = FADE_NONE;
			}
		}
		else if (g_Fade == FADE_OUT)
		{
			g_ColorFade.a += g_FadeCount;
			if (g_ColorFade.a >= 1.0f)
			{
				g_ColorFade.a = 1.0f;
				g_Fade = FADE_IN;
				SetMode(g_ModeNext);
			}
		}

		VERTEX_2D *pVtx;
		//頂点バッファをロックし頂点情報へのポインタを取得
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
		//頂点カラーの設定
		pVtx[0].col = g_ColorFade;
		pVtx[1].col = g_ColorFade;
		pVtx[2].col = g_ColorFade;
		pVtx[3].col = g_ColorFade;
		//頂点バッファをアンロックする
		g_pVtxBuffFade->Unlock();
	
	}
}

//=========================================================================================================
//フェードの描画処理
//=========================================================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, NULL);

	//ポリゴン
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void SetFade(MODE ModeNext, float Fade)
{
	g_Fade = FADE_OUT;
	g_FadeCount = Fade;
	g_ModeNext = ModeNext;
	g_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

FADE GetFade(void)
{
	return g_Fade;
}