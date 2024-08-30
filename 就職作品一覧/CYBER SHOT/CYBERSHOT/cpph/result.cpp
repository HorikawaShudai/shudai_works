//===========================================================
//
//���U���g�̏�������
//Author:�x�씋��
//
//===========================================================
#include "result.h"
#include "Input.h"
#include "sound.h"
#include "fade.h"
#include "player.h"
#include "enemy.h"
#include "Game.h"
#include "Light.h"
#include "Camera.h"
#include "Player.h"
#include "MeshIndex.h"
#include "Shadow.h"

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9 g_pTextureResult[2] = {}; //���U���g�̐��̃e�N�X�`��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffresult = NULL;  //���U���g�̐��̒��_�o�b�t�@

//=========================================================================================================
//���U���g�̏���������
//=========================================================================================================
void InitResult(void)
{
	InitLight();
	InitCamera();
	InitMeshIndex();
	InitShadow();

	GAMEMODE aMode = GetGamemode();

	if (aMode == GAMEMODE_GAMEOVER)
	{
		//�T�E���h�̏���������
		PlaySound(SOUND_LABEL_SE_LOSE);
		InitEndPlayer();
	}
	else if (aMode == GAMEMODE_GAMECLEAR)
	{
		//�T�E���h�̏���������
		PlaySound(SOUND_LABEL_SE_WIN);
		InitClearPlayer();
	}

	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4* 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffresult,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\end_001.png",
		&g_pTextureResult[0]);
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\clear.png",
		&g_pTextureResult[1]);

	VERTEX_2D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffresult->Lock(0, 0, (void**)&pVtx, 0);
	for (int nResCnt = 0; nResCnt < 2; nResCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(300.0f, 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1040.0f, 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1040.0f, 300.0f, 0.0f);

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
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffresult->Unlock();
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetPosCamera(D3DXVECTOR3(300.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 50.0f, 0.0f));
}

//=========================================================================================================
//���U���g�̏I������
//=========================================================================================================
void UninitResult(void)
{
	UninitLight();
	UninitCamera();
	UninitPlayer();
	UninitMeshIndex();
	UninitShadow();
	for (int nResCnt = 0; nResCnt < 2; nResCnt++)
	{
		if (g_pTextureResult[nResCnt] != NULL)
		{
			g_pTextureResult[nResCnt]->Release();
			g_pTextureResult[nResCnt] = NULL;
		}
	}
	if (g_pVtxBuffresult != NULL)
	{
		g_pVtxBuffresult->Release();
		g_pVtxBuffresult = NULL;
	}
	//�T�E���h�̒�~
	StopSound();
}

//=========================================================================================================
//���U���g�̍X�V����
//=========================================================================================================
void UpdateResult(void)
{
	//UpdateLight();
	UpdateShadow();
	EndCamera();
	FADE fFade;
	fFade = GetFade();
	if (GetKeyboardTrigger(DIK_RETURN) == true && fFade == FADE_NONE)
	{//space�̂݉����ꂽ�ꍇ
		SetFade(MODE_TITLE,0.05f);
		return;
	}
}

//=========================================================================================================
//���U���g�̕`�揈��
//=========================================================================================================
void DrawResult(void)
{
	SetEndCam();
	DrawPlayer();
	DrawMeshIndex();
	DrawShadow();
	PDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffresult, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	GAMEMODE aMode = GetGamemode();

	if (aMode == GAMEMODE_GAMEOVER)
	{
		pDevice->SetTexture(0, g_pTextureResult[0]);
	}
	else if (aMode == GAMEMODE_GAMECLEAR)
	{
		pDevice->SetTexture(0, g_pTextureResult[1]);
	}

	//�|���S��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}