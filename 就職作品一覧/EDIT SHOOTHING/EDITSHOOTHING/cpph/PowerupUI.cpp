//===========================================================
//
//UI�̏�������
//Author:�x�씋��
//
//===========================================================
#include "PowerupUI.h"
#include "game.h"
//#include "main.h"
#include "Input.h"
#include "Player.h"

//�}�N����`
#define NUM_UI (4)				//UI�̍ő吔

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePwUi = NULL; //UI�̐��̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPwUi = NULL;  //UI�̐��̒��_�o�b�t�@


 //=========================================================================================================
 //UI�̏���������
 //=========================================================================================================
void InitPwUi(void)
{
	int nCntUI;

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_UI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		& g_pVtxBuffPwUi ,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\PW_UI.png",
		&g_pTexturePwUi);


	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	 g_pVtxBuffPwUi ->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntUI = 0; nCntUI < NUM_UI; nCntUI++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(300.0f+(100.0f*nCntUI), 650.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(400.0f+(100.0f*nCntUI), 650.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(300.0f+(100.0f*nCntUI), 700.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(400.0f+(100.0f*nCntUI), 700.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.001f +(0.25f*nCntUI),0.01f);
		pVtx[1].tex = D3DXVECTOR2(0.25f+(0.25f*nCntUI),0.01f);
		pVtx[2].tex = D3DXVECTOR2(0.001f +(0.25f*nCntUI),1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f+(0.25f*nCntUI),1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	 g_pVtxBuffPwUi ->Unlock();
}

//=========================================================================================================
//UI�̏I������
//=========================================================================================================
void UninitPwUi(void)
{
	if (g_pTexturePwUi != NULL)
	{
		g_pTexturePwUi->Release();
		g_pTexturePwUi = NULL;
	}

	if (g_pVtxBuffPwUi != NULL)
	{
		g_pVtxBuffPwUi->Release();
		g_pVtxBuffPwUi = NULL;
	}
}

//UI�̍X�V����
void UpdataPwUi(void)
{
	D3DXCOLOR ColSelect = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Player aPlayer = *GetPlayer();


	if (aPlayer.nPoint > 0)
	{
		VERTEX_2D *pVtx;
		//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
		g_pVtxBuffPwUi->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCnt = 0; nCnt < aPlayer.nPoint; nCnt++)
		{
			//���_���W�̐ݒ�
			pVtx[0].col = D3DXCOLOR(ColSelect);
			pVtx[1].col = D3DXCOLOR(ColSelect);
			pVtx[2].col = D3DXCOLOR(ColSelect);
			pVtx[3].col = D3DXCOLOR(ColSelect);
			pVtx += 4;

		}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPwUi->Unlock();
	}

	if (GetKeyboardPress(DIK_B) == true)
	{
		ResetUI();
	}

}

//=========================================================================================================
//UI�̕`�揈��
//=========================================================================================================
void DrawPwUi(void)
{
	int nCntUI;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPwUi, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);


	pDevice->SetTexture(0, g_pTexturePwUi);

	for (nCntUI = 0; nCntUI < NUM_UI; nCntUI++)
	{
		//�|���S��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntUI * 4, 2);
	}
}

//=========================================================================================================
//UI�̃��Z�b�g����
//=========================================================================================================
void ResetUI(void)
{
	D3DXCOLOR ColNoSelect = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffPwUi->Lock(0, 0, (void**)&pVtx, 0);
	for (int nUiCnt = 0; nUiCnt < 4; nUiCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].col = D3DXCOLOR(ColNoSelect);
		pVtx[1].col = D3DXCOLOR(ColNoSelect);
		pVtx[2].col = D3DXCOLOR(ColNoSelect);
		pVtx[3].col = D3DXCOLOR(ColNoSelect);
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPwUi->Unlock();
}