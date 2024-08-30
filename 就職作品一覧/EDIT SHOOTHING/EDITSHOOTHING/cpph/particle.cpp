////===========================================================
////
////�G�t�F�N�g�̏�������
////Author:�x�씋��
////
////===========================================================
//#include "game.h"
//#include "particle.h"
//
////�}�N����`
//#define MAX_PARTICLE (4056) //�G�t�F�N�g�̍ő吔
//
////�G�t�F�N�g�̍\���̂̒�`
//typedef struct
//{
//	D3DXVECTOR3 pos;	//�ʒu
//	D3DXCOLOR col;	    //�F
//	float fRadius;		//���a
//	int nLife;			//����
//	bool bUse;			//�g�p�̗L��
//}PARTICLE;
//
////�O���[�o���ϐ��錾
//PARTICLE g_aParticle[MAX_PARTICLE];						//�G�t�F�N�g�̏��
//
////=========================================================================================================
////����������
////=========================================================================================================
//void InitParticle(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	int nCntPARTICLE;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//�G�t�F�N�g�̏��̏�����
//	for (nCntPARTICLE = 0; nCntPARTICLE <MAX_PARTICLE; nCntPARTICLE++)
//	{
//		g_aParticle[nCntPARTICLE].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		g_aParticle[nCntPARTICLE].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
//		g_aParticle[nCntPARTICLE].bUse = false;
//	}
//
//	//���_�o�b�t�@�̐���
//	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PARTICLE,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffPARTICLE,
//		NULL);
//
//	VERTEX_2D *pVtx;
//	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
//	g_pVtxBuffPARTICLE->Lock(0, 0, (void**)&pVtx, 0);
//	for (nCntPARTICLE = 0; nCntPARTICLE <MAX_PARTICLE; nCntPARTICLE++)
//	{
//		//���_���W
//		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//		//rhw�̐ݒ�
//		pVtx[0].rhw = 1.0f;
//		pVtx[1].rhw = 1.0f;
//		pVtx[2].rhw = 1.0f;
//		pVtx[3].rhw = 1.0f;
//		//���_�J���[
//		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//
//		//�e�N�X�`�����W
//		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
//		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
//		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
//
//		pVtx += 4;
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffPARTICLE->Unlock();
//
//}
//
////=========================================================================================================
////�I������
////=========================================================================================================
//void UninitParticle(void)
//{
//	//�e�N�X�`���̔j��
//	if (g_pTexturePARTICLE != NULL)
//	{
//		g_pTexturePARTICLE->Release();
//		g_pTexturePARTICLE = NULL;
//	}
//
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffPARTICLE != NULL)
//	{
//		g_pVtxBuffPARTICLE->Release();
//		g_pVtxBuffPARTICLE = NULL;
//	}
//}
//
////=========================================================================================================
////�X�V����
////=========================================================================================================
//void UpdataParticle(void)
//{
//	int nCntPARTICLE;
//	VERTEX_2D *pVtx;
//	g_pVtxBuffPARTICLE->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntPARTICLE = 0; nCntPARTICLE <MAX_PARTICLE; nCntPARTICLE++)
//	{
//		if (g_aParticle[nCntPARTICLE].bUse == true)
//		{
//			g_aParticle[nCntPARTICLE].fRadius -= 0.5f;
//			g_aParticle[nCntPARTICLE].col.a -= 0.05f;
//			//���_���W
//			pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x - g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y - g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x + g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y - g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x - g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y + g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x + g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y + g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//
//			pVtx[0].col = g_aParticle[nCntPARTICLE].col;
//			pVtx[1].col = g_aParticle[nCntPARTICLE].col;
//			pVtx[2].col = g_aParticle[nCntPARTICLE].col;
//			pVtx[3].col = g_aParticle[nCntPARTICLE].col;
//
//			g_aParticle[nCntPARTICLE].nLife--;
//			if (g_aParticle[nCntPARTICLE].nLife == 0)
//			{
//				g_aParticle[nCntPARTICLE].bUse = false;
//			}
//
//		}
//		pVtx += 4;
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffPARTICLE->Unlock();
//}
//
////=========================================================================================================
////�`�揈��
////=========================================================================================================
//void DrawParticle(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//	int nCntPARTICLE;
//
//	pDevice = GetDevice();
//	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource(0, g_pVtxBuffPARTICLE, 0, sizeof(VERTEX_2D));
//
//	//���_�t�H�[�}�b�g�̐ݒ�
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//�e�N�X�`���̐ݒ�
//	pDevice->SetTexture(0, g_pTexturePARTICLE);
//
//	//���u�����f�B���O�����Z�����ɐݒ�
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
//
//	int nCntParticle;
//	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
//	{
//		if (g_aParticle[MAX_PARTICLE].bUse == true)
//		{
//
//		}
//	}
//
//	//���u�����f�B���O����߂�
//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
//}
//
////=========================================================================================================
////�G�t�F�N�g�̐ݒu����
////=========================================================================================================
//void SetParticle(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
//{
//	int nCntPARTICLE;
//
//	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
//	VERTEX_2D *pVtx;
//	g_pVtxBuffPARTICLE->Lock(0, 0, (void**)&pVtx, 0);
//
//	for (nCntPARTICLE = 0; nCntPARTICLE <MAX_PARTICLE; nCntPARTICLE++)
//	{
//		if (g_aParticle[nCntPARTICLE].bUse == false)
//		{
//			g_aParticle[nCntPARTICLE].pos = pos;
//			g_aParticle[nCntPARTICLE].col = col;
//			g_aParticle[nCntPARTICLE].fRadius = fRadius;
//			g_aParticle[nCntPARTICLE].nLife = nLife;
//
//			//���_���W
//			pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x - g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y - g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//			pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x + g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y - g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//			pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x - g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y + g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//			pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntPARTICLE].pos.x + g_aParticle[nCntPARTICLE].fRadius,
//				g_aParticle[nCntPARTICLE].pos.y + g_aParticle[nCntPARTICLE].fRadius, 0.0f);
//
//			//���_�J���[
//			pVtx[0].col = col;
//			pVtx[1].col = col;
//			pVtx[2].col = col;
//			pVtx[3].col = col;
//
//			g_aParticle[nCntPARTICLE].bUse = true;
//			break; //���d�v�I�I
//		}
//		pVtx += 4;
//	}
//	//���_�o�b�t�@���A�����b�N����
//	g_pVtxBuffPARTICLE->Unlock();
//}