//=============================================================================
//
//�Q�[����ʏ��� [game.h]
// Author : �x�씋��
//
//=============================================================================
#include <stdio.h>
#include "game.h"
#include "bg.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "main.h"
#include "block.h"
//#include "bullet.h"
//#include "enemy.h"
//#include "explosion.h"
//#include "score.h"
#include "sound.h"
//#include "effect.h"
#include "pause.h"
#include "life.h"
#include "Item.h"
#include "DethUi.h"
#include "CreateMap.h"


//�O���[�o���ϐ��錾
bool g_bPause;
int g_nCntFade;
GAMEMODE g_Gamemode;
void DrawPos(void);
void DrawPBlock(void);

//=========================================================================================================
//�Q�[����ʂ̏���������
//=========================================================================================================
void InitGame(void)
{
	g_bPause = false;
	g_nCntFade = 0;
	g_Gamemode = GAMEMODE_NONE; 

	//�w�i�̏���������
	InitBg();
	//�u���b�N�̏���������
	InitBlock();
	//�v���C���[�̏���������
	InitPlayer();
	//���C�t�̏���������
	InitLife();
	//�A�C�e���̏���������
	InitItem();
	//UI�̏���������
	InitDethUi();
	InitPause();

	//�}�b�v����
	LoadMap();


	////�e�̏���������
	//InitBullet();
	//�����̏���������
	//InitExplosion();
	////�G�̏���������
	//InitEnemy();
	//////�G�t�F�N�g�̏���������
	//InitEffect();


	//InitScore();
	//SetScore(0);

	////�T�E���h�̏���������
	PlaySound(SOUND_LABEL_BGM007);
}

//=========================================================================================================
//�Q�[����ʂ̏I������
//=========================================================================================================
void UninitGame(void)
{
	//�w�i�̏I������
	UninitBg();
	//�u���b�N�̏I������
	UninitBlock();
	//�v���C���[�̏I������
	UninitPlayer();
	//���C�t�̏I������
	UninitLife();
	//�A�C�e���̏I������
	UninitItem();
	//�|�[�Y���j���[�̏I������
	UninitPause();
	//UI�̏I������
	UninitDethUi();
	////�e�̏I������
	//UninitBullet();
	////�G�̏I������
	//UninitEnemy();
	////�����̏I������
	//UninitExplosion();
	////�G�t�F�N�g�̏I������
	//UninitEffect();
	////�X�R�A�̏I������
	//UninitScore();
	////�|�[�Y���j���[�̏���������
	//InitPause();

	//�T�E���h�̒�~
	StopSound();
}

//=========================================================================================================
//�Q�[����ʂ̍X�V����
//=========================================================================================================
void UpdateGame(void)
{
	Player aPlayer = *GetPlayer();
	FADE fFade = GetFade();

	if (g_bPause == false)
	{
		//�w�i�̍X�V����
		UpdataBg();
		//�u���b�N�̍X�V����
		UpdateBlock();
		//�v���C���[�̍X�V����
		UpdatePlayer();
		//���C�t�̍X�V����
		UpdataLife();
		//�A�C�e���̍X�V����
		UpdataItem();
		////UI�̍X�V����
		UpdataDethUi();

		////�e�̍X�V����
		//UpdataBullet();
		//�G�̍X�V����
		//UpdataEnemy();
		//////�G�t�F�N�g�̍X�V����
		//UpdataEffect();
		////�X�R�A�̍X�V����
		//UpdataScore();
		////�����̍X�V����
		//UpdataExplosion();
	}
	//�|�[�Y���j���[�̍X�V����
	UpdataPause();
	//�X�R�A�̍X�V����
	UpdateFade();

	switch (g_Gamemode)
	{
	case GAMEMODE_NONE :
		break;

	case	GAMEMODE_GAMECLEAR:
		g_nCntFade++;
		if (g_nCntFade == 120)
		{
			SetFade(MODE_RESULT, 0.01f);
		}
		break;
	case GAMEMODE_GAMEOVER:
		g_nCntFade++;
		if (g_nCntFade == 120)
		{
			SetFade(MODE_RESULT, 0.01f);

		}
		break;
	case GAMEMODE_POUSE:
		SetEnablePause(true);

		break;




	}

	if (GetKeyboardTrigger(DIK_P) == true && fFade == FADE_NONE &&g_Gamemode ==GAMEMODE_NONE)
	{
		SetGameMode(GAMEMODE_POUSE);
	}

}

//=========================================================================================================
//�Q�[����ʂ̕`�揈��
//=========================================================================================================
void DrawGame(void)
{
	Player aPlayer = *GetPlayer();

	//�w�i�̕`�揈��
	DrawBg();
	//�u���b�N�̕`�揈��
	DrawBlock();
	//�v���C���[�̕`�揈��
	DrawPlayer();
	//���C�t�̕`�揈��
	DrawLife();	
	//�A�C�e���̕`�揈��
	DrawItem();
	//DrawPos();
	//DrawPBlock();

	//�e�̕`�揈��
	//DrawBullet();
	//�G�̕`�揈��
	//DrawEnemy();
	//�����̕`�揈��
	//DrawExplosion();
	////�G�t�F�N�g�̕`�揈��
	//DrawEffect();
	////�X�R�A�̕`�揈��
	//DrawScore();

	if (aPlayer.nType == PLAYERSTATE_DETH)
	{
		//UI�̕`�揈��
		DrawDethUi();
	}
	if (g_bPause == true)
	{
		//�|�[�Y���j���[�̕`�揈��
		DrawPause();
	}
}

void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

bool GetPouse(void)
{
	return g_bPause;
}

void SetGameMode(GAMEMODE mode)
{
	g_Gamemode = mode;
}

GAMEMODE GetGamemode(void)
{
	return g_Gamemode;
}

//=========================================================================================================
//FPS�̕`�揈��
//=========================================================================================================
void DrawPos(void)
{
	LPD3DXFONT pFont = GetFont();
	D3DXVECTOR3 World = GetWorld();
	Player aPlayer = *GetPlayer();


	RECT rect = { 100,100,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[1024];

	//������ɑ��
	//wsprintf(&aStr[0], "%.1f"/*\n y  %f\n Cx  %f\n  Cy%f\n  move.x  %f\n  move.y  %f*/, pos[4]/*, pos[1], pos[2], pos[3], pos[4], pos[5]*/);


	sprintf(&aStr[0], "%.3f \n%.3f", aPlayer.pos.x, aPlayer.pos.y);
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}