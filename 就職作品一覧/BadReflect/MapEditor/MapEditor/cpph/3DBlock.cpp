//===========================================================
//
//3D�u���b�N�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "3DBlock.h"
#include "Renderer.h"
#include "Manager.h"
#include <string.h>


//====================================================
//�ÓI�����o�ϐ��̏�����
//====================================================
C3DBlock::OBJECTINFO C3DBlock::m_ObjectInfo[OBJECT_MODEL_MAX] =
{
	{ "data\\MODEL\\floor.x" },
	{ "data\\MODEL\\train.x" },
	{ "data\\MODEL\\rubble.x" },
};
D3DXVECTOR3 C3DBlock::m_VtxMaxBlock;
D3DXVECTOR3 C3DBlock::m_VtxMinBlock;

//====================================================
//�R���X�g���N�^
//====================================================
C3DBlock::C3DBlock(int nPriority) :CObject3D(nPriority)
{
	//m_pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//====================================================
//�f�X�g���N�^
//====================================================
C3DBlock::~C3DBlock()
{

}

//=========================================================================================================
//����������
//=========================================================================================================
HRESULT C3DBlock::Init(void)
{

	int nNumVtx;
	//DWORD dwSizeFVF;
	//BYTE *pVtxBuff;

	CManager Renderer;
	CRenderer *pRenderer = Renderer.GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(m_ObjectInfo[m_num].pFilename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMatModel,
			NULL,
			&m_dwNumMatModel,
			&m_pMeshModel);

		if (m_type == TYPE_3DBLOCK)
		{
			switch (m_num)
			{
			case OBJECT_MODEL_NUM1:
				SetType(CObject::TYPE_WALLBLOCK);

				break;
			case OBJECT_MODEL_NUM2:
				SetType(CObject::TYPE_OBSTACLEBLOCK);

				break;
			case OBJECT_MODEL_NUM3:
				SetType(CObject::TYPE_RUBBLE);

				break;
			}

		}
		if (m_type == TYPE_EDITBLOCK)
		{
			SetType(CObject::TYPE_EDITBLOCK);
		}
	//���_���̎擾
	nNumVtx = m_pMeshModel->GetNumVertices();

	D3DXMATERIAL *pMat;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_apTEXtureModel[nCntMat]);
		}
	}
	SetObjectSize();
	return S_OK;
}

//=========================================================================================================
//�I������
//=========================================================================================================
void C3DBlock::Uninit(void)
{
	for (int nCntMat = 0; nCntMat < 50; nCntMat++)
	{
		if (m_apTEXtureModel[nCntMat] != NULL)
		{
			m_apTEXtureModel[nCntMat]->Release();
			m_apTEXtureModel[nCntMat] = NULL;
		}
	}
	if (m_pMeshModel != NULL)
	{
		m_pMeshModel->Release();
		m_pMeshModel = NULL;
	}
	if (m_pBuffMatModel != NULL)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = NULL;
	}
}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void C3DBlock::Update(void)
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

	if (m_type != TYPE_EDITBLOCK)
	{

		if (pPos.x > (m_pos.x + m_VtxMinBlock.x) && pPos.x < (m_pos.x + m_VtxMaxBlock.x))
		{
			if (pPos.z < (m_pos.z + m_VtxMaxBlock.z) && pPos.z >(m_pos.z + m_VtxMinBlock.z))
			{
				if (pPos.y - 10.0f < (m_pos.y + m_VtxMaxBlock.y) && pPos.y - 10.0f > (m_pos.y + m_VtxMinBlock.y))
				{
					bInv = true;
				}
				else
				{
					bInv = false;
				}

			}
			else
			{
				bInv = false;
			}

		}
		else
		{
			bInv = false;
		}
	}

	InvisibleBlock();

	

}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void C3DBlock::Draw(void)
{
	CManager Renderer;
	CRenderer *pRenderer = Renderer.GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParts;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0x01);
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->GetTransform(D3DTS_WORLD, &mtxParts);

	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParts);

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
	//pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

}

//====================================================
//���f�����Y����
//====================================================
C3DBlock *C3DBlock::CreateModel( D3DXVECTOR3 pos, int nData, TYPE type3D)
{
	C3DBlock *pObject = NULL;
	
	pObject = new C3DBlock;


	
	if (type3D == CObject::TYPE_EDITBLOCK)
	{
		pObject->m_type = TYPE_EDITBLOCK;
	}
	else
	{
		pObject->m_type = TYPE_3DBLOCK;
	}
	if (nData % OBJECT_MODEL_MAX < 0)
	{
		pObject->m_num = (nData % OBJECT_MODEL_MAX * -1);

	}
	else
	{
		pObject->m_num = nData % OBJECT_MODEL_MAX;

	}
	pObject->Init();
	pObject->m_pos = pos;
	return pObject;
}

//====================================================
//�ʒu�ݒ菈��
//====================================================
void C3DBlock::SetPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;
}

//====================================================
//�ʒu�擾����
//====================================================
D3DXVECTOR3 C3DBlock::GetPos(void)
{
	return m_pos;
}

//=========================================================================================================
//�T�C�Y�̌v�Z����
//=========================================================================================================
void C3DBlock::SetObjectSize(void)
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
		if (vtx.x > m_VtxMaxBlock.x)
		{
			m_VtxMaxBlock.x = vtx.x;
		}
		if (vtx.x < m_VtxMinBlock.x)
		{
			m_VtxMinBlock.x = vtx.x;
		}
		if (vtx.z > m_VtxMaxBlock.z)
		{
			m_VtxMaxBlock.z = vtx.z;
		}
		if (vtx.z < m_VtxMinBlock.z)
		{
			m_VtxMinBlock.z = vtx.z;
		}
		if (vtx.y> m_VtxMaxBlock.y)
		{
			m_VtxMaxBlock.y = vtx.y;
		}
		if (vtx.y < m_VtxMinBlock.y)
		{
			m_VtxMinBlock.y = vtx.y;
		}
		pVtxBuff += dwSizeFVF;
	}
}


//=========================================================================================================
//�v���C���[�Ƃ̓����蔻��
//=========================================================================================================
bool C3DBlock::Colission(D3DXVECTOR3 pos)
{
	bool bHit = false;

	if (pos.x > (m_pos.x + m_VtxMinBlock.x) &&pos.x < (m_pos.x + m_VtxMaxBlock.x))
	{
		if (pos.z < (m_pos.z + m_VtxMaxBlock.z) && pos.z > (m_pos.z + m_VtxMinBlock.z))
		{
			if (pos.y < (m_pos.y + m_VtxMaxBlock.y) && pos.y > (m_pos.y + m_VtxMinBlock.y))
			{
				bHit = true;
			}

		}
	}

	return bHit;
}

//====================================================
//�u���b�N�̍폜����
//====================================================
void C3DBlock::DeleateBlock(D3DXVECTOR3 pos)
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
				if (type == CObject::TYPE_WALLBLOCK || type == CObject::TYPE_OBSTACLEBLOCK || type == CObject::TYPE_RUBBLE)
				{
					pPos = pObj->GetPos();
					if (pObj != NULL)
					{
						if (pos.x > (pPos.x + m_VtxMinBlock.x) && pos.x < (pPos.x + m_VtxMaxBlock.x))
						{
							if (pos.z < (pPos.z + m_VtxMaxBlock.z) && pos.z >(pPos.z + m_VtxMinBlock.z))
							{
								if (pos.y - 10.0f < (pPos.y + m_VtxMaxBlock.y) && pos.y - 10.0f >(pPos.y + m_VtxMinBlock.y))
								{
									pObj->Release();
									break;
								}

							}
						}
					}
				}

			}
		}
	}

	
}

//====================================================
//������������
//====================================================
void C3DBlock::InvisibleBlock(void)
{
	
	CManager Renderer;
	CRenderer *pRenderer = Renderer.GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	switch (bInv)
	{
	case true:
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
			pMat->MatD3D.Diffuse = { 1.0f,0.0f,0.0f,0.5f };
		}
		pDevice->SetMaterial(&matDef);

		break;
	case false:
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
			pMat->MatD3D.Diffuse = { 1.0f,1.0f,1.0f,1.0f };
		}
		pDevice->SetMaterial(&matDef);

		break;
	}
}