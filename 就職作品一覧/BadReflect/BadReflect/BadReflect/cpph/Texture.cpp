//===========================================================
//
//テクスチャの処理
//Author:堀川萩大
//
//===========================================================
#include "Texture.h"
#include "Manager.h"
#include "Renderer.h"


CTexture::TEXINFO CTexture::m_aTexInfo[TEX_MAX] =
{
	{"data\\TEXTURE\\tuti001.jpg"},				// TEX_NUM1
	{"data\\TEXTURE\\acorn.png"},				// TEX_NUM2
	{"data\\TEXTURE\\Bullet.png"},				// TEX_NUM3
	{"data\\TEXTURE\\explosion000.png"},		// TEX_NUM4
	{"data\\TEXTURE\\effect000.jpg"},			// TEX_NUM5
	{"data\\TEXTURE\\Title\\TitleLogo.png"},	// TEX_NUM6
	{"data\\TEXTURE\\BG000.jpg"},				// TEX_NUM7
	{"data\\TEXTURE\\Title\\startlogo.png"},	// TEX_NUM8
	{"data\\TEXTURE\\number000.png"},			// TEX_NUM9
	{"data\\TEXTURE\\pause000.png"},			// TEX_NUM10
	{"data\\TEXTURE\\pause001.png"},			// TEX_NUM11
	{"data\\TEXTURE\\pause002.png"},			// TEX_NUM12
	{"data\\TEXTURE\\pause200.png"},			// TEX_NUM13
	{"data\\TEXTURE\\Title\\SampleTitle.jpg"},	// TEX_NUM14
	{"data\\TEXTURE\\Ranking\\1st.png"},		// TEX_NUM15
	{"data\\TEXTURE\\Ranking\\2nd.png"},		// TEX_NUM16
	{"data\\TEXTURE\\Ranking\\3rd.png"},		// TEX_NUM17
	{"data\\TEXTURE\\Ranking\\4th.png"},		// TEX_NUM18
	{"data\\TEXTURE\\Ranking\\5th.png"},		// TEX_NUM19
};

//====================================================
// コンストラクタ
//====================================================
CTexture::CTexture()
{
	for (int nCnt = 0; nCnt < MAX_TEXDATE; nCnt++)
	{
		m_pTexture[nCnt] = nullptr;
	}
}
//====================================================
// デストラクタ
//====================================================
CTexture::~CTexture()
{

}

//====================================================
// テクスチャ読み込み処理
//====================================================
HRESULT CTexture::Load()
{

	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCntTex = 0; nCntTex < TEX_MAX; nCntTex++)
	{
		if (m_pTexture[nCntTex] == nullptr)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, m_aTexInfo[nCntTex].pFilename, &m_pTexture[nCntTex]);
		}
	}
	return S_OK;
}

//====================================================
// テクスチャの破棄
//====================================================
void CTexture::Unload()
{
	for (int nCnt = 0; nCnt < MAX_TEXDATE; nCnt++)
	{
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}
}

//====================================================
// テクスチャ番号を取得
//====================================================
int CTexture::Regist(const char *pFilename)
{
	for (int nCnt = 0; nCnt < MAX_TEXDATE; nCnt++)
	{
			if (strcmp(m_aTexInfo[nCnt].pFilename, pFilename) == 0)
			{
				return nCnt;
			}
	}
	return -1;
}

//====================================================
// テクスチャアドレス取得
//====================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (nIdx == -1)
	{
		return NULL;
	}
	if (m_pTexture[nIdx] == nullptr)
	{
		CRenderer* pRenderer = CManager::Get()->GetRenderer();
		//デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice, m_aTexInfo[nIdx].pFilename, &m_pTexture[nIdx]);
	}
	return m_pTexture[nIdx];
}