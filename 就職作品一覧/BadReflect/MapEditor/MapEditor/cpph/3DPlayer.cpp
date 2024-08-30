//=========================================================================================================
//
//3D�v���C���[�̏���
//Author:�x�씋��
//
//=========================================================================================================
#include "3DPlayer.h"
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Object3D.h"
#include "3DBlock.h"
#include <assert.h>

#define PLAYER_SPEED	(0.2f)
#define MOVE_NONSHIFT (10.0f)

//====================================================
//�ÓI�����o�ϐ��̏�����
//====================================================
D3DXVECTOR3 CPlayer3D::m_VtxMaxObject;
D3DXVECTOR3 CPlayer3D::m_VtxMinObject;
D3DXVECTOR3 CPlayer3D::m_pos;
D3DXVECTOR3 CPlayer3D::m_rot;
D3DXVECTOR3 CPlayer3D::m_Length;
C3DBlock* CPlayer3D::m_pObject = nullptr;

//====================================================
//�R���X�g���N�^
//====================================================
CPlayer3D::CPlayer3D(int nPriority) :CObject3D(nPriority)
{
	m_Num = 0;

}
//====================================================
//�f�X�g���N�^
//====================================================
CPlayer3D::~CPlayer3D()
{

}


//====================================================
//����������
//====================================================
HRESULT CPlayer3D::Init(void)
{
	m_Num = 0;
	//DWORD dwSizeFVF;
	//BYTE *pVtxBuff;
	m_pObject = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pObject = C3DBlock::CreateModel(m_pos, 0, CObject::TYPE_EDITBLOCK);

	//X�t�@�C���̓ǂݍ���
	SetType(CObject::TYPE_PLAYER);
	return S_OK;
}

//====================================================
//�I������
//====================================================
void CPlayer3D::Uninit(void)
{

}

//====================================================
//�X�V����
//====================================================
void CPlayer3D::Update(void)
{
	int nCnt = 0;
	m_pos = GetPos();
	PlayerContoroll();
}

//====================================================
//�`�揈��
//====================================================
void CPlayer3D::Draw(void)
{

	{
		//CManager Renderer;
		//CRenderer *pRenderer = Renderer.GetRenderer();
		////�f�o�C�X�̎擾
		//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		//D3DXMATRIX mtxRot, mtxTrans, mtxParts;	//�v�Z�p�}�g���b�N�X
		//D3DMATERIAL9 matDef;
		//D3DXMATERIAL *pMat;

		////���[���h�}�g���b�N�X�̏�����
		//D3DXMatrixIdentity(&m_mtxWorld);

		////�����𔽉f
		//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		////�ʒu�𔽉f
		//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//pDevice->GetTransform(D3DTS_WORLD, &mtxParts);

		////D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParts);

		////���[���h�}�g���b�N�X�̐ݒ�
		//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		////���݂̃}�e���A�����擾
		//pDevice->GetMaterial(&matDef);
		////�}�e���A���f�[�^�ւ̃|�C���^���擾
		//pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

		//for (int nCntMat = 0; nCntMat < (int)m_dwNumMatModel; nCntMat++)
		//{
		//	//�}�e���A���̐ݒ�
		//	pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//	//�e�N�X�`���̐ݒ�
		//	pDevice->SetTexture(0, m_apTEXtureModel[nCntMat]);

		//	//���f���i�p�[�c�j�̕`��
		//	m_pMeshModel->DrawSubset(nCntMat);
		//	pMat->MatD3D.Diffuse = { 1.0f,1.0f,1.0f,0.2f };
		//}

		//pDevice->SetMaterial(&matDef);
	}



}

//====================================================
//�v���C���[�̑��쏈��
//====================================================
void CPlayer3D::PlayerContoroll(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();


	//�u���b�N�̈ړ�����
	{
		if (pKeyboard->GetTrigger(DIK_A) == true)
		{//A�̂݉����ꂽ�ꍇ
			m_pos.z += MOVE_NONSHIFT;	//���ړ�
			
		}
		else if (pKeyboard->GetTrigger(DIK_D) == true)
		{//D�̂݉����ꂽ�ꍇ
			m_pos.z -= MOVE_NONSHIFT;	//�E�ړ�
		}
		else if (pKeyboard->GetTrigger(DIK_W) == true)
		{//W�̂݉����ꂽ�ꍇ
			m_pos.y += MOVE_NONSHIFT;	//��ړ�

		}
		else if (pKeyboard->GetTrigger(DIK_S) == true)
		{//S�̂݉����ꂽ�ꍇ
			m_pos.y -= MOVE_NONSHIFT;	//���ړ�
		}
		else if (pKeyboard->GetTrigger(DIK_1) == true)
		{//W�̂݉����ꂽ�ꍇ
			m_pos.x += MOVE_NONSHIFT;	//���Ɉړ�

		}
		else if (pKeyboard->GetTrigger(DIK_2) == true)
		{//S�̂݉����ꂽ�ꍇ
			m_pos.x -= MOVE_NONSHIFT;	//��O�Ɉړ�
		}
		// ���f���؂�ւ�
		else if (pKeyboard->GetTrigger(DIK_3) == true)
		{//W�̂݉����ꂽ�ꍇ
			m_Num++;
			if (m_Num > C3DBlock::OBJECT_MODEL_MAX)
			{
				m_Num = 0;
			}
			m_pObject->Release();
			m_pObject = nullptr;
			m_pObject = C3DBlock::CreateModel(m_pos, m_Num, CObject::TYPE_EDITBLOCK);
			SetPos(m_pos, 0.0f, 0.0f);

		}
		else if (pKeyboard->GetTrigger(DIK_4) == true)
		{//S�̂݉����ꂽ�ꍇ
			m_Num--;
			if (m_Num <= 0)
			{
				m_Num = C3DBlock::OBJECT_MODEL_MAX;
			}
			m_pObject->Release();
			m_pObject = nullptr;
			m_pObject = C3DBlock::CreateModel(m_pos, m_Num, CObject::TYPE_EDITBLOCK);
		}
	}
	m_pObject->SetPos(m_pos, 0.0f, 0.0f);
	//�u���b�N�̐ݒu�ƃ��Z�b�g
	{
		if (pKeyboard->GetTrigger(DIK_RETURN) == true)
		{//Enter�̂݉����ꂽ�ꍇ
			CObject3D::Create(m_pos, CObject::TYPE_3DBLOCK, m_Num);
		}
		if (pKeyboard->GetTrigger(DIK_BACKSPACE) == true)
		{//F4�̂݉����ꂽ�ꍇ
			C3DBlock::DeleateBlock(m_pos);
		}
	}

	//���Z�b�g
	{
		if (pKeyboard->GetTrigger(DIK_R) == true)
		{//R�̂݉����ꂽ�ꍇ
			CObject::Reset();
		}
	}

	//�Z�[�u&���[�h
	{
		if (pKeyboard->GetTrigger(DIK_F3) == true)
		{//F3�̂݉����ꂽ�ꍇ
			CObject::WhiteTextMap();
		}
		if (pKeyboard->GetTrigger(DIK_F4) == true)
		{//F4�̂݉����ꂽ�ꍇ
			CObject::Load();
		}
	}
}

//====================================================
//�ʒu�ݒ菈��
//====================================================
void CPlayer3D::SetPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;
}

//====================================================
//�ʒu�擾����
//====================================================
D3DXVECTOR3 CPlayer3D::GetPos(void)
{
	return m_pos;
}

CPlayer3D *CPlayer3D::Create(void)
{
	CPlayer3D *p3DPlayer = NULL;
	p3DPlayer = new CPlayer3D;
	//p3DPlayer->Init();
	return p3DPlayer;
}

//=========================================================================================================
//�T�C�Y�̌v�Z����
//=========================================================================================================
void CPlayer3D::SetObjectSize(void)
{
	int nNumVtx;

	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	//���_���̎擾
	nNumVtx = m_pMeshModel->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(m_pMeshModel->GetFVF());

	//���_�o�b�t�@�����b�N
	m_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (vtx.x > m_VtxMaxObject.x)
		{
			m_VtxMaxObject.x = vtx.x;
		}
		if (vtx.x < m_VtxMinObject.x)
		{
			m_VtxMinObject.x = vtx.x;
		}
		if (vtx.z > m_VtxMaxObject.z)
		{
			m_VtxMaxObject.z = vtx.z;
		}
		if (vtx.z < m_VtxMinObject.z)
		{
			m_VtxMinObject.z = vtx.z;
		}
		if (vtx.y> m_VtxMaxObject.y)
		{
			m_VtxMaxObject.y = vtx.y;
		}
		if (vtx.y < m_VtxMinObject.y)
		{
			m_VtxMinObject.y = vtx.y;
		}
		pVtxBuff += dwSizeFVF;
	}
	float fMax, fMin;
	//z���̕��𒲂ׂ�
	{
		if (m_VtxMaxObject.z < 0)
		{//�l�����̏ꍇ���ɖ߂�
			fMax = m_VtxMaxObject.z * -1.0f;
		}
		else
		{
			fMax = m_VtxMaxObject.z;
		}
		if (m_VtxMinObject.z < 0)
		{//�l�����̏ꍇ���ɖ߂�
			fMin = m_VtxMinObject.z * -1.0f;
		}
		else
		{
			fMin = m_VtxMinObject.z;
		}
		m_Length.z = fMax + fMin;
	}

	//y���̕��𒲂ׂ�
	{
		if (m_VtxMaxObject.z < 0)
		{//�l�����̏ꍇ���ɖ߂�
			fMax = m_VtxMaxObject.y * -1.0f;
		}
		else
		{
			fMax = m_VtxMaxObject.y;
		}
		if (m_VtxMinObject.y < 0)
		{//�l�����̏ꍇ���ɖ߂�
			fMin = m_VtxMinObject.y * -1.0f;
		}
		else
		{
			fMin = m_VtxMinObject.y;
		}
		m_Length.y = fMax + fMin;
	}

	//x���̕��𒲂ׂ�
	{
		if (m_VtxMaxObject.x < 0)
		{//�l�����̏ꍇ���ɖ߂�
			fMax = m_VtxMaxObject.x * -1.0f;
		}
		else
		{
			fMax = m_VtxMaxObject.x;
		}
		if (m_VtxMinObject.x < 0)
		{//�l�����̏ꍇ���ɖ߂�
			fMin = m_VtxMinObject.x * -1.0f;
		}
		else
		{
			fMin = m_VtxMinObject.x;
		}
		m_Length.x = fMax + fMin;
	}
}