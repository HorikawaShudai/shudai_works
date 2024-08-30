//===========================================================
//
//player�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Model.h"
#include "Renderer.h"
#include "Manager.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

CModel::MDOELINFO CModel::m_Info[OBJECT_MODEL_NUM1] =
{
	{ "data\\MODEL\\Player\\00_Player_Hip.x" },		// PLAYER_MODEL1
	{ "data\\MODEL\\Player\\01_Player_Body.x" },	// PLAYER_MODEL2
	{ "data\\MODEL\\Player\\02_Player_Head.x" },	// PLAYER_MODEL3
	{ "data\\MODEL\\Player\\03_Player_Rarm.x" },	// PLAYER_MODEL4
	{ "data\\MODEL\\Player\\04_Player_Rhand.x" },	// PLAYER_MODEL5
	{ "data\\MODEL\\Player\\05_Player_Larm.x" },	// PLAYER_MODEL6
	{ "data\\MODEL\\Player\\06_Player_Lhand.x" },	// PLAYER_MODEL7
	{ "data\\MODEL\\Player\\07_Player_Rthigh.x" },	// PLAYER_MODEL8
	{ "data\\MODEL\\Player\\08_Player_Rshin.x" },	// PLAYER_MODEL9
	{ "data\\MODEL\\Player\\09_Player_Rleg.x" },	// PLAYER_MODEL10
	{ "data\\MODEL\\Player\\10_Player_Lthigh.x" },	// PLAYER_MODEL11
	{ "data\\MODEL\\Player\\11_Player_Lshin.x" },	// PLAYER_MODEL12
	{ "data\\MODEL\\Player\\12_Player_Lleg.x" },	// PLAYER_MODEL13
	{ "data\\MODEL\\Player\\Wapon_Razer.x" },		// PLAYER_MODEL14

	{ "data\\MODEL\\Enemy\\hip.x" },		// ENEMY_MODEL1
	{ "data\\MODEL\\Enemy\\body.x" },		// ENEMY_MODEL2
	{ "data\\MODEL\\Enemy\\Head.x" },		// ENEMY_MODEL3
	{ "data\\MODEL\\Enemy\\R_Shoulder.x" },	// ENEMY_MODEL4
	{ "data\\MODEL\\Enemy\\R_Arm.x" },		// ENEMY_MODEL5
	{ "data\\MODEL\\Enemy\\R_hand.x" },		// ENEMY_MODEL6
	{ "data\\MODEL\\Enemy\\L_Shoulder.x" },	// ENEMY_MODEL7
	{ "data\\MODEL\\Enemy\\L_Arm.x" },		// ENEMY_MODEL8
	{ "data\\MODEL\\Enemy\\L_hand.x" },		// ENEMY_MODEL9
	{ "data\\MODEL\\Enemy\\R_Thigh.x" },	// ENEMY_MODEL10
	{ "data\\MODEL\\Enemy\\R_Shin.x" },		// ENEMY_MODEL11
	{ "data\\MODEL\\Enemy\\R_Leg.x" },		// ENEMY_MODEL12
	{ "data\\MODEL\\Enemy\\L_Thigh.x" },	// ENEMY_MODEL13
	{ "data\\MODEL\\Enemy\\L_Shin.x" },		// ENEMY_MODEL14
	{ "data\\MODEL\\Enemy\\L_Leg.x" },		// ENEMY_MODEL15

	{ "data\\MODEL\\Boss\\Hip.x" },		// MODEL1
	{ "data\\MODEL\\Boss\\Body.x" },	// MODEL2
	{ "data\\MODEL\\Boss\\Face.x" },	// MODEL3
	{ "data\\MODEL\\Boss\\R_Arm.x" },	// MODEL4
	{ "data\\MODEL\\Boss\\R_Hand.x" },	// MODEL5
	{ "data\\MODEL\\Boss\\L_Arm.x" },	// MODEL6
	{ "data\\MODEL\\Boss\\L_Hand.x" },	// MODEL7
	{ "data\\MODEL\\Boss\\R_Thigh.x" },	// MODEL8
	{ "data\\MODEL\\Boss\\R_Leg.x" },	// MODEL9
	{ "data\\MODEL\\Boss\\L_Thigh.x" },	// MODEL10
	{ "data\\MODEL\\Boss\\L_Leg.x" },	// MODEL11
};

int CModel::m_Num;
CModel::CModel()
{
	//m_pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}
CModel::~CModel()
{

}
//=========================================================================================================
//����������
//=========================================================================================================
HRESULT CModel:: Init(void)
{

	m_Num;
	int nNumVtx;
	//DWORD dwSizeFVF;
	//BYTE *pVtxBuff;

	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(m_Info[m_Num].pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_dwNumMatModel,
		&m_pMeshModel);

	//���_���̎擾
	nNumVtx = m_pMeshModel->GetNumVertices();

	D3DXMATERIAL *pMat;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_apTEXtureModel[nCntMat]);
		}
	}
	return S_OK;
}

//=========================================================================================================
//�|���S���̏I������
//=========================================================================================================
void CModel:: Uninit(void)
{
	for (int nCntMat = 0; nCntMat < 50; nCntMat++)
	{
		if (m_apTEXtureModel[nCntMat] != nullptr)
		{
			m_apTEXtureModel[nCntMat]->Release();
			m_apTEXtureModel[nCntMat] = nullptr;
		}
	}
	if (m_pMeshModel != nullptr)
	{
		m_pMeshModel->Release();
		m_pMeshModel = nullptr;
	}
	if (m_pBuffMatModel != nullptr)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = nullptr;
	}
}

//=========================================================================================================
//�|���S���̍X�V����
//=========================================================================================================
void CModel:: Update(void)
{
	//CKeyboard *pKeyboard = CManager::GetInputKeyboard();
	//if (pKeyboard->GetPress(DIK_N))
	//{
	//	m_rot.y -= 0.02f;
	//}
	//else if (pKeyboard->GetPress(DIK_M))
	//{
	//	m_rot.y += 0.02f;

	//}
}

//=========================================================================================================
//�|���S���̕`�揈��
//=========================================================================================================
void CModel:: Draw(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans,mtxParts;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{
		mtxParts = GetMtxWorld();

	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParts);
	}
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParts);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_apTEXtureModel[nCntMat]);

		//���f���i�p�[�c�j�̕`��
		m_pMeshModel->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);

}

//====================================================
//���f�����Y����
//====================================================
CModel *CModel::CreateModel( int ModelNum)
{
	m_Num = ModelNum;
	CModel *pObject = nullptr;

	pObject = DBG_NEW CModel;

	pObject->Init();
	

	return pObject;
}

//====================================================
//�ʒu�ݒ菈��
//====================================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//====================================================
//�ʒu�ݒ菈��
//====================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//====================================================
//�ʒu�擾����
//====================================================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}


D3DMATRIX CModel::GetMtxWorld(void)
{
	return m_pParent->m_mtxWorld;
}