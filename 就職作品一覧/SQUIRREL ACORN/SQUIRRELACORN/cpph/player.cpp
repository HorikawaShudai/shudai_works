//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "player.h"
#include "game.h"
#include "input.h"
#include "block.h"
#include "Item.h"
#include "fade.h"
#include "sound.h"

//マクロ定義
#define MOVE_DATA (2.0f)  //移動量
#define GRAVITY (0.5f)

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;
Player g_Player;
D3DXVECTOR3 g_WorldPos;

int g_nPatternHeightPlayer;
int g_nCount;
float g_fLengthPlayer;
float g_fAnglePlayer;

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitPlayer(void)
{
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 1.0f);	//現在位置
	g_WorldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.posOld = g_Player.pos;						//前回位置
	g_Player.Checkpos = g_Player.pos;						//前回位置
	g_Player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);			//回転速度
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動速度
	g_Player.nCntAnim = 0;
	g_Player.nrot = 0;
	g_Player.nPatternAnim= 0;
	g_Player.bUse = false;								//生死確認
	g_Player.bJump = false;								//ジャンプ確認
	g_Player.nLifeFly = 80;								//ジャンプ確認
	g_Player.nType= PLAYERSTATE_NORMAL;					//ジャンプ確認


	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice(); 
	
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player001.png",
		&g_pTexturePlayer);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_WIDTH /*+ sinf(g_Player.rot.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer*/,
		g_Player.pos.y - PLAYER_HEIGHT /*cosf(g_Player.rot.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer*/, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_WIDTH  /*sinf(g_Player.rot.z - D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer*/,
		g_Player.pos.y - PLAYER_HEIGHT /*cosf(g_Player.rot.z - D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer*/, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_WIDTH /*+ sinf(g_Player.rot.z - g_fAnglePlayer)* g_fLengthPlayer*/,
		g_Player.pos.y /*+ cosf(g_Player.rot.z - g_fAnglePlayer) * g_fLengthPlayer*/, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_WIDTH /*sinf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer*/,
		g_Player.pos.y /*+ cosf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer*/, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//対角線の長さを算出
	g_fLengthPlayer = sqrtf((PLAYER_WIDTH  * PLAYER_WIDTH) +
		(PLAYER_HEIGHT *PLAYER_HEIGHT)) * 0.5f;

	//対角線の角度を算出
	g_fAnglePlayer = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//=========================================================================================================
//プレイヤーの終了処理
//=========================================================================================================
void UninitPlayer(void)
{
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
	
}

//=========================================================================================================
//プレイヤーの更新処理
//=========================================================================================================
void UpdatePlayer(void)
{
	g_Player.posOld = g_Player.pos;

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);


	//if (GetKeyboardPress(DIK_W) == true)
	//{//Wのみ押された場合
	//	if (GetKeyboardPress(DIK_A) == true)
	//	{//Aのみ押された場合
	//		g_Player.move.x += sinf(-D3DX_PI * 0.75f) * MOVE_DATA;
	//		g_Player.move.y += cosf(-D3DX_PI * 0.75f) * MOVE_DATA;
	//	}
	//	else if (GetKeyboardPress(DIK_D) == true)
	//	{//Aのみ押された場合
	//		g_Player.move.x += sinf(D3DX_PI * 0.75f) * MOVE_DATA;
	//		g_Player.move.y += cosf(D3DX_PI * 0.75f) * MOVE_DATA;
	//	}
	//	else
	//	{
	//		g_Player.move.y -= /*cosf(D3DX_PI *0.001f)**/MOVE_DATA;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_S) == true)
	//{//Sのみ押された場合
	//	if (GetKeyboardPress(DIK_A) == true)
	//	{//Dのみ押された場合
	//		g_Player.move.x += sinf(-D3DX_PI * 0.25f) * MOVE_DATA;
	//		g_Player.move.y += cosf(-D3DX_PI * 0.25f) * MOVE_DATA;
	//
	//	}
	//	else if (GetKeyboardPress(DIK_D) == true)
	//	{//Dのみ押された場合
	//		g_Player.move.x += sinf(D3DX_PI * 0.25f) * MOVE_DATA;
	//		g_Player.move.y += cosf(D3DX_PI * 0.25f) * MOVE_DATA;
	//
	//	}
	//	else
	//	{
	//		g_Player.move.y += /*cosf(D3DX_PI *0.001f)**/MOVE_DATA;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_A) == true)
	//{//Aのみ押された場合
	//
	//	g_Player.move.x -= /*sinf(D3DX_PI *0.09f)**/MOVE_DATA;
	//}
	//else if (GetKeyboardPress(DIK_D) == true)
	//{//Dのみ押された場合
	//
	//	g_Player.move.x += /*sinf(D3DX_PI *0.09f)**/MOVE_DATA;
	//
	//}

	//if (GetKeyboardPress(DIK_RIGHT) == true)
	//{//右キーのみ押された場合
	//	g_Player.rot.z -= 0.9f /**D3DX_PI*/;
	//}
	//else if (GetKeyboardPress(DIK_LEFT) == true)
	//{//左キーのみ押された場合
	//	g_Player.rot.z += 0.9f /**D3DX_PI*/;
	//}
	//if (GetKeyboardPress(DIK_UP) == true)
	//{//上キーのみ押された場合
	//	g_Player.size.z += 0.02f;
	//}
	//if (GetKeyboardPress(DIK_DOWN) == true)
	//{//下キーのみ押された場合
	//	g_Player.size.z -= 0.02f;
	//}

	if (GetKeyboardTrigger(DIK_R) == true)
	{
		g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動速度
		g_WorldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//g_Player.Checkpos = D3DXVECTOR3(200.0f, 650.0f, 1.0f);
		g_Player.pos = g_Player.Checkpos;
		//g_Player.pos.y -= g_WorldPos.y;
		g_Player.posOld = g_Player.pos;
		g_Player.nrot = 0;
		pVtx[0].tex.x = 0.0f;
		pVtx[1].tex.x = 0.25f;
		pVtx[2].tex.x = 0.0f;
		pVtx[3].tex.x = 0.25f;
		SetType(PLAYERSTATE_NORMAL);
		g_Player.bUse = true;
	}

	if (g_Player.bUse == true)
	{
		//移動操作
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_Player.nrot = 1;
			if (g_Player.bJump == true)
			{
				g_Player.move.x = -4.00f;

			}
			else
			{
				g_Player.move.x = -5.00f;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			g_Player.nrot = 0;
			if (g_Player.bJump == true)
			{
				g_Player.move.x = 4.00f;

			}
			else
			{
				g_Player.move.x = 5.00f;
			}
		}
		if (GetKeyboardPress(DIK_A) == false && GetKeyboardPress(DIK_D) == false)
		{
			g_Player.move.x = 0.0f;
		}

		//ジャンプ操作

		if (GetKeyboardTrigger(DIK_SPACE) == true && g_Player.bJump == false)
		{
			if (g_Player.bJump == false)
			{
				SetType(PLAYERSTATE_NORMAL);
				g_Player.bJump = true;
				g_Player.move.y -= 13.0f;
				PlaySound(SOUND_LABEL_SE_JUMP);
			}
		}
		if (GetKeyboardPress(DIK_LSHIFT) == true || GetKeyboardPress(DIK_RSHIFT) == true && g_Player.bJump == true)
		{
			g_Player.nLifeFly--;
			if (g_Player.nLifeFly > 0)
			{
				g_Player.move.y = +0.2f;
			}

		}
		//アニメーション
		if (GetKeyboardPress(DIK_A) == false && GetKeyboardPress(DIK_D) == false)
		{
			pVtx[0].tex.x = 0.0f;
			pVtx[1].tex.x = 0.25f;
			pVtx[2].tex.x = 0.0f;
			pVtx[3].tex.x = 0.25f;
		}
		else if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_D) == true)
		{
			g_Player.nCntAnim++;
			if (g_Player.nCntAnim % 5 == 0)
			{
				g_Player.nPatternAnim++;

				pVtx[0].tex = D3DXVECTOR2(0.0f + ((g_Player.nPatternAnim % 4)*0.25f), 0.0f + (0.5f*g_Player.nrot));
				pVtx[1].tex = D3DXVECTOR2(0.25f + ((g_Player.nPatternAnim % 4)*0.25f), 0.0f + (0.5f*g_Player.nrot));
				pVtx[2].tex = D3DXVECTOR2(0.0f + ((g_Player.nPatternAnim % 4)*0.25f), 0.5f + (0.5f*g_Player.nrot));
				pVtx[3].tex = D3DXVECTOR2(0.25f + ((g_Player.nPatternAnim % 4)*0.25f), 0.5f + (0.5f*g_Player.nrot));
			}
		}

		if (g_Player.pBlock != NULL)
		{
			if (g_Player.pBlock->ntype != BLOCKTYPE_LADDER)
			{
				g_Player.nType = PLAYERSTATE_NORMAL;
				if (g_Player.pBlock->ntype == BLOCKTYPE_RIFT)
				{
					g_Player.pos.x += g_Player.pBlock->pos.x - g_Player.pBlock->posold.x;
				}
				else if (g_Player.pBlock->ntype == BLOCKTYPE_ELEVETOR)
				{
					g_Player.pos.y += g_Player.pBlock->pos.y - g_Player.pBlock->posold.y;

				}
			}
		}



		//g_Player.rot.z += (0.0f - g_Player.rot.z)*0.05f;
		//g_Player.move.x += (0.0f - g_Player.move.x)*0.5f;
		if (g_Player.nType != PLAYERSTATE_CATCH)
		{
			g_Player.move.y += GRAVITY;
		}
		//g_fLengthPlayer += (0.0f - g_fLengthPlayer)*0.005f;

		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;
		//g_fLengthPlayer += g_fsizePlayer.z;

		


		if (CollisionBlock(&g_Player.pos, &g_Player.posOld, &g_Player.move, PLAYER_WIDTH -6.0f, PLAYER_HEIGHT, &g_Player.pBlock) == true)
		{
			g_Player.bJump = false;
			g_Player.nLifeFly = 80;
		}
		else
		{
			g_Player.bJump = true;
			g_Player.pBlock = NULL;
		}
		ScloolWorld();
		if (g_Player.nType != PLAYERSTATE_DETH && g_Player.pBlock == NULL)
		{
			SetType(PLAYERSTATE_NORMAL);
		}
		if (CollisionItem(g_Player.pos, PLAYER_WIDTH - 12.0f, PLAYER_HEIGHT) == true)
		{
			FADE aFade = GetFade();
			if (aFade == FADE_NONE)
			{
				SetFade(MODE_RESULT, 0.01f);
			}
		}


		if (g_Player.pos.y - g_WorldPos.y >= WORLD_HEIGHT)
		{
			SetType(PLAYERSTATE_DETH);
		}



		//テクスチャ座標の設定
		//pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer,
		//	g_Player.pos.y - PLAYER_HEIGHT/*cosf(g_Player.rot.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer*/, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.z - D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer,
		//	g_Player.pos.y - PLAYER_HEIGHT/*cosf(g_Player.rot.z - D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer*/, 0.0f);
		//pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.z - g_fAnglePlayer) * g_fLengthPlayer,
		//	g_Player.pos.y /*+ cosf(g_Player.rot.z - g_fAnglePlayer) * g_fLengthPlayer*/, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer,
		//	g_Player.pos.y/* + cosf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer*/, 0.0f);

		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_WIDTH /*+ sinf(g_Player.rot.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer*/,
			g_Player.pos.y - PLAYER_HEIGHT /*cosf(g_Player.rot.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer*/, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_WIDTH  /*sinf(g_Player.rot.z - D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer*/,
			g_Player.pos.y - PLAYER_HEIGHT /*cosf(g_Player.rot.z - D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer*/, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_WIDTH /*+ sinf(g_Player.rot.z - g_fAnglePlayer)* g_fLengthPlayer*/,
			g_Player.pos.y /*+ cosf(g_Player.rot.z - g_fAnglePlayer) * g_fLengthPlayer*/, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_WIDTH /*sinf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer*/,
			g_Player.pos.y /*+ cosf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer*/, 0.0f);

		//if (g_Player.pos.x <= PLAYER_WIDTH / 2)
		//{
		//	g_Player.pos.x = PLAYER_WIDTH / 2;
		//}
		//if (g_Player.pos.x >= SCREEN_WIDTH - (PLAYER_WIDTH / 2))
		//{
		//	g_Player.pos.x = SCREEN_WIDTH - PLAYER_WIDTH / 2;
		//}
		//if (g_Player.pos.y < PLAYER_HEIGHT / 2)
		//{
		//	g_Player.pos.y = PLAYER_HEIGHT / 2;
		//}
		//if (g_Player.pos.y >= SCREEN_HEIGHT - (PLAYER_HEIGHT / 2))
		//{
		//	g_Player.pos.y = SCREEN_HEIGHT - (PLAYER_HEIGHT / 2);
		//}

	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();





#if 0
	g_nCounterAnimPlayer++;
	if ((g_nCounterAnimPlayer % 5) == 0)
	{
		g_nPatternAnimPlayer = (g_nPatternAnimPlayer + 1) % 10;
	}
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (g_nPatternAnimPlayer % 5)*0.2f,
		0.0f + (g_nPatternAnimPlayer / 5)*0.5f);
	pVtx[1].tex = D3DXVECTOR2(0.2f + (g_nPatternAnimPlayer % 5)*0.2f,
		0.0f + (g_nPatternAnimPlayer / 5)*0.5f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (g_nPatternAnimPlayer % 5)*0.2f,
		0.5f + (g_nPatternAnimPlayer / 5)*0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.2f + (g_nPatternAnimPlayer % 5)*0.2f,
		0.5f + (g_nPatternAnimPlayer / 5)*0.5f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
#endif
}

//=========================================================================================================
//プレイヤーの描画処理
//=========================================================================================================
void DrawPlayer(void)
{
	if (g_Player.bUse == true)
	{
		LPDIRECT3DDEVICE9 pDevice;
		//デバイスの取得
		pDevice = GetDevice();

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		pDevice->SetFVF(FVF_VERTEX_2D);


		pDevice->SetTexture(0, g_pTexturePlayer);

		//ポリゴン
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=========================================================================================================
//プレイヤー情報の取得処理
//=========================================================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}

void SetType(PLAYERSTATE ntype)
{
	g_Player.nType = ntype;

	switch (g_Player.nType)
	{
	case PLAYERSTATE_NORMAL:
		g_Player.bUse = true;
		break;
	case PLAYERSTATE_CATCH:
		//g_Player.bUse = true;
		break;
	case PLAYERSTATE_DETH:
		PlaySound(SOUND_LABEL_SE_DEAD);
		g_Player.move = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_Player.bUse = false;
		break;
	}
}

//========================================================================================================
//攻撃がヒットしてしまったとき
//========================================================================================================
void ScloolWorld(void)
{
	if (g_Player.pos.x > 920.0f )
	{
		g_Player.pos.x = 920.0f;

		g_WorldPos.x -= g_Player.move.x;
		if (g_Player.pBlock != NULL)
		{
			g_WorldPos.x -= g_Player.pBlock->move.x;
		}

	}
	else if (g_Player.pos.x < 360.0f)
	{
		g_Player.pos.x = 360.0f;

		g_WorldPos.x -= g_Player.move.x;
		if (g_Player.pBlock != NULL)
		{
			g_WorldPos.x -= g_Player.pBlock->move.x;
		}

	}
	if (g_Player.pos.y >  500.0f)
	{
		g_Player.pos.y = 500.0f;

		g_WorldPos.y -= g_Player.move.y;

	}
	else if (g_Player.pos.y < 220.0f)
	{
		g_Player.pos.y = 220.0f;

		g_WorldPos.y -= g_Player.move.y;
		if (g_Player.pBlock != NULL)
		{
			g_WorldPos.y -= g_Player.pBlock->move.y;
		}

	}
}

D3DXVECTOR3 GetWorld(void)
{
	return g_WorldPos;
}

void SetPlayer(float posx, float posy)
{
	if (g_Player.bUse == false)
	{
		g_WorldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Player.pos.x = posx;
		g_Player.pos.y = posy;
		if (g_Player.pos.x > 920.0f)
		{
			g_WorldPos.x +=posx-920.0f;

			g_Player.pos.x = 920.0f;
		}
		else if (g_Player.pos.x < 360.0f)
		{
			g_WorldPos.x += posx+300.0f-360.0f;

			g_Player.pos.x = 360.0f;
		}
		if (g_Player.pos.y >  500.0f)
		{
			g_WorldPos.y -= posy-100.0f - 500.0f;
			g_Player.pos.y = 500.0f;


		}
		else if (g_Player.pos.y < 220.0f)
		{
			g_WorldPos.y -= posy - 220.0f;
			g_Player.pos.y = 220.0f;

		}
		
		g_Player.posOld = g_Player.pos;						//前回位置
		g_Player.Checkpos = g_Player.pos;						//前回位置
		g_Player.nCntAnim = 0;
		g_Player.nrot = 0;
		g_Player.nPatternAnim = 0;
		g_Player.bUse = true;								//生死確認
		g_Player.bJump = false;								//ジャンプ確認
		g_Player.nLifeFly = 80;								//ジャンプ確認
		g_Player.nType = PLAYERSTATE_NORMAL;					//ジャンプ確認
	}
}
void SetPos(D3DXVECTOR3 pos)
{
	g_WorldPos = pos;
}