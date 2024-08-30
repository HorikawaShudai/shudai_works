//===========================================================
//
//�A�C�e���̏�������
//Author:�x�씋��
//
//===========================================================
#include "game.h"
//#include "main.h"
#include "Item.h"
#include "block.h"
#include "Input.h"
#include "player.h"

//�}�N����`
#define NUM_ITEM (80)				//�A�C�e���̍ő吔
#define NUM_TEX (2)


//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureItem[NUM_TEX] = {}; //�A�C�e���̐��̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;  //�A�C�e���̐��̒��_�o�b�t�@
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
		"data\\TEXTURE\\acorn.png",
		&g_pTextureItem[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Key.png",
		&g_pTextureItem[1]);


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
	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			g_aItem[nCntItem].bUse = false;
		}
	}
	for (int nCntTex = 0; nCntTex < NUM_TEX; nCntTex++)
	{
		if (g_pTextureItem[nCntTex] != NULL)
		{
			g_pTextureItem[nCntTex]->Release();
			g_pTextureItem[nCntTex] = NULL;
		}
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
	D3DXVECTOR3 Worldpos = GetWorld();

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	VERTEX_2D *pVtx;
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			g_aItem[nCntItem].pos = g_aItem[nCntItem].posworld + Worldpos;
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 50.0f, g_aItem[nCntItem].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 50.0f, g_aItem[nCntItem].pos.y + 50.0f, 0.0f);
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


	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].nType]);

			//�|���S��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4* nCntItem, 2);
		}
	}
}

//=========================================================================================================
//�h���b�v�A�C�e���̏���
//=========================================================================================================
void SetItem(D3DXVECTOR3 pos, ITEM_KIND ntype)
{
	int nCntItem;
	D3DXVECTOR3 Worldpos = GetWorld();

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	VERTEX_2D *pVtx;
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].pos = pos+ Worldpos;
			g_aItem[nCntItem].posworld = pos+ Worldpos;
			g_aItem[nCntItem].nType = ntype;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x,       g_aItem[nCntItem].pos.y ,0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x +50.0f,g_aItem[nCntItem].pos.y ,0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x,       g_aItem[nCntItem].pos.y + 50.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + 50.0f, g_aItem[nCntItem].pos.y + 50.0f,0.0f);

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
bool CollisionItem(D3DXVECTOR3 pPos, float fWidth, float fHeight)
{
	bool bCatch =false;
	Player *pPlayer = GetPlayer();

	for (int nCntItem = 0; nCntItem < NUM_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == true)
		{
			float flength[3];
			flength[0] = (pPlayer->pos.x - ((g_aItem[nCntItem].pos.x + (50.0f / 2.0f)))) * (pPlayer->pos.x - ((g_aItem[nCntItem].pos.x + (50.0f / 2.0f))));
			flength[1] = (pPlayer->pos.y - fHeight - g_aItem[nCntItem].pos.y)* (pPlayer->pos.y - fHeight - g_aItem[nCntItem].pos.y);
			flength[2] = (fWidth + (50.0f / 2.0f)) * (fWidth + (50.0f / 2.0f));
			if (flength[0] + flength[1] <= flength[2])
			{//�����蔻��
				if (g_aItem[nCntItem].nType == ITEM_KEY)
				{
					DleatBlock(BLOCKTYPE_ORI);
					g_aItem[nCntItem].bUse = false;
				}
				if (g_aItem[nCntItem].nType == ITEM_GOAL)
				{
					bCatch = true;
					g_aItem[nCntItem].bUse = false;
				}
			}
		}
	}
	return bCatch;
}
