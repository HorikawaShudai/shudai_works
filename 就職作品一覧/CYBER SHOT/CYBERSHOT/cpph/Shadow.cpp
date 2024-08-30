//===========================================================
//
//�e�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Shadow.h"

//�}�N���ϐ�
#define MAX_SHADOW (720)

typedef struct
{
	D3DXVECTOR3 posShadow;
	D3DXVECTOR3 rotShadow;
	D3DXMATRIX  mtxWorldShadow;
	float fLength;
	bool bUse;
}SHADOW;

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;		//���_�o�b�t�@�|�C���g
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;			//�e�N�X�`���|�C���^
SHADOW g_shadow[MAX_SHADOW];

//=========================================================================================================
//����������
//=========================================================================================================
void InitShadow(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4*MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_shadow[nCntShadow].posShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCntShadow].rotShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCntShadow].bUse = false;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-15.0f, 0.0f, +15.0f);
		pVtx[1].pos = D3DXVECTOR3(+15.0f, 0.0f, +15.0f);
		pVtx[2].pos = D3DXVECTOR3(-15.0f, 0.0f, -15.0f);
		pVtx[3].pos = D3DXVECTOR3(+15.0f, 0.0f, -15.0f);

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

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//=========================================================================================================
//�e�̏I������
//=========================================================================================================
void UninitShadow(void)
{
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == true)
		{
			g_shadow[nCntShadow].bUse = false;
		}
	}
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=========================================================================================================
//�e�̍X�V����
//=========================================================================================================
void UpdateShadow(void)
{

}

//=========================================================================================================
//�e�̕`�揈��
//=========================================================================================================
void DrawShadow(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == true)
		{


			D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

			//���Z�����̐ݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_shadow[nCntShadow].mtxWorldShadow);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_shadow[nCntShadow].rotShadow.y, g_shadow[nCntShadow].rotShadow.x, g_shadow[nCntShadow].rotShadow.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorldShadow, &g_shadow[nCntShadow].mtxWorldShadow, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_shadow[nCntShadow].posShadow.x, g_shadow[nCntShadow].posShadow.y, g_shadow[nCntShadow].posShadow.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorldShadow, &g_shadow[nCntShadow].mtxWorldShadow, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_shadow[nCntShadow].mtxWorldShadow);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);


			pDevice->SetTexture(0, g_pTextureShadow);

			//�e�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4* nCntShadow, 2);

		}
	}
	//�ʏ퍇���̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=========================================================================================================
//�e�̎g�p�ԍ����擾
//=========================================================================================================
int SetShadow(float fLength, D3DXVECTOR3 pos)
{
	int nCntShadow;
	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == false)
		{
			g_shadow[nCntShadow].posShadow = pos;
			g_shadow[nCntShadow].rotShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-fLength, 1.0f, +fLength);
			pVtx[1].pos = D3DXVECTOR3(+fLength, 1.0f, +fLength);
			pVtx[2].pos = D3DXVECTOR3(-fLength, 1.0f, -fLength);
			pVtx[3].pos = D3DXVECTOR3(+fLength, 1.0f, -fLength);
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

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			g_shadow[nCntShadow].bUse = true;
			break;
		}
		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
	return nCntShadow;
}

//=========================================================================================================
//�e�̐ݒu����
//=========================================================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_shadow[nIdxShadow].posShadow = pos;
	
}


//=========================================================================================================
//�e�̏�������
//=========================================================================================================
void FinishShadow(int nIdxShadow)
{
 	g_shadow[nIdxShadow].bUse = false;
}