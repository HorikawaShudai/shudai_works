//===========================================================
//
//ビルボードの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"
#include "Object.h"

class CBillboard : public CObject
{
public:
	CBillboard();
	~CBillboard();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetSize(float x ,float y);
	//void SetCol(D3DCOLOR col);
	D3DXVECTOR3 GetPos(void);
	static CObject *CreateBillboard(void);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		//頂点バッファポイント
	D3DXVECTOR3 m_pos;
	D3DXMATRIX m_mtxWorld;
	float m_Height;
	float m_Width;
};


#endif