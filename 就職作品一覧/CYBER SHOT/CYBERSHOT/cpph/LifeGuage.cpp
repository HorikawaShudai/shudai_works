//===========================================================
//
//���C�t�̏�������
//Author:�x�씋��
//
//===========================================================
#include "game.h"
#include "player.h"
#include "Enemy.h"
#include "LifeGuage.h"
#include "input.h"

//�}�N����`
#define NUM_LIFE (4) //���C�t�̍ő吔
#define GUAGE_HEIGHT (400.0f)

//���C�t�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;	    //�F
	LPDIRECT3DTEXTURE9 TexNum;
	int MaxLife;
}LIFE;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturelife = NULL;		//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufflife = NULL;	//���_�o�b�t�@�̃|�C���^
LIFE g_aLifeGuage[NUM_LIFE];
//=========================================================================================================
//����������
//=========================================================================================================
void InitLifeGuage(void)
{

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\gage.png",
		&g_pTexturelife);


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufflife,
		NULL);
	PLAYER aPlayer = GetPlayer();
	ENEMY aEnemy = GetEnemy();

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBufflife->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCnt = 0; nCnt < NUM_LIFE; nCnt++)
	{
		switch (nCnt)
		{
		case 0:

			g_aLifeGuage[nCnt].pos = D3DXVECTOR3(140.0f, 10.0f, 0.0f);
			g_aLifeGuage[nCnt].MaxLife = aPlayer.nLife;
			g_aLifeGuage[nCnt].TexNum = NULL;
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x + ((GUAGE_HEIGHT / g_aLifeGuage[nCnt].MaxLife)*aPlayer.nLife), g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y + 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x + ((GUAGE_HEIGHT / g_aLifeGuage[nCnt].MaxLife)*aPlayer.nLife), g_aLifeGuage[nCnt].pos.y + 20.0f, 0.0f);
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
			break;
		case 1:
			g_aLifeGuage[nCnt].pos = D3DXVECTOR3(1140.0f, 10.0f, 0.0f);
			g_aLifeGuage[nCnt].MaxLife = aEnemy.nLife;
			g_aLifeGuage[nCnt].TexNum = NULL;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x - ((GUAGE_HEIGHT/ g_aLifeGuage[nCnt].MaxLife)*aEnemy.nLife), g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y + 20.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x - ((GUAGE_HEIGHT/ g_aLifeGuage[nCnt].MaxLife)*aEnemy.nLife), g_aLifeGuage[nCnt].pos.y + 20.0f, 0.0f);
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			break;

		case 2:

			g_aLifeGuage[nCnt].pos = D3DXVECTOR3(135.0f, 5.0f, 0.0f);
			g_aLifeGuage[nCnt].MaxLife = aPlayer.nLife;
			g_aLifeGuage[nCnt].TexNum = g_pTexturelife;
			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x + 410.0f, g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y + 30.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x + 410.0f, g_aLifeGuage[nCnt].pos.y + 30.0f, 0.0f);
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case 3:
			g_aLifeGuage[nCnt].pos = D3DXVECTOR3(735.0f, 5.0f, 0.0f);
			g_aLifeGuage[nCnt].MaxLife = aEnemy.nLife;
			g_aLifeGuage[nCnt].TexNum = g_pTexturelife;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x + 410.0f, g_aLifeGuage[nCnt].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x, g_aLifeGuage[nCnt].pos.y + 30.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aLifeGuage[nCnt].pos.x + 410.0f, g_aLifeGuage[nCnt].pos.y + 30.0f, 0.0f);
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;


		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBufflife->Unlock();

}

//=========================================================================================================
//�I������
//=========================================================================================================
void UninitLifeGuage(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturelife != NULL)
	{
		g_pTexturelife->Release();
		g_pTexturelife = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBufflife != NULL)
	{
		g_pVtxBufflife->Release();
		g_pVtxBufflife = NULL;
	}
}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void UpdatePlayerGuage(void)
{

	PLAYER aPlayer = GetPlayer();

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBufflife->Lock(0, 0, (void**)&pVtx, 0);


	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_aLifeGuage[0].pos.x, 
		g_aLifeGuage[0].pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aLifeGuage[0].pos.x + ((GUAGE_HEIGHT / g_aLifeGuage[0].MaxLife)*aPlayer.nLife), 
		g_aLifeGuage[0].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aLifeGuage[0].pos.x, 
		g_aLifeGuage[0].pos.y + 20.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aLifeGuage[0].pos.x + ((GUAGE_HEIGHT / g_aLifeGuage[0].MaxLife)*aPlayer.nLife), 
		g_aLifeGuage[0].pos.y + 20.0f, 0.0f);
	if (aPlayer.nLife <= 3)
	{
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else 
	{
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBufflife->Unlock();
}
//=========================================================================================================
//�X�V����
//=========================================================================================================
void UpdateEnemyGuage(void)
{

	ENEMY aEnemy = GetEnemy();

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBufflife->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4;
	//���_���Wh
	pVtx[0].pos = D3DXVECTOR3(g_aLifeGuage[1].pos.x - ((GUAGE_HEIGHT / g_aLifeGuage[1].MaxLife)*aEnemy.nLife),
		g_aLifeGuage[1].pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aLifeGuage[1].pos.x, 
		g_aLifeGuage[1].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aLifeGuage[1].pos.x - ((GUAGE_HEIGHT / g_aLifeGuage[1].MaxLife)*aEnemy.nLife),
		g_aLifeGuage[1].pos.y + 20.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aLifeGuage[1].pos.x,
		g_aLifeGuage[1].pos.y + 20.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBufflife->Unlock();
}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void DrawLifeGuage(void)
{

	LPDIRECT3DDEVICE9 pDevice;


	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufflife, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	MODE aMode = GetMode();
	if (aMode == MODE_TUTORIAL)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_aLifeGuage[0].TexNum);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);  //�E�����Ԗڂ�ς��Ȃ��Ƃ܂����I�I
																   //�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_aLifeGuage[2].TexNum);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * 2, 2);  //�E�����Ԗڂ�ς��Ȃ��Ƃ܂����I�I
	}
	else if (aMode == MODE_GAME)
	{
		for (int nCnt = 0; nCnt < NUM_LIFE; nCnt++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_aLifeGuage[nCnt].TexNum);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);  //�E�����Ԗڂ�ς��Ȃ��Ƃ܂����I�I
		}
	}

}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void DrawPlayerGuage(void)
{

	LPDIRECT3DDEVICE9 pDevice;


	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBufflife, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);  //�E�����Ԗڂ�ς��Ȃ��Ƃ܂����I�I
}