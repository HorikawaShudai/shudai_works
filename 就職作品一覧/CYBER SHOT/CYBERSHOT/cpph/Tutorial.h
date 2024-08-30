//=============================================================================
//
//チュートリアル画面処理 [Tutorial.h]
// Author : 堀川萩大
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

//プロタイプ宣言
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void UpdateText(void);

#endif