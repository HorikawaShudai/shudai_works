//===========================================================
//
//ゲーム画面処理
//Author:堀川萩大
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
//静的メンバ変数の初期化
//====================================================
int  CGame::m_nCnt =0;
CScore* CGame::m_pScore = nullptr;


//====================================================
// コンストラクタ
//====================================================
CGame::CGame()
{

}

//====================================================
// デストラクタ
//====================================================
CGame::~CGame()
{

}

//====================================================
// 初期化処理
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
// 終了処理
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
// 更新処理
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
// 描画処理
//====================================================
void CGame::Draw(void)
{
	if (m_pScore != nullptr)
	{
		m_pScore->Draw();
	}
}