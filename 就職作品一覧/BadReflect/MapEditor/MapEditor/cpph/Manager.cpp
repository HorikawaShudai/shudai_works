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
#include "Model.h"

//====================================================
//静的メンバ変数の初期化
//====================================================
CRenderer *CManager::m_pRenderer = nullptr;
CInputKeyboard *CManager::m_pInputKeyboard = nullptr;
CLight *CManager::m_pLight = nullptr;
CCamera *CManager::m_pCamera = nullptr;
CTexture *CManager::m_pTexture = nullptr;
LPDIRECT3DTEXTURE9 CManager::m_aTexturePlayer = nullptr;

//====================================================
//コンストラクタ
//====================================================
CManager::CManager()
{

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
	m_pRenderer = DBG_NEW CRenderer;
	m_pRenderer->Init(hWnd, TRUE);

	m_pInputKeyboard = DBG_NEW CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = m_pRenderer->GetDevice();

	m_pTexture = DBG_NEW CTexture;
	m_pTexture->Load();


	m_pLight = DBG_NEW CLight;
	m_pLight->Init();
	m_pCamera = DBG_NEW CCamera;
	m_pCamera->Init();
	CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CObject::TYPE_FIELD,0);
	CObject3D::Create( D3DXVECTOR3(0.0f,0.0f,0.0f),CObject::TYPE_PLAYER,0);
	return S_OK;
}

//====================================================
//終了処理
//====================================================
void CManager::Uninit(void)
{
	//すべてのオブジェクトを破棄
	CObject::ReleaseAll();

	// レンダラーの破棄
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// キーボードの破棄
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	// カメラの破棄
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// ライトの破棄
	if (m_pLight != nullptr)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = nullptr;
	}
	CField::UnLoad();

	if (m_pTexture != nullptr)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
}

//====================================================
//更新処理
//====================================================
void CManager::Update(void)
{
	m_pInputKeyboard->Update();
	m_pRenderer->Update();
	m_pCamera->Update();
	//m_pPlayer3D->Update();
}

//====================================================
//描画処理
//====================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//====================================================
//レンダラーの取得処理
//====================================================
CRenderer *CManager:: GetRenderer(void)
{
	return m_pRenderer;
}

//====================================================
//レンダラーの取得処理
//====================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//====================================================
//カメラの取得処理
//====================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

//====================================================
//テクスチャの取得処理
//====================================================
CTexture *CManager::GetpTexture(void)
{
	return m_pTexture;
}