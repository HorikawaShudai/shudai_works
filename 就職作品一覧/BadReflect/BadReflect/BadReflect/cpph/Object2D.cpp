//=========================================================================================================
//
//2D��p�̃|���S���̏���
//Author:�x�씋��
//
//=========================================================================================================
#include "Object2D.h"
#include "Renderer.h"
#include "Manager.h"
#include "Player.h"
#include "Bg.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Effect.h"
#include "Score.h"
#include "Block.h"

const float POLYGON_HEIGHT	(30.0f);
const float POLYGON_WIDTH	(50.0f);

//====================================================
//�R���X�g���N�^
//====================================================
CObject2D::CObject2D(int nPriority):CObject(nPriority)
{
	//m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_moveTex = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//====================================================
//�f�X�g���N�^
//====================================================
CObject2D::~CObject2D()
{

}


//====================================================
//�|���S���̏���������
//====================================================
HRESULT CObject2D::Init(void)
{
	//m_pos = D3DXVECTOR3(640.0f, 600.0f, 0.0f);

	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - POLYGON_HEIGHT, m_pos.y - POLYGON_WIDTH, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + POLYGON_HEIGHT, m_pos.y - POLYGON_WIDTH, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - POLYGON_HEIGHT, m_pos.y + POLYGON_WIDTH, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + POLYGON_HEIGHT, m_pos.y + POLYGON_WIDTH, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

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
//�|���S���̏I������
//====================================================
void CObject2D::Uninit(void)
{
	//if (m_pTexture != nullptr)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = nullptr;
	//}
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//====================================================
//�|���S���̕`�揈��
//====================================================
void CObject2D::Draw(void)
{
	
	CTexture *pTexture = CManager::Get()->GetpTexture();
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	pDevice = pRenderer->GetDevice();
	if (pDevice != nullptr)
	{


		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		pDevice->SetFVF(FVF_VERTEX_2D);

		if (m_TexId != -1)
		{
			pDevice->SetTexture(0, pTexture->GetAddress(m_TexId));
		}
		else
		{
			pDevice->SetTexture(0, nullptr);
		}

		if (m_bAlpha == true)
		{
			//���u�����f�B���O�����Z�����ɐݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		//�|���S��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		if (m_bAlpha == true)
		{
			//���u�����f�B���O����߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}

//====================================================
//�|���S���̍X�V����
//====================================================
void CObject2D::Update(void)
{

}

//====================================================
//�|���S���̈ʒu�̐ݒ�
//====================================================
void CObject2D::SetPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x- Height, m_pos.y- Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x+ Height, m_pos.y- Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x- Height, m_pos.y+ Width, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x+ Height, m_pos.y+ Width, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//====================================================
//�|���S���̈ʒu�̐ݒ�
//====================================================
void CObject2D::SetPlayerPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - Height, m_pos.y - Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + Height, m_pos.y - Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - Height, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + Height, m_pos.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}


//====================================================
//�|���S���̌����̐ݒ�
//====================================================
void CObject2D::SetRot(float rot)
{
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (cosf(D3DX_PI *rot)* POLYGON_HEIGHT), m_pos.y-(cosf(D3DX_PI * rot)* POLYGON_WIDTH), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (cosf(D3DX_PI *rot)* POLYGON_HEIGHT), m_pos.y-(cosf(D3DX_PI * rot)* POLYGON_WIDTH), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (cosf(D3DX_PI *rot)* POLYGON_HEIGHT), m_pos.y+(cosf(D3DX_PI * rot)* POLYGON_WIDTH), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (cosf(D3DX_PI *rot)* POLYGON_HEIGHT), m_pos.y+(cosf(D3DX_PI * rot)* POLYGON_WIDTH), 0.0f);
	float  frot  = sinf(D3DX_PI *rot)* POLYGON_HEIGHT;
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================================
//�I�u�W�F�N�g�̐�������
//====================================================
CObject2D *CObject2D::Create()
{
	CObject2D *pObject2D = nullptr;

	pObject2D = new CObject2D;

	return pObject2D;
}

//====================================================
//�e�N�X�`���̐ݒ菈��
//====================================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//m_pTexture = pTexture;
}

//====================================================
//�e�N�X�`�����W�̐ݒ菈��
//====================================================
void CObject2D::SetAnim(int xCount,int xPuttern,int yCount,int yPuttern)
{
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	

	//�e�N�X�`�����W�̐ݒ� 
	pVtx[0].tex = D3DXVECTOR2(0.0f +            1.0f / xPuttern*xCount, 0.0f			+ 1.0f / yPuttern*yCount);
	pVtx[1].tex = D3DXVECTOR2(1.0f / xPuttern + 1.0f / xPuttern*xCount, 0.0f			+ 1.0f / yPuttern*yCount);
	pVtx[2].tex = D3DXVECTOR2(0.0f +			1.0f / xPuttern*xCount, 1.0f / yPuttern + 1.0f / yPuttern*yCount);
	pVtx[3].tex = D3DXVECTOR2(1.0f / xPuttern + 1.0f / xPuttern*xCount, 1.0f / yPuttern + 1.0f / yPuttern*yCount);
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================================
//�ʒu�̎擾����
//====================================================
D3DXVECTOR3 CObject2D::GetPos(void)
{
	return m_pos;
}

//====================================================
//�e�N�X�`���̎����J��
//====================================================
void CObject2D::AutoScroll(float hMoveTex, float wMoveTex)
{
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ� 
	pVtx[0].tex = D3DXVECTOR2(0.0f + hMoveTex, 0.0f + wMoveTex);
	pVtx[1].tex = D3DXVECTOR2(1.0f + hMoveTex, 0.0f + wMoveTex);
	pVtx[2].tex = D3DXVECTOR2(0.0f + hMoveTex, 1.0f + wMoveTex);
	pVtx[3].tex = D3DXVECTOR2(1.0f + hMoveTex, 1.0f + wMoveTex);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CObject2D::SetSize(float Height, float Width)
{

	VERTEX_2D *pVtx;
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

void CObject2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	pVtx[0].col = D3DXCOLOR(col);
	pVtx[1].col = D3DXCOLOR(col);
	pVtx[2].col = D3DXCOLOR(col);
	pVtx[3].col = D3DXCOLOR(col);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

