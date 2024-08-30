//===========================================================
//
//���C�t�̏�������
//Author:�x�씋��
//
//===========================================================
#include "game.h"
#include "player.h"
#include "life.h"

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
LPDIRECT3DTEXTURE9 g_pTexturelife = NULL;		//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufflife = NULL;	//���_�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_posLife;							//���C�t�̈ʒu
LIFE g_aLife[NUM_LIFE];

//=========================================================================================================
//����������
//=========================================================================================================
void InitLife(void)
{
	Player aPlayer = *GetPlayer();

	LPDIRECT3DDEVICE9 pDevice;
	int nCntlife;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player.png",
		&g_pTexturelife);

	//���C�t�̏��̏�����
	g_posLife = D3DXVECTOR3(190.0f, 10.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufflife,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBufflife->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntlife = 0; nCntlife < NUM_LIFE; nCntlife++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_posLife.x + (40.0f*nCntlife)
			, g_posLife.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posLife.x + 40.0f + (40.0f*nCntlife)
			, g_posLife.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posLife.x + (40.0f*nCntlife)
			, g_posLife.y + 40.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posLife.x + 40.0f + (40.0f*nCntlife)
			, g_posLife.y + 40.0f, 0.0f);
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

		g_aLife[nCntlife].bUse = false;

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBufflife->Unlock();

}

//=========================================================================================================
//�I������
//=========================================================================================================
void UninitLife(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturelife != NULL)
	{
		g_pTexturelife->Release();
		g_pTexturelife = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBufflife != NULL)
	{
		g_pVtxBufflife->Release();
		g_pVtxBufflife = NULL;
	}
}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void UpdataLife(void)
{
	Player aPlayer = *GetPlayer();
	for (int nCntlife = 0; nCntlife < NUM_LIFE; nCntlife++)
	{
		if (aPlayer.life > nCntlife)
		{
			g_aLife[nCntlife].bUse = true;

		}
		else if (aPlayer.life <= nCntlife)
		{
			g_aLife[nCntlife].bUse = false;

		}
	}
}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntlife;

	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufflife, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturelife);

	for (nCntlife = 0; nCntlife < NUM_LIFE; nCntlife++)
	{
		if (g_aLife[nCntlife].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntlife * 4, 2);  //�E�����Ԗڂ�ς��Ȃ��Ƃ܂����I�I
		}
	}
}