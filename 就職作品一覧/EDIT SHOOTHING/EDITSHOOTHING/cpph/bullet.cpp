//===========================================================
//
//�e�̏�������
//Author:�x�씋��
//
//===========================================================
#include "game.h"
#include "bullet.h"
#include "explosion.h"
#include "input.h"
#include "enemy.h"
#include "player.h"
#include "sound.h"
#include "effect.h"

//�}�N����`
#define MAX_BULLET (512) //�e�̍ő吔
#define BULLET_SIZE (10.0f) //�e�̍ő吔
#define BULLET_WIDTH (20.0f) //�e�̍ő吔
#define BULLET_HEIGHT (20.0f) //�e�̍ő吔

//�e�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 frot;		   //�e�̌���
	D3DXCOLOR col;
	BULLETTYPE type;	//�e�̎��
	bool bUse;			//�g�p�̗L��
}Bullet;//�e

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@�̃|�C���^
Bullet g_aBullet[MAX_BULLET];						//�e�̏��
float g_fAngleBullet;
float g_fLengthBullet;

//�v���g�^�C�v�錾
void CollisionEnemy(Bullet *pBullet);
void CollisionPlayer(Bullet *pBullet);

//=========================================================================================================
//����������
//=========================================================================================================
void InitBullet(void)
{

	g_fLengthBullet = sqrtf((BULLET_WIDTH *BULLET_WIDTH)+ (BULLET_HEIGHT*BULLET_HEIGHT))*0.5f;
	g_fAngleBullet = atan2f(BULLET_WIDTH, BULLET_HEIGHT);
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\player_shot.png",
		&g_pTextureBullet);

	//�e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].frot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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
		pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

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
void UpdataBullet(void)
{
	int nCntBullet;
	//int nCntEnemy;
	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].pos.x += sinf(g_aBullet[nCntBullet].frot.z) * g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].pos.y += cosf(g_aBullet[nCntBullet].frot.z) * g_aBullet[nCntBullet].move.y;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x +sinf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z +(D3DX_PI + g_fAngleBullet)) * g_fLengthBullet, 
				                      g_aBullet[nCntBullet].pos.y +cosf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z + (D3DX_PI + g_fAngleBullet)) * g_fLengthBullet,
				                      0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + sinf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z + (D3DX_PI - g_fAngleBullet)) * g_fLengthBullet,
				                      g_aBullet[nCntBullet].pos.y + cosf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z + (D3DX_PI - g_fAngleBullet)) * g_fLengthBullet,
				                      0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + sinf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z  - g_fAngleBullet) * g_fLengthBullet,
				                      g_aBullet[nCntBullet].pos.y + cosf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z - g_fAngleBullet) * g_fLengthBullet,
				                      0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + sinf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z + g_fAngleBullet) * g_fLengthBullet,
				                      g_aBullet[nCntBullet].pos.y + cosf((D3DX_PI *0.5f) + g_aBullet[nCntBullet].frot.z + g_fAngleBullet) * g_fLengthBullet,
				                      0.0f);
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{

				SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 20.0f, 3,0);
			}
			if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{

				SetEffect(D3DXVECTOR3(g_aBullet[nCntBullet].pos), D3DXCOLOR(0.0f, 8.0f, 0.0f, 1.0f), 20.0f, 3,0);
			}
			//�e����ʊO�ɍs�����Ƃ�
			if (g_aBullet[nCntBullet].pos.y <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			else if (g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			else if (g_aBullet[nCntBullet].pos.x <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			else if (g_aBullet[nCntBullet].pos.x >= SCREEN_WIDTH)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			Player *pPlayer = GetPlayer();
			GAMEMODE aMode = GetGamemode();
			
			if (aMode == GAMEMODE_NONE)
			{
				//�e�Ƃ̓����蔻��
				if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
				{//�����̒e������ɓ���������
					CollisionEnemy(&g_aBullet[nCntBullet]);
				}
				else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY && pPlayer->state == PLAYERSTATE_NORMAL)
				{//�G�̒e�������ɓ���������
					CollisionPlayer(&g_aBullet[nCntBullet]);
				}
			}
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
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0 ; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);  //�E�����Ԗڂ�ς��Ȃ��Ƃ܂����I�I
		}
	}
}

//=========================================================================================================
//�e�̐ݒ菈��
//=========================================================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot,BULLETTYPE type , D3DXCOLOR col)
{
	int nCntBullet;
	Player aPlayer = *GetPlayer();

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].col = col;
			g_aBullet[nCntBullet].frot.z = rot.z;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE , g_aBullet[nCntBullet].pos.y - BULLET_SIZE , 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE , g_aBullet[nCntBullet].pos.y - BULLET_SIZE , 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE , g_aBullet[nCntBullet].pos.y + BULLET_SIZE , 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE , g_aBullet[nCntBullet].pos.y + BULLET_SIZE , 0.0f);
			
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(g_aBullet[nCntBullet].col);
			pVtx[1].col = D3DXCOLOR(g_aBullet[nCntBullet].col);
			pVtx[2].col = D3DXCOLOR(g_aBullet[nCntBullet].col);
			pVtx[3].col = D3DXCOLOR(g_aBullet[nCntBullet].col);

			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].bUse = true;

			break; //���d�v�I�I
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//=========================================================================================================
//�G�̓����蔻��
//=========================================================================================================
void CollisionEnemy(Bullet *pBullet)
{
	Enemy *pEnemy = GetEnemy();
	Player *pPlayer = GetPlayer();
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy <= MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			if (pEnemy->nType == 0 || pEnemy->nType == 1 || pEnemy->nType == 2)
			{
				if (pBullet->pos.x >= pEnemy->pos.x - pEnemy->fsize && pBullet->pos.x <= pEnemy->pos.x + pEnemy->fsize  &&
					pBullet->pos.y >= pEnemy->pos.y - pEnemy->fsize && pBullet->pos.y <= pEnemy->pos.y + pEnemy->fsize)
				{
					HitEnemy(nCntEnemy, 1 + pPlayer->Attackpt[0]);
					pBullet->bUse = false;
				}
			}
			else if (pEnemy->nType == 3)
			{
				if (pBullet->pos.x >= (pEnemy->pos.x - (pEnemy->fsize-50.0f)) && 
					pBullet->pos.x <= (pEnemy->pos.x + pEnemy->fsize)  &&
					pBullet->pos.y >= (pEnemy->pos.y - pEnemy->fsize +BULLET_SIZE) && 
					pBullet->pos.y <= (pEnemy->pos.y + pEnemy->fsize-BULLET_SIZE) )
				{
					HitEnemy(nCntEnemy, 1 + pPlayer->Attackpt[0]);
					pBullet->bUse = false;
				}

				 else if (pBullet->pos.x >= (pEnemy->pos.x - pEnemy->fsize) &&
					pBullet->pos.x <= pEnemy->pos.x &&
					pBullet->pos.y >= (pEnemy->pos.y - pEnemy->fsize + (BULLET_SIZE+60.0f)) &&
					pBullet->pos.y <= (pEnemy->pos.y + pEnemy->fsize - (BULLET_SIZE+60.0f)))
				{
					HitEnemy(nCntEnemy, 1 + pPlayer->Attackpt[0]);
					pBullet->bUse = false;
				}
			}
		}
	}
}

//=========================================================================================================
//�v���C���[�̓����蔻��
//=========================================================================================================
void CollisionPlayer(Bullet *pBullet)
{
	int nCntEnemy;
	Enemy *pEnemy = GetEnemy();
	Player *pPlayer = GetPlayer();

	if (pBullet->pos.x >= pPlayer->pos.x - 20.0f && pBullet->pos.x <= pPlayer->pos.x + 20.0f  &&
		pBullet->pos.y >= pPlayer->pos.y - 20.0f && pBullet->pos.y <= pPlayer->pos.y + 20.0f)
	{
		if (pPlayer->life <= 1)
		{
			SetEnablePause(true);
			HitPlayer(1);

		}
		else
		{
			SetExplosion(pBullet->pos, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
			HitPlayer(1);
		}
		pBullet->bUse = false;
	}
	for (nCntEnemy = 0; nCntEnemy <= MAX_ENEMY; nCntEnemy++, pEnemy++)

	{
		if (pEnemy->bUse == true)
		{
			if (pPlayer->pos.x - 20.0f >= pEnemy->pos.x - pEnemy->fsize &&  pPlayer->pos.x + 20.0f <= pEnemy->pos.x + pEnemy->fsize  &&
				pPlayer->pos.y - 20.0f >= pEnemy->pos.y - pEnemy->fsize &&  pPlayer->pos.y + 20.0f <= pEnemy->pos.y + pEnemy->fsize)
			{
				HitPlayer(1);
				pBullet->bUse = false;
			}
		}
	}
}

