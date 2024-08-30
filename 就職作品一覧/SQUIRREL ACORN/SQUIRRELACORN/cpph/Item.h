//=============================================================
//
//アイテムの処理
//Autor:堀川萩大
//
//=============================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"

typedef enum
{
	ITEM_GOAL = 0,	//ゴール
	ITEM_KEY,		//ゴール
	ITEM_MAX,
}ITEM_KIND;

typedef struct
{
	bool bUse;
	ITEM_KIND nType;
	D3DXVECTOR3 pos;		//アイテムの位置
	D3DXVECTOR3 posworld;		//アイテムの位置
}ITEM;

//プロトタイプ宣言
void InitItem(void);
void UninitItem(void);
void UpdataItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, ITEM_KIND ntype);
bool CollisionItem(D3DXVECTOR3 pPos,float fWidth, float fHeight);
#endif