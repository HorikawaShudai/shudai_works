//===========================================================
//
//カメラの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Camera.h"
#include "Player.h"
#include "Manager.h"
#include "Renderer.h"
#include "3DPlayer.h"

//D3DXMATRIX m_mtxWorldCamera;


CCamera::CCamera()
{

}
CCamera::~CCamera()
{
}


//=========================================================================================================
//初期化処理
//=========================================================================================================
void CCamera:: Init(void)
{
	m_posV = D3DXVECTOR3(0.0f,500.0f,0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DostposR = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f,0.0f);
	m_bMatrix = true;
	m_ViewCamera = 3.0f;
	////対角線の長さを算出
	//m_Length = sqrtf(sqrtf(((m_posV.x - m_posR.x)*(m_posV.x - m_posR.x))  +
	//							  ((m_posV.z - m_posR.z)*(m_posV.z - m_posR.z))  *0.5f)+
	//							  ((m_posV.y - m_posR.y)*(m_posV.y - m_posR.y))) *0.5f;
	m_Length = 100.0f;
	m_LengthR = 20.0f;
	m_posV.z = m_posR.z + sinf(m_rot.y)* m_Length;
	m_posV.x = m_posR.x + cosf(m_rot.y)* m_Length;
	m_State = STATE_NONE;
}

//=========================================================================================================
//カメラの終了処理
//=========================================================================================================
void CCamera:: Uninit(void)
{

	

}

//=========================================================================================================
//カメラの更新処理
//=========================================================================================================
void CCamera:: Update(void)
{
#if 0
	PLAYER aPlayer = GetPlayer();

	{//Booll型のOn/Off操作
		if (GetKeyboardTrigger(DIK_F9) == true)
		{
			switch (m_Bool.Homing)
			{
			case false:
				m_Bool.Homing = true;
				break;
			case true:
				m_Bool.Homing = false;
				break;
			}
		}
	}


	{//=====================注視点操作=============================

		if (GetKeyboardPress(DIK_UP) == true)
		{
			m_posR.y += 2.0f;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{
			m_posR.y -= 2.0f;
		}
		if (GetKeyboardPress(DIK_LEFT) == true)
		{
			m_rot.y += 0.02f;
			if (m_rot.y > D3DX_PI)
			{
				m_rot.y = -D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			m_rot.y -= 0.02f;
			if (m_rot.y < -D3DX_PI)
			{
				m_rot.y = D3DX_PI;
			}

		}
	}
	/*
		{//=====================視点操作===============================
			if (GetKeyboardPress(DIK_W) == true)
			{//Uを入力
				if (GetKeyboardPress(DIK_A) == true)
				{//Hを入力

				}
				else if (GetKeyboardPress(DIK_D) == true)
				{//Kを入力

				}
				else
				{

				}
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//Jを入力
				if (GetKeyboardPress(DIK_A) == true)
				{//Hを入力

				}
				else if (GetKeyboardPress(DIK_D) == true)
				{//Kを入力

				}
				else
				{

				}
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{//Hのみ押された場

			}
			else if (GetKeyboardPress(DIK_D) == true)
			{//Kを入力


			}
		}
		*/
		//注視点を中心とした旋回
		//if (GetKeyboardPress(DIK_Q) == true)
		//{
		//	m_rot.y += 0.02f;
		//	if (m_rot.y > D3DX_PI)
		//	{
		//		m_rot.y = -D3DX_PI;
		//	}
		//	m_posR.z = m_posV.z + sinf(m_rot.y)* m_Length;
		//	m_posR.x = m_posV.x + cosf(m_rot.y)* m_Length;
		//}
		//else if (GetKeyboardPress(DIK_E) == true)
		//{
		//	m_rot.y -= 0.02f;
		//	if (m_rot.y < -D3DX_PI)
		//	{
		//		m_rot.y = D3DX_PI;
		//	}
		//	m_posR.z = m_posV.z + sinf(m_rot.y)* m_Length;
		//	m_posR.x = m_posV.x + cosf(m_rot.y)* m_Length;
		//}

	{//=====================注視点距離操作===============================
		if (GetKeyboardPress(DIK_L) == true)
		{
			m_Length += 0.5f;

			if (m_Length > 500.0f)
			{
				m_Length = 500.0f;
			}
			m_posV.z = m_posR.z - sinf(m_rot.y)* m_Length;
			m_posV.x = m_posR.x - cosf(m_rot.y)* m_Length;
		}
		else if (GetKeyboardPress(DIK_O) == true)
		{
			m_Length -= 0.5f;
			if (m_Length < 50.0f)
			{
				m_Length = 50.0f;
			}
			m_posV.z = m_posR.z - sinf(m_rot.y)* m_Length;
			m_posV.x = m_posR.x - cosf(m_rot.y)* m_Length;
		}
	}

	{//=====================注視点距離操作===============================
		if (GetKeyboardPress(DIK_I) == true)
		{
			m_posV.y += 0.5f;
		}
		else if (GetKeyboardPress(DIK_K) == true)
		{
			m_posV.y -= 0.5f;

		}
	}

	
	//カメラ追尾
	{
		if (m_Bool.Homing == false)
		{
			if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_S) == true ||
				GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_D) == true ||
				GetKeyboardPress(DIK_LEFT) == true || GetKeyboardPress(DIK_RIGHT) == true)
			{
				m_Time = 0;
			}

			else if (GetKeyboardPress(DIK_W) == false && GetKeyboardPress(DIK_S) == false &&
				GetKeyboardPress(DIK_A) == false && GetKeyboardPress(DIK_D) == false &&
				GetKeyboardPress(DIK_LEFT) == false && GetKeyboardPress(DIK_RIGHT) == false)
			{
				m_Time++;
				m_Destrot.y = -aPlayer.rot.y;
			}

			if (m_Time > 20)
			{
				//カメラの向き
				{
					m_Diffrot.y = m_Destrot.y - m_rot.y;

					if (m_Diffrot.y > D3DX_PI)
					{
						m_Diffrot.y -= D3DX_PI * 2;
					}
					else if (m_Diffrot.y < -D3DX_PI)
					{
						m_Diffrot.y += D3DX_PI * 2;

					}

					m_rot.y += (m_Diffrot.y)*0.05f;

					if (m_rot.y > D3DX_PI)
					{
						m_rot.y -= D3DX_PI * 2;
					}
					else if (m_rot.y < -D3DX_PI)
					{
						m_rot.y += D3DX_PI * 2;
					}
				}
			}
		}
		else if (m_Bool.Homing == true)
		{

			m_Destrot.y = -aPlayer.rot.y;

			m_Diffrot.y = m_Destrot.y - m_rot.y;

			if (m_Diffrot.y > D3DX_PI)
			{
				m_Diffrot.y -= D3DX_PI * 2;
			}
			else if (m_Diffrot.y < -D3DX_PI)
			{
				m_Diffrot.y += D3DX_PI * 2;

			}

			m_rot.y += (m_Diffrot.y)*0.05f;

			if (m_rot.y > D3DX_PI)
			{
				m_rot.y -= D3DX_PI * 2;
			}
			else if (m_rot.y < -D3DX_PI)
			{
				m_rot.y += D3DX_PI * 2;
			}
		}
	}
	m_posV.z = m_posR.z - sinf(m_rot.y)* m_Length;
	m_posV.x = m_posR.x - cosf(m_rot.y)* m_Length;
	m_posV += aPlayer.moveP;
	m_posR += aPlayer.moveP;
	m_posR = aPlayer.pos;
#endif

	D3DXVECTOR3 pPos;
	pPos = CPlayer3D::GetPos();
	
	CKeyboard *pKeyboard = CManager::Get()->GetInputKeyboard();
	D3DXVECTOR3 pMove;

	//平行投影時
	if (m_bMatrix == true)
	{
		if (m_State == STATE_WAVE)
		{
			m_ViewCamera = 1.2f;
		}
		if (m_State != STATE_WAVE)
		{
			m_ViewCamera = 3.0f;
		}
		//プレイヤーの開始位置に合わせる
		if (m_State == STATE_NONE)
		{

				pPos = CPlayer3D::GetPos();
				pPos.y += 500.0f;
				m_posR.x = pPos.x;
				m_posR.y = 0.0f;
				m_posR.z = pPos.z;
				m_posV.y = pPos.y;
				m_posV.x = pPos.x;
				m_posV.z = pPos.z;
				m_State = STATE_STAY;
		}
		//プレイヤーが範囲外に行くまで待機する
		if (m_State == STATE_STAY)
		{
			pPos = CPlayer3D::GetPos();
			if (m_posV.z + 65.0f < pPos.z || 
				m_posV.z - 65.0f > pPos.z || 
				m_posV.y <pPos.y+65.0f || 
				pPos.y < m_posV.y - 5.0f || 
				m_posV.x + 65.0f < pPos.x 
				|| m_posV.x - 65.0f > pPos.x)
			{
				m_State = STATE_MOVE;
			}
			else
			{
				m_State = STATE_STAY;
			}
		}
		//プレイヤーが範囲内に戻るまで動き続ける
		if (m_State == STATE_MOVE)
		{
			pPos = CPlayer3D::GetPos();

			pPos.y += 65.0f;
			if (pPos.z>m_posV.z + 65.0f)
			{
				m_posV.z = pPos.z - 65.0f;
				m_posR.z = pPos.z - 65.0f;

			}
			else if (pPos.z<m_posV.z - 65.0f)
			{
				m_posV.z = pPos.z + 65.0f;
				m_posR.z = pPos.z + 65.0f;

			}
			if (pPos.y > m_posV.y + 300.0f)
			{
				m_posV.y = pPos.y+300.0f;
				m_posR.y = pPos.y-65.0f;
			}
			else if (pPos.y < m_posV.y - 5.0f)
			{
				m_posV.y = pPos.y + 300.0f;
				m_posR.y = pPos.y + 5.0f;
			}
			if (pPos.x > m_posV.x + 65.0f)
			{
				m_posV.x = pPos.x - 65.0f;
				m_posR.x = pPos.x - 65.0f;

			}
			else if (pPos.x < m_posV.x - 65.0f)
			{
				m_posV.x = pPos.x + 65.0f;
				m_posR.x = pPos.x + 65.0f;

			}
			if (m_posV.z + 65.0f < pPos.z || 
				m_posV.z - 65.0f > pPos.z || 
				m_posV.y <pPos.y + 65.0f || 
				pPos.y < m_posV.y - 5.0f ||
				m_posV.x + 65.0f < pPos.x || 
				m_posV.x - 65.0f > pPos.x)
			{
				m_State = STATE_MOVE;
			}
			else
			{
				m_State = STATE_STAY;
			}
		}
	}
	if (pKeyboard->GetPress(DIK_K) == true)
	{//Wを入力
		if (pKeyboard->GetPress(DIK_J) == true)
		{//Aを入力
			m_posV.x += cosf(D3DX_PI * 0.75f)*5.0f;
			m_posV.z += sinf(D3DX_PI * 0.75f)*5.0f;
			m_posR.x += cosf(D3DX_PI * 0.75f)*5.0f;
			m_posR.z += sinf(D3DX_PI * 0.75f)*5.0f;
		}
		else if (pKeyboard->GetPress(DIK_L) == true)
		{//Dを入力
			
			m_posV.x += cosf(-D3DX_PI * 0.75f)*5.0f;
			m_posV.z += sinf(-D3DX_PI * 0.75f)*5.0f;
			m_posR.x += cosf(-D3DX_PI * 0.75f)*5.0f;
			m_posR.z += sinf(-D3DX_PI * 0.75f)*5.0f;
		}
		else
		{
			m_posV.x += cosf(D3DX_PI *1.0f)*5.0f;
			m_posV.z += sinf(D3DX_PI *1.0f)*5.0f;
			m_posR.x += cosf(D3DX_PI *1.0f)*5.0f;
			m_posR.z += sinf(D3DX_PI *1.0f)*5.0f;
		}
	}
	else if (pKeyboard->GetPress(DIK_I) == true)
	{//Sを入力
		if (pKeyboard->GetPress(DIK_J) == true)
		{//Aを入力
			m_posV.x += cosf(D3DX_PI * 0.25f)*5.0f;
			m_posV.z += sinf(D3DX_PI * 0.25f)*5.0f;
			m_posR.x += cosf(D3DX_PI * 0.25f)*5.0f;
			m_posR.z += sinf(D3DX_PI * 0.25f)*5.0f;
		}
		else if (pKeyboard->GetPress(DIK_L) == true)
		{//Dを入力
			m_posV.x += cosf(-D3DX_PI * 0.25f)*5.0f;
			m_posV.z += sinf(-D3DX_PI * 0.25f)*5.0f;
			m_posR.x += cosf(-D3DX_PI * 0.25f)*5.0f;
			m_posR.z += sinf(-D3DX_PI * 0.25f)*5.0f;
		}
		else
		{
			m_posV.x += cosf(D3DX_PI *0.0f)*5.0f;
			m_posV.z += sinf(D3DX_PI *0.0f)*5.0f;
			m_posR.x += cosf(D3DX_PI *0.0f)*5.0f;
			m_posR.z += sinf(D3DX_PI *0.0f)*5.0f;
		}
	}
	else if (pKeyboard->GetPress(DIK_J) == true)
	{//Aのみ押された場
		m_posV.x += cosf(D3DX_PI * 0.5f)*5.0f;
		m_posV.z += sinf(D3DX_PI * 0.5f)*5.0f;
		m_posR.x += cosf(D3DX_PI * 0.5f)*5.0f;
		m_posR.z += sinf(D3DX_PI * 0.5f)*5.0f;

	}
	else if (pKeyboard->GetPress(DIK_L) == true)
	{//Dを入力
		m_posV.x += cosf(-D3DX_PI * 0.5f)*5.0f;
		m_posV.z += sinf(-D3DX_PI * 0.5f)*5.0f;
		m_posR.x += cosf(-D3DX_PI * 0.5f)*5.0f;
		m_posR.z += sinf(-D3DX_PI * 0.5f)*5.0f;
	}
	else if (pKeyboard->GetPress(DIK_UP) == true)
	{//Sを入力
		m_posV.y += 0.5f;
		m_posR.y += 0.5f;
	}
	else if (pKeyboard->GetPress(DIK_DOWN) == true)
	{//Sを入力
		m_posV.y -= 0.5f;
		m_posR.y -= 0.5f;

	}

	if (pKeyboard->GetPress(DIK_LEFT) == true)
	{
		m_rot.y += 0.02f;
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y = -D3DX_PI;
		}
	}
	else if (pKeyboard->GetPress(DIK_RIGHT) == true)
	{
		m_rot.y -= 0.02f;
		if (m_rot.y < -D3DX_PI)
		{
			m_rot.y = D3DX_PI;
		}

	}
	if (pKeyboard->GetTrigger(DIK_9) == true)
	{//Sを入力
		/*switch (m_bMatrix)
		{
		case true:
			pPos.y += 100.0f;
			m_posV.y = pPos.y;

			m_posR.y = pPos.y;
			m_State = STATE_NONE;
			m_bMatrix = false;
			break;
		case false:
			m_bMatrix = true;
			break;
		}*/

	}

	m_posV.z = m_posR.z - sinf(m_rot.y)* m_Length;
	m_posV.x = m_posR.x - cosf(m_rot.y)* m_Length;

}

//=========================================================================================================
//カメラの描画処理
//=========================================================================================================
void CCamera:: SetCamera(void)
{

	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);


	if (m_bMatrix == true)
	{
		//プロジェクションマトリックスの作成
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(60.0f),								//視野角
			(float)SCREEN_HEIGHT / (float)SCREEN_WIDTH,			//アスペクト比
			10.0f,												//Z値の最小値
			5000.0f);											//Z値の最大値
	}
			
	if (m_bMatrix == false)
	{
		D3DXMatrixOrthoLH(&m_mtxProjection,						//プロジェクションマトリックス
			SCREEN_HEIGHT / m_ViewCamera,							//画面の幅
			SCREEN_WIDTH / m_ViewCamera,						//画面の高さ
			10.0f,												//Z値の最小値
			500000.0f);											//Z値の最大値
	}
	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);


	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_posU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}

float CCamera::GetRot()
{
	return m_rot.y;
}