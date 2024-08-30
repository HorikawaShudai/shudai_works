//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Player.h"
#include "Camera.h"
#include "Shadow.h"
#include "Bullet.h"
#include "Object.h"
#include "MeshWall.h"
#include "Item.h"
#include "Fade.h"
#include "Game.h"
#include "Sound.h"
#include "Enemy.h"
#include "ModelBullet.h"
#include "effect.h"

#define MODEL_NAME "data\\MODEL\\Player.x"
#define MODEL_NAMEEND "data\\MODEL\\Player_end.x"
#define MODEL_NAMECLEAR "data\\MODEL\\Player_Clear.x"
#define MOVE_SPEED (0.7f)
#define GRAVITY (1.8f)
#define ENAGY (3)
#define MAX_MAT (256) 
#define MAX_LIFE (10)

//グローバル変数宣言
LPD3DXMESH g_pMeshPlayer = NULL;
LPD3DXBUFFER g_pBuffMatPlayer = NULL;
DWORD g_dwNumMatPlayer = 0;
PLAYER g_Player;
LPDIRECT3DTEXTURE9 g_apTEXturePlayer[MAX_MAT] = {};

void PlayerMod(void);
void PlayerEnemy(void);
//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitPlayer(void)
{

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_Player.pos = D3DXVECTOR3(-1650.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.moveP = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nIdxShadow = -1;
	g_Player.VtxMaxPlayer = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_Player.VtxMinPlayer = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_Player.aModel[5] = {};
	g_Player.col[MAX_MAT] = {};
	g_Player.nLife = 10;
	g_Player.nEnagy = ENAGY;
	g_Player.EngCnt = 0;
	g_Player.CameraLock = false;


	//Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL* pMat;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		g_Player.col[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTEXturePlayer[nCntMat]);
		}
	}


	int nNumVtx;
	DWORD dwSizeFVF;
	BYTE* pVtxBuff;

	//頂点数の取得
	nNumVtx = g_pMeshPlayer->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer->GetFVF());

	//頂点バッファをロック
	g_pMeshPlayer->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (vtx.x > g_Player.VtxMaxPlayer.x)
		{
			g_Player.VtxMaxPlayer.x = vtx.x;
		}
		if (vtx.z > g_Player.VtxMaxPlayer.z)
		{
			g_Player.VtxMaxPlayer.z = vtx.z;
		}
		if (vtx.x < g_Player.VtxMinPlayer.x)
		{
			g_Player.VtxMinPlayer.x = vtx.x;
		}

		if (vtx.z < g_Player.VtxMinPlayer.z)
		{
			g_Player.VtxMinPlayer.z = vtx.z;
		}
		if (vtx.y > g_Player.VtxMaxPlayer.y)
		{
			g_Player.VtxMaxPlayer.y = vtx.y;
		}
		if (vtx.y < g_Player.VtxMinPlayer.y)
		{
			g_Player.VtxMinPlayer.y = vtx.y;
		}
		pVtxBuff += dwSizeFVF;
	}
	g_Player.nIdxShadow = SetShadow(15.0f, g_Player.pos);

	g_Player.bUse = true;
}

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitEndPlayer(void)
{

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_Player.pos = D3DXVECTOR3(-1650.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.moveP = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nIdxShadow = -1;
	g_Player.aModel[5] = {};
	g_Player.nLife = 1;


	//Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAMEEND,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL* pMat;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		g_Player.col[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTEXturePlayer[nCntMat]);
		}
	}
	g_Player.nIdxShadow = SetShadow(15.0f, g_Player.pos);

	g_Player.bUse = true;
}

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitClearPlayer(void)
{

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_Player.pos = D3DXVECTOR3(-1650.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.moveP = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nIdxShadow = -1;
	g_Player.aModel[5] = {};
	g_Player.nLife = 1;


	//Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAMECLEAR,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL* pMat;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		g_Player.col[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTEXturePlayer[nCntMat]);
		}
	}
	g_Player.nIdxShadow = SetShadow(15.0f, g_Player.pos);

	g_Player.bUse = true;
}



//=========================================================================================================
//プレイヤーの終了処理
//=========================================================================================================
void UninitPlayer(void)
{
	for (int nCntMat = 0; nCntMat < MAX_MAT; nCntMat++)
	{
		if (g_apTEXturePlayer[nCntMat] != NULL)
		{
			g_apTEXturePlayer[nCntMat]->Release();
			g_apTEXturePlayer[nCntMat] = NULL;
		}
	}
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
	StopSound();
}

//=========================================================================================================
//プレイヤーの更新処理
//=========================================================================================================
void UpdatePlayer(void)
{
	Camera aCamera = GetCamera();
	g_Player.posOld = g_Player.pos;

	MODE aMode = GetMode();
	if (aMode == MODE_TUTORIAL)
	{
		if (GetKeyboardPress(DIK_8) == true)
		{
			g_Player.nLife = 10;
			g_Player.bUse = true;
		}
	}

	if (g_Player.bUse == true)
	{

		//移動操作
		PlayerMove();

		//ダッシュ操作
		PlayerEnagy();
		if (g_Player.CameraLock == true)
		{
			EnemyLockOn();
		}
		{//攻撃操作
			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{
				PlaySound(SOUND_LABEL_SE_SHOT);
				SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 40.0f, g_Player.pos.z - (cosf(g_Player.rot.y) * 10.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.5f), g_Player.rot, BULLETTYPE_PLAYER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
		if (GetKeyboardTrigger(DIK_I) == true)
		{
			switch (g_Player.CameraLock)
			{
			case true:
				SetHoming(false);
				g_Player.CameraLock = false;
				break;
			case false:
				SetHoming(true);
				g_Player.CameraLock = true;
				break;
			}
		}

		//プレイヤーの向き補正
		{
			{
				g_Player.Diffrot.y = g_Player.Destrot.y - g_Player.rot.y;

				if (g_Player.Diffrot.y > D3DX_PI)
				{
					g_Player.Diffrot.y -= D3DX_PI * 2;
				}
				else if (g_Player.Diffrot.y < -D3DX_PI)
				{
					g_Player.Diffrot.y += D3DX_PI * 2;

				}

				g_Player.rot.y += (g_Player.Diffrot.y) * 0.1f;

				if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y -= D3DX_PI * 2;
				}
				else if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y += D3DX_PI * 2;
				}
			}
		}

		//位置更新
		{
			g_Player.moveP.y -= GRAVITY;
			g_Player.moveP *= 0.9f;
			g_Player.pos += g_Player.moveP;
			if (g_Player.pos.y < 0.0f)
			{
				g_Player.pos.y = 0.0f;
				g_Player.moveP.y = 0.0f;
			}
		}

		if (g_Player.nLife < 10)
		{
			//アイテムの当たり判定
			ColissionItem(g_Player.pos, g_Player.posOld, g_Player.moveP);
		}
		//オブジェクトとの当たり判定
		PlayerObject();

		//壁との当たり判定
		PlayerWall();

		PlayerMod();
		PlayerEnemy();

		//プレイヤーの遷移状態
		PlayerState();

		SetPositionShadow(g_Player.nIdxShadow, D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z));
	}
}

//=========================================================================================================
//プレイヤーの描画処理
//=========================================================================================================
void DrawPlayer(void)
{
	if (g_Player.bUse == true)
	{
		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
		D3DMATERIAL9 matDef;
		D3DXMATERIAL* pMat;

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.mtxWorldPlayer);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
		D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
		D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorldPlayer);

		//現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);
		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
		{
			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_apTEXturePlayer[nCntMat]);

			//プレイヤー（パーツ）の描画
			g_pMeshPlayer->DrawSubset(nCntMat);
		}
		pDevice->SetMaterial(&matDef);
	}
}

//=========================================================================================================
//プレイヤーの弾の当たり判定
//=========================================================================================================
bool ColissionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 pMove)
{
	bool bHit = false;
	D3DXVECTOR3 RPos;
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecTopos;
	D3DXVECTOR3 vecmove;
	RPos = pos;
	vecmove = pos - posOld;




	if (g_Player.bUse == true)
	{
		{//交点処理
		 //vecLine.x = g_Player.VtxMaxPlayer.x - g_Player.VtxMinPlayer.x;
		 //vecLine.z = g_Player.VtxMaxPlayer.z - g_Player.VtxMaxPlayer.z;
		 //vecTopos = pos - D3DXVECTOR3(g_Player.VtxMinPlayer.x, 0.0f, g_Player.VtxMaxPlayer.z);


		 //Playerpos[0] = (vecTopos.z*vecmove.x) - (vecTopos.x*vecmove.z);
		 //Playerpos[1] = (vecLine.z*vecmove.x) - (vecLine.x*vecmove.z);
		 //Playerpos[2] = Playerpos[0] / Playerpos[1];
		 //if (Playerpos[2] >= 0.0f&&Playerpos[2] <= 1.0f)
		 //{
		 //	RPos = D3DXVECTOR3(0.0f, 300.0f, 500.0f);
		 //}
		}

		if (pos.x >= (g_Player.pos.x + g_Player.VtxMinPlayer.x) && pos.z <= (g_Player.pos.z + g_Player.VtxMaxPlayer.z) &&
			pos.x <= (g_Player.pos.x + g_Player.VtxMaxPlayer.x) && pos.z >= (g_Player.pos.z + g_Player.VtxMinPlayer.z) &&
			pos.y <= (g_Player.pos.y + g_Player.VtxMaxPlayer.y) && pos.y >= (g_Player.pos.y + g_Player.VtxMinPlayer.y))
		{
			HitPlayer(1);
			bHit = true;
		}
	}

	return bHit;
}

//=========================================================================================================
//プレイヤーのヒット処理
//=========================================================================================================
void HitPlayer(int nDamage)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (g_Player.state != PLAYERSTATE_DUSH)
	{

		if (g_Player.state == PLAYERSTATE_NORMAL)
		{
			PlaySound(SOUND_LABEL_SE_HIT);
			g_Player.nLife -= nDamage;
		}
		if (g_Player.nLife < 1)
		{
			g_Player.bUse = false;
			FADE fFade = GetFade();
			if (g_Player.nLife <= 0 && fFade == FADE_NONE)
			{
				MODE aMode = GetMode();
				if (aMode == MODE_GAME)
				{
					SetGamemode(GAMEMODE_GAMEOVER);
					//PlaySound(SOUND_LABEL_SE_DECISION);
					SetFade(MODE_RESULT, 0.05f);
				}
			}
		}
		else
		{

			if (g_Player.state == PLAYERSTATE_NORMAL)
			{
				g_Player.state = PLAYERSTATE_DAMAGE;

				D3DXMATERIAL* pMat;

				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++, pMat++)
				{
					pMat->MatD3D.Diffuse = { 1.0f,0.0f,0.0f,1.0f };
				}
				g_Player.nCntState = 60;
			}

		}
	}

}

//=========================================================================================================
//敵の状態遷移処理
//=========================================================================================================
void HitItem(ITEM aItem)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	if (aItem.nType == ITEM_KIND_000)
	{
		g_Player.nLife += 10;
		if (g_Player.nLife > MAX_LIFE)
		{
			g_Player.nLife = MAX_LIFE;
		}
	}
}

//=========================================================================================================
//プレイヤー情報の取得処理
//=========================================================================================================
PLAYER GetPlayer(void)
{
	return g_Player;
}

//=========================================================================================================
//プレイヤーの移動操作
//=========================================================================================================
void PlayerMove(void)
{
	//移動操作
	{
		Camera aCamera = GetCamera();

		if (GetKeyboardPress(DIK_W) == true)
		{//Wのみ押された場合
			if (GetKeyboardPress(DIK_A) == true)
			{//Aのみ押された場合
				g_Player.moveP.x += cosf(D3DX_PI * 0.25f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.moveP.z += sinf(D3DX_PI * 0.25f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.Destrot.y = -D3DX_PI * 0.25f - aCamera.rot.y;
				if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y = D3DX_PI;
				}
				else if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y = -D3DX_PI;
				}
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{//Dのみ押された場合
				g_Player.moveP.x += cosf(-D3DX_PI * 0.25f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.moveP.z += sinf(-D3DX_PI * 0.25f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.Destrot.y = D3DX_PI * 0.25f - aCamera.rot.y;
				if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y = D3DX_PI;
				}
				else if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y = -D3DX_PI;
				}
			}
			else
			{
				g_Player.moveP.x += cosf(D3DX_PI * 0.0f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.moveP.z += sinf(D3DX_PI * 0.0f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.Destrot.y = +D3DX_PI * 0.0f - aCamera.rot.y;
				if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y = D3DX_PI;
				}
				else if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y = -D3DX_PI;
				}
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//Sのみ押された場合
			if (GetKeyboardPress(DIK_A) == true)
			{//Aのみ押された場合
				g_Player.moveP.x += cosf(D3DX_PI * 0.75f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.moveP.z += sinf(D3DX_PI * 0.75f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.Destrot.y = -D3DX_PI * 0.75f - aCamera.rot.y;
				if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y = D3DX_PI;
				}
				else if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y = -D3DX_PI;
				}
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{//Dのみ押された場合
				g_Player.moveP.x += cosf(-D3DX_PI * 0.75f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.moveP.z += sinf(-D3DX_PI * 0.75f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.Destrot.y = D3DX_PI * 0.75f - aCamera.rot.y;
				if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y = D3DX_PI;
				}
				else if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y = -D3DX_PI;
				}
			}
			else
			{
				g_Player.moveP.x += cosf(+D3DX_PI * 1.0f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.moveP.z += sinf(+D3DX_PI * 1.0f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.Destrot.y = -D3DX_PI * 1.0f - aCamera.rot.y;
				if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y = D3DX_PI;
				}
				else if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y = -D3DX_PI;
				}
			}
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{//Aのみ押された場
			g_Player.moveP.x += cosf(D3DX_PI * 0.5f + aCamera.rot.y) * MOVE_SPEED;
			g_Player.moveP.z += sinf(D3DX_PI * 0.5f + aCamera.rot.y) * MOVE_SPEED;
			g_Player.Destrot.y = -D3DX_PI * 0.5f - aCamera.rot.y;
			if (g_Player.rot.y < -D3DX_PI)
			{
				g_Player.rot.y = D3DX_PI;
			}
			else if (g_Player.rot.y > D3DX_PI)
			{
				g_Player.rot.y = -D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Dのみ押された場合
			g_Player.moveP.x += cosf(-D3DX_PI * 0.5f + aCamera.rot.y) * MOVE_SPEED;
			g_Player.moveP.z += sinf(-D3DX_PI * 0.5f + aCamera.rot.y) * MOVE_SPEED;
			g_Player.Destrot.y = D3DX_PI * 0.5f - aCamera.rot.y;
			if (g_Player.rot.y < -D3DX_PI)
			{
				g_Player.rot.y = D3DX_PI;
			}
			else if (g_Player.rot.y > D3DX_PI)
			{
				g_Player.rot.y = -D3DX_PI;
			}
		}


	}
}

//=========================================================================================================
//プレイヤーのダッシュ操作
//=========================================================================================================
void PlayerEnagy(void)
{
	if (GetKeyboardTrigger(DIK_K) == true && g_Player.nEnagy > 0)
	{//Eのみ押された場合
		g_Player.nEnagy -= 1;
		g_Player.state = PLAYERSTATE_DUSH;
		g_Player.nCntState = 20;
		g_Player.moveP.x += cosf(g_Player.rot.y) * 20.0f;
		g_Player.moveP.z -= sinf(g_Player.rot.y) * 20.0f;

		D3DXMATERIAL* pMat;
		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++, pMat++)
		{
			pMat->MatD3D.Diffuse = { 0.0f,1.0f,0.0f,0.8f };
		}
	}
	if (g_Player.nEnagy < ENAGY)
	{
		g_Player.EngCnt++;
		if (g_Player.EngCnt % 120 == 0)
		{
			g_Player.nEnagy++;
		}
	}
	if (g_Player.nEnagy >= ENAGY)
	{
		g_Player.EngCnt = 0;
	}
}

//=========================================================================================================
//プレイヤーと壁の当たり判定
//=========================================================================================================
void PlayerWall(void)
{

	//D3DXVECTOR3 HitWall = ColissionWall(g_Player.pos, g_Player.posOld, &g_Player.moveP);
	//
	//g_Player.pos = HitWall;
	{//+Xの壁
		if (g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x) > 1700.0f)
		{
			g_Player.pos.x = 1700.0f - (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x);
			g_Player.moveP.x = 0.0f;
		}
		else if (g_Player.pos.x + cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x > 1700.0f)
		{
			g_Player.pos.x = 1700.0f - (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x);
			g_Player.moveP.x = 0.0f;
		}
		if (g_Player.pos.x + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z) > 1700.0f)
		{
			g_Player.pos.x = 1700.0f - (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z);
			g_Player.moveP.x = 0.0f;
		}
		else if (g_Player.pos.x + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z) > 1700.0f)
		{
			g_Player.pos.x = 1700.0f - (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z);
			g_Player.moveP.x = 0.0f;
		}
	}

	{//-Xの壁
		if (g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x) < -1700.0f)
		{
			g_Player.pos.x = -1700.0f - (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x);
			g_Player.moveP.x = 0.0f;
		}
		else if (g_Player.pos.x + cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x < -1700.0f)
		{
			g_Player.pos.x = -1700.0f - (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x);
			g_Player.moveP.x = 0.0f;
		}
		else if (g_Player.pos.x + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z) < -1700.0f)
		{
			g_Player.pos.x = -1700.0f - (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z);
			g_Player.moveP.x = 0.0f;
		}
		else if (g_Player.pos.x + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z) < -1700.0f)
		{
			g_Player.pos.x = -1700.0f - (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z);
			g_Player.moveP.x = 0.0f;
		}
	}

	{//+Zの壁
		if (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x) > 1990.0f)
		{
			g_Player.pos.z = 1990.0f - (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x);
			g_Player.moveP.z = 0.0f;
		}
		else if (g_Player.pos.z + sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.x > 1990.0f)
		{
			g_Player.pos.z = 1990.0f - (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.x);
			g_Player.moveP.z = 0.0f;
		}
		else if (g_Player.pos.z + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.z) > 1700.0f)
		{
			g_Player.pos.z = 1700.0f - (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.z);
			g_Player.moveP.z = 0.0f;
		}
		else if (g_Player.pos.z + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z) > 1700.0f)
		{
			g_Player.pos.z = 1700.0f - (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z);
			g_Player.moveP.z = 0.0f;
		}

	}
	{//-Zの壁
		if ((g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)) < -1700.0f)
		{
			g_Player.pos.z = (-1700.0f + (-sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x));
			g_Player.moveP.z = 0.0f;
		}
		else if ((g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)) < -1700.0f)
		{
			g_Player.pos.z = (-1700.0f + (-sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.x));
			g_Player.moveP.z = 0.0f;
		}
		else if ((g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z)) < -1990.0f)
		{
			g_Player.pos.z = (-1990.0f - (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z));
			g_Player.moveP.z = 0.0f;
		}
		else if ((g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z)) < -1990.0f)
		{
			g_Player.pos.z = (-1990.0f - (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z));
			g_Player.moveP.z = 0.0f;
		}

	}
}

//=========================================================================================================
//プレイヤーとオブジェクトの当たり判定
//=========================================================================================================
void PlayerObject(void)
{
	D3DXVECTOR3 HitObject;
	HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	g_Player.pos = HitObject;
	HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	g_Player.pos = HitObject;
	HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	g_Player.pos = HitObject;
	HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	g_Player.pos = HitObject;
	//HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y)*g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (cosf(g_Player.rot.y)*g_Player.VtxMinPlayer.x))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	//g_Player.pos = HitObject;
	//HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y)*g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (cosf(g_Player.rot.y)*g_Player.VtxMaxPlayer.x))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	//g_Player.pos = HitObject;
	//HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y)*g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (cosf(g_Player.rot.y)*g_Player.VtxMinPlayer.x))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	//g_Player.pos = HitObject;
	//HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y)*g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (cosf(g_Player.rot.y)*g_Player.VtxMaxPlayer.x))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	//g_Player.pos = HitObject;
}

void PlayerMod(void)
{
	if (ColissionModBull(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
	if (ColissionModBull(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
	if (ColissionModBull(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
	if (ColissionModBull(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
}

void PlayerEnemy(void)
{
	if (ColPlayEnemy(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
	if (ColPlayEnemy(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
	if (ColPlayEnemy(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
	if (ColPlayEnemy(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
}

//=========================================================================================================
//プレイヤーの遷移状態
//=========================================================================================================
void PlayerState(void)
{
	switch (g_Player.state)
	{
	case PLAYERSTATE_NORMAL:
		D3DXMATERIAL* pMat;

		//マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++, pMat++)
		{
			pMat->MatD3D.Diffuse = g_Player.col[nCntMat];

		}
		break;

	case PLAYERSTATE_DAMAGE:
		g_Player.nCntState--;
		if (g_Player.nCntState <= 0)
		{
			g_Player.state = PLAYERSTATE_NORMAL;
		}
		break;
	case PLAYERSTATE_DUSH:
		g_Player.nCntState--;
		SetEffect(g_Player.pos, D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f), 15.0f, 10, EFFECT_KIND_SANDDUST);
		if (g_Player.nCntState <= 0)
		{
			g_Player.state = PLAYERSTATE_NORMAL;
		}
		break;
	}
}

void SetPosition(D3DXVECTOR3 pos)
{
	g_Player.pos = pos;
}

void EnemyLockOn(void)
{

	if (GetKeyboardPress(DIK_J) == true)
	{
		g_Player.rot.y -= 0.02f;
		if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y = -D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_L) == true)
	{
		g_Player.rot.y += 0.02f;
		if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y = D3DX_PI;
		}

	}
	ENEMY aEnemy = GetEnemy();
	g_Player.rot = g_Player.rot;
	g_Player.Destrot = g_Player.rot;
	//g_Player.rot = D3DXVECTOR3(0.0f, -atan2f((aEnemy.pos.x), (aEnemy.pos.z)), 0.0f);
}