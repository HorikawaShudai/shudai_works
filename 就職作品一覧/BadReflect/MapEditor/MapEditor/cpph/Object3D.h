//=========================================================================================================
//
//3D専用のオブジェクトの処理
//Author:堀川萩大
//
//=========================================================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "Object.h"



class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);
	~CObject3D();

	HRESULT Init(void) = 0;
	void Uninit(void);
	void Update(void) = 0;
	void Draw(void) = 0;

	void SetPos(D3DXVECTOR3 pos, float Height, float Width);
	void SetSize(float Height, float Width);
	static CObject3D *Create(D3DXVECTOR3 pPos, TYPE type3D,int nDate);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	D3DXVECTOR3 GetPos(void);
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
protected:
private:
	D3DXVECTOR3 m_pos;
	int m_nNumObject3D;

	D3DXVECTOR3 m_rot;
	D3DXMATRIX  m_mtxWorld;
};

#endif