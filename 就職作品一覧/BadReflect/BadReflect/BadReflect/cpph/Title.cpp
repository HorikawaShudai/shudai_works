//===========================================================
//
//タイトル画面処理
//Author:堀川萩大
//
//===========================================================

#include "Title.h"
#include "input.h"
#include "Manager.h"
#include "Object2D.h"
#include "fade.h"
#include "sound.h"

//====================================================
// コンストラクタ
//====================================================

CTitle::CTitle()
{
	m_pLogo = nullptr;
	m_pButton = nullptr;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fadespeed = -FADESPEED;
}
//====================================================
// デストラクタ
//====================================================
CTitle::~CTitle()
{

}

//====================================================
// タイトルの初期化処理
//====================================================
HRESULT CTitle::Init(void)
{
	CTexture* pTexture;
	pTexture = CManager::Get()->GetpTexture();

	if (m_pLogo == nullptr)
	{
		m_pLogo = CObject2D::Create();

		m_pLogo->Init();
		m_pLogo->SetAlpha(false);
		m_pLogo->BindTexture(pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\Title\\TitleLogo.png")));
		m_pLogo->SetTexId(pTexture->Regist("data\\TEXTURE\\Title\\TitleLogo.png"));
		m_pLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pLogo->SetPos(D3DXVECTOR3(SCREEN_HEIGHT / 2, 200.0f, 0.0f), 300.0f, 200.0f);

	}
	if (m_pButton == nullptr)
	{
		m_pButton = CObject2D::Create();

		m_pButton->Init();
		m_pButton->SetAlpha(false);
		m_pButton->BindTexture(pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\Title\\startlogo.png")));
		m_pButton->SetTexId(pTexture->Regist("data\\TEXTURE\\Title\\startlogo.png"));
		m_pButton->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pButton->SetPos(D3DXVECTOR3(SCREEN_HEIGHT / 2, 500.0f, 0.0f), 400.0f, 40);

	}


	CSound::Play(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CTitle::Uninit(void)
{
	if (m_pLogo != nullptr)
	{
		m_pLogo->Release();
		m_pLogo = nullptr;
	}
	if (m_pButton != nullptr)
	{
		m_pButton->Release();
		m_pButton = nullptr;
	}

	CObject::ModeRelease(CObject::MODE_OBJECT::MODE_OBJECT_TITLE);

	CSound::StopSound();
}

//====================================================
// 更新処理
//====================================================
void CTitle::Update(void)
{
	CKeyboard* pKeyboard = CManager::Get()->GetInputKeyboard();

	CFade* pFade = CManager::Get()->GetpFade();

	changecol();

	CFade::FADE StateFade;
	StateFade = pFade->GetFade();
	if (pKeyboard->GetTrigger(DIK_RETURN) == true && StateFade == CFade::FADE_NONE)
	{
		m_fadespeed = SELECTFADESPEED;
		pFade->SetFade(CScene::MODE_GAME, 0.1f);
	}
}
//====================================================
// 描画処理
//====================================================
void CTitle::Draw(void)
{
	if (m_pLogo != nullptr)
	{
		m_pLogo->Draw();
	}
	if (m_pButton != nullptr)
	{
		m_pButton->Draw();
	}
}

void CTitle::changecol(void)
{

	if (CManager::Get()->GetpFade()->GetFade() == CFade::FADE_OUT)
	{
		m_col.a += m_fadespeed;
		if (m_col.a <= 0.0f && m_fadespeed == -SELECTFADESPEED)
		{
			m_fadespeed = SELECTFADESPEED;
		}
		else if (m_col.a >= 1.0f && m_fadespeed == SELECTFADESPEED)
		{
			m_fadespeed = -SELECTFADESPEED;
		}
		m_pButton->SetCol(m_col);

	}
	else
	{
		if (m_fadestop <= 0)
		{
			m_col.a += m_fadespeed;
			if (m_col.a <= 0.0f && m_fadespeed == -FADESPEED)
			{
				m_fadespeed = FADESPEED;
			}
			else if (m_col.a >= 1.0f && m_fadespeed == FADESPEED)
			{
				m_fadestop = 120;
				m_fadespeed = -FADESPEED;
			}
			m_pButton->SetCol(m_col);
		}
		else
		{
			m_fadestop--;
		}
	}
}
