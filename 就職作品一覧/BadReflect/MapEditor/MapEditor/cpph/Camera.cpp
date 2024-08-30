//===========================================================
//
//�J�����̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Camera.h"
#include "Manager.h"
#include "Renderer.h"
#include "3DPlayer.h"

//====================================================
//�R���X�g���N�^
//====================================================
CCamera::CCamera()
{

}

//====================================================
//�f�X�g���N�^
//====================================================
CCamera::~CCamera()
{

}

//=========================================================================================================
//����������
//=========================================================================================================
void CCamera:: Init(void)
{
	m_posV = D3DXVECTOR3(0.0f,10.0f,0.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DostposR = D3DXVECTOR3(0.0f,44.0f,0.0f);
	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_bMatrix = false;
	m_ViewCamera = 3.0f;
	////�Ίp���̒������Z�o
	//m_Length = sqrtf(sqrtf(((m_posV.x - m_posR.x)*(m_posV.x - m_posR.x))  +
	//							  ((m_posV.z - m_posR.z)*(m_posV.z - m_posR.z))  *0.5f)+
	//							  ((m_posV.y - m_posR.y)*(m_posV.y - m_posR.y))) *0.5f;
	m_Length = 100.0f;
	m_LengthR = 20.0f;
	m_posV.z = m_posR.z - sinf(m_rot.y)* m_Length;
	m_posV.x = m_posR.x - cosf(m_rot.y)* m_Length;
	m_State = STATE_NONE;
}

//=========================================================================================================
//�I������
//=========================================================================================================
void CCamera:: Uninit(void)
{

	

}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void CCamera:: Update(void)
{
	D3DXVECTOR3 pPos;
	CObject *pObj;

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < NUM_POLYGON; nCntObj++)
		{
			pObj = CObject::GetObject(nCntPri, nCntObj);
			if (pObj != NULL)
			{
				CObject::TYPE type;
				type = pObj->GetType();
				if (type == CObject::TYPE_PLAYER)
				{
				 pPos = pObj->GetPos();
				}

			}
		}
	}

	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	//���s���e��
	if (m_bMatrix == false)
	{
		//�v���C���[�̊J�n�ʒu�ɍ��킹��
		if (m_State == STATE_NONE)
		{

			if (pObj != NULL)
			{
				pPos = pObj->GetPos();
				pPos.y += 100.0f;
				m_posR.x = pPos.x;
				m_posR.y = pPos.y;
				m_posR.z = pPos.z;
				m_posV.y = pPos.y;
				m_posV.x = pPos.x - 20.0f;
				m_posV.z = pPos.z;
				m_State = STATE_STAY;
			}
		}
		//�v���C���[���͈͊O�ɍs���܂őҋ@����
		if (m_State == STATE_STAY)
		{
			pPos = pObj->GetPos();
			if (m_posV.z + 65.0f < pPos.z || m_posV.z - 65.0f > pPos.z || m_posV.y <pPos.y+65.0f || pPos.y < m_posV.y - 5.0f)
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
			pPos = pObj->GetPos();

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
			if (pPos.y > m_posV.y + 65.0f)
			{
				m_posV.y = pPos.y-65.0f;
				m_posR.y = pPos.y-65.0f;
			}
			else if (pPos.y < m_posV.y - 5.0f)
			{
				m_posV.y = pPos.y + 5.0f;
				m_posR.y = pPos.y + 5.0f;
			}
			if (m_posV.z + 65.0f < pPos.z || m_posV.z - 65.0f > pPos.z || m_posV.y <pPos.y + 65.0f || pPos.y < m_posV.y - 5.0f)
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
	{//W�̂݉����ꂽ�ꍇ
		if (pKeyboard->GetPress(DIK_J) == true)
		{//A�̂݉����ꂽ�ꍇ
			m_posV.x += cosf(D3DX_PI * 0.75f)*5.0f;
			m_posV.z += sinf(D3DX_PI * 0.75f)*5.0f;
			m_posR.x += cosf(D3DX_PI * 0.75f)*5.0f;
			m_posR.z += sinf(D3DX_PI * 0.75f)*5.0f;
		}
		else if (pKeyboard->GetPress(DIK_L) == true)
		{//D�̂݉����ꂽ�ꍇ
			
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
	{//S�̂݉����ꂽ�ꍇ
		if (pKeyboard->GetPress(DIK_J) == true)
		{//A�̂݉����ꂽ�ꍇ
			m_posV.x += cosf(D3DX_PI * 0.25f)*5.0f;
			m_posV.z += sinf(D3DX_PI * 0.25f)*5.0f;
			m_posR.x += cosf(D3DX_PI * 0.25f)*5.0f;
			m_posR.z += sinf(D3DX_PI * 0.25f)*5.0f;
		}
		else if (pKeyboard->GetPress(DIK_L) == true)
		{//D�̂݉����ꂽ�ꍇ
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
	{//D�̂݉����ꂽ�ꍇ
		m_posV.x += cosf(-D3DX_PI * 0.5f)*5.0f;
		m_posV.z += sinf(-D3DX_PI * 0.5f)*5.0f;
		m_posR.x += cosf(-D3DX_PI * 0.5f)*5.0f;
		m_posR.z += sinf(-D3DX_PI * 0.5f)*5.0f;
	}
	else if (pKeyboard->GetPress(DIK_U) == true)
	{//S�̂݉����ꂽ�ꍇ
		m_posV.y += 2.0f;
		m_posR.y += 2.0f;
	}
	else if (pKeyboard->GetPress(DIK_M) == true)
	{//S�̂݉����ꂽ�ꍇ
		m_posV.y -= 2.0f;
		m_posR.y -= 2.0f;

	}
	if (pKeyboard->GetPress(DIK_O) == true)
	{//S�̂݉����ꂽ�ꍇ
		m_Length += 2.0f;
	}
	else if (pKeyboard->GetPress(DIK_P) == true)
	{//S�̂݉����ꂽ�ꍇ
		m_Length -= 2.0f;

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
	else if (pKeyboard->GetPress(DIK_UP) == true)
	{
		m_posR.y += 1.00f;

	}
	else if (pKeyboard->GetPress(DIK_DOWN) == true)
	{
		m_posR.y -= 1.00f;

	}
	if (pKeyboard->GetTrigger(DIK_9) == true)
	{//S�̂݉����ꂽ�ꍇ
		m_rot.y = 0.0f;
		switch (m_bMatrix)
		{
		case true:
			pPos.y += 100.0f;
			m_posV.y = pPos.y;

			m_posR.y = pPos.y;
			m_bMatrix = false;
			break;
		case false:
			m_bMatrix = true;
			break;
		}

	}

	m_posV.z = m_posR.z - sinf(m_rot.y)* m_Length;
	m_posV.x = m_posR.x - cosf(m_rot.y)* m_Length;

}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void CCamera:: SetCamera(void)
{

	CManager Renderer;
	CRenderer *pRenderer = Renderer.GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);


	if (m_bMatrix == true)
	{
		//�v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(60.0f),								//����p
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,			//�A�X�y�N�g��
			10.0f,												//Z�l�̍ŏ��l
			5000.0f);											//Z�l�̍ő�l
	}
			
	if (m_bMatrix == false)
	{
		D3DXMatrixOrthoLH(&m_mtxProjection,						//�v���W�F�N�V�����}�g���b�N�X
			SCREEN_WIDTH/ m_ViewCamera,							//��ʂ̕�
			SCREEN_HEIGHT/ m_ViewCamera,						//��ʂ̍���
			10.0f,												//Z�l�̍ŏ��l
			50000.0f);											//Z�l�̍ő�l
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