//===========================================================
//
//ポーズメニューの処理操作
//Author:堀川萩大
//
//===========================================================
#include "pause.h"
#include "game.h"
#include "Input.h"
#include "fade.h"
#include "Renderer.h"
#include "Manager.h"

CPause::CPause(int nPriority)
{
	m_pPauseBg = nullptr;
	for (int nCnt = 0; nCnt < PAUSE_MAX; nCnt++)
	{
		m_pPauseObject[nCnt] = nullptr;
	}
}
CPause::~CPause()
{

}

//=================================================
// 初期化処理
//=================================================
HRESULT CPause::Init(void)
{
	CTexture* pTexture;
	pTexture = CManager::Get()->GetpTexture();

	PauseMenu = PAUSE_CONTENU;
	ColSelect = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	ColNoSelect = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);


	m_pPauseBg = CObject2D::Create();
	m_pPauseBg->Init();
	m_pPauseBg->SetAlpha(false);
	m_pPauseBg->BindTexture(pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\pause200.png")));
	m_pPauseBg->SetTexId(pTexture->Regist("data\\TEXTURE\\pause200.png"));
	m_pPauseBg->SetCol(ColSelect);
	m_pPauseBg->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f), 240.0f,220.0f);
	m_pPauseBg->SetType(CObject::TYPE_PAUSE);
	m_pPauseBg->SetModeobject(CObject::MODE_OBJECT_SETTING);


	for (int nCnt = 0; nCnt < PAUSE_MAX; nCnt++)
	{
		m_pPauseObject[nCnt] = CObject2D::Create();
		m_pPauseObject[nCnt]->Init();
		m_pPauseObject[nCnt]->SetAlpha(false);

		switch (nCnt)
		{
		case PAUSE_CONTENU:
			m_pPauseObject[nCnt]->BindTexture(pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\pause000.png")));
			m_pPauseObject[nCnt]->SetTexId(pTexture->Regist("data\\TEXTURE\\pause000.png"));
			break;
		case PAUSE_RETRY:
			m_pPauseObject[nCnt]->BindTexture(pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\pause001.png")));
			m_pPauseObject[nCnt]->SetTexId(pTexture->Regist("data\\TEXTURE\\pause001.png"));
			break;
		case PAUSE_QUIT:
			m_pPauseObject[nCnt]->BindTexture(pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\pause002.png")));
			m_pPauseObject[nCnt]->SetTexId(pTexture->Regist("data\\TEXTURE\\pause002.png"));
			break;
		}

		if(nCnt == PauseMenu)
		{
			m_pPauseObject[nCnt]->SetCol(ColSelect);
		}
		else
		{
			m_pPauseObject[nCnt]->SetCol(ColNoSelect);
		}
		m_pPauseObject[nCnt]->SetPos(D3DXVECTOR3(630.0f, (280.0f + (80.0f*nCnt)), 0.0f), 200.0f, 20.0f);
		m_pPauseObject[nCnt]->SetType(CObject::TYPE_PAUSE);
		m_pPauseObject[nCnt]->SetModeobject(CObject::MODE_OBJECT_SETTING);
	}

	return S_OK;
}

//=================================================
// 終了処理
//=================================================
void CPause::Uninit(void)
{
	int nCnt;
	for (nCnt = 0; nCnt < NUM_PAUSE; nCnt++)
	{
		if (m_pPauseObject[nCnt] != nullptr)
		{
			m_pPauseObject[nCnt]->Release();
			m_pPauseObject[nCnt] = nullptr;
		}
	}
	if (m_pPauseBg != nullptr)
	{
		m_pPauseBg->Release();
		m_pPauseBg = nullptr;
	}
}

//=================================================
// 更新処理
//=================================================
void CPause::Update(void)
{
	bool bPouse = CManager::GetPause();

	CFade *pFade = CManager::Get()->GetpFade();

	CFade::FADE StateFade;
	StateFade = pFade->GetFade();
	
	CKeyboard *pKeyboard = CManager::Get()->GetInputKeyboard();

	if (CManager::Get()->GetMode() == CScene::MODE_GAME)
	{


		if (pKeyboard->GetTrigger(DIK_P) == true && StateFade == CFade::FADE_NONE)
		{
			if (!m_PressP)
			{
				switch (CManager::GetPause())
				{
				case true:
					CManager::SetPause(false);
					PauseMenu = PAUSE_CONTENU;
					break;
				case false:
					CManager::SetPause(true);
					break;

				}
				m_PressP = true;
			}
		}
		else
		{
			m_PressP = false;
		}
		if (CManager::GetPause() == true)
		{
			Select();

			Changecol();

		}
	}
	else
	{
		PauseMenu = PAUSE_CONTENU;
	}
}

//=================================================
// 描画処理
//=================================================
void CPause::Draw(void)
{
	if (CManager::GetPause() == true && CManager::Get()->GetMode() ==CScene::MODE_GAME)
	{
		if (m_pPauseBg != nullptr)
		{
			m_pPauseBg->Draw();

		}

		for (int nCnt = 0; nCnt < NUM_PAUSE; nCnt++)
		{
			if (m_pPauseObject[nCnt] != nullptr)
			{
				m_pPauseObject[nCnt]->Draw();

			}
		}
	}

}

//=================================================
// 生成処理
//=================================================
CPause* CPause::Create(void)
{
	CPause *pPause = nullptr;
	pPause = DBG_NEW CPause;
	pPause->Init();
	return pPause;
}

//=================================================
// セレクト処理
//=================================================
void CPause::Select(void)
{
	CFade* pFade = CManager::Get()->GetpFade();

	CFade::FADE StateFade;
	StateFade = pFade->GetFade();
	CKeyboard* pKeyboard = CManager::Get()->GetInputKeyboard();

	if (pKeyboard->GetTrigger(DIK_W) == true)
	{
		switch (PauseMenu)
		{
		case PAUSE_CONTENU:
			PauseMenu = PAUSE_QUIT;
			break;
		case PAUSE_RETRY:
			PauseMenu = PAUSE_CONTENU;
			break;
		case PAUSE_QUIT:
			PauseMenu = PAUSE_RETRY;
			break;
		}
	}
	if (pKeyboard->GetTrigger(DIK_S) == true)
	{
		switch (PauseMenu)
		{
		case PAUSE_CONTENU:
			PauseMenu = PAUSE_RETRY;
			break;
		case PAUSE_RETRY:
			PauseMenu = PAUSE_QUIT;
			break;
		case PAUSE_QUIT:
			PauseMenu = PAUSE_CONTENU;
			break;
		}
	}

	if (pKeyboard->GetTrigger(DIK_RETURN) == true && StateFade == CFade::FADE_NONE)
	{
		switch (PauseMenu)
		{
		case PAUSE_CONTENU:
			CManager::SetPause(false);
			break;
		case PAUSE_RETRY:
			pFade->SetFade(CScene::MODE_GAME, 0.001f);
			break;
		case PAUSE_QUIT:
			pFade->SetFade(CScene::MODE_TITLE, 0.001f);
			break;
		}

	}
}

//=================================================
// カラーチェンジ処理
//=================================================
void CPause::Changecol(void)
{
	for (int nCnt = 0; nCnt < NUM_PAUSE; nCnt++)
	{
		switch (nCnt)
		{
		case PAUSE_CONTENU:
			if (PauseMenu == PAUSE_CONTENU)
			{
				m_pPauseObject[nCnt]->SetCol(ColSelect);
			}
			else
			{
				m_pPauseObject[nCnt]->SetCol(ColNoSelect);
			}
			break;
		case PAUSE_RETRY:
			if (PauseMenu == PAUSE_RETRY)
			{
				m_pPauseObject[nCnt]->SetCol(ColSelect);
			}
			else
			{
				m_pPauseObject[nCnt]->SetCol(ColNoSelect);
			}
			break;
		case PAUSE_QUIT:
			if (PauseMenu == PAUSE_QUIT)
			{
				m_pPauseObject[nCnt]->SetCol(ColSelect);
			}
			else
			{
				m_pPauseObject[nCnt]->SetCol(ColNoSelect);
			}
			break;
		}
	}
}


D3DXVECTOR3 CPause::GetPos(void)
{
	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}

