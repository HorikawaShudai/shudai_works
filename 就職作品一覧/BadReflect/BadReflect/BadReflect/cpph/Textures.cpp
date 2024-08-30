//=========================================================================================================
//
//2D��p�̕����w�i�̏���
//Author:�x�씋��
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
//�R���X�g���N�^
//====================================================
CTextures::CTextures()
{
	m_pVtxBuff = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	NumTexAll++;
}
//====================================================
//�f�X�g���N�^
//====================================================
CTextures::~CTextures()
{

}


//====================================================
//�|���S���̏���������
//====================================================
HRESULT CTextures::Init(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* MAX_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		BindTexture(m_pTexture[nCnt]);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================================
//�|���S���̏I������
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
//�|���S���̕`�揈��
//====================================================
void CTextures::Draw(void)
{

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{
			
			CRenderer *pRenderer = CManager::Get()->GetRenderer();
			//�f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

			pDevice->SetFVF(FVF_VERTEX_2D);

			pDevice->SetTexture(0, m_pTexture[nCnt]);

			//�|���S��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 + nCnt * 4, 2);
		}
	}
}

//====================================================
//�|���S���̍X�V����
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
//�I�u�W�F�N�g�̐�������
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
//�e�N�X�`���̓ǂݍ��ݏ���
//====================================================
void CTextures::Load(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG001.jpg",
		&m_pTexture[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG002.png",
		&m_pTexture[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG003.png",
		&m_pTexture[2]);


	m_pTexmove[0] = D3DXVECTOR3(0.000001f,0.0f,0.0f);
	m_pTexmove[1] = D3DXVECTOR3(0.00002f,0.0f,0.0f);
	m_pTexmove[2] = D3DXVECTOR3(0.00003f,0.0f,0.0f);
}