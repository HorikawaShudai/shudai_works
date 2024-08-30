//=========================================================================================================
//
//3D��p�̃I�u�W�F�N�g�̏���
//Author:�x�씋��
//
//=========================================================================================================
#include "Object3D.h"
#include "Renderer.h"
#include "Manager.h"
#include "3DBlock.h"

#define POLYGON_HEIGHT	(30.0f)
#define POLYGON_WIDTH	(50.0f)

//====================================================
//�R���X�g���N�^
//====================================================
CObject3D::CObject3D(int nPriority) :CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
}
//====================================================
//�f�X�g���N�^
//====================================================
CObject3D::~CObject3D()
{

}


//====================================================
//�I�u�W�F�N�g�̏���������
//====================================================
HRESULT CObject3D::Init(void)
{
	CManager Renderer;
	CRenderer *pRenderer = Renderer.GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	pVtx[0].pos = D3DXVECTOR3(-FIELF_SIZE, 0.0f, +FIELF_SIZE);
	pVtx[1].pos = D3DXVECTOR3(+FIELF_SIZE, 0.0f, +FIELF_SIZE);
	pVtx[2].pos = D3DXVECTOR3(-FIELF_SIZE, 0.0f, -FIELF_SIZE);
	pVtx[3].pos = D3DXVECTOR3(+FIELF_SIZE, 0.0f, -FIELF_SIZE);

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

//====================================================
//�I�u�W�F�N�g�̏I������
//====================================================
void CObject3D::Uninit(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//====================================================
//�I�u�W�F�N�g�̕`�揈��
//====================================================
void CObject3D::Draw(void)
{

}

//====================================================
//�I�u�W�F�N�g�̍X�V����
//====================================================
void CObject3D::Update(void)
{

}

//====================================================
//�I�u�W�F�N�g�̈ʒu�̐ݒ�
//====================================================
void CObject3D::SetPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - Height, m_pos.y , m_pos.z + Width);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + Height, m_pos.y, m_pos.z + Width);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - Height, m_pos.y, m_pos.z - Width);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + Height, m_pos.y, m_pos.z - Width);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================================
//�I�u�W�F�N�g�̐�������
//====================================================
CObject3D *CObject3D::Create(D3DXVECTOR3 pPos,TYPE type3D,int nDate)
{
	CObject3D *pObject3D = NULL;

	switch (type3D)
	{
	case TYPE_FIELD:
		pObject3D = new CField;

		pObject3D->Init();
		break;
	case TYPE_3DBLOCK:
		pObject3D = C3DBlock::CreateModel(pPos, nDate, TYPE_3DBLOCK);
		pObject3D->Init();
		break;
	case TYPE_PLAYER:
		pObject3D = CPlayer3D::Create();
		pObject3D->Init();
		break;
	case TYPE_EDITBLOCK:
		pObject3D = C3DBlock::CreateModel(pPos, nDate,TYPE_EDITBLOCK);
		pObject3D->Init();
		break;
	}


	return pObject3D;
}

//====================================================
//�e�N�X�`���̐ݒ菈��
//====================================================
void CObject3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//====================================================
//�T�C�Y�̐ݒ菈��
//====================================================
void CObject3D::SetSize(float Height, float Width)
{

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - Height, m_pos.y - Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + Height, m_pos.y - Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - Height, m_pos.y + Width, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + Height, m_pos.y + Width, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================================
//�擾����
//====================================================
D3DXVECTOR3 CObject3D::GetPos(void)
{
	return m_pos;
}