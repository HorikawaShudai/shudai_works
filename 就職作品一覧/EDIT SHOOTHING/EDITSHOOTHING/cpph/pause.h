//=============================================================
//
//フェードの処理
//Autor:堀川萩大
//
//=============================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"

typedef enum
{
	PAUSE_CONTENU = 0,	//ゲームに戻る
	PAUSE_RETRY,		//やり直す
	PAUSE_QUIT,			//タイトルに戻る
	PAUSE_RULE,			//操作方法表示
	PAUSE_MAX,
}PAUSE_MENU;

//プロトタイプ宣言
void InitPause(void);
void UninitPause(void);
void UpdataPause(void);
void DrawPause(void);
#endif