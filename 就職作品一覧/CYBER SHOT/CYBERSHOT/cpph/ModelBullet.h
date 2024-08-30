//===========================================================
//
//���f���e�̏�������
//Author:�x�씋��
//
//===========================================================
#ifndef _MODELBULLET_H_
#define _MODELBULLET_H_
#include "main.h"
#include "model.h"
#include "Bullet.h"

typedef struct
{
	D3DXVECTOR3		pos;
	D3DXVECTOR3		posOld;
	D3DXVECTOR3		rot;
	D3DXVECTOR3		move;
	D3DXVECTOR3		VtxMinModBull;
	D3DXVECTOR3		VtxMaxModBull;
	D3DXMATRIX		mtxWorldModBull;
	DWORD			dwNumMatModBull;
	LPD3DXMESH		pMeshModBull;
	int				nIdxShadow;
	bool			bUse;
	LPDIRECT3DTEXTURE9 pTEXtureModBull[50];
	D3DCOLORVALUE col[256];
	BULLETTYPE type;	//�e�̎��

	//MODEL aModBullModel[2];
}MODBULL;

//�v���g�^�C�v�錾
void InitModBull(void);
void UninitModBull(void);
void UpdateModBull(void);
void DrawModBull(void);
void SetModBull(D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXVECTOR3 move, char *pModBullename);
bool ColissionModBull(D3DXVECTOR3 pos, D3DXVECTOR3 posOld);
void AttackPart(void);
void AttackMob(int nNum);
#endif
