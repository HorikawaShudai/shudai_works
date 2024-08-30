//=============================================================
//
//�A�C�e���̏���
//Autor:�x�씋��
//
//=============================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"

typedef enum
{
	ITEM_GOAL = 0,	//�S�[��
	ITEM_KEY,		//�S�[��
	ITEM_MAX,
}ITEM_KIND;

typedef struct
{
	bool bUse;
	ITEM_KIND nType;
	D3DXVECTOR3 pos;		//�A�C�e���̈ʒu
	D3DXVECTOR3 posworld;		//�A�C�e���̈ʒu
}ITEM;

//�v���g�^�C�v�錾
void InitItem(void);
void UninitItem(void);
void UpdataItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, ITEM_KIND ntype);
bool CollisionItem(D3DXVECTOR3 pPos,float fWidth, float fHeight);
#endif