//===========================================================
//
//チュートリアル画面処理
//Author:堀川萩大
//
//===========================================================

#include "Tutorial.h"
#include "input.h"
#include "Manager.h"
#include "fade.h"

//====================================================
// コンストラクタ
//====================================================
CTutorial::CTutorial()
{

}

//====================================================
// デストラクタ
//====================================================
CTutorial::~CTutorial()
{

}

//====================================================
// 初期化処理
//====================================================
HRESULT CTutorial::Init(void)
{
	m_pPoly = CObject2D::Create();
	if (m_pPoly != nullptr)
	{
		m_pPoly->Init();
		m_pPoly->SetAlpha(false);
		m_pPoly->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pPoly->SetSize(1280.0f, 720.0f);
	}

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CTutorial::Uninit(void)
{

}

//====================================================
// 更新処理
//====================================================
void CTutorial::Update(void)
{
	CKeyboard *pKeyboard = CManager::Get()->GetInputKeyboard();

	CFade *pFade = CManager::Get()->GetpFade();

	CFade::FADE StateFade;
	StateFade = pFade->GetFade();
	if (pKeyboard->GetTrigger(DIK_RETURN) == true && StateFade == CFade::FADE_NONE)
	{

		pFade->SetFade(CScene::MODE_GAME, 0.001f);
	}
}

//====================================================
// 描画処理
//====================================================
void CTutorial::Draw(void)
{

}