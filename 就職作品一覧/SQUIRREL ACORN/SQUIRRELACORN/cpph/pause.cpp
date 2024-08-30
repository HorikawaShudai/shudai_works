//===========================================================
//
//�|�[�Y���j���[�̏�������
//Author:�x�씋��
//
//===========================================================
#include "pause.h"
#include "game.h"
//#include "main.h"
#include "Input.h"
#include "fade.h"

//�}�N����`
#define NUM_PAUSE (4)				//�|�[�Y���j���[�̍ő吔

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTexturePause[NUM_PAUSE] = {}; //�|�[�Y���j���[�̐��̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;  //�|�[�Y���j���[�̐��̒��_�o�b�t�@
PAUSE_MENU g_PauseMenu;
D3DXCOLOR g_ColSelect;
D3DXCOLOR g_ColNoSelect;
D3DXCOLOR g_ColInv;

//=========================================================================================================
//�|�[�Y���j���[�̏���������
//=========================================================================================================
void InitPause(void)
{
	int nCntPAUSE;
	g_PauseMenu = PAUSE_CONTENU;
	g_ColSelect = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_ColNoSelect = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	g_ColInv = D3DXCOLOR(0.4f, 0.4f, 0.4f, 0.0f);

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\MENU\\pause000.png",
		&g_pTexturePause[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\MENU\\pause001.png",
		&g_pTexturePause[1]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\MENU\\pause002.png",
		&g_pTexturePause[2]);	
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\MENU\\pause200.png",
		&g_pTexturePause[3]);


	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntPAUSE = 0; nCntPAUSE < NUM_PAUSE; nCntPAUSE++)
	{
		//���_���W�̐ݒ�
		switch (nCntPAUSE)
		{
		case PAUSE_CONTENU:
			pVtx[0].pos = D3DXVECTOR3(430.0f, 260.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(830.0f, 260.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(430.0f, 300.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(830.0f, 300.0f, 0.0f);
			//���_�J���[
			pVtx[0].col = g_ColInv;
			pVtx[1].col = g_ColInv;
			pVtx[2].col = g_ColInv;
			pVtx[3].col = g_ColInv;
			break;
		case PAUSE_RETRY:
			pVtx[0].pos = D3DXVECTOR3(430.0f, 320.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(830.0f, 320.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(430.0f, 360.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(830.0f, 360.0f, 0.0f);
			//���_�J���[
			pVtx[0].col =g_ColInv;
			pVtx[1].col =g_ColInv;
			pVtx[2].col =g_ColInv;
			pVtx[3].col =g_ColInv;
			break;
		case PAUSE_QUIT:
			pVtx[0].pos = D3DXVECTOR3(430.0f, 380.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(830.0f, 380.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(430.0f, 420.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(830.0f, 420.0f, 0.0f);
			//���_�J���[
			pVtx[0].col = g_ColInv;
			pVtx[1].col = g_ColInv;
			pVtx[2].col = g_ColInv;
			pVtx[3].col = g_ColInv;
			break;
		case PAUSE_MAX:
			pVtx[0].pos = D3DXVECTOR3(410.0f, 200.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(890.0f, 200.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(410.0f, 480.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(890.0f, 480.0f, 0.0f);
			//���_�J���[
			pVtx[0].col = g_ColInv;
			pVtx[1].col = g_ColInv;
			pVtx[2].col = g_ColInv;
			pVtx[3].col = g_ColInv;
			break;
		}

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}

//=========================================================================================================
//�|�[�Y���j���[�̏I������
//=========================================================================================================
void UninitPause(void)
{
	int nCntPAUSE;
	for (nCntPAUSE = 0; nCntPAUSE < NUM_PAUSE; nCntPAUSE++)
	{
		if (g_pTexturePause[nCntPAUSE] != NULL)
		{
			g_pTexturePause[nCntPAUSE]->Release();
			g_pTexturePause[nCntPAUSE] = NULL;
		}
	}
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=========================================================================================================
//�|�[�Y���j���[�̍X�V����
//=========================================================================================================
void UpdataPause(void)
{
	int nCntPAUSE;
	bool bPouse = GetPouse();
	FADE fFade = GetFade();
	
	if (bPouse == true)
	{
		VERTEX_2D *pVtx;
		//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
		g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

		if (GetKeyboardTrigger(DIK_W) == true)
		{
			switch (g_PauseMenu)
			{
			case PAUSE_CONTENU:
				g_PauseMenu = PAUSE_QUIT;
				break;
			case PAUSE_RETRY:
				g_PauseMenu = PAUSE_CONTENU;
				break;
			case PAUSE_QUIT:
				g_PauseMenu = PAUSE_RETRY;
				break;
			}
		}
		if (GetKeyboardTrigger(DIK_S) == true)
		{
			switch (g_PauseMenu)
			{
			case PAUSE_CONTENU:
				g_PauseMenu = PAUSE_RETRY;
				break;
			case PAUSE_RETRY:
				g_PauseMenu = PAUSE_QUIT;
				break;
			case PAUSE_QUIT:
				g_PauseMenu = PAUSE_CONTENU;
				break;
			}
		}

		for (nCntPAUSE = 0; nCntPAUSE < NUM_PAUSE; nCntPAUSE++)
		{

			//���_���W�̐ݒ�
			switch (nCntPAUSE)
			{
			case PAUSE_CONTENU:
				if (g_PauseMenu == PAUSE_CONTENU)
				{
					//���_�J���[
					pVtx[0].col = g_ColSelect;
					pVtx[1].col = g_ColSelect;
					pVtx[2].col = g_ColSelect;
					pVtx[3].col = g_ColSelect;
				}
				else
				{
					pVtx[0].col = g_ColNoSelect;
					pVtx[1].col = g_ColNoSelect;
					pVtx[2].col = g_ColNoSelect;
					pVtx[3].col = g_ColNoSelect;
				}
				break;
			case PAUSE_RETRY:
				if (g_PauseMenu == PAUSE_RETRY)
				{
					//���_�J���[
					pVtx[0].col = g_ColSelect;
					pVtx[1].col = g_ColSelect;
					pVtx[2].col = g_ColSelect;
					pVtx[3].col = g_ColSelect;
				}
				else
				{
					pVtx[0].col = g_ColNoSelect;
					pVtx[1].col = g_ColNoSelect;
					pVtx[2].col = g_ColNoSelect;
					pVtx[3].col = g_ColNoSelect;
				}
				break;
			case PAUSE_QUIT:
				if (g_PauseMenu == PAUSE_QUIT)
				{
					//���_�J���[
					pVtx[0].col = g_ColSelect;
					pVtx[1].col = g_ColSelect;
					pVtx[2].col = g_ColSelect;
					pVtx[3].col = g_ColSelect;
				}
				else
				{
					pVtx[0].col = g_ColNoSelect;
					pVtx[1].col = g_ColNoSelect;
					pVtx[2].col = g_ColNoSelect;
					pVtx[3].col = g_ColNoSelect;
				}
				break;
			case PAUSE_MAX:
				//���_�J���[
				pVtx[0].col = g_ColSelect;
				pVtx[1].col = g_ColSelect;
				pVtx[2].col = g_ColSelect;
				pVtx[3].col = g_ColSelect;
				break;

				break;
			}
			pVtx += 4;

		}

		GAMEMODE mode = GetGamemode();

		if (GetKeyboardTrigger(DIK_RETURN) == true &&  fFade == FADE_NONE && mode == GAMEMODE_POUSE)
		{
			switch (g_PauseMenu)
			{
			case PAUSE_CONTENU:
				SetEnablePause(false);
				SetGameMode(GAMEMODE_NONE);
				break;
			case PAUSE_RETRY:
				SetFade(MODE_GAME, 0.01f);
				SetEnablePause(false);
				SetGameMode(GAMEMODE_NONE);
				break;
			case PAUSE_QUIT:
				SetFade(MODE_TITLE, 0.01f);
				break;
			}
		}

		//else if (GetKeyboardTrigger(DIK_P) == true && fFade == FADE_NONE && mode == GAMEMODE_POUSE)
		//{
		//	SetGameMode(GAMEMODE_NONE);
		//	SetEnablePause(false);


		//}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPause->Unlock();
	}
}

//=========================================================================================================
//�|�[�Y���j���[�̕`�揈��
//=========================================================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntPAUSE;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_pTexturePause[3]);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 3 * 4, 2);

	for (nCntPAUSE = 0; nCntPAUSE < 3; nCntPAUSE++)
	{
		pDevice->SetTexture(0, g_pTexturePause[nCntPAUSE]);

		//�|���S��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPAUSE * 4, 2);
	}
}