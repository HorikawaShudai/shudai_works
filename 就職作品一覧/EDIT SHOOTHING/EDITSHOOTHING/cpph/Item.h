//=============================================================
//
//�A�C�e���̏���
//Autor:�x�씋��
//
//=============================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"


typedef struct
{
	bool bUse;
	D3DXVECTOR3 pos;		//�A�C�e���̈ʒu
}ITEM;

//�v���g�^�C�v�錾
void InitItem(void);
void UninitItem(void);
void UpdataItem(void);
void DrawItem(void);
void DropItem(D3DXVECTOR3 pos);
void CollisionItem(ITEM *pItem);
#endif