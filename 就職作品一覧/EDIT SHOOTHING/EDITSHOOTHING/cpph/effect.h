//=============================================================
//
//�G�t�F�N�g�̏���
//Author:�x�씋��
//
//=============================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

void InitEffect(void);
void UninitEffect(void);
void UpdataEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col,float fRadius,int nLife,int nTex);

#endif