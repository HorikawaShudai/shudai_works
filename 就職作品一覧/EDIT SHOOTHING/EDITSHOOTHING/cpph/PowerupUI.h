//=============================================================
//
//UI（パワーアップ）の処理
//Autor:堀川萩大
//
//=============================================================
#ifndef _PowerupUI_H_
#define _PowerupUI_H_
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;	    //位置
	D3DXCOLOR col;			//色
}PWUI;

//プロトタイプ宣言
void InitPwUi(void);
void UninitPwUi(void);
void UpdataPwUi(void);
void DrawPwUi(void);
void ResetUI(void);
#endif
