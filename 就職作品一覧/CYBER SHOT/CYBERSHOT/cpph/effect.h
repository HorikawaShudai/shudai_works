//=============================================================
//
//エフェクトの処理
//Author:堀川萩大
//
//=============================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

typedef enum
{
	EFFECT_KIND_BULLET = 0,
	EFFECT_KIND_SANDDUST,
	EFFECT_KIND_MAX,
}EFFECTKIND;

void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col,float fRadius,int nLife, EFFECTKIND type);

#endif