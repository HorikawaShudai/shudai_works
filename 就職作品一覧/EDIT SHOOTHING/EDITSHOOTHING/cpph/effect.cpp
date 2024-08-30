//===========================================================
//
//�G�t�F�N�g�̏�������
//Author:�x�씋��
//
//===========================================================
#include "game.h"
#include "effect.h"
#include "Player.h"
#include "explosion.h"

//�}�N����`
#define MAX_EFFECT (4056) //�G�t�F�N�g�̍ő吔

//�G�t�F�N�g�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;	    //�F
	float fRadius;		//���a
	int nLife;			//����
	int NumTex;			//�e�N�X�`���ԍ�
	bool bUse;			//�g�p�̗L��
}EFFECT;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEffect[2] = {};		//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//���_�o�b�t�@�̃|�C���^
EFFECT g_aEffect[MAX_EFFECT];						//�G�t�F�N�g�̏��

void CollisionRazer(EFFECT *pEffecet);


//=========================================================================================================
//����������
//=========================================================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect001.jpg",
		&g_pTextureEffect[1]);

	//�G�t�F�N�g�̏��̏�����
	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		 g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		 g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		 g_aEffect[nCntEffect].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		//���_���W
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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();

}

//=========================================================================================================
//�I������
//=========================================================================================================
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect[0] != NULL)
	{
		g_pTextureEffect[0]->Release();
		g_pTextureEffect[0] = NULL;
	}
	if (g_pTextureEffect[1] != NULL)
	{
		g_pTextureEffect[1]->Release();
		g_pTextureEffect[1] = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void UpdataEffect(void)
{
	int nCntEffect;
	VERTEX_2D *pVtx;
	Player *pPlayer = GetPlayer();

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		if ( g_aEffect[nCntEffect].bUse == true)
		{
			if (g_aEffect[nCntEffect].NumTex == 0)
			{
				g_aEffect[nCntEffect].fRadius -= 0.5f;
				g_aEffect[nCntEffect].col.a -= 0.05f;
				pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius,
					g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius,
					g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius,
					g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius,
					g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			}
			else if (g_aEffect[nCntEffect].NumTex == 1)
			{
				g_aEffect[nCntEffect].fRadius -= 0.1f;
				g_aEffect[nCntEffect].col.a -= 0.001f;
				pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 1000.0f,
					g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 25.0f,
					g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 1000.0f,
					g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 25.0f,
					g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			}
			//���_���W


			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			g_aEffect[nCntEffect].nLife--;
			if (g_aEffect[nCntEffect].nLife <= 0 || g_aEffect[nCntEffect].fRadius<= 0.0f)
			{
				g_aEffect[nCntEffect].bUse = false;
			}

			if (g_aEffect[nCntEffect].NumTex == 1 && pPlayer->state == PLAYERSTATE_NORMAL)
			{
				CollisionRazer(&g_aEffect[nCntEffect]);
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);



	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		if ( g_aEffect[nCntEffect].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect[g_aEffect[nCntEffect].NumTex]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);  //�E�����Ԗڂ�ς��Ȃ��Ƃ܂����I�I
		}
	}

	//���u�����f�B���O����߂�
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
}

//=========================================================================================================
//�G�t�F�N�g�̐ݒu����
//=========================================================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col ,float fRadius,int nLife,int nTex)
{
	int nCntEffect;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	VERTEX_2D *pVtx;
  	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		if ( g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].NumTex = nTex;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius,
				g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius,
				g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius,
				g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius,
				g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

			//���_�J���[
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			 g_aEffect[nCntEffect].bUse = true;
			break; //���d�v�I�I
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
void CollisionRazer(EFFECT *pEffect)
{
	Player *pPlayer = GetPlayer();

	if (pEffect->pos.x - 1000.0f >= pPlayer->pos.x - 20.0f && pEffect->pos.x + 25.0f <= pPlayer->pos.x + 20.0f  ||
		pEffect->pos.y - pEffect->fRadius >= pPlayer->pos.y - 20.0f && pEffect->pos.y + pEffect->fRadius <= pPlayer->pos.y + 20.0f)
	{

		if (pPlayer->life <= 1)
		{
			SetEnablePause(true);
			HitPlayer(1);

		}
		else
		{
			SetExplosion(pEffect->pos, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
			HitPlayer(1);
		}
	}
}