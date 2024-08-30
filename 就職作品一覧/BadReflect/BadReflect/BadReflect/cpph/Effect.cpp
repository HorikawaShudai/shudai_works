//===========================================================
//
//�G�t�F�N�g�̏�������
//Author:�x�씋��
//
//===========================================================
#include "Effect.h"
#include "Player.h"
#include "Renderer.h"
#include "Manager.h"
#include "Billboard.h"

LPDIRECT3DTEXTURE9 CEffect::m_pTexture = nullptr;

//====================================================
//�R���X�g���N�^
//====================================================
CEffect::CEffect(int nPriority)
{
	m_fRadius = 10.0f;
	m_nLife = 80;
	m_col = D3DXCOLOR(0.2f,0.0f,1.0f,1.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//====================================================
//�f�X�g���N�^
//====================================================
CEffect::~CEffect()
{

}

//=========================================================================================================
//����������
//=========================================================================================================
HRESULT CEffect::Init(void)
{

	CBillboard::Init();
	SetType(TYPE_EFFECT);
	return S_OK;

}

//=========================================================================================================
//�I������
//=========================================================================================================
void CEffect::Uninit(void)
{

}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void CEffect::Update(void)
{
	//m_fRadius -= 0.01f;
	m_col.a -= 0.008f;
	SetSize( m_fRadius, m_fRadius);
	//SetCol(m_col);

	m_nLife--;
	if (m_nLife <= 0 || m_fRadius <= 0.0f || m_col.a <=0.0f)
	{
		//Release();
	}
}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void CEffect::Draw(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();


	//���u�����f�B���O����߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//====================================================
//�G�t�F�N�g�̐�������
//====================================================
CEffect* CEffect::Create(D3DXVECTOR3 pos)
{
	CEffect* pObject;
	pObject = new CEffect;
	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetPos(pos);
		return pObject;
	}
}