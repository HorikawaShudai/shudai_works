//===========================================================
//
//ポリゴンの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_
#include "Object3D.h"

class CCylinder :public CObject3D

{
public:
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		//頂点バッファポイント
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_Length;
	D3DXMATRIX m_mtxWorld;
};
#define MAX_CYLINDER  (30)			//分割数
#define CYLINDER_SIZE (2500.0f)		//距離
#define CYLINDER_HEIGHT (5000.0f)	//高さ

#endif