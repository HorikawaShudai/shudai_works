//===========================================================
//
//ƒ^ƒCƒgƒ‹‰æ–Êˆ—
//Author:–xì”‹‘å
//
//===========================================================

#include "Result.h"
#include "input.h"
#include "Manager.h"
#include "fade.h"
#include "Ranking.h"

CResult::CResult()
{
	m_pPoly = nullptr;
}
CResult::~CResult()
{

}

HRESULT CResult::Init(void)
{
	m_pPoly = CObject2D::Create();
	if (m_pPoly != nullptr)
	{
		m_pPoly->Init();
		m_pPoly->SetAlpha(false);
		m_pPoly->SetCol(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		m_pPoly->SetSize(1280.0f, 720.0f);
	}

	return S_OK;
}
void CResult::Uninit(void)
{
	CRanking::LordScore();
}
void CResult::Update(void)
{
	CKeyboard *pKeyboard = CManager::Get()->GetInputKeyboard();

	CFade *pFade = CManager::Get()->GetpFade();

	CFade::FADE StateFade;
	StateFade = pFade->GetFade();
	if (pKeyboard->GetTrigger(DIK_RETURN) == true && StateFade == CFade::FADE_NONE)
	{

		pFade->SetFade(CScene::MODE_TITLE, 0.001f);
	}
}
void CResult::Draw(void)
{
	if (m_pPoly != nullptr)
	{
		m_pPoly->Draw();
	}
}