//===========================================================
//
//�^�C�g���̏�������
//Author:�x�씋��
//
//===========================================================
#include "main.h"
#include "title.h"
#include "Input.h"
#include "sound.h"
#include "fade.h"

//�}�N����`
#define NUM_TITLE (3)

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_TITLE] = {}; //�^�C�g���̐��̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;  //�^�C�g���̐��̒��_�o�b�t�@
D3DXCOLOR g_FadeCol;
float g_Movefade;

//�^�C�g���̏���������
void InitTitle(void)
{
	//�T�E���h�̏���������
	PlaySound(SOUND_LABEL_BGM007);

	g_FadeCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Movefade = 0.02f;


	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\title_bg.png",
		&g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Logo.png",
		&g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\startlogo.png",
		&g_pTextureTitle[2]);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//���_���W�̐ݒ�
		switch (nCntTitle)
		{
		case 0:
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
			break;
		}
		case 1:
		{
			pVtx[0].pos = D3DXVECTOR3(135.0f, 55.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1150.0f, 55.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(135.0f, 200.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1150.0f, 200.0f, 0.0f);
			break;
		}
		case 2:
		{
			pVtx[0].pos = D3DXVECTOR3(320.0f, 350.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(960.0f, 350.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(320.0f, 400.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(960.0f, 400.0f, 0.0f);
			break;
		}
		}
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(g_FadeCol);
		pVtx[1].col = D3DXCOLOR(g_FadeCol);
		pVtx[2].col = D3DXCOLOR(g_FadeCol);
		pVtx[3].col = D3DXCOLOR(g_FadeCol);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();


}

//=======================================================
//�^�C�g���̏I������
//=======================================================
void UninitTitle(void)
{
	int nCntTitle;
	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
	//�T�E���h�̒�~
	StopSound();
}

//�^�C�g���̍X�V����
void UpdateTitle(void)
{
	g_FadeCol.a -= g_Movefade;
	if (g_FadeCol.a <= 0.0f || g_FadeCol.a >= 1.0f)
	{
		g_Movefade *= -1.0f;
	}

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * 2;

	//���_���W�̐ݒ�
	pVtx[0].col = D3DXCOLOR(g_FadeCol);
	pVtx[1].col = D3DXCOLOR(g_FadeCol);
	pVtx[2].col = D3DXCOLOR(g_FadeCol);
	pVtx[3].col = D3DXCOLOR(g_FadeCol);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	FADE fFade;
	fFade = GetFade();
	if (GetKeyboardTrigger(DIK_RETURN) == true&& fFade == FADE_NONE)
	{//space�̂݉����ꂽ�ꍇ
		PlaySound(SOUND_LABEL_SE_DECISION);
		SetFade(MODE_EDIT,0.05f);
	}
}

//�^�C�g���̕`�揈��
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);

		//�|���S��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTitle, 2);
	}
}