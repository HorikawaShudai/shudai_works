//===========================================================
//
//UI�̏�������
//Author:�x�씋��
//
//===========================================================
#include "DethUi.h"
#include "game.h"

//�}�N����`

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureDethUi = NULL; //UI�̐��̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffDethUi = NULL;  //UI�̐��̒��_�o�b�t�@


//=========================================================================================================
//UI�̏���������
//=========================================================================================================
void InitDethUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffDethUi,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\DETH.png",
		&g_pTextureDethUi);


	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffDethUi->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(320.0f, 200.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(960.0f, 200.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(320.0f, 550.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(960.0f, 550.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffDethUi->Unlock();
}

//=========================================================================================================
//UI�̏I������
//=========================================================================================================
void UninitDethUi(void)
{
	if (g_pTextureDethUi != NULL)
	{
		g_pTextureDethUi->Release();
		g_pTextureDethUi = NULL;
	}

	if (g_pVtxBuffDethUi != NULL)
	{
		g_pVtxBuffDethUi->Release();
		g_pVtxBuffDethUi = NULL;
	}
}

//UI�̍X�V����
void UpdataDethUi(void)
{

}

//=========================================================================================================
//UI�̕`�揈��
//=========================================================================================================
void DrawDethUi(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffDethUi, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);


	pDevice->SetTexture(0, g_pTextureDethUi);

	//�|���S��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}