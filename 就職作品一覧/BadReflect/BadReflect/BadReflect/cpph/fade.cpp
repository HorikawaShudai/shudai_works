//===========================================================
//
//�t�F�[�h�̏���
//Author:�x�씋��
//
//===========================================================
#include "fade.h"
#include "main.h"
#include "game.h"
#include "Renderer.h"
//#include "sound.h"

//====================================================
// �R���X�g���N�^
//====================================================
CFade::CFade()
{
	m_pPoly = nullptr;
}
//====================================================
// �f�X�g���N�^
//====================================================
CFade::~CFade()
{

}

//====================================================
// ����������
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
// �I������
//====================================================
void CFade::Uninit(void)
{
	m_pPoly = nullptr;
}

//====================================================
// �X�V����
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
// �`�揈��
//====================================================
void CFade::Draw(void)
{
	if (m_pPoly != nullptr)
	{
		m_pPoly->Draw();
	}
}

//====================================================
// �ݒ菈��
//====================================================
void CFade::SetFade(CScene::MODE ModeNext, float Fade)
{
	m_Fade = FADE_OUT;
	m_FadeCount = Fade;
	m_ModeNext = ModeNext;
	m_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//====================================================
// ��Ԏ擾
//====================================================
CFade::FADE CFade::GetFade(void)
{
	return m_Fade;
}

//====================================================
// ��������
//====================================================
CFade *CFade::Create(void)
{
	CFade *pObject = NULL;

	pObject = DBG_NEW CFade;
	pObject->Init();

	return pObject;
}