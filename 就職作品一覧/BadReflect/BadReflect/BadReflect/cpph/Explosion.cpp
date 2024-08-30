//=========================================================================================================
//
//2D��p�̔����̏���
//Author:�x�씋��
//
//=========================================================================================================
#include "Explosion.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Player.h"

#define BULLET_HEIGHT	(30.0f)
#define BULLET_WIDTH	(30.0f)

D3DXVECTOR3 CExplosion::m_pos;
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture;
//====================================================
//�R���X�g���N�^
//====================================================
CExplosion::CExplosion()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;
	m_nCntPattern = 0;

}
//====================================================
//�f�X�g���N�^
//====================================================
CExplosion::~CExplosion()
{

}


//====================================================
//�����̏���������
//====================================================
HRESULT CExplosion::Init(void)
{

	CObject2D::Init();


	m_move = D3DXVECTOR3(5.0f, 0.0f, 0.0f);

	SetPos(m_pos, BULLET_HEIGHT, BULLET_WIDTH);

	CTexture *pTexture = CManager::Get()->GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\explosion000.png");

	SetAnim(m_nCntPattern, 8, 0, 1);
	SetType(TYPE_EXPLOSION);


	return S_OK;
}

//====================================================
//�����̏I������
//====================================================
void CExplosion::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//====================================================
//�����̍X�V����
//====================================================
void CExplosion::Update(void)
{
	m_nCntAnim++;
	if (m_nCntAnim % 10 == 0)
	{
		m_nCntPattern++;
		SetAnim(m_nCntPattern,8,0,1);
	}
	if (m_nCntPattern > 8)
	{
		Release();
	}
}

//====================================================
//�����̕`�揈��
//====================================================
void CExplosion::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//�����̐�������
//====================================================
void CExplosion::Create(D3DXVECTOR3 pos)
{
	m_pos = pos;

	CObject2D::Create();

}
