//=============================================================================
//
//�`���[�g���A����ʏ��� [Tutorial.h]
// Author : �x�씋��
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

typedef struct
{
	int nCntText;
	bool bUse;
}TEXT;

//�v���^�C�v�錾
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void UpdateText(void);

#endif