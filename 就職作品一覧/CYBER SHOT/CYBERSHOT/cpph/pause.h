//=============================================================
//
//�|�[�Y���j���[����
//Autor:�x�씋��
//
//=============================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"

typedef enum
{
	PAUSE_CONTENU = 0,	//�Q�[���ɖ߂�
	PAUSE_RETRY,		//��蒼��
	PAUSE_QUIT,			//�^�C�g���ɖ߂�
	PAUSE_MAX,
}PAUSE_MENU;

//�v���g�^�C�v�錾
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
#endif