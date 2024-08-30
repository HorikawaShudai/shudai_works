//===========================================================
//
//ポリゴンの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _FIELD_H_
#define _FIELD_H_
#include "main.h"
#include "Object3D.h"


#define MAX_FIELD  (50)
#define FIELF_SIZE (500.0f)


class CField:public CObject3D
{
public:
	CField(int nPriority = 1);
	~CField();
	//プロトタイプ宣言
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX  m_mtxWorld;
	static LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャポインタ
};

//グローバル変数宣言

#endif