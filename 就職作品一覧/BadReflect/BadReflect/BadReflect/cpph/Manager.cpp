//=========================================================================================================
//
//マネージャの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "Object.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Textures.h"
#include "Effect.h"
#include "Enemy.h"
#include "Sound.h"
#include "Score.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "fade.h"
#include "Tutorial.h"
#include "Ranking.h"

//====================================================
//静的メンバ変数の初期化
//====================================================
CManager* CManager::m_pManager = nullptr;
bool CManager::bPause = false;
//====================================================
//コンストラクタ
//====================================================
CManager::CManager()
{
	m_pRenderer = nullptr;
	m_pTexture = nullptr;
	m_pLight = nullptr;
	m_pCamera = nullptr;
	m_pFade = nullptr;
	m_pInputKeyboard = nullptr;
	m_pInputGamepad = nullptr;
	m_pScene = nullptr;
	m_pPause = nullptr;
}

//====================================================
//デストラクタ
//====================================================
CManager::~CManager()
{

}

//====================================================
//初期化処理
//====================================================
HRESULT CManager::Init(HINSTANCE hInstance ,HWND hWnd, BOOL bWindow)
{

	// レンダラー
	m_pRenderer = DBG_NEW CRenderer;
	m_pRenderer->Init(hWnd, TRUE);
	
	// 入力
	m_pInputKeyboard = DBG_NEW CKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);
	m_pInputGamepad = DBG_NEW CGamepad;
	m_pInputGamepad->Init(hInstance, hWnd);

	// 音楽
	CSound::Init(hWnd);

	// テクスチャ
	m_pTexture = DBG_NEW CTexture;
	m_pTexture->Load();

	// ライト
	m_pLight = DBG_NEW CLight;
	m_pLight->Init();

	// カメラ
	m_pCamera = DBG_NEW CCamera;
	m_pCamera->Init();

	SetMode(CScene::MODE_TITLE);

	// フェード
	m_pFade = CFade::Create();

	m_pPause = CPause::Create();

	//m_pFade->SetFade(CScene::MODE_TITLE, 0.01f);
	return S_OK;
}

//====================================================
//終了処理
//====================================================
void CManager::Uninit(void)
{

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}
	if (m_pInputGamepad != nullptr)
	{
		m_pInputGamepad->Uninit();
		delete m_pInputGamepad;
		m_pInputGamepad = nullptr;
	}
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}
	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = nullptr;
	}
	CField::UnLoad();
	CSound::StopSound();
	CSound::Uninit();
	if (m_pTexture != nullptr)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	if (m_pManager != nullptr)
	{
		delete m_pManager;

		m_pManager = nullptr;
	}
	//すべてのオブジェクトを破棄
	CObject::ReleaseAll();
}

//====================================================
//更新処理
//====================================================
void CManager::Update(void)
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Update();
	}
	if (m_pInputGamepad != nullptr)
	{
		m_pInputGamepad->Update();
	}
	if (m_pCamera != nullptr)
	{
		m_pCamera->Update();
	}
	if (m_pScene != nullptr)
	{
		m_pScene->Update();
	}
	if (m_pFade != nullptr)
	{
		m_pFade->Update();
	}
	if (m_pPause != nullptr)
	{
		m_pPause->Update();
	}
}

//====================================================
//描画処理
//====================================================
void CManager::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}

//====================================================
//レンダラーの取得処理
//====================================================
CRenderer *CManager:: GetRenderer(void)
{
	return m_pRenderer;
}

//====================================================
//キーボードの取得処理
//====================================================
CKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//====================================================
//ゲームパッドの取得処理
//====================================================
CGamepad *CManager::GetInputGamepad(void)
{
	return m_pInputGamepad;
}

//====================================================
//カメラの取得処理
//====================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

CTexture *CManager::GetpTexture(void)
{
	return m_pTexture;
}
CFade *CManager::GetpFade(void)
{
	return m_pFade;
}

void CManager::SetMode(CScene::MODE mode)
{
	// メモリの確保がされていたら
	if (m_pScene != nullptr)
	{
		// 終了処理
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = nullptr;
	}
	m_pScene = CScene::Create(mode);
	m_pScene->m_mode = mode;
	m_pScene->Init();
}

CManager* CManager::Get(void)
{
	if (m_pManager != nullptr)
	{ // マネージャーの NULL じゃない場合

		// マネージャーの情報を返す
		return m_pManager;
	}
	else
	{ // 上記以外

		// マネージャーを生成する
		return CManager::Create();
	}
}
CManager* CManager::Create(void)
{
	if (m_pManager == nullptr)
	{ // マネージャーが NULL の場合

		// マネージャーを生成する
		m_pManager = DBG_NEW CManager;

		// マネージャーの情報を返す
		return m_pManager;
	}
	else
	{ // 上記以外

		// マネージャーの情報を返す
		return m_pManager;
	}
}


CScene::MODE CManager::GetMode(void)
{
	return m_pScene->m_mode;
}

CPause* CManager::GetpPause(void)
{
	return m_pPause;
}

CScene* CManager::GetpScene(void)
{
	return m_pScene;
}


//====================================================
// ポーズ設定処理
//====================================================
void CManager::SetPause(bool PouseNext)
{
	switch (bPause)
	{
	case true:
		bPause = PouseNext;
		return;
	case false:
		bPause = PouseNext;
		return;

	}

}