//=============================================================================
//
//�Q�[����ʏ��� [game.h]
// Author : �x�씋��
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_


//��ʃ��[�h�̎��
typedef enum
{
	GAMEMODE_NONE = 0,	//�^�C�g�����
	GAMEMODE_GAMECLEAR,		//�U���I�����
	GAMEMODE_GAMEOVER,		//�Q�[�����
	GAMEMODE_POUSE,	//���U���g���
	GAMEMODE_MAX
}GAMEMODE;

#include "main.h"

//�v���^�C�v�錾
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
GAMEMODE GetGamemode(void);
void SetGamemode(GAMEMODE mode);
void SetEnablePause(bool bPause);
bool GetPouse(void);
#endif