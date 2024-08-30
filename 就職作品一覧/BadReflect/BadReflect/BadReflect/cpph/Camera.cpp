//===========================================================
//
//�J�����̏�������
//Author:�x�씋��
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
//����������
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
	////�Ίp���̒������Z�o
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
//�J�����̏I������
//=========================================================================================================
void CCamera:: Uninit(void)
{

	

}

//=========================================================================================================
//�J�����̍X�V����
//=========================================================================================================
void CCamera:: Update(void)
{
#if 0
	PLAYER aPlayer = GetPlayer();

	{//Booll�^��On/Off����
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


	{//=====================�����_����=============================

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
		{//=====================���_����===============================
			if (GetKeyboardPress(DIK_W) == true)
			{//U�����
				if (GetKeyboardPress(DIK_A) == true)
				{//H�����

				}
				else if (GetKeyboardPress(DIK_D) == true)
				{//K�����

				}
				else
				{

				}
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//J�����
				if (GetKeyboardPress(DIK_A) == true)
				{//H�����

				}
				else if (GetKeyboardPress(DIK_D) == true)
				{//K�����

				}
				else
				{

				}
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{//H�̂݉����ꂽ��

			}
			else if (GetKeyboardPress(DIK_D) == true)
			{//K�����


			}
		}
		*/
		//�����_�𒆐S�Ƃ�������
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

	{//=====================�����_��������===============================
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

	{//=====================�����_��������===============================
		if (GetKeyboardPress(DIK_I) == true)
		{
			m_posV.y += 0.5f;
		}
		else if (GetKeyboardPress(DIK_K) == true)
		{
			m_posV.y -= 0.5f;

		}
	}

	
	//�J�����ǔ�
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
				//�J�����̌���
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

	//���s���e��
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
		//�v���C���[�̊J�n�ʒu�ɍ��킹��
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
		//�v���C���[���͈͊O�ɍs���܂őҋ@����
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
		//�v���C���[���͈͓��ɖ߂�܂œ���������
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
	{//W�����
		if (pKeyboard->GetPress(DIK_J) == true)
		{//A�����
			m_posV.x += cosf(D3DX_PI * 0.75f)*5.0f;
			m_posV.z += sinf(D3DX_PI * 0.75f)*5.0f;
			m_posR.x += cosf(D3DX_PI * 0.75f)*5.0f;
			m_posR.z += sinf(D3DX_PI * 0.75f)*5.0f;
		}
		else if (pKeyboard->GetPress(DIK_L) == true)
		{//D�����
			
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
	{//S�����
		if (pKeyboard->GetPress(DIK_J) == true)
		{//A�����
			m_posV.x += cosf(D3DX_PI * 0.25f)*5.0f;
			m_posV.z += sinf(D3DX_PI * 0.25f)*5.0f;
			m_posR.x += cosf(D3DX_PI * 0.25f)*5.0f;
			m_posR.z += sinf(D3DX_PI * 0.25f)*5.0f;
		}
		else if (pKeyboard->GetPress(DIK_L) == true)
		{//D�����
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
	{//A�̂݉����ꂽ��
		m_posV.x += cosf(D3DX_PI * 0.5f)*5.0f;
		m_posV.z += sinf(D3DX_PI * 0.5f)*5.0f;
		m_posR.x += cosf(D3DX_PI * 0.5f)*5.0f;
		m_posR.z += sinf(D3DX_PI * 0.5f)*5.0f;

	}
	else if (pKeyboard->GetPress(DIK_L) == true)
	{//D�����
		m_posV.x += cosf(-D3DX_PI * 0.5f)*5.0f;
		m_posV.z += sinf(-D3DX_PI * 0.5f)*5.0f;
		m_posR.x += cosf(-D3DX_PI * 0.5f)*5.0f;
		m_posR.z += sinf(-D3DX_PI * 0.5f)*5.0f;
	}
	else if (pKeyboard->GetPress(DIK_UP) == true)
	{//S�����
		m_posV.y += 0.5f;
		m_posR.y += 0.5f;
	}
	else if (pKeyboard->GetPress(DIK_DOWN) == true)
	{//S�����
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
	{//S�����
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
//�J�����̕`�揈��
//=========================================================================================================
void CCamera:: SetCamera(void)
{

	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);


	if (m_bMatrix == true)
	{
		//�v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(60.0f),								//����p
			(float)SCREEN_HEIGHT / (float)SCREEN_WIDTH,			//�A�X�y�N�g��
			10.0f,												//Z�l�̍ŏ��l
			5000.0f);											//Z�l�̍ő�l
	}
			
	if (m_bMatrix == false)
	{
		D3DXMatrixOrthoLH(&m_mtxProjection,						//�v���W�F�N�V�����}�g���b�N�X
			SCREEN_HEIGHT / m_ViewCamera,							//��ʂ̕�
			SCREEN_WIDTH / m_ViewCamera,						//��ʂ̍���
			10.0f,												//Z�l�̍ŏ��l
			500000.0f);											//Z�l�̍ő�l
	}
	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);


	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_posU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

}

float CCamera::GetRot()
{
	return m_rot.y;
}