//=========================================================================================================
//
//�}�l�[�W���̏���
//Author:�x�씋��
//
//=========================================================================================================
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "Object.h"
#include "Model.h"

//====================================================
//�ÓI�����o�ϐ��̏�����
//====================================================
CRenderer *CManager::m_pRenderer = nullptr;
CInputKeyboard *CManager::m_pInputKeyboard = nullptr;
CLight *CManager::m_pLight = nullptr;
CCamera *CManager::m_pCamera = nullptr;
CTexture *CManager::m_pTexture = nullptr;
LPDIRECT3DTEXTURE9 CManager::m_aTexturePlayer = nullptr;

//====================================================
//�R���X�g���N�^
//====================================================
CManager::CManager()
{

}

//====================================================
//�f�X�g���N�^
//====================================================
CManager::~CManager()
{

}

//====================================================
//����������
//====================================================
HRESULT CManager::Init(HINSTANCE hInstance ,HWND hWnd, BOOL bWindow)
{
	m_pRenderer = DBG_NEW CRenderer;
	m_pRenderer->Init(hWnd, TRUE);

	m_pInputKeyboard = DBG_NEW CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	//�f�o�C�X�̎擾
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
//�I������
//====================================================
void CManager::Uninit(void)
{
	//���ׂẴI�u�W�F�N�g��j��
	CObject::ReleaseAll();

	// �����_���[�̔j��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != nullptr)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	// �J�����̔j��
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	// ���C�g�̔j��
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
//�X�V����
//====================================================
void CManager::Update(void)
{
	m_pInputKeyboard->Update();
	m_pRenderer->Update();
	m_pCamera->Update();
	//m_pPlayer3D->Update();
}

//====================================================
//�`�揈��
//====================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}

//====================================================
//�����_���[�̎擾����
//====================================================
CRenderer *CManager:: GetRenderer(void)
{
	return m_pRenderer;
}

//====================================================
//�����_���[�̎擾����
//====================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//====================================================
//�J�����̎擾����
//====================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

//====================================================
//�e�N�X�`���̎擾����
//====================================================
CTexture *CManager::GetpTexture(void)
{
	return m_pTexture;
}