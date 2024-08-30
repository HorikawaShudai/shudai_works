//===========================================================
//
//Blockの処理操作
//Author:堀川萩大
//
//===========================================================
#include "block.h"
#include "input.h"
#include "player.h"
#include "game.h"


//マクロ定義
#define MAX_BLOCK (1024) //Blockの最大数
#define MAX_TEX (4) //Blockの最大数


//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTextureBlock[MAX_TEX] = {};			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	//頂点バッファのポインタ
Block g_aBlock[MAX_BLOCK];						//Blockの情報数


//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tuti001.jpg",
		&g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ladder.png",
		&g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\saw.png",
		&g_pTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ori.png",
		&g_pTextureBlock[3]);
	//Blockの情報の初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].nCnt = 0.0f;
		g_aBlock[nCntBlock].CntMove = 1.0f;

	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
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
	g_pVtxBuffBlock->Unlock();

	/*for (int nCount = 0; nCount < 28; nCount++)
	{
		SetBlock(D3DXVECTOR3(0.0f, (0.0f + (nCount*100.0f)), 0.0f), 100.0f, 100.0f, BLOCKTYPE_NONE);
	}
	for (int nCount = 0; nCount < 10; nCount++)
	{
		if (nCount % 2 == 0)
		{
			SetBlock(D3DXVECTOR3(4200.0f, (-200.0f + nCount* 100.0f), 0.0f), 100.0f, 20.0f, BLOCKTYPE_JUMP);
		}
		else if(nCount % 2 == 1)
		{
			SetBlock(D3DXVECTOR3(4000.0f, (-200.0f + nCount* 100.0f), 0.0f), 100.0f, 20.0f, BLOCKTYPE_JUMP);

		}
	}
	SetBlock(D3DXVECTOR3(100.0f, 600.0f, 0.0f), 80.0f, 20.0f, BLOCKTYPE_ELEVETOR);
	SetBlock(D3DXVECTOR3(100.0f, 600.0f, 0.0f), 300.0f, 20.0f,BLOCKTYPE_JUMP);
	
	SetBlock(D3DXVECTOR3(900.0f, 0.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_SAW);
	SetBlock(D3DXVECTOR3(900.0f, 50.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_LADDER);
	SetBlock(D3DXVECTOR3(900.0f, 100.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_LADDER);
	SetBlock(D3DXVECTOR3(900.0f, 150.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_LADDER);
	SetBlock(D3DXVECTOR3(900.0f, 200.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_LADDER);
	SetBlock(D3DXVECTOR3(900.0f, 500.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_SAW);

	SetBlock(D3DXVECTOR3(800.0f, 0.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_SAW);
	SetBlock(D3DXVECTOR3(800.0f, 50.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_LADDER);
	SetBlock(D3DXVECTOR3(800.0f, 100.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_LADDER);
	SetBlock(D3DXVECTOR3(800.0f, 150.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_LADDER);
	SetBlock(D3DXVECTOR3(800.0f, 200.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_LADDER);
	SetBlock(D3DXVECTOR3(800.0f, 250.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_SAW);

	SetBlock(D3DXVECTOR3(700.0f, 0.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_SAW);
	SetBlock(D3DXVECTOR3(700.0f, 500.0f,  0.0f), 50.0f, 50.0f, BLOCKTYPE_LADDER);
	SetBlock(D3DXVECTOR3(700.0f, 550.0f,  0.0f), 50.0f, 50.0f, BLOCKTYPE_LADDER);
	SetBlock(D3DXVECTOR3(700.0f, 600.0f,  0.0f), 50.0f, 50.0f, BLOCKTYPE_LADDER);
	SetBlock(D3DXVECTOR3(700.0f, 650.0f,  0.0f), 50.0f, 50.0f, BLOCKTYPE_LADDER);
	SetBlock(D3DXVECTOR3(700.0f, 250.0f, 0.0f), 50.0f, 50.0f, BLOCKTYPE_SAW);

	for (int nCount = 0; nCount < 50; nCount++)
	{
		SetBlock(D3DXVECTOR3((-1000.0f+ (nCount*100.0f)), 680.0f, 0.0f),100.0f, 100.0f, BLOCKTYPE_NONE);
	}
	for (int nCount = 0; nCount < 50; nCount++)
	{
		SetBlock(D3DXVECTOR3((-1000.0f + (nCount*100.0f)), -200.0f, 0.0f), 100.0f, 100.0f, BLOCKTYPE_NONE);
	}
	for (int nCount = 0; nCount < 80; nCount++)
	{
		SetBlock(D3DXVECTOR3((-1000.0f + (nCount*25.0f)), 500.0f, 0.0f), 25.0f, 25.0f, BLOCKTYPE_NONE);
	}
	for (int nCount = 0; nCount < 40; nCount++)
	{
		SetBlock(D3DXVECTOR3((300.0f + (nCount*25.0f)), 320.0f, 0.0f), 25.0f, 25.0f, BLOCKTYPE_NONE);
	}
	for (int nCount = 0; nCount < 40; nCount++)
	{
		SetBlock(D3DXVECTOR3((-300.0f + (nCount*25.0f)), 140.0f, 0.0f), 25.0f, 25.0f, BLOCKTYPE_NONE);
	}
	SetBlock(D3DXVECTOR3(-1000.0f, 1200.0f, 0.0f), 3000.0f, 20.0f, BLOCKTYPE_NONE);
	SetBlock(D3DXVECTOR3(-1000.0f, 500.0f, 0.0f), 2000.0f, 20.0f, BLOCKTYPE_NONE);
	SetBlock(D3DXVECTOR3(300.0f, 320.0f, 0.0f), 1000.0f, 20.0f, BLOCKTYPE_NONE);
	SetBlock(D3DXVECTOR3(-300.0f ,140.0f, 0.0f), 1000.0f, 20.0f, BLOCKTYPE_NONE);*/
}

//=========================================================================================================
//終了処理
//=========================================================================================================
void UninitBlock(void)
{
	//テクスチャの破棄
	for (int CntTex = 0; CntTex < MAX_TEX; CntTex++)
	{
		if (g_pTextureBlock[CntTex] != NULL)
		{
			g_pTextureBlock[CntTex]->Release();
			g_pTextureBlock[CntTex] = NULL;
		}
	}
	for (int CntBuff = 0; CntBuff < MAX_BLOCK; CntBuff++)
	{
		if (g_aBlock[CntBuff].bUse == true)
		{
			g_aBlock[CntBuff].bUse = false;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}

//=========================================================================================================
//更新処理
//=========================================================================================================
void UpdateBlock(void)
{
	Player aPlayer = *GetPlayer();
	D3DXVECTOR3 Worldpos = GetWorld();


	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_2D *pVtx;
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);



	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{

			g_aBlock[nCntBlock].posold = g_aBlock[nCntBlock].pos;
			g_aBlock[nCntBlock].pos = g_aBlock[nCntBlock].posworld + Worldpos;

			if (g_aBlock[nCntBlock].ntype == BLOCKTYPE_RIFT || g_aBlock[nCntBlock].ntype == BLOCKTYPE_ELEVETOR)
			{
				g_aBlock[nCntBlock].nCnt += g_aBlock[nCntBlock].CntMove;
				g_aBlock[nCntBlock].pos = g_aBlock[nCntBlock].posworld + Worldpos+ (g_aBlock[nCntBlock].move*g_aBlock[nCntBlock].nCnt);
				if (g_aBlock[nCntBlock].nCnt > g_aBlock[nCntBlock].nSpan)
				{
					g_aBlock[nCntBlock].CntMove = -1.0f * g_aBlock[nCntBlock].CntMove;
					//g_aBlock[nCntBlock].move = -1.0f*(g_aBlock[nCntBlock].move);
				}
				if (g_aBlock[nCntBlock].nCnt <0.0f)
				{
					g_aBlock[nCntBlock].CntMove = -1.0f * g_aBlock[nCntBlock].CntMove;
					//g_aBlock[nCntBlock].move = -1.0f*(g_aBlock[nCntBlock].move);
				}
			}

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//=========================================================================================================
//描画処理
//=========================================================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);



	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].TexNum]);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);  //右から二番目を変えないとまずい！！
		}
	}
}

//=========================================================================================================
//ブロックの設定処理
//=========================================================================================================
void SetBlock(D3DXVECTOR3 pos,float width,float height, BOLOCKTYPE type)
{

	D3DXVECTOR3 Worldpos = GetWorld();

	int nCntBlock;

	//頂点バッファをロックし頂点情報へのポインタを取得
	VERTEX_2D *pVtx;
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			g_aBlock[nCntBlock].pos = pos+ Worldpos;
			g_aBlock[nCntBlock].posworld = pos+ Worldpos;
			g_aBlock[nCntBlock].fWidth = width;
			g_aBlock[nCntBlock].fHeight = height;
			g_aBlock[nCntBlock].ntype = type;
			if (g_aBlock[nCntBlock].ntype == BLOCKTYPE_RIFT)
			{
				g_aBlock[nCntBlock].move = D3DXVECTOR3(1.2f,0.0f,0.0f);
				g_aBlock[nCntBlock].nSpan =200.0f;
			}
			else if (g_aBlock[nCntBlock].ntype == BLOCKTYPE_ELEVETOR)
			{
				g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 1.2f, 0.0f);
				g_aBlock[nCntBlock].nSpan = 200.0f;
			}

			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y+g_aBlock[nCntBlock].fHeight, 0.0f);
			if (g_aBlock[nCntBlock].ntype == BLOCKTYPE_JUMP)
			{
				pVtx[0].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.3f, 1.0f, 0.3f, 1.0f);
			}
			else if (g_aBlock[nCntBlock].ntype == BLOCKTYPE_RIFT || g_aBlock[nCntBlock].ntype == BLOCKTYPE_ELEVETOR)
			{
				pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.9f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.9f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.9f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.9f, 1.0f);
			}

			if (g_aBlock[nCntBlock].ntype == BLOCKTYPE_LADDER)
			{
				g_aBlock[nCntBlock].TexNum = 1;

			}
			else if (g_aBlock[nCntBlock].ntype == BLOCKTYPE_SAW)
			{
				g_aBlock[nCntBlock].TexNum = 2;
			}
			else if (g_aBlock[nCntBlock].ntype == BLOCKTYPE_ORI)
			{
				g_aBlock[nCntBlock].TexNum = 3;
			}
			else
			{
				g_aBlock[nCntBlock].TexNum = 0;

			}
			g_aBlock[nCntBlock].bUse = true;

			break; //←重要！！
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}


//========================================================================================
//ブロックの当たり判定
//========================================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, Block **pBlock)
{
	D3DXVECTOR3 Worldpos = GetWorld();
	Player aPlayer = *GetPlayer();
	bool bLand = false;
	float fmove = pPos->x - pPosOld->x;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{

			g_aBlock[nCntBlock].pos = g_aBlock[nCntBlock].posworld + Worldpos;

			if (g_aBlock[nCntBlock].ntype != BLOCKTYPE_LADDER && g_aBlock[nCntBlock].ntype != BLOCKTYPE_SAW)
			{//梯子、ダメージブロック以外の場合
				if (pPos->x + fWidth >= g_aBlock[nCntBlock].pos.x   && pPos->x - fWidth <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
				{

					if (pPos->y >= g_aBlock[nCntBlock].pos.y && pPosOld->y <= g_aBlock[nCntBlock].pos.y)
					{//着地判定
						if (g_aBlock[nCntBlock].ntype == BLOCKTYPE_JUMP)
						{//ジャンプ床の場合
							pPos->y = g_aBlock[nCntBlock].pos.y;
							*pBlock = &g_aBlock[nCntBlock];
							pMove->y = -15.0f;
						}
						else if (/*pBlock != NULL&&*/g_aBlock[nCntBlock].ntype == BLOCKTYPE_RIFT || g_aBlock[nCntBlock].ntype == BLOCKTYPE_ELEVETOR)
						{//移動床の場合（二種類）
							bLand = true;
							pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].move.y;
							pPos->x += g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].posold.x;
							*pBlock = &g_aBlock[nCntBlock];
							pMove->y = 0.0f;
						}
						else
						{//普通の床の場合
							bLand = true;
							pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].move.y-0.5f;
							*pBlock = &g_aBlock[nCntBlock];
							pMove->y = 0.0f;
						}

					}
					else if (pPos->y >= g_aBlock[nCntBlock].pos.y && pPosOld->y >= g_aBlock[nCntBlock].pos.y&&
						pPos->y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fWidth && pPosOld->y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fWidth)
					{//着地判定

						if (g_aBlock[nCntBlock].ntype == BLOCKTYPE_JUMP)
						{//ジャンプ床の場合
							pPos->y = g_aBlock[nCntBlock].pos.y;
							*pBlock = &g_aBlock[nCntBlock];
							pMove->y = -15.0f;
						}
						else if (/*pBlock != NULL&&*/g_aBlock[nCntBlock].ntype == BLOCKTYPE_RIFT || g_aBlock[nCntBlock].ntype == BLOCKTYPE_ELEVETOR)
						{//移動床の場合（二種類）
							bLand = true;
							pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].move.y;
							pPos->x += g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].posold.x;
							*pBlock = &g_aBlock[nCntBlock];
							pMove->y = 0.0f;
						}
						else
						{//普通の床の場合
							bLand = true;
							pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].move.y - 0.5f;
							*pBlock = &g_aBlock[nCntBlock];
							pMove->y = 0.0f;
						}
					}
					else if ((pPos->y - fHeight) <= (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight) &&
						(pPosOld->y - fHeight) >= (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight))
					{//頭判定
						pPos->y = g_aBlock[nCntBlock].pos.y + (g_aBlock[nCntBlock].fHeight + fHeight) + g_aBlock[nCntBlock].move.y;
						pMove->y = 0.0f;

					}
				}


				//横判定
				if (g_aBlock[nCntBlock].pos.y <= (pPos->y) &&
					g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight >= (pPos->y))
				{//脚だけが横に入った場合
					if ((pPos->x + fWidth) >= g_aBlock[nCntBlock].pos.x && (pPosOld->x + fWidth) < g_aBlock[nCntBlock].pos.x)
					{//左判定
						//pPos->x = g_aBlock[nCntBlock].pos.x - fWidth - 6.0f;
						pPos->x = g_aBlock[nCntBlock].pos.x - fWidth - pMove->x;
						pMove->x = 0.0f;

					}
					else if ((pPos->x - fWidth) <= (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth )&&
						(pPosOld->x - fWidth) > (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth))
					{//右判定
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + fWidth + (pMove->x*-1.0f);
						pMove->x = 0.0f;
					}

					
				}
				else if ((g_aBlock[nCntBlock].pos.y) <= (pPos->y - fHeight) &&
					(g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight) >= (pPos->y - fHeight))
				{//頭だけ入った場合
					if ((pPos->x + fWidth) >= g_aBlock[nCntBlock].pos.x && (pPosOld->x + fWidth) <= g_aBlock[nCntBlock].pos.x)
					{//左判定
						pPos->x = g_aBlock[nCntBlock].pos.x - fWidth - 3.0f;
						pMove->x = 0.0f;

					}
					else if ((pPos->x - fWidth) <= (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth) &&
						(pPosOld->x - fWidth) >= (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth))
					{//右判定
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + fWidth + (pMove->x*-1.0f);
						pMove->x = 0.0f;
					}
				}
				else if ((g_aBlock[nCntBlock].pos.y) >= (pPos->y - fHeight) &&
					(g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight) <= (pPos->y - fHeight)&&
					g_aBlock[nCntBlock].pos.y <= (pPos->y - fHeight) &&
					g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight >= (pPos->y - fHeight))
				{//両方入った場合
					if ((pPos->x + fWidth) >= g_aBlock[nCntBlock].pos.x && (pPosOld->x + fWidth) <= g_aBlock[nCntBlock].pos.x)
					{//左判定
						pPos->x = g_aBlock[nCntBlock].pos.x - fWidth - 3.0f;
						pMove->x = 0.0f;

					}
					else if ((pPos->x - fWidth) <= (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth) &&
						(pPosOld->x - fWidth) >= (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth))
					{//右判定
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + fWidth + (pMove->x*-1.0f);
						pMove->x = 0.0f;
					}
				}
				else if ((g_aBlock[nCntBlock].pos.y) <= (pPos->y) &&
					(g_aBlock[nCntBlock].pos.y) >= (pPos->y - fHeight))
				{
					if ((pPos->x + fWidth) >= g_aBlock[nCntBlock].pos.x && (pPosOld->x + fWidth) <= g_aBlock[nCntBlock].pos.x)
					{//左判定
						pPos->x = g_aBlock[nCntBlock].pos.x - fWidth - 3.0f;
						pMove->x = 0.0f;

					}
					else if ((pPos->x - fWidth) <= (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth) &&
						(pPosOld->x - fWidth) >= (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth))
					{//右判定
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + fWidth + (pMove->x*-1.0f);
						pMove->x = 0.0f;
					}
				}
				if ((g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight) <= (pPos->y) &&
					(g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight) >= (pPos->y - fHeight))
				{

					if ((pPos->x + fWidth) >= g_aBlock[nCntBlock].pos.x && (pPosOld->x + fWidth) <= g_aBlock[nCntBlock].pos.x)
					{//左判定
						pPos->x = g_aBlock[nCntBlock].pos.x - fWidth - 3.0f;
						pMove->x = 0.0f;

					}
					else if ((pPos->x - fWidth) <= (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth) &&
						(pPosOld->x - fWidth) >= (g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth))
					{//右判定
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + fWidth + (pMove->x*-1.0f);
						pMove->x = 0.0f;
					}
				}
				
				else if (pPosOld->x/* + fWidth*/ <= g_aBlock[nCntBlock].pos.x   && pPos->x + fWidth >= g_aBlock[nCntBlock].pos.x )
				{
					if (pPos->y >= g_aBlock[nCntBlock].pos.y && pPosOld->y <= g_aBlock[nCntBlock].pos.y)
					{//着地判定
						
						if (g_aBlock[nCntBlock].ntype == BLOCKTYPE_JUMP)
						{//ジャンプ床の場合
							pPos->y = g_aBlock[nCntBlock].pos.y;
							*pBlock = &g_aBlock[nCntBlock];
							pMove->y = -15.0f;
						}
						else if (/*pBlock != NULL&&*/g_aBlock[nCntBlock].ntype == BLOCKTYPE_RIFT || g_aBlock[nCntBlock].ntype == BLOCKTYPE_ELEVETOR)
						{//移動床の場合（二種類）
							bLand = true;
							pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].move.y;
							pPos->x += g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].posold.x;
							*pBlock = &g_aBlock[nCntBlock];
							pMove->y = 0.0f;
						}
						else
						{//普通の床の場合
							bLand = true;
							pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].move.y - 0.5f;
							*pBlock = &g_aBlock[nCntBlock];
							pMove->y = 0.0f;
						}
					}

						
				}


			}
			else if (/*pBlock != NULL && */g_aBlock[nCntBlock].ntype == BLOCKTYPE_SAW)
			{//ダメージブロックの場合
				float flength[3];
				flength[0] = (pPos->x - (g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth / 2.0f))) * (pPos->x - (g_aBlock[nCntBlock].pos.x + (g_aBlock[nCntBlock].fWidth / 2.0f)));
				flength[1] = (pPos->y - fHeight - g_aBlock[nCntBlock].pos.y)* (pPos->y - fHeight - g_aBlock[nCntBlock].pos.y);
				flength[2] = (fWidth + (g_aBlock[nCntBlock].fWidth / 2.0f)) * (fWidth + (g_aBlock[nCntBlock].fWidth / 2.0f));
				if (flength[0] + flength[1] <= flength[2])
				{//当たり判定
					SetType(PLAYERSTATE_DETH);
				}
			}
			else
			{//梯子の場合
				if (pPos->x >= g_aBlock[nCntBlock].pos.x - fWidth + 2.0f  &&
					pPos->x <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + fWidth - 2.0f &&
					pPos->y <= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fWidth&&
					pPos->y >= g_aBlock[nCntBlock].pos.y)
				{
					if (GetKeyboardPress(DIK_W) == true)
					{
						SetType(PLAYERSTATE_CATCH);
						//pPos->y -= 0.5f;
						pMove->y = -2.0f;
					}
					else if (GetKeyboardPress(DIK_S) == true)
					{
						SetType(PLAYERSTATE_CATCH);
						//pPos->y -= 0.5f;
						pMove->y = 2.0f;
					}
					else if (GetKeyboardPress(DIK_W) == false && GetKeyboardPress(DIK_S) == false)
					{
						//SetType(PLAYERSTATE_NORMAL);
						pMove->y = 0.0f;
					}
					//pPos->y -= 0.5f;
					else if (GetKeyboardPress(DIK_SPACE) == true)
					{
						SetType(PLAYERSTATE_NORMAL);
					}

				}

			}
		}
	}
	return bLand;
}

void DleatBlock(BOLOCKTYPE type)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{


			if (g_aBlock[nCntBlock].ntype == type)
			{//梯子、ダメージブロック以外の場合
				g_aBlock[nCntBlock].bUse = false;

			}
		}
	}
}