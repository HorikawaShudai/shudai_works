//===========================================================
//
//影の処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"

//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(float fLength, D3DXVECTOR3 pos);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void FinishShadow(int nIdxShadow);
#endif