//===========================================================
//
//�t�F�[�h�̏�������
//Author:�x�씋��
//
//===========================================================
#include "fade.h"
#include "main.h"
#include "game.h"
#include "sound.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;  //�t�F�[�h�̐��̒��_�o�b�t�@
FADE g_Fade;
float g_FadeCount;
MODE g_ModeNext;
D3DXCOLOR g_ColorFade;

//=========================================================================================================
//�t�F�[�h�̏���������
//=========================================================================================================
void InitFade(MODE ModeNext)
{
	g_Fade = FADE_IN;
	g_ModeNext = ModeNext;
	g_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();

	SetMode(g_ModeNext);
}

//=========================================================================================================
//�t�F�[�h�̏I������
//=========================================================================================================
void UninitFade(void)
{
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//�t�F�[�h�̍X�V����
void UpdateFade(void)
{
	if (g_Fade != FADE_NONE)
	{
		if (g_Fade == FADE_IN)
		{
			g_ColorFade.a -= 0.05f;
			if (g_ColorFade.a <= 0.0f)
			{
				g_ColorFade.a = 0.0f;
				g_Fade = FADE_NONE;
			}
		}
		else if (g_Fade == FADE_OUT)
		{
			g_ColorFade.a += g_FadeCount;
			if (g_ColorFade.a >= 1.0f)
			{
				g_ColorFade.a = 1.0f;
				g_Fade = FADE_IN;
				SetMode(g_ModeNext);
			}
		}

		VERTEX_2D *pVtx;
		//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
		//���_�J���[�̐ݒ�
		pVtx[0].col = g_ColorFade;
		pVtx[1].col = g_ColorFade;
		pVtx[2].col = g_ColorFade;
		pVtx[3].col = g_ColorFade;
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffFade->Unlock();
	
	}
}

//=========================================================================================================
//�t�F�[�h�̕`�揈��
//=========================================================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, NULL);

	//�|���S��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void SetFade(MODE ModeNext, float Fade)
{
	g_Fade = FADE_OUT;
	g_FadeCount = Fade;
	g_ModeNext = ModeNext;
	g_ColorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

FADE GetFade(void)
{
	return g_Fade;
}