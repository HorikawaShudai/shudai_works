//===========================================================
//
//�J�����̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Camera.h"
#include "Player.h"

//�O���[�o���ϐ��錾
Camera g_Camera;
BoolCamera g_Bool;
int g_Time;
D3DXMATRIX g_mtxWorldCamera;

//=========================================================================================================
//����������
//=========================================================================================================
void InitCamera(void)
{
	g_Bool.Homing = false;
	g_Camera.posV = D3DXVECTOR3(0.0f,200.0f,0.0f);
	g_Camera.posR = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_Camera.DostposR = D3DXVECTOR3(0.0f,44.0f,0.0f);
	g_Camera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	////�Ίp���̒������Z�o
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
//�J�����̏I������
//=========================================================================================================
void UninitCamera(void)
{

	

}

//=========================================================================================================
//�J�����̍X�V����
//=========================================================================================================
void UpdateCamera(void)
{
	PLAYER aPlayer = GetPlayer();

	{//Booll�^��On/Off����
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


	{//=====================�����_����=============================

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
		{//=====================���_����===============================
			if (GetKeyboardPress(DIK_W) == true)
			{//U�̂݉����ꂽ�ꍇ
				if (GetKeyboardPress(DIK_A) == true)
				{//H�̂݉����ꂽ�ꍇ

				}
				else if (GetKeyboardPress(DIK_D) == true)
				{//K�̂݉����ꂽ�ꍇ

				}
				else
				{

				}
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//J�̂݉����ꂽ�ꍇ
				if (GetKeyboardPress(DIK_A) == true)
				{//H�̂݉����ꂽ�ꍇ

				}
				else if (GetKeyboardPress(DIK_D) == true)
				{//K�̂݉����ꂽ�ꍇ

				}
				else
				{

				}
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{//H�̂݉����ꂽ��

			}
			else if (GetKeyboardPress(DIK_D) == true)
			{//K�̂݉����ꂽ�ꍇ


			}
		}
		*/
		

	{//=====================�����_��������===============================
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

	{//=====================�����_��������===============================
		//if (GetKeyboardPress(DIK_I) == true)
		//{
		//	g_Camera.posV.y += 0.5f;
		//}
		//else if (GetKeyboardPress(DIK_K) == true)
		//{
		//	g_Camera.posV.y -= 0.5f;

		//}
	}

	//�J�����ǔ�
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
				//�J�����̌���
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
	//�����_�𒆐S�Ƃ�������
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
	//�����_�𒆐S�Ƃ�������
	g_Camera.rot.y += 0.002f;
	if (g_Camera.rot.y > D3DX_PI)
	{
		g_Camera.rot.y = -D3DX_PI;
	}
	g_Camera.posV.z = g_Camera.posR.z + sinf(g_Camera.rot.y)* 250.0f;
	g_Camera.posV.x = g_Camera.posR.x + cosf(g_Camera.rot.y)* 250.0f;
}

//=========================================================================================================
//�J�����̕`�揈��
//=========================================================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, 
		D3DXToRadian(45.0f),								//����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//�A�X�y�N�g��
		10.0f,												//Z�l�̍ŏ��l
		20000.0f);											//Z�l�̍ő�l
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);


	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.posV, &g_Camera.posR, &g_Camera.posU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);

}
//=========================================================================================================
//�J�����̕`�揈��
//=========================================================================================================
void SetEndCam(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		D3DXToRadian(25.0f),								//����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//�A�X�y�N�g��
		10.0f,												//Z�l�̍ŏ��l
		700.0f);											//Z�l�̍ő�l
															//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);


	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.posV, &g_Camera.posR, &g_Camera.posU);

	//�r���[�}�g���b�N�X�̐ݒ�
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