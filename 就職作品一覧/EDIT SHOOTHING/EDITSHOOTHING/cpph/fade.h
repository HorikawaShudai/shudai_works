//=============================================================
//
//フェードの処理
//Autor:堀川萩大
//
//=============================================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"

typedef enum
{
	FADE_NONE = 0,	//何もしていない状態
	FADE_IN,		//フェードイン状態
	FADE_OUT,		//	フェードアウト状態
	FADE_MAX,
}FADE;

//プロトタイプ宣言
void InitFade(MODE ModeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(MODE ModeNext,float Fade);
FADE GetFade(void);
#endif