//=========================================================================================================
//
//2D専用の複数背景の処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Textures.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Bg.h"

#define BG_HEIGHT	(640.0f)
#define BG_WIDTH	(360.0f)


int CTextures::NumTexAll = -1;
CObject2D *CTextures::m_apObject[MAX_BG];
LPDIRECT3DTEXTURE9 CTextures::m_pTexture[MAX_BG];
D3DXVECTOR3 CTextures::m_pTexmove[MAX_BG];

//====================================================
//コンストラクタ
//====================================================
CTextures::CTextures()
{
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NumTexAll++;
}
//====================================================
//デストラクタ
//====================================================
CTextures::~CTextures()
{

}


//====================================================
//ポリゴンの初期化処理
//====================================================
HRESULT CTextures::Init(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* MAX_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		BindTexture(m_pTexture[nCnt]);
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================================
//ポリゴンの終了処理
//====================================================
void CTextures::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//====================================================
//ポリゴンの描画処理
//====================================================
void CTextures::Draw(void)
{

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{
			
			CRenderer *pRenderer = CManager::Get()->GetRenderer();
			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

			pDevice->SetFVF(FVF_VERTEX_2D);

			pDevice->SetTexture(0, m_pTexture[nCnt]);

			//ポリゴン
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + nCnt * 4, 2);
		}
	}
}

//====================================================
//ポリゴンの更新処理
//====================================================
void CTextures::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{
			m_Texpos += m_pTexmove[nCnt];
			m_apObject[nCnt]->AutoScroll(m_Texpos.x, m_Texpos.y);
		}
	}
}



void CTextures::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_apTexture = pTexture;
}



//====================================================
//オブジェクトの生成処理
//====================================================
CObject2D *CTextures::Create(TYPE type2D)
{
	NumTexAll++;

	CObject2D *pObject2D = nullptr;

	switch (type2D)
	{
	case TYPE_BGS:
		for (int nCnt = 0; nCnt < MAX_BG; nCnt++, NumTexAll++)
		{
			pObject2D = DBG_NEW CBg;
			pObject2D->Init();
			pObject2D->SetTexmove(m_pTexmove[NumTexAll]);
			Load();

			pObject2D->BindTexture(m_pTexture[NumTexAll]);
		}
		break;
	}


	return pObject2D;
}

//====================================================
//テクスチャの読み込み処理
//====================================================
void CTextures::Load(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG001.jpg",
		&m_pTexture[0]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG002.png",
		&m_pTexture[1]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG003.png",
		&m_pTexture[2]);


	m_pTexmove[0] = D3DXVECTOR3(0.000001f,0.0f,0.0f);
	m_pTexmove[1] = D3DXVECTOR3(0.00002f,0.0f,0.0f);
	m_pTexmove[2] = D3DXVECTOR3(0.00003f,0.0f,0.0f);
}