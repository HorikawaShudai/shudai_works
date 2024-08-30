//===========================================================
//
//�Q�[����ʏ���
//Author:�x�씋��
//
//===========================================================

#include "Game.h"
#include "input.h"
#include "Manager.h"
#include "Score.h"
#include "fade.h"
#include "Manager.h"
#include "sound.h"
#include "Object.h"

//====================================================
//�ÓI�����o�ϐ��̏�����
//====================================================
int  CGame::m_nCnt =0;
CScore* CGame::m_pScore = nullptr;


//====================================================
// �R���X�g���N�^
//====================================================
CGame::CGame()
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CGame::~CGame()
{

}

//====================================================
// ����������
//====================================================
HRESULT CGame::Init(void)
{
	CGame::m_nCnt = 0;
	//m_pPause = CPause::Create();
	//CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),1.0f, CObject::TYPE_CYLINDER,0);
	CObject::LoadMap();
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),1.0f, CObject::TYPE_PLAYER,0);
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, CObject::TYPE_FIELD,0);
	m_pScore = CScore::pCreate(D3DXVECTOR3(1020.0f, 80.0f, 0.0f));
	m_pScore->SetScore(0);
	m_pScore->SetModeobject(CObject::MODE_OBJECT_NONE);
	CSound::Play(CSound::SOUND_LABEL_BGM001);

	return S_OK;
}

//====================================================
// �I������
//====================================================
void CGame::Uninit(void)
{
	if (m_pScore != nullptr)
	{
		m_pScore->Release();
		m_pScore = nullptr;
	
	}
	CObject::ModeRelease(CObject::MODE_OBJECT::MODE_OBJECT_GAME);

	CSound::StopSound();
	CManager::Get()->SetPause(false);
}

//====================================================
// �X�V����
//====================================================
void CGame::Update(void)
{
	CFade *pFade = CManager::Get()->GetpFade();
	if (CManager::Get()->GetPause() == false)
	{
		m_nCnt++;
		if (m_nCnt % 240 == 0 && m_nCnt != 0)
		{
			float randPosX, randPosZ;
			randPosX = float(rand() % 901);
			randPosZ = float(rand() % 861);
			CObject3D::Create(D3DXVECTOR3(randPosX - 450.0f, 0.0f, randPosZ - 430.f), 1.0f, CObject::TYPE_ENEMY, 0);
		}
	}
}

//====================================================
// �`�揈��
//====================================================
void CGame::Draw(void)
{
	if (m_pScore != nullptr)
	{
		m_pScore->Draw();
	}
}