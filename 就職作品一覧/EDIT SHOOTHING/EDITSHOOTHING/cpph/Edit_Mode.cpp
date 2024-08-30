//===========================================================
//
//�U���I����ʂ̏�������
//Author:�x�씋��
//
//===========================================================
#include "edit_mode.h"
#include "game.h"
#include "main.h"
#include "Input.h"
#include "fade.h"
#include "sound.h"

//�}�N����`
#define TEX_EDSL (3)				//�U���I���̃e�N�X�`����
#define NUM_EDSL (8)				//�U���I���̕\����

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEdMd[TEX_EDSL] = {}; //�U���I���̐��̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEdMd = NULL;  //�U���I���̐��̒��_�o�b�t�@
NUM_EDIT g_NumEdMd;
EDIT g_EditMode[NUM_EDSL];
int g_EdMd[PWUP_MAX];
int g_PWUP_Data;

//=========================================================================================================
//�U���I����ʂ̏���������
//=========================================================================================================
void InitEdMd(void)
{
	//�T�E���h�̏���������
	PlaySound(SOUND_LABEL_BGM002);


	int nCntEdMd;
	D3DXCOLOR ColSelect = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR ColNoSelect = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	g_PWUP_Data = PWUP_NUM2;
	g_EdMd[PWUP_NUM1] = SHOT_NUM1;
	g_EdMd[PWUP_NUM2] = SHOT_NUM2;
	g_EdMd[PWUP_NUM3] = SHOT_NUM3;
	g_EdMd[PWUP_NUM4] = SHOT_NUM4;

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_EDSL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEdMd,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\editmode.png",
		&g_pTextureEdMd[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\edit_UI.png",
		&g_pTextureEdMd[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Select_UI.png",
		&g_pTextureEdMd[2]);


	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEdMd->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEdMd = 0; nCntEdMd < NUM_EDSL; nCntEdMd++)
	{
		if (nCntEdMd < NUM_EDSL)
		{
			if (nCntEdMd == 0)
			{
				g_EditMode[nCntEdMd].pos = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
				g_EditMode[nCntEdMd].size = D3DXVECTOR3(640.0f, 360.0f, 0.0f);
				g_EditMode[nCntEdMd].TexNum = 0;
				g_EditMode[nCntEdMd].col = ColSelect;
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			}
			else if (nCntEdMd == 1)
			{
				g_EditMode[nCntEdMd].pos = D3DXVECTOR3(400.0f, 240.0f, 0.0f);
				g_EditMode[nCntEdMd].size = D3DXVECTOR3(80.0f, 40.0f, 0.0f);
				g_EditMode[nCntEdMd].TexNum = 1;
				g_EditMode[nCntEdMd].col = ColSelect;
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);
			}
			else if (nCntEdMd == 2 || nCntEdMd == 3)
			{
				g_EditMode[nCntEdMd].pos = D3DXVECTOR3(400.0f + (200.0f*(nCntEdMd - 2)), 360.0f, 0.0f);
				g_EditMode[nCntEdMd].size = D3DXVECTOR3(80.0f, 40.0f, 0.0f);
				g_EditMode[2].col = ColSelect;
				g_EditMode[3].col = ColNoSelect;
				g_EditMode[nCntEdMd].TexNum = 1;

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.25f + (0.25f*(nCntEdMd - 2)), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f + (0.25f*(nCntEdMd - 2)), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.25f + (0.25f*(nCntEdMd - 2)), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f + (0.25f*(nCntEdMd - 2)), 1.0f);
			}
			else if (nCntEdMd == 4 || nCntEdMd == 5)
			{
				g_EditMode[nCntEdMd].pos = D3DXVECTOR3(400.0f + (200.0f*(nCntEdMd - 4)), 490.0f, 0.0f);
				g_EditMode[nCntEdMd].size = D3DXVECTOR3(80.0f, 40.0f, 0.0f);

				g_EditMode[4].col = ColNoSelect;
				g_EditMode[5].col = ColSelect;
				g_EditMode[nCntEdMd].TexNum = 1;

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.25f +(0.25f*(nCntEdMd-4)), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f + (0.25f*(nCntEdMd - 4)),  0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.25f + (0.25f*(nCntEdMd - 4)), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f + (0.25f*(nCntEdMd - 4)), 1.0f);

			}
			else if (nCntEdMd == 6)
			{
				g_EditMode[nCntEdMd].pos = D3DXVECTOR3(400.0f, 620.0f, 0.0f);
				g_EditMode[nCntEdMd].size = D3DXVECTOR3(80.0f, 40.0f, 0.0f);
				g_EditMode[nCntEdMd].TexNum = 1;
				g_EditMode[nCntEdMd].col = ColSelect;
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.75f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.75f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if(nCntEdMd ==7)
			{
				g_EditMode[nCntEdMd].pos = D3DXVECTOR3(400.0f, 360.0f, 0.0f);
				g_EditMode[nCntEdMd].size = D3DXVECTOR3(115.0f, 55.0f, 0.0f);
				g_EditMode[nCntEdMd].TexNum = 2;
				g_EditMode[nCntEdMd].col = ColSelect;
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			}
		}



		pVtx[0].pos = D3DXVECTOR3(g_EditMode[nCntEdMd].pos.x - g_EditMode[nCntEdMd].size.x, g_EditMode[nCntEdMd].pos.y - g_EditMode[nCntEdMd].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_EditMode[nCntEdMd].pos.x + g_EditMode[nCntEdMd].size.x, g_EditMode[nCntEdMd].pos.y - g_EditMode[nCntEdMd].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_EditMode[nCntEdMd].pos.x - g_EditMode[nCntEdMd].size.x, g_EditMode[nCntEdMd].pos.y + g_EditMode[nCntEdMd].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_EditMode[nCntEdMd].pos.x + g_EditMode[nCntEdMd].size.x, g_EditMode[nCntEdMd].pos.y + g_EditMode[nCntEdMd].size.y, 0.0f);
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = g_EditMode[nCntEdMd].col;
		pVtx[1].col = g_EditMode[nCntEdMd].col;
		pVtx[2].col = g_EditMode[nCntEdMd].col;
		pVtx[3].col = g_EditMode[nCntEdMd].col;



		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEdMd->Unlock();
}

//=========================================================================================================
//�U���I����ʂ̏I������
//=========================================================================================================
void UninitEdMd(void)
{
	int nCntEdMd;
	for (nCntEdMd = 0; nCntEdMd <TEX_EDSL; nCntEdMd++)
	{
		if (g_pTextureEdMd[nCntEdMd] != NULL)
		{
			g_pTextureEdMd[nCntEdMd]->Release();
			g_pTextureEdMd[nCntEdMd] = NULL;
		}
	}
	if (g_pVtxBuffEdMd != NULL)
	{
		g_pVtxBuffEdMd->Release();
		g_pVtxBuffEdMd = NULL;
	}
	//�T�E���h�̒�~
	StopSound();
}

//=========================================================================================================
//�U���I����ʂ̍X�V����
//=========================================================================================================
void UpdataEdMd(void)
{
	int nCntEdMd;
	FADE fFade = GetFade();
	D3DXCOLOR ColSelect = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXCOLOR ColNoSelect = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);

	//�U���I�𑀍�
	if (fFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_W) == true || GetKeyboardTrigger(DIK_S) == true)
		{
			PlaySound(SOUND_LABEL_SELECT);

			switch (g_PWUP_Data)
			{
			case PWUP_NUM2:
				g_PWUP_Data = PWUP_NUM3;
				break;
			case PWUP_NUM3:
				g_PWUP_Data = PWUP_NUM2;
				break;
			}
		}
		 else if (GetKeyboardTrigger(DIK_D) == true || GetKeyboardTrigger(DIK_A) == true)
		{
			PlaySound(SOUND_LABEL_SELECT);

			switch (g_EdMd[g_PWUP_Data])
			{
			case SHOT_NUM2:
				g_EdMd[g_PWUP_Data] = SHOT_NUM3;
				break;
			case SHOT_NUM3:
				g_EdMd[g_PWUP_Data] = SHOT_NUM2;
				break;
			}
		}
	}

	//�I��F�ς�
	if (g_PWUP_Data == PWUP_NUM2)
	{
		switch (g_EdMd[g_PWUP_Data])
		{
		case SHOT_NUM2:
			g_EditMode[2].col = ColSelect;
			g_EditMode[3].col = ColNoSelect;
			g_EditMode[7].pos = g_EditMode[2].pos;
			break;
		case SHOT_NUM3:
			g_EditMode[3].col = ColSelect;
			g_EditMode[2].col = ColNoSelect;
			g_EditMode[7].pos = g_EditMode[3].pos;
			break;
		}
	}
	else if (g_PWUP_Data == PWUP_NUM3)
	{
		switch (g_EdMd[g_PWUP_Data])
		{
		case SHOT_NUM2:
			g_EditMode[4].col = ColSelect;
			g_EditMode[5].col = ColNoSelect;
			g_EditMode[7].pos = g_EditMode[4].pos;
			break;
		case SHOT_NUM3:
			g_EditMode[5].col = ColSelect;
			g_EditMode[4].col = ColNoSelect;
			g_EditMode[7].pos = g_EditMode[5].pos;
			break;
		}
	}

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEdMd->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEdMd = 0; nCntEdMd < NUM_EDSL; nCntEdMd++)
	{
		pVtx[0].col = g_EditMode[nCntEdMd].col;
		pVtx[1].col = g_EditMode[nCntEdMd].col;
		pVtx[2].col = g_EditMode[nCntEdMd].col;
		pVtx[3].col = g_EditMode[nCntEdMd].col;
		pVtx[0].pos = D3DXVECTOR3(g_EditMode[nCntEdMd].pos.x - g_EditMode[nCntEdMd].size.x, g_EditMode[nCntEdMd].pos.y - g_EditMode[nCntEdMd].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_EditMode[nCntEdMd].pos.x + g_EditMode[nCntEdMd].size.x, g_EditMode[nCntEdMd].pos.y - g_EditMode[nCntEdMd].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_EditMode[nCntEdMd].pos.x - g_EditMode[nCntEdMd].size.x, g_EditMode[nCntEdMd].pos.y + g_EditMode[nCntEdMd].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_EditMode[nCntEdMd].pos.x + g_EditMode[nCntEdMd].size.x, g_EditMode[nCntEdMd].pos.y + g_EditMode[nCntEdMd].size.y, 0.0f);
		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEdMd->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true && fFade == FADE_NONE)
	{//space�̂݉����ꂽ�ꍇ
		PlaySound(SOUND_LABEL_SE_DECISION);

		SetFade(MODE_GAME, 0.05f);
	}

}

//=========================================================================================================
//�U���I����ʂ̕`�揈��
//=========================================================================================================
void DrawEdMd(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEdMd;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEdMd, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEdMd = 0; nCntEdMd <  NUM_EDSL; nCntEdMd++)
	{
			pDevice->SetTexture(0, g_pTextureEdMd[g_EditMode[nCntEdMd].TexNum]);
		
		//�|���S��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,4 * nCntEdMd, 2);
	}
}

int *GetNumEdMd(int Num)
{
	return &g_EdMd[Num];
}