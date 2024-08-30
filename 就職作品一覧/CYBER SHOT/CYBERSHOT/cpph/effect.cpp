//===========================================================
//
//�G�t�F�N�g�̏�������
//Author:�x�씋��
//
//===========================================================
#include "effect.h"
#include "explosion.h"

//�}�N����`
#define MAX_EFFECT (4096) //�G�t�F�N�g�̍ő吔

//�G�t�F�N�g�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;	    //�F
	EFFECTKIND type;
	float fRadius;		//���a
	int nLife;			//����
	bool bUse;			//�g�p�̗L��
}EFFECT;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureEffect = {};		//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//���_�o�b�t�@�̃|�C���^
EFFECT g_aEffect[MAX_EFFECT];						//�G�t�F�N�g�̏��
D3DXMATRIX g_mtxWorldEffect;


//=========================================================================================================
//����������
//=========================================================================================================
void InitEffect(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntEffect;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);

	//�G�t�F�N�g�̏��̏�����
	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		 g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		 g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		 g_aEffect[nCntEffect].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 *MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(-50.0f, 30.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f, 30.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		//nor�̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
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
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
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
void UpdateEffect(void)
{
	int nCntEffect;
	VERTEX_3D *pVtx;

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		if ( g_aEffect[nCntEffect].bUse == true)
		{
			if (g_aEffect[nCntEffect].type == EFFECT_KIND_BULLET)
			{
				g_aEffect[nCntEffect].fRadius -= 0.5f;
				g_aEffect[nCntEffect].col.a -= 0.05f;
				pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius,
					+g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius,
					+g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius,
					-g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius,
					-g_aEffect[nCntEffect].fRadius, 0.0f);

				g_aEffect[nCntEffect].nLife--;
				if (g_aEffect[nCntEffect].nLife <= 0 || g_aEffect[nCntEffect].fRadius <= 0.0f)
				{
					g_aEffect[nCntEffect].bUse = false;
				}
			}
			else if(g_aEffect[nCntEffect].type == EFFECT_KIND_SANDDUST)
			{
				g_aEffect[nCntEffect].pos.y +=1.0f;
				g_aEffect[nCntEffect].fRadius += 1.0f;
				g_aEffect[nCntEffect].col.a -= 0.05f;
				pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius,g_aEffect[nCntEffect].pos.y+g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius,g_aEffect[nCntEffect].pos.y+g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius,g_aEffect[nCntEffect].pos.y-g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(+g_aEffect[nCntEffect].fRadius,g_aEffect[nCntEffect].pos.y-g_aEffect[nCntEffect].fRadius, 0.0f);

				g_aEffect[nCntEffect].nLife--;
				if (g_aEffect[nCntEffect].nLife <= 0 || g_aEffect[nCntEffect].fRadius <= 0.0f)
				{
					g_aEffect[nCntEffect].bUse = false;
				}
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//�f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�̎擾�p

									//Z�e�X�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//���e�X�g��L��
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldEffect);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_mtxWorldEffect, NULL, &mtxView);
			g_mtxWorldEffect._41 = 0.0f;
			g_mtxWorldEffect._42 = 0.0f;
			g_mtxWorldEffect._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEffect);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);


			pDevice->SetTexture(0, g_pTextureEffect);

			//�r���{�[�h
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);

			//���e�X�g��L��
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

			//Z�e�X�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
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
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col ,float fRadius,int nLife, EFFECTKIND type)
{
	int nCntEffect;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	VERTEX_3D *pVtx;
  	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect <MAX_EFFECT; nCntEffect++)
	{
		if ( g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].type = type;
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