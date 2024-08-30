//===========================================================
//
//�w�i�̏�������
//Author:�x�씋��
//
//===========================================================
#include "Bg.h"
#include "game.h"
#include "Input.h"

//�}�N����`
#define NUM_BG (3)				//�w�i�̍ő吔

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBg[NUM_BG] = {}; //�w�i�̐��̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;  //�w�i�̐��̒��_�o�b�t�@
float g_aTexV[NUM_BG];                        //�w�i�̈ړ���V�l
float g_aTexU[NUM_BG];                        //�w�i�̈ړ���U�l

//=========================================================================================================
//�w�i�̏���������
//=========================================================================================================
void InitBg(void)
{
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4*NUM_BG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG\\bg200.jpg",
		&g_pTextureBg[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG\\bg100.png",
		&g_pTextureBg[1]);	
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG\\bg102.png",
		&g_pTextureBg[2]);

	//�e�N�X�`�����W�i3�����j�̊J�n�ʒu�̏�����
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aTexV[nCntBG] = 0.0f;
	}

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f - g_aTexU[nCntBG], g_aTexV[nCntBG]);
		pVtx[1].tex = D3DXVECTOR2(1.0f - g_aTexU[nCntBG], g_aTexV[nCntBG]);
		pVtx[2].tex = D3DXVECTOR2(0.0f - g_aTexU[nCntBG], g_aTexV[nCntBG] + 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f - g_aTexU[nCntBG], g_aTexV[nCntBG] + 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg->Unlock();
}

//=========================================================================================================
//�w�i�̏I������
//=========================================================================================================
void UninitBg(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (g_pTextureBg[nCntBG] != NULL)
		{
			g_pTextureBg[nCntBG]->Release();
			g_pTextureBg[nCntBG] = NULL;
		}
	}
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
}

//�w�i�̍X�V����
void UpdataBg(void)
{
	int nCntBG;

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);
	
	g_aTexV[0] -= 0.000f;
	g_aTexV[1] -= 0.000f;
	g_aTexV[2] -= 0.000f;
	g_aTexU[0] -= 0.0001f;
	g_aTexU[1] -= 0.003f;
	g_aTexU[2] -= 0.002f;
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{	
		
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f- g_aTexU[nCntBG], g_aTexV[nCntBG]);
		pVtx[1].tex = D3DXVECTOR2(1.0f- g_aTexU[nCntBG], g_aTexV[nCntBG]);
		pVtx[2].tex = D3DXVECTOR2(0.0f- g_aTexU[nCntBG], g_aTexV[nCntBG] + 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f- g_aTexU[nCntBG], g_aTexV[nCntBG] + 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg->Unlock();
}

//=========================================================================================================
//�w�i�̕`�揈��
//=========================================================================================================
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBG;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		pDevice->SetTexture(0, g_pTextureBg[nCntBG]);

		//�|���S��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4*nCntBG, 2);
	}
}