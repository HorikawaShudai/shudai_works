//===========================================================
//
//モデルの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 Oldpos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 Destrot;
	D3DXVECTOR3 Diffrot;
	D3DXVECTOR3 moveP;
	D3DXVECTOR3 moveR;
	D3DXVECTOR3 VtxMinModel;
	D3DXVECTOR3 VtxMaxModel;
	D3DXMATRIX  mtxWorldModel;
	int nIdxShadow;
	int nIdxModelParent;
}MODEL;

//プロトタイプ宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
MODEL GetModel(void);

#endif
