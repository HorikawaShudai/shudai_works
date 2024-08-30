//===========================================================
//
//カメラの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Camera.h"
#include "Player.h"

//グローバル変数宣言
Camera g_Camera;
BoolCamera g_Bool;
int g_Time;
D3DXMATRIX g_mtxWorldCamera;

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitCamera(void)
{
	g_Bool.Homing = false;
	g_Camera.posV = D3DXVECTOR3(0.0f,200.0f,0.0f);
	g_Camera.posR = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_Camera.DostposR = D3DXVECTOR3(0.0f,44.0f,0.0f);
	g_Camera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	////対角線の長さを算出
	//g_Camera.Length = sqrtf(sqrtf(((g_Camera.posV.x - g_Camera.posR.x)*(g_Camera.posV.x - g_Camera.posR.x))  +
	//							  ((g_Camera.posV.z - g_Camera.posR.z)*(g_Camera.posV.z - g_Camera.posR.z))  *0.5f)+
	//							  ((g_Camera.posV.y - g_Camera.posR.y)*(g_Camera.posV.y - g_Camera.posR.y))) *0.5f;
	g_Camera.Length = 500.0f;
	g_Camera.LengthR = 100.0f;
	g_Camera.posV.z = g_Camera.posR.z - sinf(g_Camera.rot.y)* g_Camera.Length;
	g_Camera.posV.x = g_Camera.posR.x - cosf(g_Camera.rot.y)* g_Camera.Length;
	//g_Camera.posV.y = g_Camera.posR.y + cosf(g_Camera.rot.y)* g_Camera.LengthR;
}

//=========================================================================================================
//カメラの終了処理
//=========================================================================================================
void UninitCamera(void)
{

	

}

//=========================================================================================================
//カメラの更新処理
//=========================================================================================================
void UpdateCamera(void)
{
	PLAYER aPlayer = GetPlayer();

	{//Booll型のOn/Off操作
		//if (GetKeyboardTrigger(DIK_F9) == true)
		//{
		//	switch (g_Bool.Homing)
		//	{
		//	case false:
		//		g_Bool.Homing = true;
		//		break;
		//	case true:
		//		g_Bool.Homing = false;
		//		break;
		//	}
		//}
	}


	{//=====================注視点操作=============================

		//if (GetKeyboardPress(DIK_UP) == true)
		//{
		//	g_Camera.posR.y += 2.0f;
		//}
		//else if (GetKeyboardPress(DIK_DOWN) == true)
		//{
		//	g_Camera.posR.y -= 2.0f;
		//}
		if (GetKeyboardPress(DIK_J) == true)
		{
			g_Camera.rot.y += 0.02f;
			if (g_Camera.rot.y > D3DX_PI)
			{
				g_Camera.rot.y = -D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_L) == true)
		{
			g_Camera.rot.y -= 0.02f;
			if (g_Camera.rot.y < -D3DX_PI)
			{
				g_Camera.rot.y = D3DX_PI;
			}

		}
	}
	/*
		{//=====================視点操作===============================
			if (GetKeyboardPress(DIK_W) == true)
			{//Uのみ押された場合
				if (GetKeyboardPress(DIK_A) == true)
				{//Hのみ押された場合

				}
				else if (GetKeyboardPress(DIK_D) == true)
				{//Kのみ押された場合

				}
				else
				{

				}
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//Jのみ押された場合
				if (GetKeyboardPress(DIK_A) == true)
				{//Hのみ押された場合

				}
				else if (GetKeyboardPress(DIK_D) == true)
				{//Kのみ押された場合

				}
				else
				{

				}
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{//Hのみ押された場

			}
			else if (GetKeyboardPress(DIK_D) == true)
			{//Kのみ押された場合


			}
		}
		*/
		

	{//=====================注視点距離操作===============================
		//if (GetKeyboardPress(DIK_L) == true)
		//{
		//	g_Camera.Length += 0.5f;

		//	if (g_Camera.Length > 500.0f)
		//	{
		//		g_Camera.Length = 500.0f;
		//	}
		//	g_Camera.posV.z = g_Camera.posR.z - sinf(g_Camera.rot.y)* g_Camera.Length;
		//	g_Camera.posV.x = g_Camera.posR.x - cosf(g_Camera.rot.y)* g_Camera.Length;
		//}
		//else if (GetKeyboardPress(DIK_O) == true)
		//{
		//	g_Camera.Length -= 0.5f;
		//	if (g_Camera.Length < 50.0f)
		//	{
		//		g_Camera.Length = 50.0f;
		//	}
		//	g_Camera.posV.z = g_Camera.posR.z - sinf(g_Camera.rot.y)* g_Camera.Length;
		//	g_Camera.posV.x = g_Camera.posR.x - cosf(g_Camera.rot.y)* g_Camera.Length;
		//}
	}

	{//=====================注視点距離操作===============================
		//if (GetKeyboardPress(DIK_I) == true)
		//{
		//	g_Camera.posV.y += 0.5f;
		//}
		//else if (GetKeyboardPress(DIK_K) == true)
		//{
		//	g_Camera.posV.y -= 0.5f;

		//}
	}

	//カメラ追尾
	{
		if (g_Bool.Homing == false)
		{
			if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_S) == true ||
				GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_D) == true ||
				GetKeyboardPress(DIK_L) == true || GetKeyboardPress(DIK_J) == true)
			{
				g_Time = 0;
			}

			else if (GetKeyboardPress(DIK_W) == false && GetKeyboardPress(DIK_S) == false &&
				GetKeyboardPress(DIK_A) == false && GetKeyboardPress(DIK_D) == false &&
				GetKeyboardPress(DIK_J) == false && GetKeyboardPress(DIK_L) == false)
			{
				g_Time++;
				g_Camera.Destrot.y = -aPlayer.rot.y;
			}

			if (g_Time > 20)
			{
				//カメラの向き
				{
					g_Camera.Diffrot.y = g_Camera.Destrot.y - g_Camera.rot.y;

					if (g_Camera.Diffrot.y > D3DX_PI)
					{
						g_Camera.Diffrot.y -= D3DX_PI * 2;
					}
					else if (g_Camera.Diffrot.y < -D3DX_PI)
					{
						g_Camera.Diffrot.y += D3DX_PI * 2;

					}

					g_Camera.rot.y += (g_Camera.Diffrot.y)*0.05f;

					if (g_Camera.rot.y > D3DX_PI)
					{
						g_Camera.rot.y -= D3DX_PI * 2;
					}
					else if (g_Camera.rot.y < -D3DX_PI)
					{
						g_Camera.rot.y += D3DX_PI * 2;
					}
				}
			}
		}
		else if (g_Bool.Homing == true)
		{

			g_Camera.Destrot.y = -aPlayer.rot.y;

			g_Camera.Diffrot.y = g_Camera.Destrot.y - g_Camera.rot.y;

			if (g_Camera.Diffrot.y > D3DX_PI)
			{
				g_Camera.Diffrot.y -= D3DX_PI * 2;
			}
			else if (g_Camera.Diffrot.y < -D3DX_PI)
			{
				g_Camera.Diffrot.y += D3DX_PI * 2;

			}

			g_Camera.rot.y += (g_Camera.Diffrot.y)*0.05f;

			if (g_Camera.rot.y > D3DX_PI)
			{
				g_Camera.rot.y -= D3DX_PI * 2;
			}
			else if (g_Camera.rot.y < -D3DX_PI)
			{
				g_Camera.rot.y += D3DX_PI * 2;
			}
		}
	}
	g_Camera.posV.z = g_Camera.posR.z - sinf(g_Camera.rot.y)* g_Camera.Length;
	g_Camera.posV.x = g_Camera.posR.x - cosf(g_Camera.rot.y)* g_Camera.Length;
	//g_Camera.posV.y = g_Camera.posR.y - tanf(g_Camera.rot.y)* g_Camera.Length;
	g_Camera.posV += aPlayer.moveP;
	g_Camera.posR += aPlayer.moveP;
	g_Camera.posR.z = aPlayer.pos.z + sinf(g_Camera.rot.y)*50.0f;
	g_Camera.posR.x = aPlayer.pos.x + cosf(g_Camera.rot.y)*50.0f;
}

void TitleCamera(void)
{
	//注視点を中心とした旋回
		g_Camera.rot.y += 0.002f;
		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y = -D3DX_PI;
		}
		g_Camera.posV.z = g_Camera.posR.z + sinf(g_Camera.rot.y)* 2000.0f;
		g_Camera.posV.x = g_Camera.posR.x + cosf(g_Camera.rot.y)* 2000.0f;
}
void EndCamera(void)
{
	//注視点を中心とした旋回
	g_Camera.rot.y += 0.002f;
	if (g_Camera.rot.y > D3DX_PI)
	{
		g_Camera.rot.y = -D3DX_PI;
	}
	g_Camera.posV.z = g_Camera.posR.z + sinf(g_Camera.rot.y)* 250.0f;
	g_Camera.posV.x = g_Camera.posR.x + cosf(g_Camera.rot.y)* 250.0f;
}

//=========================================================================================================
//カメラの描画処理
//=========================================================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, 
		D3DXToRadian(45.0f),								//視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//アスペクト比
		10.0f,												//Z値の最小値
		20000.0f);											//Z値の最大値
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);


	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.posV, &g_Camera.posR, &g_Camera.posU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);

}
//=========================================================================================================
//カメラの描画処理
//=========================================================================================================
void SetEndCam(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		D3DXToRadian(25.0f),								//視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//アスペクト比
		10.0f,												//Z値の最小値
		700.0f);											//Z値の最大値
															//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);


	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.posV, &g_Camera.posR, &g_Camera.posU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);

}

Camera GetCamera(void)
{
	return g_Camera;
}

void SetPosCamera(D3DXVECTOR3 posV, D3DXVECTOR3 posR)
{
	g_Camera.posV = posV;
	g_Camera.posR = posR;
}

void SetHoming(bool onoff)
{
	g_Bool.Homing = onoff;
}