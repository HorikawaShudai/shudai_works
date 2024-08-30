//===========================================================
//
//�e�N�X�`���̏���
//Author:�x�씋��
//
//===========================================================
#include "Texture.h"
#include "Manager.h"
#include "Renderer.h"


CTexture::TEXINFO CTexture::m_aTexInfo[TEX_NUMMAX] =
{
	{"data\\TEXTURE\\tuti001.jpg"},
	{"data\\TEXTURE\\acorn.png"},
	{ "data\\TEXTURE\\Bullet.png" },
	{ "data\\TEXTURE\\explosion000.png" },
	{ "data\\TEXTURE\\effect000.jpg" },
	{ "data\\TEXTURE\\player001.png" },
	{ "data\\TEXTURE\\BG000.jpg" },
	{ "data\\TEXTURE\\enemy004.png" },
	{ "data\\TEXTURE\\number000.png" },
	{ "data\\TEXTURE\\tree000.png" }
};

//====================================================
// �R���X�g���N�^
//====================================================
CTexture::CTexture()
{

}
//====================================================
// �f�X�g���N�^
//====================================================
CTexture::~CTexture()
{

}

//====================================================
//�e�N�X�`���ǂݍ��ݏ���
//====================================================
HRESULT CTexture::Load()
{
	CRenderer *pRenderer = CManager::GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		for (int nCnt = 0; nCnt < TEX_NUMMAX; nCnt++)
		{
			if (m_pTexture[nCnt] == NULL)
			{
				//�e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice, m_aTexInfo[nCntTex].pFilename, &m_pTexture[nCnt]);
				break;
			}
		}
	}
	return S_OK;
}

//====================================================
//�e�N�X�`���̔j��
//====================================================
void CTexture::Unload()
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}
}

//====================================================
//�e�N�X�`���ԍ����擾
//====================================================
int CTexture::Regist(const char *pFilename)
{
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
			if (m_aTexInfo[nCnt].pFilename == pFilename)
			{
				return nCnt;
			}
	}
	return -1;
}
//====================================================
//�e�N�X�`���A�h���X�擾
//====================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	return m_pTexture[nIdx];
}