//===========================================================
//
//�n�ʂ̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Field.h"
#include "Renderer.h"
#include "Manager.h"
#include "Texture.h"

//====================================================
//�ÓI�����o�ϐ��̏�����
//====================================================
LPDIRECT3DTEXTURE9 CField::m_pTexture = NULL;

//====================================================
//�R���X�g���N�^
//====================================================
CField::CField(int nPriority) :CObject3D(nPriority)
{

}
//====================================================
//�f�X�g���N�^
//====================================================
CField::~CField()
{

}
//=========================================================================================================
//����������
//=========================================================================================================
HRESULT CField::Init(void)
{

	CObject3D::Init();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�n�ʂ�ݒu
	SetPos(m_pos, FIELF_SIZE, FIELF_SIZE);

	CTexture *pTexture = CManager::GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\tuti001.jpg");
	return S_OK;

}

//=========================================================================================================
//�I������
//=========================================================================================================
void CField:: Uninit(void)
{

}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void CField:: Update(void)
{

}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void CField::Draw(void)
{
	CManager Renderer;
	CRenderer *pRenderer = Renderer.GetRenderer();
	CTexture *pTexture = CManager::GetpTexture();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);


	pDevice->SetTexture(0, pTexture->GetAddress(m_TexId));

	//�n��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//====================================================
//�e�N�X�`���̍폜
//====================================================
void CField::UnLoad(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
