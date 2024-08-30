//===========================================================
//
//���C�t�̏�������
//Author:�x�씋��
//
//===========================================================
#include "game.h"
#include "player.h"
#include "Enagy.h"

//�}�N����`
#define NUM_LIFE (20) //���C�t�̍ő吔

//���C�t�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;	    //�F
	bool bUse;
}LIFE;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEnagy = NULL;		//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnagy = NULL;	//���_�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_posEnagy;							//���C�t�̈ʒu
LIFE g_aEnagy[NUM_LIFE];

//=========================================================================================================
//����������
//=========================================================================================================
void InitEnagy(void)
{


	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnagy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Enagy.png",
		&g_pTextureEnagy);

	//���C�t�̏��̏�����
	g_posEnagy = D3DXVECTOR3(190.0f, 40.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnagy,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEnagy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnagy = 0; nCntEnagy < NUM_LIFE; nCntEnagy++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_posEnagy.x + (40.0f*nCntEnagy)
			, g_posEnagy.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posEnagy.x + 40.0f + (40.0f*nCntEnagy)
			, g_posEnagy.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posEnagy.x + (40.0f*nCntEnagy)
			, g_posEnagy.y + 40.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posEnagy.x + 40.0f + (40.0f*nCntEnagy)
			, g_posEnagy.y + 40.0f, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		g_aEnagy[nCntEnagy].bUse = false;

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnagy->Unlock();

	PLAYER aPlayer = GetPlayer();
	for (int nCnt = 0; nCnt < aPlayer.nEnagy; nCnt++)
	{
		g_aEnagy[nCnt].bUse = true;
	}

}

//=========================================================================================================
//�I������
//=========================================================================================================
void UninitEnagy(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEnagy != NULL)
	{
		g_pTextureEnagy->Release();
		g_pTextureEnagy = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEnagy != NULL)
	{
		g_pVtxBuffEnagy->Release();
		g_pVtxBuffEnagy = NULL;
	}
}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void UpdateEnagy(void)
{
	PLAYER aPlayer = GetPlayer();
	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEnagy->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntEnagy = 0; nCntEnagy < NUM_LIFE; nCntEnagy++)
	{
		if (g_aEnagy[nCntEnagy].bUse == true)
		{
			if (aPlayer.nEnagy > nCntEnagy)
			{
				g_aEnagy[nCntEnagy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else if (aPlayer.nEnagy <= nCntEnagy)
			{
				g_aEnagy[nCntEnagy].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			}

			//���_�J���[
			pVtx[0].col =g_aEnagy[nCntEnagy].col;
			pVtx[1].col =g_aEnagy[nCntEnagy].col;
			pVtx[2].col =g_aEnagy[nCntEnagy].col;
			pVtx[3].col =g_aEnagy[nCntEnagy].col;

			pVtx += 4;
		}
	}
}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void DrawEnagy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnagy;

	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnagy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEnagy);

	for (nCntEnagy = 0; nCntEnagy < NUM_LIFE; nCntEnagy++)
	{
		if (g_aEnagy[nCntEnagy].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnagy * 4, 2);  //�E�����Ԗڂ�ς��Ȃ��Ƃ܂����I�I
		}
	}
}