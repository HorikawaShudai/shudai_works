//===========================================================
//
//pアイテムの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"

typedef enum
{
	ITEM_KIND_000 = 0,
	ITEM_KIND_MAX
}ITEM_KIND;


typedef struct
{
	D3DXVECTOR3		pos;
	D3DXVECTOR3		rot;
	D3DXVECTOR3		VtxMinItem;
	D3DXVECTOR3		VtxMaxItem;
	D3DXMATRIX		mtxWorldItem;
	DWORD			dwNumMatItem;
	LPD3DXMESH		pMeshItem;
	int				nIdxShadow;
	bool			bUse;
	LPDIRECT3DTEXTURE9 pTEXtureItem[50]; 
	ITEM_KIND nType;
}ITEM;



//プロトタイプ宣言
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pItemename);
ITEM GetItem(void);
D3DXVECTOR3 ColissionItem(D3DXVECTOR3 possize, D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *pMove);
void ColissionItem(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 pMove);

#endif
