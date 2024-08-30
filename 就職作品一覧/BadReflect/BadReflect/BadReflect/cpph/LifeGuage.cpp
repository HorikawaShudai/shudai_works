//===========================================================
//
//���C�t�̏�������
//Author:�x�씋��
//
//===========================================================
#include "player.h"
#include "Enemy.h"
#include "LifeGuage.h"
#include "input.h"
#include "Renderer.h"
#include "Manager.h"
#include "Fade.h"
#include "Score.h"
#include "Game.h"
//=========================================================================================================
//�R���X�g���N�^
//=========================================================================================================
CLifeGuage::CLifeGuage(int nPriority) :CObject2D(nPriority)
{

}
//=========================================================================================================
//�f�X�g���N�^
//=========================================================================================================
CLifeGuage::~CLifeGuage()
{

}

//=========================================================================================================
//����������
//=========================================================================================================
HRESULT CLifeGuage::Init(void)
{

	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\gage.png",
		&m_pTexture);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	if (m_type == TYPE_PLAYERLIFE)
	{
		m_MaxLife = CPlayer3D::GetLife();
		m_Life = m_MaxLife;
	}
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	TexNum = NULL;
	//���_���W
	if (m_type == TYPE_PLAYERLIFE)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + ((GUAGE_HEIGHT / m_MaxLife)*m_Enagy), m_pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + ((GUAGE_HEIGHT / m_MaxLife)*m_Enagy), m_pos.y + 20.0f, 0.0f);
	}
	else if (m_type == TYPE_PLAYERENAGY)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + ((GUAGE_HEIGHT / m_MaxEnagy)*m_Life), m_pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + ((GUAGE_HEIGHT / m_MaxEnagy)*m_Life), m_pos.y + 20.0f, 0.0f);
	}
	//���_�J���[
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=========================================================================================================
//�I������
//=========================================================================================================
void CLifeGuage::Uninit(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void CLifeGuage::Update(void)
{
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_type == TYPE_PLAYERLIFE )
	{
		m_Life = CPlayer3D::GetLife();

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + ((GUAGE_HEIGHT / m_MaxLife)*m_Life), m_pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + ((GUAGE_HEIGHT / m_MaxLife)*m_Life), m_pos.y + 20.0f, 0.0f);
		if (m_Life <= 3)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		}
	}			    
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	CFade *pFade = CManager::Get()->GetpFade();

	CFade::FADE StateFade;
	StateFade = pFade->GetFade();
	if (m_type == TYPE_PLAYERLIFE)
	{
		if (m_Life <= 0 && StateFade == CFade::FADE_NONE)
		{

			pFade->SetFade(CScene::MODE_END, 0.001f);
		}
	}

}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void CLifeGuage::Draw(void)
{

	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);  //�E�����Ԗڂ�ς��Ȃ��Ƃ܂����I�I
}

//=========================================================================================================
//��������
//=========================================================================================================
CLifeGuage *CLifeGuage::Create(int type)
{
	CLifeGuage *pObj = NULL;
	pObj = new CLifeGuage;
	if (type == TYPE_PLAYERLIFE)
	{
		pObj->m_pos = D3DXVECTOR3(40.0f, 80.0f, 0.0f);
		pObj->m_col = D3DXCOLOR(0.0f, 0.0f, 0.7f, 1.0f);
		pObj->m_Height = 40.0f;
		pObj->m_type = TYPE_PLAYERLIFE;
	}
	else if (type == TYPE_PLAYERENAGY)
	{
		pObj->m_pos = D3DXVECTOR3(40.0f, 110.0f, 0.0f);
		pObj->m_col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pObj->m_Height = 40.0f;
		pObj->m_type = TYPE_PLAYERENAGY;
	}
	else if (type == TYPE_BOSSLIFE)
	{
		pObj->m_pos = D3DXVECTOR3(300.0f, 500.0f, 0.0f);
		pObj->m_col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pObj->m_Height = 40.0f;
		pObj->m_type = TYPE_BOSSLIFE;
	}
	return pObj;
}