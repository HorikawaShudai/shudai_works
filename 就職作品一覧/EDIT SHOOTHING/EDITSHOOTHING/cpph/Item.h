//=============================================================
//
//アイテムの処理
//Autor:堀川萩大
//
//=============================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"


typedef struct
{
	bool bUse;
	D3DXVECTOR3 pos;		//アイテムの位置
}ITEM;

//プロトタイプ宣言
void InitItem(void);
void UninitItem(void);
void UpdataItem(void);
void DrawItem(void);
void DropItem(D3DXVECTOR3 pos);
void CollisionItem(ITEM *pItem);
#endif