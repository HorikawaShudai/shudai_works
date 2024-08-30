//===========================================================
//
//�X�R�A�̏�������
//Author:�x�씋��
//
//===========================================================
#include "game.h"
#include "score.h"
#include "input.h"

//�}�N����`
#define NUM_PLACE (8) //�X�R�A�̍ő吔

//�X�R�A�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR col;	    //�F
}score;

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturescore = NULL;		//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffscore = NULL;	//���_�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_posScore;							//�X�R�A�̈ʒu
int g_nScore;									//�X�R�A�̒l

//=========================================================================================================
//����������
//=========================================================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntscore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\number000.png",
		&g_pTexturescore);

	//�X�R�A�̏��̏�����
	g_posScore = D3DXVECTOR3(1000.0f, 10.0f, 0.0f);
	g_nScore = 0;


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffscore,
		NULL);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffscore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntscore = 0; nCntscore < NUM_PLACE; nCntscore++)
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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffscore->Unlock();

}

//=========================================================================================================
//�I������
//=========================================================================================================
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturescore != NULL)
	{
		g_pTexturescore->Release();
		g_pTexturescore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffscore != NULL)
	{
		g_pVtxBuffscore->Release();
		g_pVtxBuffscore = NULL;
	}
}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void UpdataScore(void)
{
	//if (GetKeyboardPress(DIK_1) == true)
	//{//A�̂݉����ꂽ�ꍇ
	//	AddScore(10000000);
	//}
	//if (GetKeyboardPress(DIK_2) == true)
	//{//A�̂݉����ꂽ�ꍇ
	//	AddScore(1000000);
	//}	
	//if (GetKeyboardPress(DIK_3) == true)
	//{//A�̂݉����ꂽ�ꍇ
	//	AddScore(100000);
	//}	
	//if (GetKeyboardPress(DIK_4) == true)
	//{//A�̂݉����ꂽ�ꍇ
	//	AddScore(10000);
	//}	
	//if (GetKeyboardPress(DIK_5) == true)
	//{//A�̂݉����ꂽ�ꍇ
	//	AddScore(1000);
	//}
	//if (GetKeyboardPress(DIK_6) == true)
	//{//A�̂݉����ꂽ�ꍇ
	//	AddScore(100);
	//}
	//if (GetKeyboardPress(DIK_7) == true)
	//{//A�̂݉����ꂽ�ꍇ
	//	AddScore(10);
	//}
	//if (GetKeyboardPress(DIK_8) == true)
	//{//A�̂݉����ꂽ�ꍇ
	//	AddScore(1);
	//}
	//if (GetKeyboardPress(DIK_0) == true)
	//{//A�̂݉����ꂽ�ꍇ
	//	AddScore(-99999999);
	//}
}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntscore;

	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffscore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturescore);

	for (nCntscore = 0; nCntscore < NUM_PLACE; nCntscore++)
	{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntscore * 4, 2);  //�E�����Ԗڂ�ς��Ȃ��Ƃ܂����I�I
	}
}

//=========================================================================================================
//�X�R�A�̐ݒ菈��
//=========================================================================================================
void SetScore(int nScore)
{
	int nCntscore;
	int aTexU[NUM_PLACE];
	int Max;
	int Min;
	int nCount;
	g_nScore += nScore;
	
	for (nCount = 0,Max = 100000000,Min = 10000000; nCount < NUM_PLACE; nCount++,Max/=10,Min/=10)
	{
		aTexU[nCount] = g_nScore % Max / Min;
	}

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	VERTEX_2D *pVtx;
	g_pVtxBuffscore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntscore = 0; nCntscore < NUM_PLACE; nCntscore++)
	{
		pVtx[0].pos = D3DXVECTOR3(g_posScore.x + (20.0f*nCntscore)
			, g_posScore.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posScore.x + 20.0f + (20.0f*nCntscore)
			, g_posScore.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posScore.x + (20.0f*nCntscore)
			, g_posScore.y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posScore.x + 20.0f + (20.0f*nCntscore)
			, g_posScore.y + 20.0f, 0.0f);
		
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f , 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f , 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f , 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f , 1.0f);

		//break; //���d�v�I�I

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffscore->Unlock();
}

//=========================================================================================================
//�X�R�A�̌v�Z����
//=========================================================================================================
void AddScore(int nValue)
{
	int aTexU[NUM_PLACE];
	int nCntscore;
	int Max;
	int Min;
	int nCount;

	g_nScore += nValue;

	if (g_nScore > 99999999)
	{
		g_nScore = 99999999;
	}
	if (g_nScore < 0)
	{
		g_nScore = 0;
	}

	for (nCount = 0, Max = 100000000, Min = 10000000; nCount < NUM_PLACE; nCount++, Max /= 10, Min /= 10)
	{
		aTexU[nCount] = g_nScore % Max / Min;
	}

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	VERTEX_2D *pVtx;
	g_pVtxBuffscore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntscore = 0; nCntscore < NUM_PLACE; nCntscore++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f*aTexU[nCntscore]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f*aTexU[nCntscore]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f*aTexU[nCntscore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f*aTexU[nCntscore]), 1.0f);

		//break; //���d�v�I�I

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffscore->Unlock();
}