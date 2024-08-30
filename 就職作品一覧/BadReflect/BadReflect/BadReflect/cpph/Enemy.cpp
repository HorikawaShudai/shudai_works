//=========================================================================================================
//
//2D��p�̓G�̏���
//Author:�x�씋��
//
//=========================================================================================================
#include "Enemy.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"

#define ENEMY_HEIGHT	(30.0f)	//�G�̉���
#define ENEMY_WIDTH		(30.0f)	//�G�̏c��
#define ENEMY_SPEED		(0.8f)	//�G�̈ړ����x

LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;
D3DXVECTOR3 CEnemy::m_pos = {};
//====================================================
//�R���X�g���N�^
//====================================================
CEnemy::CEnemy()
{
	//m_pos = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	m_move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SetType(TYPE_ENEMY);
	m_pTexture = NULL;
	m_nLife = 1;
}
//====================================================
//�f�X�g���N�^
//====================================================
CEnemy::~CEnemy()
{

}


//====================================================
//�G�̏���������
//====================================================
HRESULT CEnemy::Init(void)
{
	

	CObject2D::Init();


	CTexture *pTexture = CManager::Get()->GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\enemy004.png");

	SetPos(m_pos, ENEMY_HEIGHT, ENEMY_WIDTH);

	return S_OK;
}

//====================================================
//�G�̏I������
//====================================================
void CEnemy::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//====================================================
//�G�̍X�V����
//====================================================
void CEnemy::Update(void)
{
	if (m_nLife <= 0)
	{

		Release();
	}
}

//====================================================
//�G�̕`�揈��
//====================================================
void CEnemy::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//�G�̃q�b�g����
//====================================================
void CEnemy::HitEnemy(int nDamage)
{

}

//====================================================
//�G�̐�������
//====================================================
void CEnemy::Create(D3DXVECTOR3 pos)
{
	m_pos = pos;

	CObject2D::Create();
}