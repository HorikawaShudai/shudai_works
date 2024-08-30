//===========================================================
//
//�e�̏�������
//Author:�x�씋��
//
//===========================================================
#include "bullet.h"
#include "explosion.h"
#include "input.h"
#include "model.h"
#include "shadow.h"
#include "effect.h"
#include "MeshWall.h"
#include "Object.h"
#include "Enemy.h"
#include "Player.h"
//#include "sound.h"

//�}�N����`
#define MAX_BULLET (4048) //�e�̍ő吔
#define BULLET_WIDTH (10.0f) //�e�̍���
#define BULLET_HEIGHT (10.0f) //�e�̕�

//�e�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//���݈ʒu
	D3DXVECTOR3 posOld;	//���݈ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 frot;	//�e�̌���
	float Length;
	int nIdxShadow;
	D3DXCOLOR col;
	BULLETTYPE type;	//�e�̎��
	bool bUse;			//�g�p�̗L��
}Bullet;//�e

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@�̃|�C���^
Bullet g_aBullet[MAX_BULLET];						//�e�̏��
D3DXMATRIX g_mtxWorldBullet;
int g_UseBullet;

float g_fAngleBullet;
float g_fLengthBullet;

//=========================================================================================================
//����������
//=========================================================================================================
void InitBullet(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_UseBullet= 0;


	//�e�̏��̏�����
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].frot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].Length = 0.0f;
		g_aBullet[nCntBullet].nIdxShadow = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player_shot.png",
		&g_pTextureBullet);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-BULLET_HEIGHT, BULLET_WIDTH, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+BULLET_HEIGHT, BULLET_WIDTH, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_HEIGHT, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+BULLET_HEIGHT, 0.0f, 0.0f); 

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
	g_pVtxBuffBullet->Unlock();
}

//=========================================================================================================
//�I������
//=========================================================================================================
void UninitBullet(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].bUse = false;
			g_UseBullet -= 1;
		}
	}
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void UpdateBullet(void)
{
	int nCntBullet;
	//int nCntEnemy;
	VERTEX_3D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].posOld = g_aBullet[nCntBullet].pos;

			g_aBullet[nCntBullet].Length += g_aBullet[nCntBullet].move.z;
			if (g_aBullet[nCntBullet].frot.y > 0)
			{
				g_aBullet[nCntBullet].pos.z = g_aBullet[nCntBullet].pos.z - sinf(g_aBullet[nCntBullet].frot.y)* g_aBullet[nCntBullet].Length;
				g_aBullet[nCntBullet].pos.x = g_aBullet[nCntBullet].pos.x + cosf(g_aBullet[nCntBullet].frot.y)* g_aBullet[nCntBullet].Length;
			}
			if (g_aBullet[nCntBullet].frot.y <= 0)
			{
				g_aBullet[nCntBullet].pos.z = g_aBullet[nCntBullet].pos.z - sinf(g_aBullet[nCntBullet].frot.y)* g_aBullet[nCntBullet].Length;
				g_aBullet[nCntBullet].pos.x = g_aBullet[nCntBullet].pos.x + cosf(g_aBullet[nCntBullet].frot.y)* g_aBullet[nCntBullet].Length;
			}

			
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				if (ColissionEnemy(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].posOld, g_aBullet[nCntBullet].move))
				{
					SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
					FinishShadow(g_aBullet[nCntBullet].nIdxShadow);
					g_aBullet[nCntBullet].nIdxShadow = -1;
					g_aBullet[nCntBullet].bUse = false;
					g_UseBullet -= 1;
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				if (ColissionPlayer(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].posOld, g_aBullet[nCntBullet].move))
				{
					SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
					FinishShadow(g_aBullet[nCntBullet].nIdxShadow);
					g_aBullet[nCntBullet].nIdxShadow = -1;
					g_aBullet[nCntBullet].bUse = false;
					g_UseBullet -= 1;
				}
			}

			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 20.0f, 7, EFFECT_KIND_BULLET);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{
				SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f), 20.0f, 7, EFFECT_KIND_BULLET);
			}
			
			BulletFalse();

			SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, 0.0f, g_aBullet[nCntBullet].pos.z));

		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();

}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void DrawBullet(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//�f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxView;		//�r���[�}�g���b�N�X�̎擾�p

									//Z�e�X�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldBullet);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_mtxWorldBullet, NULL, &mtxView);
			g_mtxWorldBullet._41 = 0.0f;
			g_mtxWorldBullet._42 = 0.0f;
			g_mtxWorldBullet._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldBullet, &g_mtxWorldBullet, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);


			pDevice->SetTexture(0, g_pTextureBullet);

			//�r���{�[�h
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);

			//Z�e�X�g��L���ɂ���
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}
	}
}

//=========================================================================================================
//�e�̐ݒ菈��
//=========================================================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot,BULLETTYPE type , D3DXCOLOR col)
{
	int nCntBullet;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	VERTEX_3D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].col = col;
			g_aBullet[nCntBullet].frot= rot;
			g_aBullet[nCntBullet].Length = 10.0f;
			
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(g_aBullet[nCntBullet].col);
			pVtx[1].col = D3DXCOLOR(g_aBullet[nCntBullet].col);
			pVtx[2].col = D3DXCOLOR(g_aBullet[nCntBullet].col);
			pVtx[3].col = D3DXCOLOR(g_aBullet[nCntBullet].col);

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].nIdxShadow = SetShadow(15.0f, g_aBullet[nCntBullet].pos);

			g_aBullet[nCntBullet].bUse = true;
			g_UseBullet +=1;

			break; //���d�v�I�I
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//{
////=========================================================================================================
////�G�̓����蔻��
////=========================================================================================================
//void CollisionEnemy(Bullet *pBullet)
//{
//	Enemy *pEnemy = GetEnemy();
//	Player *pPlayer = GetPlayer();
//	int nCntEnemy;
//
//	for (nCntEnemy = 0; nCntEnemy <= MAX_ENEMY; nCntEnemy++, pEnemy++)
//	{
//		if (pEnemy->bUse == true)
//		{
//			if (pEnemy->nType == 0 || pEnemy->nType == 1 || pEnemy->nType == 2)
//			{
//				if (pBullet->pos.x >= pEnemy->pos.x - pEnemy->fsize && pBullet->pos.x <= pEnemy->pos.x + pEnemy->fsize  &&
//					pBullet->pos.y >= pEnemy->pos.y - pEnemy->fsize && pBullet->pos.y <= pEnemy->pos.y + pEnemy->fsize)
//				{
//					HitEnemy(nCntEnemy, 1 + pPlayer->Attackpt[0]);
//					pBullet->bUse = false;
//				}
//			}
//			else if (pEnemy->nType == 3)
//			{
//				if (pBullet->pos.x >= (pEnemy->pos.x - (pEnemy->fsize-50.0f)) && 
//					pBullet->pos.x <= (pEnemy->pos.x + pEnemy->fsize)  &&
//					pBullet->pos.y >= (pEnemy->pos.y - pEnemy->fsize +BULLET_SIZE) && 
//					pBullet->pos.y <= (pEnemy->pos.y + pEnemy->fsize-BULLET_SIZE) )
//				{
//					HitEnemy(nCntEnemy, 1 + pPlayer->Attackpt[0]);
//					pBullet->bUse = false;
//				}
//
//				 else if (pBullet->pos.x >= (pEnemy->pos.x - pEnemy->fsize) &&
//					pBullet->pos.x <= pEnemy->pos.x &&
//					pBullet->pos.y >= (pEnemy->pos.y - pEnemy->fsize + (BULLET_SIZE+60.0f)) &&
//					pBullet->pos.y <= (pEnemy->pos.y + pEnemy->fsize - (BULLET_SIZE+60.0f)))
//				{
//					HitEnemy(nCntEnemy, 1 + pPlayer->Attackpt[0]);
//					pBullet->bUse = false;
//				}
//			}
//		}
//	}
//}
//
////=========================================================================================================
////�v���C���[�̓����蔻��
////=========================================================================================================
//void CollisionPlayer(Bullet *pBullet)
//{
//	int nCntEnemy;
//	Enemy *pEnemy = GetEnemy();
//	Player *pPlayer = GetPlayer();
//
//	if (pBullet->pos.x >= pPlayer->pos.x - 20.0f && pBullet->pos.x <= pPlayer->pos.x + 20.0f  &&
//		pBullet->pos.y >= pPlayer->pos.y - 20.0f && pBullet->pos.y <= pPlayer->pos.y + 20.0f)
//	{
//		if (pPlayer->life <= 1)
//		{
//			SetEnablePause(true);
//			HitPlayer(1);
//
//		}
//		else
//		{
//			SetExplosion(pBullet->pos, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
//			HitPlayer(1);
//		}
//		pBullet->bUse = false;
//	}
//	for (nCntEnemy = 0; nCntEnemy <= MAX_ENEMY; nCntEnemy++, pEnemy++)
//
//	{
//		if (pEnemy->bUse == true)
//		{
//			if (pPlayer->pos.x - 20.0f >= pEnemy->pos.x - pEnemy->fsize &&  pPlayer->pos.x + 20.0f <= pEnemy->pos.x + pEnemy->fsize  &&
//				pPlayer->pos.y - 20.0f >= pEnemy->pos.y - pEnemy->fsize &&  pPlayer->pos.y + 20.0f <= pEnemy->pos.y + pEnemy->fsize)
//			{
//				HitPlayer(1);
//				pBullet->bUse = false;
//			}
//		}
//	}
//}
//}

void BulletFalse(void)
{
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			if (g_aBullet[nCntBullet].Length > 50.0f)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				FinishShadow(g_aBullet[nCntBullet].nIdxShadow);
				g_aBullet[nCntBullet].nIdxShadow = -1;
				g_aBullet[nCntBullet].bUse = false;
				g_UseBullet -= 1;

			}
			else if (g_aBullet[nCntBullet].pos.x >= 1700.0f || g_aBullet[nCntBullet].pos.x <= -1700.0f || g_aBullet[nCntBullet].pos.z >= 1700.0f || g_aBullet[nCntBullet].pos.z <= -1700.0f)
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				FinishShadow(g_aBullet[nCntBullet].nIdxShadow);
				g_aBullet[nCntBullet].nIdxShadow = -1;
				g_aBullet[nCntBullet].bUse = false;
				g_UseBullet -= 1;
			}
			else if (ColissionBullet(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].posOld, g_aBullet[nCntBullet].move, g_aBullet[nCntBullet].type))
			{
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
				FinishShadow(g_aBullet[nCntBullet].nIdxShadow);
				g_aBullet[nCntBullet].nIdxShadow = -1;
				g_aBullet[nCntBullet].bUse = false;
				g_UseBullet -= 1;
			}
		}
	}
}

int GetUseBullet(void)
{
	return g_UseBullet;
}

