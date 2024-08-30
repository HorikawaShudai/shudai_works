//===========================================================
//
//フェードの処理
//Author:堀川萩大
//
//===========================================================
#include "fade.h"
#include "main.h"
#include "game.h"
#include "Renderer.h"
//#include "sound.h"

//====================================================
// コンストラクタ
//====================================================
CFade::CFade()
{
	m_pPoly = nullptr;
}
//====================================================
// デストラクタ
//====================================================
CFade::~CFade()
{

}

//====================================================
// 初期化処理
//====================================================
HRESULT CFade::Init(void)
{
	
	m_Fade = FADE_NONE;
	m_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_pPoly = CObject2D::Create();
	m_pPoly->SetModeobject(CObject::MODE_OBJECT_SETTING);
	if (m_pPoly != nullptr)
	{
		m_pPoly->Init();
		m_pPoly->SetAlpha(false);
		m_pPoly->SetCol(m_ColorFade);
		m_pPoly->SetSize(1280.0f, 720.0f);
		m_pPoly->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f),1280.0f, 720.0f);
	}
	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CFade::Uninit(void)
{
	m_pPoly = nullptr;
}

//====================================================
// 更新処理
//====================================================
void CFade::Update(void)
{
	if (m_Fade != FADE_NONE)
	{
		if (m_Fade == FADE_IN)
		{
			m_ColorFade.a -= 0.05f;
			if (m_ColorFade.a <= 0.0f)
			{
				m_ColorFade.a = 0.0f;
				m_Fade = FADE_NONE;
			}
		}
		else if (m_Fade == FADE_OUT)
		{
			m_ColorFade.a += 0.01f;
			if (m_ColorFade.a >= 1.0f)
			{
				m_ColorFade.a = 1.0f;
				m_Fade = FADE_IN;
				CManager::Get()->SetMode(m_ModeNext);
			}
		}
		if (m_pPoly != nullptr)
		{
			m_pPoly->SetCol(m_ColorFade);
		}
	}
}

//====================================================
// 描画処理
//====================================================
void CFade::Draw(void)
{
	if (m_pPoly != nullptr)
	{
		m_pPoly->Draw();
	}
}

//====================================================
// 設定処理
//====================================================
void CFade::SetFade(CScene::MODE ModeNext, float Fade)
{
	m_Fade = FADE_OUT;
	m_FadeCount = Fade;
	m_ModeNext = ModeNext;
	m_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//====================================================
// 状態取得
//====================================================
CFade::FADE CFade::GetFade(void)
{
	return m_Fade;
}

//====================================================
// 生成処理
//====================================================
CFade *CFade::Create(void)
{
	CFade *pObject = NULL;

	pObject = DBG_NEW CFade;
	pObject->Init();

	return pObject;
}