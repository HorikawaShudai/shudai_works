//=============================================================
//
//UI�i�p���[�A�b�v�j�̏���
//Autor:�x�씋��
//
//=============================================================
#ifndef _PowerupUI_H_
#define _PowerupUI_H_
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;	    //�ʒu
	D3DXCOLOR col;			//�F
}PWUI;

//�v���g�^�C�v�錾
void InitPwUi(void);
void UninitPwUi(void);
void UpdataPwUi(void);
void DrawPwUi(void);
void ResetUI(void);
#endif
