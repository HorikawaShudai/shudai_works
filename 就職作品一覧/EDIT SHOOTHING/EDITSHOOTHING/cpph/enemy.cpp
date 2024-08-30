//===========================================================
//
//�G�̏�������
//Author:�x�씋��
//
//===========================================================
#include "game.h"
#include "enemy.h"
#include "Input.h"
#include "Bullet.h"
#include "explosion.h"
#include "score.h"
#include "sound.h"
#include "fade.h"
#include "Item.h"
#include "effect.h"
#include "Player.h"

//�}�N����`
#define NUM_ENEMY  (128)				//�G�̍ő吔

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_apTextureEnemy[4] = {};	//�G�̎�ނ̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//�G�̎�ނ̒��_�o�b�t�@
Enemy g_aEnemy[MAX_ENEMY];								//�G�̎��
int g_nNumEnemy;										//�G�̐�
float g_aEnemySixe[MAX_ENEMY] = {};										//�G�̃T�C�Y
D3DXVECTOR3 g_fpos = D3DXVECTOR3(1000.0f, 360.0f, 0.0f);
D3DXVECTOR3 g_fmove = D3DXVECTOR3(0.0f, 200.0f, 0.0f);
int g_killNum;
int g_nCntShot;

//=========================================================================================================
//�G�̏���������
//=========================================================================================================
void InitEnemy(void)
{
	int nCntEnemy;
	g_nNumEnemy = 0;
	g_killNum = 0;

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ENEMY\\enemy004.png",
		&g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ENEMY\\enemy003.png",
		&g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ENEMY\\enemy001.png",
		&g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ENEMY\\boss.png",
		&g_apTextureEnemy[3]);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntEnemy = 0; nCntEnemy <NUM_ENEMY ; nCntEnemy++)
	{
		//���_���W�̐ݒ�
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
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].EneBullet = 0;
		g_aEnemy[nCntEnemy].EneBtCnt = 0;
		g_aEnemy[nCntEnemy].nLifeHarf = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

	//�G�̐ݒ菈��
	SetEnemy(D3DXVECTOR3(1300.0f, 220.0f, 0.0f), 1, 27.0f); //0
	SetEnemy(D3DXVECTOR3(1350.0f, 220.0f, 0.0f), 1, 27.0f); //1
	SetEnemy(D3DXVECTOR3(1400.0f, 220.0f, 0.0f), 1, 27.0f); //2
	SetEnemy(D3DXVECTOR3(1450.0f, 220.0f, 0.0f), 2, 27.0f); //3
	//�G�̐ݒ菈��								 
	SetEnemy(D3DXVECTOR3(2100.0f, 500.0f, 0.0f), 1, 27.0f); //4
	SetEnemy(D3DXVECTOR3(2150.0f, 500.0f, 0.0f), 1, 27.0f); //5
	SetEnemy(D3DXVECTOR3(2200.0f, 500.0f, 0.0f), 1, 27.0f); //6
	SetEnemy(D3DXVECTOR3(2250.0f, 500.0f, 0.0f), 2, 27.0f); //7
	//�G�̐ݒ菈��								 
	SetEnemy(D3DXVECTOR3(2900.0f, 100.0f, 0.0f), 1, 27.0f); //8
	SetEnemy(D3DXVECTOR3(2900.0f, 200.0f, 0.0f), 0, 27.0f); //9
	SetEnemy(D3DXVECTOR3(2900.0f, 400.0f, 0.0f), 0, 27.0f); //10
	SetEnemy(D3DXVECTOR3(2900.0f, 500.0f, 0.0f), 1, 27.0f); //11
	//�G�̐ݒ菈��								 
	SetEnemy(D3DXVECTOR3(3700.0f, 100.0f, 0.0f), 1, 27.0f); //12
	SetEnemy(D3DXVECTOR3(3800.0f, 200.0f, 0.0f), 0, 27.0f);//13
	SetEnemy(D3DXVECTOR3(3900.0f, 300.0f, 0.0f), 1, 27.0f); //14
	SetEnemy(D3DXVECTOR3(3800.0f, 400.0f, 0.0f), 0, 27.0f);//15
	SetEnemy(D3DXVECTOR3(3700.0f, 500.0f, 0.0f), 1, 27.0f); //16
	//�G�̐ݒ菈��								 
	SetEnemy(D3DXVECTOR3(4700.0f, 100.0f, 0.0f), 1, 27.0f); //17
	SetEnemy(D3DXVECTOR3(4600.0f, 200.0f, 0.0f), 0, 27.0f); //18
	SetEnemy(D3DXVECTOR3(4500.0f, 300.0f, 0.0f), 1, 27.0f); //19
	SetEnemy(D3DXVECTOR3(4600.0f, 400.0f, 0.0f), 0, 27.0f); //20
	SetEnemy(D3DXVECTOR3(4700.0f, 500.0f, 0.0f), 1, 27.0f); //21

}

//=========================================================================================================
//�G�̏I������
//=========================================================================================================
void UninitEnemy(void)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].bUse = false;
		}
	}
	for (nCntEnemy = 0; nCntEnemy < 4; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

		if (g_pVtxBuffEnemy != NULL)
		{
			g_pVtxBuffEnemy->Release();
			g_pVtxBuffEnemy = NULL;
		}
}

//=========================================================================================================
//�G�̍X�V����
//=========================================================================================================
void UpdataEnemy(void)
{
	int nCntEnemy;
	FADE fFade = GetFade();
	int nNumEnemy = *GetNumEnemy();
	Enemy aEnemy = *GetEnemy();
	Player aPlayer = *GetPlayer();
	GAMEMODE aMode = GetGamemode();

	//�{�X����
	if ( nNumEnemy <= 0 && aMode == GAMEMODE_NONE)
	{//�G�����Ȃ��Ȃ����ꍇ

		SetEnemy(D3DXVECTOR3(1400.0f, 350.0f, 0.0f), 3, 100.0f);

	}

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (g_aEnemy[nCntEnemy].nType == 3)
			{//�{�X�̏ꍇ
				if (g_aEnemy[nCntEnemy].pos.x > 900.0f  && g_aEnemy[nCntEnemy].state == ENEMYSTATE_MAX)
				{
					g_aEnemy[nCntEnemy].pos.x -= 1.0f;
				}
				if (g_aEnemy[nCntEnemy].pos.x == 1000.0f  && g_aEnemy[nCntEnemy].state == ENEMYSTATE_MAX )
				{
					//�T�E���h�̒�~
					StopSound();
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					//�T�E���h�̏���������
					PlaySound(SOUND_LABEL_BGM001);
				}

				if (g_aEnemy[nCntEnemy].state != ENEMYSTATE_MAX)
				{
					if (g_aEnemy[nCntEnemy].pos.y < g_fpos.y)
					{
						g_aEnemy[nCntEnemy].pos.y += 1.0f;
					}
					else if (g_aEnemy[nCntEnemy].pos.y > g_fpos.y)
					{
						g_aEnemy[nCntEnemy].pos.y -= 1.0f;
					}

					if (g_aEnemy[nCntEnemy].pos.y == g_fpos.y)
					{
						g_fpos.y += g_fmove.y;

						if (750.0f <= g_fpos.y + g_fmove.y)
						{
							g_fmove.y *= -1.0f;
						}
						else if (10.0f >= g_fpos.y + g_fmove.y)
						{
							g_fmove.y *= -1.0f;
						}
					}
				}
			}
			else
			{//�{�X�ȊO

				g_aEnemy[nCntEnemy].pos.x -= 1.0f;

				if (nCntEnemy <= 3 && nCntEnemy >= 0)
				{
					if (g_aEnemy[nCntEnemy].pos.x <900.0f)
					{
						if (g_aEnemy[nCntEnemy].Farstpos.y > 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y += 2.0f;
						}
						else if (g_aEnemy[nCntEnemy].Farstpos.y < 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y -= 2.0f;
						}
						else
						{
							g_aEnemy[nCntEnemy].pos.x -= 2.0f;
						}
					}
				}
				else if (nCntEnemy <=7 && nCntEnemy >= 4)
				{
					if (g_aEnemy[nCntEnemy].pos.x <900.0f)
					{
						if (g_aEnemy[nCntEnemy].Farstpos.y > 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y += 2.0f;
						}
						else if (g_aEnemy[nCntEnemy].Farstpos.y < 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y -= 2.0f;
						}
						else
						{
							g_aEnemy[nCntEnemy].pos.x -= 2.0f;
						}
					}
				}
				else if (nCntEnemy <=11 && nCntEnemy >= 8)
				{
					if (g_aEnemy[nCntEnemy].pos.x <1000.0f)
					{
						if (g_aEnemy[nCntEnemy].Farstpos.y > 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y -= 1.0f;
						}
						else if (g_aEnemy[nCntEnemy].Farstpos.y < 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y += 1.0f;
						}
						else
						{
							g_aEnemy[nCntEnemy].pos.x -= 1.0f;
						}
					}
				}
				else if (nCntEnemy <=16 && nCntEnemy >= 12)
				{
					if (g_aEnemy[nCntEnemy].pos.x <900.0f)
					{
						if (g_aEnemy[nCntEnemy].Farstpos.y > 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y -= 1.0f;
						}
						else if (g_aEnemy[nCntEnemy].Farstpos.y < 360.f)
						{

							g_aEnemy[nCntEnemy].pos.y += 1.0f;
						}
						else
						{
							g_aEnemy[nCntEnemy].pos.x -= 1.0f;
						}
					}
				}
				else if (nCntEnemy <=21 && nCntEnemy >= 17)
				{
					if (g_aEnemy[nCntEnemy].pos.x <900.0f)
					{
						if (g_aEnemy[nCntEnemy].Farstpos.y > 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y -= 1.0f;
						}
						else if (g_aEnemy[nCntEnemy].Farstpos.y < 360.f)
						{
							g_aEnemy[nCntEnemy].pos.y += 1.0f;
						}
						else
						{
							g_aEnemy[nCntEnemy].pos.x -= 1.0f;
						}
					}
				}

				//�͈͊O�ɏo���ꍇ
					if (g_aEnemy[nCntEnemy].pos.x < 0.0f || g_aEnemy[nCntEnemy].pos.y < 0.0f || g_aEnemy[nCntEnemy].pos.y > 720.0f)
					{
						g_aEnemy[nCntEnemy].bUse = false;
						g_nNumEnemy--;
						g_killNum++;
					}
			}


			if (g_aEnemy[nCntEnemy].pos.x > 0.0f && g_aEnemy[nCntEnemy].pos.x < 1280.0f)
			{

				g_aEnemy[nCntEnemy].EneBullet++;
				if (g_aEnemy[nCntEnemy].nType == 1 || g_aEnemy[nCntEnemy].nType == 2)
				{
					if ((g_aEnemy[nCntEnemy].EneBullet % g_aEnemy[nCntEnemy].EneBtCnt) == 0)
					{
						SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y, 0.0f),
							D3DXVECTOR3(-5.5f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), BULLETTYPE_ENEMY, D3DXCOLOR(0.8f, 0.4f, 0.4f, 1.0f));
					}
				}
				else if (g_aEnemy[nCntEnemy].nType == 0)
				{
					if ((g_aEnemy[nCntEnemy].EneBullet % g_aEnemy[nCntEnemy].EneBtCnt) == 0)
					{
  						SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y, 0.0f),
							D3DXVECTOR3(-6.5f, -6.5f, 0.0f),
							D3DXVECTOR3(0.0f, 0.0f, atan2f((g_aEnemy[nCntEnemy].pos.x -20.0f) - aPlayer.pos.x, (g_aEnemy[nCntEnemy].pos.y) - aPlayer.pos.y))
							, BULLETTYPE_ENEMY, D3DXCOLOR(0.8f, 0.4f, 0.4f, 1.0f));
					}
				}
				else if (g_aEnemy[nCntEnemy].nType == 3  && g_aEnemy[nCntEnemy].state != ENEMYSTATE_MAX)
				{
					if ((g_aEnemy[nCntEnemy].EneBullet % g_aEnemy[nCntEnemy].EneBtCnt) == 0)
					{
						SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 20.0f, g_aEnemy[nCntEnemy].pos.y, 0.0f),
							D3DXVECTOR3(-7.2f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), BULLETTYPE_ENEMY, D3DXCOLOR(0.8f, 0.4f, 0.4f, 1.0f));
						if (g_aEnemy[nCntEnemy].nLife < g_aEnemy[nCntEnemy].nLifeHarf)
						{
							SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 40.0f, g_aEnemy[nCntEnemy].pos.y + 80.0f, 0.0f),
								D3DXVECTOR3(-6.5f, -8.5f, 0.0f), 
								D3DXVECTOR3(0.0f, 0.0f, atan2f((g_aEnemy[nCntEnemy].pos.x + 40.0f)- aPlayer.pos.x, (g_aEnemy[nCntEnemy].pos.y + 80.0f) - aPlayer.pos.y))
								, BULLETTYPE_ENEMY, D3DXCOLOR(0.8f, 0.4f, 0.4f, 1.0f));
							SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 40.0f, g_aEnemy[nCntEnemy].pos.y - 80.0f, 0.0f),
								D3DXVECTOR3(-6.5f, -8.5f, 0.0f), 
								D3DXVECTOR3(0.0f, 0.0f,atan2f((g_aEnemy[nCntEnemy].pos.x + 40.0f)- aPlayer.pos.x, (g_aEnemy[nCntEnemy].pos.y - 80.0f) - aPlayer.pos.y))
								, BULLETTYPE_ENEMY, D3DXCOLOR(0.8f, 0.4f, 0.4f, 1.0f));
							g_nCntShot++;
							if (g_nCntShot % 5 == 0)
							{
								SetEffect(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x, g_aEnemy[nCntEnemy].pos.y, 0.0f),
									D3DXCOLOR(0.0f, 8.0f, 0.0f, 1.0f), 10.0f, 1000, 1);
							}
						}
					}
				}
			}
			if (g_aEnemy[nCntEnemy].nType == 3 && g_aEnemy[nCntEnemy].nLife <= g_aEnemy[nCntEnemy].nLifeHarf)
			{
				g_aEnemy[nCntEnemy].EneBtCnt = 50;
				pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			}
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterstate--;
				if (g_aEnemy[nCntEnemy].nCounterstate <= 0)
				{
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
				}
				break;
			}

			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fsize, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].fsize, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fsize, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].fsize, 0.0f);
		}
		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();


}

//=========================================================================================================
//�G�̕`�揈��
//=========================================================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy <NUM_ENEMY ; nCntEnemy++)
	{

		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			//�|���S��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//=========================================================================================================
//�G�̐ݒu����
//=========================================================================================================
void SetEnemy(D3DXVECTOR3 pos,int Type , float size)
{
	int nCntEnemy;
	Player aPlayer = *GetPlayer();

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{

			g_aEnemy[nCntEnemy].pos = pos;
			g_aEnemy[nCntEnemy].Farstpos = pos;	

			g_aEnemy[nCntEnemy].fsize = size;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3( g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y -g_aEnemy[nCntEnemy].fsize, 0.0f);
			pVtx[1].pos = D3DXVECTOR3( g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y -g_aEnemy[nCntEnemy].fsize, 0.0f);
			pVtx[2].pos = D3DXVECTOR3( g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y +g_aEnemy[nCntEnemy].fsize, 0.0f);
			pVtx[3].pos = D3DXVECTOR3( g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].fsize, g_aEnemy[nCntEnemy].pos.y +g_aEnemy[nCntEnemy].fsize, 0.0f);

			g_aEnemy[nCntEnemy].nType = Type;
			switch (Type)
			{
			case 0:
				g_aEnemy[nCntEnemy].EneBtCnt = 95;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
				g_aEnemy[nCntEnemy].nLife = 8;

				break;
			case 1:
				g_aEnemy[nCntEnemy].EneBtCnt = 75;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
				g_aEnemy[nCntEnemy].nLife = 5;

				break;
			case 2:
				g_aEnemy[nCntEnemy].EneBtCnt = 85;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
				g_aEnemy[nCntEnemy].nLife = 5;

				break;
			case 3:
				g_aEnemy[nCntEnemy].EneBtCnt = 60;
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_MAX;
				g_aEnemy[nCntEnemy].nLife = (80 + (aPlayer.Attackpt[0] * 20));

				break;
			}
			g_aEnemy[nCntEnemy].bUse = true;
			g_nNumEnemy++;

			if (g_aEnemy[nCntEnemy].nLife % 2 == 1)
			{
				g_aEnemy[nCntEnemy].nLifeHarf = ((g_aEnemy[nCntEnemy].nLife - 1) / 2);
			}
			else
			{
				g_aEnemy[nCntEnemy].nLifeHarf = (g_aEnemy[nCntEnemy].nLife / 2);
			}

			break; //���d�v�I�I
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================
//�G�̏�ԑJ�ڏ���
//=========================================================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	FADE fFade = GetFade();
	Player aPlayer = *GetPlayer();


	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_NORMAL)
	{
		g_aEnemy[nCntEnemy].nLife -= nDamage;
	}
	if (g_aEnemy[nCntEnemy].nLife < 1)
	{
		g_nNumEnemy--;
		g_killNum++;

		if (g_aEnemy[nCntEnemy].nType == 3 && fFade == FADE_NONE)
		{
			SetGameMode(GAMEMODE_GAMECLEAR);
			AddScore(16000-(aPlayer.Attackpt[0] * 2000));
		}
		else 
		{
			if (g_aEnemy[nCntEnemy].nType == 2 || g_aEnemy[nCntEnemy].nType == 0)
			{
				DropItem(g_aEnemy[nCntEnemy].pos);
			}
			AddScore(450 - (aPlayer.Attackpt[0] * 50));
		}
		SetExplosion(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 40.0f, g_aEnemy[nCntEnemy].pos.y, 0.0f)
			, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_aEnemy[nCntEnemy].bUse = false;
	}
	else
	{
		pVtx += (4 * nCntEnemy);

		if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_NORMAL)
		{

			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

			g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
			g_aEnemy[nCntEnemy].nCounterstate = 5;
			PlaySound(SOUND_LABEL_SE_HIT);
		}
		else if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_MAX)
		{
			PlaySound(SOUND_LABEL_SE_NOHIT);
		}
	}
	g_pVtxBuffEnemy->Unlock();

}

//=========================================================================================================
//�G�̏��擾����
//=========================================================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//=========================================================================================================
//�G���̎擾����
//=========================================================================================================
int *GetNumEnemy(void)
{
	return &g_nNumEnemy;
}

//=========================================================================================================
//kill���̎擾����
//=========================================================================================================
int *Getg_killNum(void)
{
	return &g_killNum;
}