//===========================================================
//
//�A�C�e���̏�������
//Author:�x�씋��
//
//===========================================================
#include "game.h"
//#include "main.h"
#include "Item.h"
#include "Input.h"
#include "enemy.h"
#include "player.h"

//�}�N����`
#define NUM_ITEM (80)				//�A�C�e���̍ő吔

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureItem = NULL; //�A�C�e���̐��̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;  //�A�C�e���̐��̒��_�o�b�t�@
float g_TexV;                        //�A�C�e���̈ړ���V�l
float g_TexU;                        //�A�C�e���̈ړ���U�l
ITEM g_aItem[NUM_ITEM];



 //=========================================================================================================
 //�A�C�e���̏���������
 //=========================================================================================================
void InitItem(void)
{
	int nCntItem;

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\dropitem.png",
		&g_pTextureItem);

	//�e�N�X�`���ړ����x�̏�����
	g_TexV = 0.5f;	//�A�C�e���̈ړ���V�l
	g_TexU = 0.000f;	//�A�C�e���̈ړ���U�l

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f ,0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f ,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f ,1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f ,1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=========================================================================================================
//�A�C�e���̏I������
//=========================================================================================================
void UninitItem(void)
{
	int nCntItem;

	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			g_aItem[nCntItem].bUse = false;
		}
	}
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//�A�C�e���̍X�V����
void UpdataItem(void)
{
	int nCntItem;

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	
	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			g_aItem[nCntItem].pos.x -= g_TexV;
			g_aItem[nCntItem].pos.y -= g_TexU;
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y - 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y - 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - 20.0f, g_aItem[nCntItem].pos.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 20.0f, g_aItem[nCntItem].pos.y + 20.0f, 0.0f);

		if (g_aItem[nCntItem].pos.x <= 0)
		{
			g_aItem[nCntItem].bUse = false;
		}

		//�A�C�e���̎擾����
		CollisionItem(&g_aItem[nCntItem]);

		}
		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=========================================================================================================
//�A�C�e���̕`�揈��
//=========================================================================================================
void DrawItem(void)
{
	int nCntItem;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_pTextureItem);

	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			//�|���S��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4* nCntItem, 2);
		}
	}
}

//=========================================================================================================
//�h���b�v�A�C�e���̏���
//=========================================================================================================
void DropItem(D3DXVECTOR3 pos)
{
	int nCntItem;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	VERTEX_2D *pVtx;
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].pos = pos;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x -10.0f,g_aItem[nCntItem].pos.y - 10.0f,0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x +10.0f,g_aItem[nCntItem].pos.y - 10.0f,0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x -10.0f,g_aItem[nCntItem].pos.y + 10.0f,0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x +10.0f,g_aItem[nCntItem].pos.y + 10.0f,0.0f);

			g_aItem[nCntItem].bUse = true;
			break; //���d�v�I�I
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=========================================================================================================
//�A�C�e���̎擾����
//=========================================================================================================
void CollisionItem(ITEM *pItem)
{
	Player *pPlayer = GetPlayer();

	if (pItem->pos.x >= pPlayer->pos.x - 20.0f && pItem->pos.x <= pPlayer->pos.x + 20.0f  &&
		pItem->pos.y >= pPlayer->pos.y - 20.0f && pItem->pos.y <= pPlayer->pos.y + 20.0f)
	{
		GetItem(1);

		pItem->bUse = false;
	}
}
