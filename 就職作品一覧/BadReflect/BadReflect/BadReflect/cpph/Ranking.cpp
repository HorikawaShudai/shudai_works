//===========================================================
//
//スコアの処理操作
//Author:堀川萩大
//
//===========================================================
#include <stdio.h>
#include "game.h"
#include "Ranking.h"
#include "score.h"
#include "input.h"
#include "fade.h"
#include "Renderer.h"


CScore *CRanking::m_pScore[NUM_RANKING];
int CRanking::g_nTitleCnt;
int CRanking::m_rank[NUM_RANKUI];

CRanking::CRanking()
{
	for (int nCnt = 0; nCnt < NUM_RANKUI; nCnt++)
	{
		m_rankUi[nCnt] = nullptr;
	}
}
CRanking::~CRanking()
{

}
//=========================================================================================================
//初期化処理
//=========================================================================================================
HRESULT CRanking::Init(void)
{
	CSound::Play(CSound::SOUND_LABEL_BGM001);
	
	g_nTitleCnt =0;


	LordScore();
	for (int nCnt = 0; nCnt < NUM_RANKUI; nCnt++)
	{
		if (m_rankUi[nCnt] == nullptr)
		{
			CTexture* pTexture = CManager::Get()->GetpTexture();

			m_rankUi[nCnt] = CObject2D::Create();

			m_rankUi[nCnt]->Init();
			m_rankUi[nCnt]->SetAlpha(false);
			switch (m_rank[nCnt])
			{
			case 0:
				m_rankUi[nCnt]->BindTexture(pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\Ranking\\1st.png")));
				m_rankUi[nCnt]->SetTexId(pTexture->Regist("data\\TEXTURE\\Ranking\\1st.png"));
				break;
			case 1:
				m_rankUi[nCnt]->BindTexture(pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\Ranking\\2nd.png")));
				m_rankUi[nCnt]->SetTexId(pTexture->Regist("data\\TEXTURE\\Ranking\\2nd.png"));
				break;
			case 2:
				m_rankUi[nCnt]->BindTexture(pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\Ranking\\3rd.png")));
				m_rankUi[nCnt]->SetTexId(pTexture->Regist("data\\TEXTURE\\Ranking\\3rd.png"));
				break;
			case 3:
				m_rankUi[nCnt]->BindTexture(pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\Ranking\\4th.png")));
				m_rankUi[nCnt]->SetTexId(pTexture->Regist("data\\TEXTURE\\Ranking\\4th.png"));
				break;
			case 4:
				m_rankUi[nCnt]->BindTexture(pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\Ranking\\5th.png")));
				m_rankUi[nCnt]->SetTexId(pTexture->Regist("data\\TEXTURE\\Ranking\\5th.png"));
				break;
			}
			m_rankUi[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_rankUi[nCnt]->SetPos(D3DXVECTOR3(400.0f, 50.0f + (50.0f * nCnt),0.0f), 50.0f, 35.0f);
			m_rankUi[nCnt]->SetModeobject(CObject::MODE_OBJECT_NONE);
		}
	}
	return S_OK;
}

//=========================================================================================================
//終了処理
//=========================================================================================================
void CRanking::Uninit(void)
{
	for (int nCount = 0; nCount < NUM_RANKING; nCount++)
	{
		if (m_pScore[nCount] != nullptr)
		{
			m_pScore[nCount]->Release();
			m_pScore[nCount] = nullptr;
		}
		if (nCount < NUM_RANKUI)
		{
			if (m_rankUi[nCount] != nullptr)
			{
				m_rankUi[nCount]->Release();
				m_rankUi[nCount] = nullptr;
			}
		}
	}
		
	//サウンドの停止
	CSound::StopSound();

}

//=========================================================================================================
//更新処理
//=========================================================================================================
void CRanking::Update(void)
{
	g_nTitleCnt++;
	CKeyboard* pKeyboard = CManager::Get()->GetInputKeyboard();

	CFade* pFade = CManager::Get()->GetpFade();

	CFade::FADE StateFade;
	StateFade = pFade->GetFade();
	if (pKeyboard->GetTrigger(DIK_RETURN) == true && StateFade == CFade::FADE_NONE)
	{
		pFade->SetFade(CScene::MODE_TITLE, 0.001f);

	}
	if (g_nTitleCnt > 3000 && StateFade == CFade::FADE_NONE)
	{
		pFade->SetFade(CScene::MODE_TITLE, 0.001f);

	}
	if (m_pScore[5] != nullptr)
	{
		m_pScore[5]->FadeScore();

	}
}

//=========================================================================================================
//描画処理
//=========================================================================================================
void CRanking::Draw(void)
{
	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		if (m_pScore[nCnt] != nullptr)
		{
			m_pScore[nCnt]->Draw();

		}
	}
	for (int nCnt = 0; nCnt < NUM_RANKUI; nCnt++)
	{
		if (m_rankUi[nCnt] != nullptr)
		{
			m_rankUi[nCnt]->Draw();
		}
	}

}

void CRanking::LordScore(void)
{
	int aScore[6] = {};
	FILE *pFile;
	pFile = fopen("data\\TEXT\\Score.txt", "r");
	if (pFile != NULL)
	{
		for (int nCount = 0; nCount < 6; nCount++)
		{
			fscanf(pFile, "%d", &aScore[nCount]);
		}
		fclose(pFile);
	}
	else
	{

	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		m_pScore[nCnt] = CScore::pCreate(D3DXVECTOR3(500.0f, 50.0f + (50.0f * nCnt), 0.0f));
		m_pScore[nCnt]->SetScore(aScore[nCnt]);
	}
	m_pScore[5] = CScore::pCreate(D3DXVECTOR3(500.0f, 500.0f, 0.0f));
	m_pScore[5]->SetScore(aScore[5]);
	
	int nRank = 0;
	for (int nCnt = 0; nCnt < NUM_RANKUI; nCnt++)
	{
		if (nCnt == 0)
		{
			m_rank[nCnt] = nRank;
		}
		else
		{
			if (aScore[nCnt] == aScore[nCnt - 1])
			{
				m_rank[nCnt] = m_rank[nCnt - 1];
			}
			else
			{
				m_rank[nCnt] = nRank;
			}
		}
		nRank++;
	}
}