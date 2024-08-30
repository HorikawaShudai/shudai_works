//=========================================================================================================
//
//2D��p�̃|���S���̏���
//Author:�x�씋��
//
//=========================================================================================================
#include "Bg.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"

#define BG_HEIGHT	(640.0f)
#define BG_WIDTH	(360.0f)



//====================================================
//�R���X�g���N�^
//====================================================
CBg::CBg(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3 (0.0f,0.0f,0.0f);
	m_move = D3DXVECTOR3 (0.0f,0.0f,0.0f);
	m_Texpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//====================================================
//�f�X�g���N�^
//====================================================
CBg::~CBg()
{
	
}


//====================================================
//�|���S���̏���������
//====================================================
HRESULT CBg::Init(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	LPDIRECT3DTEXTURE9 pTexture;

	CObject2D::Init();

	m_pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	CManager pManager;
	CScene::MODE mode;
	mode = CManager::Get()->GetMode();


	
	
	if (mode == CScene::MODE_TITLE)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\SampleTitle.jpg",
			&pTexture);
		BindTexture(pTexture);

	}
	else if (mode == CScene::MODE_CLEAR)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\SampleResult.jpg",
			&pTexture);
		BindTexture(pTexture);

	}
	else if (mode == CScene::MODE_END)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\end_000.jpeg",
			&pTexture);
		BindTexture(pTexture);

	}
	else if (mode == CScene::MODE_TUTORIAL)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\ContorolBG.jpg",
			&pTexture);
		BindTexture(pTexture);

	}
	
	SetType(TYPE_BG);

	SetPos(m_pos, BG_HEIGHT, BG_WIDTH);
	return S_OK;
}

//====================================================
//�|���S���̏I������
//====================================================
void CBg::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

}

//====================================================
//�|���S���̍X�V����
//====================================================
void CBg::Update(void)
{

	m_Texpos += m_move;
	m_Texpos += m_moveTex;
	AutoScroll(m_moveTex.x, m_moveTex.y);
	//SetScroll(m_Texpos.x, m_Texpos.y);
}

//====================================================
//�|���S���̕`�揈��
//====================================================
void CBg::Draw(void)
{
	CObject2D::Draw();
}

