//=============================================================================
//
//�Q�[����ʏ��� [game.h]
// Author : �x�씋��
//
//=============================================================================
#include "game.h"
#include "bg.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "effect.h"
#include "pause.h"
#include "main.h"
#include "life.h"
#include "Item.h"
#include "PowerupUI.h"


//�O���[�o���ϐ��錾
bool g_bPause;
int g_nCntFade;
GAMEMODE g_Gamemode;

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
	//�v���C���[�̏���������
	InitPlayer();
	//�e�̏���������
	InitBullet();
	//�����̏���������
	InitExplosion();
	//�G�̏���������
	InitEnemy();
	////�G�t�F�N�g�̏���������
	InitEffect();
	//���C�t�̏���������
	InitLife();
	//�A�C�e���̏���������
	InitItem();
	//UI�̏���������

	InitPwUi();
	InitPause();

	InitScore();
	SetScore(0);

	//�T�E���h�̏���������
	PlaySound(SOUND_LABEL_BGM005);
}

//=========================================================================================================
//�Q�[����ʂ̏I������
//=========================================================================================================
void UninitGame(void)
{
	//�w�i�̏I������
	UninitBg();
	//�e�̏I������
	UninitBullet();
	//�G�̏I������
	UninitEnemy();
	//�����̏I������
	UninitExplosion();
	//�|���S���̏I������
	UninitPlayer();
	//���C�t�̏I������
	UninitLife();
	////�G�t�F�N�g�̏I������
	UninitEffect();
	//�X�R�A�̏I������
	UninitScore();
	//�A�C�e���̏I������
	UninitItem();
	//�|�[�Y���j���[�̏���������
	InitPause();
	//�|�[�Y���j���[�̏I������
	UninitPause();
	//UI�̏I������
	UninitPwUi();

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
	/*int nNumEnemy = *GetNumEnemy();
	Enemy aEnemy = *GetEnemy();*/

	if (g_bPause == false)
	{
		//�w�i�̍X�V����
		UpdataBg();
		//�v���C���[�̍X�V����
		UpdataPlayer();
		//���C�t�̍X�V����
		UpdataLife();
		//�e�̍X�V����
		UpdataBullet();
		//�G�̍X�V����
		UpdataEnemy();
		////�G�t�F�N�g�̍X�V����
		UpdataEffect();
		//�X�R�A�̍X�V����
		UpdataScore();
		//�A�C�e���̍X�V����
		UpdataItem();
		//�����̍X�V����
		UpdataExplosion();
		//UI�̍X�V����
		UpdataPwUi();
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

	if (GetKeyboardTrigger(DIK_P) == true && fFade == FADE_NONE && aPlayer.life > 0  &&g_Gamemode ==GAMEMODE_NONE)
	{
		SetGameMode(GAMEMODE_POUSE);
	}

}

//=========================================================================================================
//�Q�[����ʂ̕`�揈��
//=========================================================================================================
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBg();
	//�e�̕`�揈��
	DrawBullet();
	//�v���C���[�̕`�揈��
	DrawPlayer();
	//���C�t�̕`�揈��
	DrawLife();	
	//�G�̕`�揈��
	DrawEnemy();
	//�����̕`�揈��
	DrawExplosion();
	////�G�t�F�N�g�̕`�揈��
	DrawEffect();
	//�X�R�A�̕`�揈��
	DrawScore();
	//�A�C�e���̕`�揈��
	DrawItem();
	DrawPwUi();

	Player aPlayer = *GetPlayer();

	if (g_bPause == true && aPlayer.life > 0)
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