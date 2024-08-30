//===========================================================
//
//�`���[�g���A����ʏ���
//Author:�x�씋��
//
//===========================================================

#include "Tutorial.h"
#include "input.h"
#include "Manager.h"
#include "fade.h"

//====================================================
// �R���X�g���N�^
//====================================================
CTutorial::CTutorial()
{

}

//====================================================
// �f�X�g���N�^
//====================================================
CTutorial::~CTutorial()
{

}

//====================================================
// ����������
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
// �I������
//====================================================
void CTutorial::Uninit(void)
{

}

//====================================================
// �X�V����
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
// �`�揈��
//====================================================
void CTutorial::Draw(void)
{

}