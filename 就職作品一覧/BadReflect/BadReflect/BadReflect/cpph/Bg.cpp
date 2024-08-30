//=========================================================================================================
//
//2D専用のポリゴンの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Bg.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"

#define BG_HEIGHT	(640.0f)
#define BG_WIDTH	(360.0f)



//====================================================
//コンストラクタ
//====================================================
CBg::CBg(int nPriority):CObject2D(nPriority)
{
	m_pos = D3DXVECTOR3 (0.0f,0.0f,0.0f);
	m_move = D3DXVECTOR3 (0.0f,0.0f,0.0f);
	m_Texpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//====================================================
//デストラクタ
//====================================================
CBg::~CBg()
{
	
}


//====================================================
//ポリゴンの初期化処理
//====================================================
HRESULT CBg::Init(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	LPDIRECT3DTEXTURE9 pTexture;

	CObject2D::Init();

	m_pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
	CManager pManager;
	CScene::MODE mode;
	mode = CManager::Get()->GetMode();


	
	
	if (mode == CScene::MODE_TITLE)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\SampleTitle.jpg",
			&pTexture);
		BindTexture(pTexture);

	}
	else if (mode == CScene::MODE_CLEAR)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\SampleResult.jpg",
			&pTexture);
		BindTexture(pTexture);

	}
	else if (mode == CScene::MODE_END)
	{
		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\end_000.jpeg",
			&pTexture);
		BindTexture(pTexture);

	}
	else if (mode == CScene::MODE_TUTORIAL)
	{
		//テクスチャの読み込み
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
//ポリゴンの終了処理
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
//ポリゴンの更新処理
//====================================================
void CBg::Update(void)
{

	m_Texpos += m_move;
	m_Texpos += m_moveTex;
	AutoScroll(m_moveTex.x, m_moveTex.y);
	//SetScroll(m_Texpos.x, m_Texpos.y);
}

//====================================================
//ポリゴンの描画処理
//====================================================
void CBg::Draw(void)
{
	CObject2D::Draw();
}

