//===========================================================
//
//オブジェクトの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"
#include "Bullet.h"

typedef enum
{
	OBJECT_KIND_000 = 0,
	OBJECT_KIND_001,
	OBJECT_KIND_MAX
}OBJECT_KIND;

typedef struct
{
	D3DXVECTOR3		pos;
	D3DXVECTOR3		rot;
	D3DXVECTOR3		VtxMinObject;
	D3DXVECTOR3		VtxMaxObject;
	D3DXMATRIX		mtxWorldObject;
	DWORD			dwNumMatObject;
	LPD3DXMESH		pMeshObject;
	int				nIdxShadow;
	bool			bUse;
	LPDIRECT3DTEXTURE9 pTEXtureObject[50];
	OBJECT_KIND ObjectCode;
}OBJECT;

//プロトタイプ宣言
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pObjectename);
OBJECT GetObject(void);
D3DXVECTOR3 ColissionObject(D3DXVECTOR3 possize, D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *pMove);
bool ColissionBullet(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 pMove,BULLETTYPE nType);


#endif
