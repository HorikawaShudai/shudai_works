//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "game.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "explosion.h"
#include "fade.h"
#include "effect.h"
#include "PowerupUI.h"
#include "edit_mode.h"


//マクロ定義
#define MOVE_DATA (2.0f)  //移動量

//グローバル変数宣言
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;
Player g_Player;
int g_nCounterAnimPlayer;
int g_nPatternAnimPlayer;
int g_nPatternHeightPlayer;
int g_nCount;
float g_fLengthPlayer;
float g_fAnglePlayer;
int g_shotcnt;

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitPlayer(void)
{
	g_nCounterAnimPlayer = 0;
	g_nPatternAnimPlayer = 0;
	g_Player.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);			//回転速度
	g_Player.pos = D3DXVECTOR3(100.0f, 360.0f, 100.0f);	//位置
	g_Player.move= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動速度
	g_Player.size= D3DXVECTOR3(0.0f, 0.0f, 0.0f);       //拡大縮小
	g_Player.life= 5;									//体力
	g_Player.bUse = true;								//生死確認
	g_Player.nPoint = 0;								//初期ポイント数
	g_shotcnt = 0;
	for (int nCount = 0; nCount < 4; nCount++)
	{
		g_Player.Attackpt[nCount] = 0;								//初期ポイント数
		g_Player.EditNum[nCount] = *GetNumEdMd(nCount);
	}


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
		"data\\TEXTURE\\player.png",
		&g_pTexturePlayer);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer,
		g_Player.pos.y + cosf(g_Player.rot.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.z - D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer,
		g_Player.pos.y + cosf(g_Player.rot.z - D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.z - g_fAnglePlayer)* g_fLengthPlayer,
		g_Player.pos.y + cosf(g_Player.rot.z - g_fAnglePlayer) * g_fLengthPlayer, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer,
		g_Player.pos.y + cosf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer, 0.0f);

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
void UpdataPlayer(void)
{
	VERTEX_2D *pVtx;


	if (GetKeyboardPress(DIK_W) == true)
	{//Wのみ押された場合
		if (GetKeyboardPress(DIK_A) == true)
		{//Aのみ押された場合
			g_Player.move.x += sinf(-D3DX_PI * 0.75f) * MOVE_DATA;
			g_Player.move.y += cosf(-D3DX_PI * 0.75f) * MOVE_DATA;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Aのみ押された場合
			g_Player.move.x += sinf(D3DX_PI * 0.75f) * MOVE_DATA;
			g_Player.move.y += cosf(D3DX_PI * 0.75f) * MOVE_DATA;
		}
		else
		{
			g_Player.move.y -= /*cosf(D3DX_PI *0.001f)**/MOVE_DATA;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//Sのみ押された場合
		if (GetKeyboardPress(DIK_A) == true)
		{//Dのみ押された場合
			g_Player.move.x += sinf(-D3DX_PI * 0.25f) * MOVE_DATA;
			g_Player.move.y += cosf(-D3DX_PI * 0.25f) * MOVE_DATA;

		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Dのみ押された場合
			g_Player.move.x += sinf(D3DX_PI * 0.25f) * MOVE_DATA;
			g_Player.move.y += cosf(D3DX_PI * 0.25f) * MOVE_DATA;

		}
		else
		{
			g_Player.move.y += /*cosf(D3DX_PI *0.001f)**/MOVE_DATA;
		}
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{//Aのみ押された場合
	 /*if (GetKeyboardPress(DIK_W) == true)
	 {
	 g_Player.move.x -= sinf(D3DX_PI *0.25f)*MOVE_DATA;
	 g_Player.move.y -= cosf(D3DX_PI *0.25f)*MOVE_DATA;


	 }
	 else if (GetKeyboardPress(DIK_S) == true)
	 {
	 g_Player.move.x -= sinf(D3DX_PI *0.25f)*MOVE_DATA;
	 g_Player.move.y += cosf(D3DX_PI *0.25f)*MOVE_DATA;

	 }
	 else
	 {
	 g_Player.move.x -= sinf(D3DX_PI *0.09f)*MOVE_DATA;
	 }*/
		g_Player.move.x -= /*sinf(D3DX_PI *0.09f)**/MOVE_DATA;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//Dのみ押された場合
	 /*if (GetKeyboardPress(DIK_S) == true)
	 {
	 g_Player.move.x += sinf(D3DX_PI *0.25f)*MOVE_DATA;
	 g_Player.move.y += cosf(D3DX_PI *0.25f)*MOVE_DATA;

	 }
	 else if (GetKeyboardPress(DIK_W) == true)
	 {
	 g_Player.move.x += sinf(D3DX_PI *0.25f)*MOVE_DATA;
	 g_Player.move.y -= cosf(D3DX_PI *0.25f)*MOVE_DATA;

	 }
	 else
	 {
	 g_Player.move.x += sinf(D3DX_PI *0.09f)*MOVE_DATA;
	 }*/
		g_Player.move.x += /*sinf(D3DX_PI *0.09f)**/MOVE_DATA;

	}

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


	//攻撃手段
	if (GetKeyboardTrigger(DIK_SPACE) == true && g_Player.state == PLAYERSTATE_NORMAL)
	{//spaceのみ押された場合
		PlaySound(SOUND_LABEL_SE_SHOT);
		SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, 1.0f), D3DXVECTOR3(8.5f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f));
     }
	if (g_Player.state == PLAYERSTATE_NORMAL)
	{
		g_shotcnt++;
		if (g_shotcnt % 60 == 0)
		{
			if (g_Player.Attackpt[1] > 0 || g_Player.Attackpt[2] > 0)
			{
				if (g_Player.EditNum[PWUP_NUM2] == g_Player.EditNum[PWUP_NUM3])
				{
					if (g_Player.EditNum[PWUP_NUM2] == SHOT_NUM2)
					{//攻撃パターンの二つとも右上攻撃だった場合
						for (int Shot = 0; Shot < (g_Player.Attackpt[1] + g_Player.Attackpt[2]); Shot++)
						{
							SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, 1.0f), D3DXVECTOR3(3.0f - (Shot*0.1f), -3.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f));
						}
					}
					else if (g_Player.EditNum[PWUP_NUM2] == SHOT_NUM3)
					{//攻撃パターンの二つとも右下攻撃だった場合
						for (int Shot = 0; Shot < (g_Player.Attackpt[1] + g_Player.Attackpt[2]); Shot++)
						{
							SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, 1.0f), D3DXVECTOR3(3.0f - (Shot*0.1f), 3.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f));
						}
					}
				}
				else
				{
					if (g_Player.EditNum[PWUP_NUM2] == SHOT_NUM2)
					{//攻撃パターンNo,2が右上攻撃だった場合
						for (int Shot = 0; Shot < g_Player.Attackpt[1]; Shot++)
						{
							SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, 1.0f), D3DXVECTOR3(3.0f - (Shot*0.5f), -3.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f));
						}
					}
					else if (g_Player.EditNum[PWUP_NUM2] == SHOT_NUM3)
					{//攻撃パターンNo,2が右下攻撃だった場合
						for (int Shot = 0; Shot < g_Player.Attackpt[1]; Shot++)
						{
							SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, 1.0f), D3DXVECTOR3(3.0f - (Shot*0.5f), +3.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f));
						}
					}
					if (g_Player.EditNum[PWUP_NUM3] == SHOT_NUM2)
					{//攻撃パターンNo,3が右上攻撃だった場合
						for (int Shot = 0; Shot < g_Player.Attackpt[2]; Shot++)
						{
							SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, 1.0f), D3DXVECTOR3(3.0f - (Shot*0.5f), -3.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f));
						}
					}
					else if (g_Player.EditNum[PWUP_NUM3] == SHOT_NUM3)
					{//攻撃パターンNo,3が右下攻撃だった場合
						for (int Shot = 0; Shot < g_Player.Attackpt[2]; Shot++)
						{
							SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, 1.0f), D3DXVECTOR3(3.0f - (Shot*0.5f), +3.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f));
						}
					}
				}
			}
		}
	}


#if 0
		if (GetKeyboardPress(DIK_SPACE) == true && GetKeyboardPress(DIK_LSHIFT) == true && g_Player.state == PLAYERSTATE_NORMAL)
		{//shiftとspaceのみ押された場合
			SetBullet(g_Player.pos, D3DXVECTOR3(8.5f, 0.0f, 0.0f), BULLETTYPE_PLAYER, D3DXCOLOR(0.6f, 0.6f, 1.0f, 1.0f));
		}
#endif

		//強化内容
		if (GetKeyboardPress(DIK_B) == true)
		{
			switch(g_Player.nPoint)
			{ 
			case 1:
				g_Player.Attackpt[0] += 1;
				break;
			case 2:
				g_Player.Attackpt[1] += 1;
				break;
			case 3:
				g_Player.Attackpt[2] += 1;
				break;
			case 4:
				g_Player.Attackpt[3] += 1;
				g_Player.life += 1;
				g_Player.Attackpt[3] = 0;
				break;
			}
			g_Player.nPoint = 0;
		}


		//頂点バッファをロックし頂点情報へのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
		g_Player.pos.x += g_Player.move.x;
		g_Player.pos.y += g_Player.move.y;
		//g_fLengthPlayer += g_fsizePlayer.z;

		g_Player.rot.z += (0.0f - g_Player.rot.z)*0.05f;
		g_Player.move.x += (0.0f - g_Player.move.x)*0.5f;
		g_Player.move.y += (0.0f - g_Player.move.y)*0.5f;
		//g_fLengthPlayer += (0.0f - g_fLengthPlayer)*0.005f;

		//テクスチャ座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer,
			g_Player.pos.y + cosf(g_Player.rot.z - D3DX_PI + g_fAnglePlayer) * g_fLengthPlayer, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.z - D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer,
			g_Player.pos.y + cosf(g_Player.rot.z - D3DX_PI - g_fAnglePlayer) * g_fLengthPlayer, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.z - g_fAnglePlayer) * g_fLengthPlayer,
			g_Player.pos.y + cosf(g_Player.rot.z - g_fAnglePlayer) * g_fLengthPlayer, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + sinf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer,
			g_Player.pos.y + cosf(g_Player.rot.z + g_fAnglePlayer) * g_fLengthPlayer, 0.0f);

		if (g_Player.pos.x <= PLAYER_WIDTH / 2)
		{
			g_Player.pos.x = PLAYER_WIDTH / 2;
		}

		if (g_Player.pos.x >= SCREEN_WIDTH - (PLAYER_WIDTH / 2))
		{
			g_Player.pos.x = SCREEN_WIDTH - PLAYER_WIDTH / 2;
		}

		if (g_Player.pos.y < PLAYER_HEIGHT / 2)
		{
			g_Player.pos.y = PLAYER_HEIGHT / 2;
		}
		if (g_Player.pos.y >= SCREEN_HEIGHT - (PLAYER_HEIGHT / 2))
		{
			g_Player.pos.y = SCREEN_HEIGHT - (PLAYER_HEIGHT / 2);
		}

		//自機遷移表現
		switch (g_Player.state)
		{
		case PLAYERSTATE_NORMAL:
			break;
		case PLAYERSTATE_DAMAGE:
			g_Player.nCounterstate--;
			if (g_Player.nCounterstate <= 0)
			{
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				g_Player.state = PLAYERSTATE_NORMAL;
			}
			else
			{
				if (g_Player.nCounterstate % 2== 0)
				{
					g_nCount++;
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
					if (g_nCount ==7)
					{
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						g_nCount = 0;
					}
				}
			}
			break;
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

//=========================================================================================================
//敵の状態遷移処理
//=========================================================================================================
void HitPlayer(int nDamage)
{
	//int StopCount;
	VERTEX_2D *pVtx;
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	g_Player.life -= nDamage;
	g_Player.nPoint = 0;
	g_Player.Attackpt[4] = (0,0,0,0);
	ResetUI();
	if (g_Player.life <= 0)
	{
		SetExplosion(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y, 0.0f)
			, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_Player.bUse = false;
		FADE fFade = GetFade();
		if (fFade == FADE_NONE)
		{
			SetGameMode(GAMEMODE_GAMEOVER);
		}
	}
	else
	{
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCounterstate = 120;
		PlaySound(SOUND_LABEL_SE_HIT);

	}
	g_pVtxBuffPlayer->Unlock();

}
//=========================================================================================================
//アイテムの取得処理
//=========================================================================================================
void GetItem(int Point)
{
	//int StopCount;
	VERTEX_2D *pVtx;
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	g_Player.nPoint += Point;
	if (g_Player.nPoint >= 5)
	{
		g_Player.nPoint = 4;
	}

	g_pVtxBuffPlayer->Unlock();

}