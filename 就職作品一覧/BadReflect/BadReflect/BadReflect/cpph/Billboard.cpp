//===========================================================
//
//�r���{�[�h�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Billboard.h"
#include "Renderer.h"
#include "Manager.h"
#include "Texture.h"



CBillboard::CBillboard()
{

}
CBillboard::~CBillboard()
{

}
//=========================================================================================================
//����������
//=========================================================================================================
HRESULT CBillboard::Init(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = D3DXVECTOR3(-200.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Height, m_pos.y+m_Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Height, m_pos.y+m_Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Height, m_pos.y-m_Width, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Height, m_pos.y-m_Width, 0.0f);

	//nor�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=========================================================================================================
//�r���{�[�h�̏I������
//=========================================================================================================
void CBillboard::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//=========================================================================================================
//�r���{�[�h�̍X�V����
//=========================================================================================================
void CBillboard::Update(void)
{
}

//=========================================================================================================
//�r���{�[�h�̕`�揈��
//=========================================================================================================
void CBillboard::Draw(void)
{
	
	CTexture *pTexture = CManager::Get()->GetpTexture();
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�̎擾�p

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
	
	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);

	if (m_TexId != -1)
	{
		pDevice->SetTexture(0, pTexture->GetAddress(m_TexId));
	}
	else
	{
		pDevice->SetTexture(0, nullptr);
	}

	//�r���{�[�h
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

CObject *CBillboard::CreateBillboard(void)
{
	CObject *pObject = NULL;

	pObject = DBG_NEW CBillboard;
	pObject->Init();

	return pObject;
}
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Height, m_pos.y + m_Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Height, m_pos.y + m_Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Height, m_pos.y - m_Width, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Height, m_pos.y - m_Width, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CBillboard::SetSize(float x, float y)
{
	m_Height = x;
	m_Width = y;

	VERTEX_3D* pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x-m_Height, m_pos.y+m_Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x+m_Height, m_pos.y+m_Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x-m_Height, m_pos.y-m_Width, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x+m_Height, m_pos.y-m_Width, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

D3DXVECTOR3 CBillboard::GetPos(void)
{
	return m_pos;
}
