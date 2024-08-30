//=============================================================
//
//体力の処理
//Autor:堀川萩大
//
//=============================================================
#ifndef _LIFEGUAGE_H_
#define _LIFEGUAGE_H_

#include "main.h"
#include "Object2D.h"

//マクロ定義
#define NUM_LIFE (2) //ライフの最大数
#define GUAGE_HEIGHT (400.0f)

typedef enum
{
	TYPE_PLAYERLIFE = 0,
	TYPE_PLAYERENAGY,
	TYPE_BOSSLIFE,
}GETTYPE;

class CLifeGuage:public CObject2D
{
public:
	CLifeGuage(int nPriority = 6);
	~CLifeGuage();

	
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CLifeGuage *Create(int type);
private:
	LPDIRECT3DTEXTURE9 m_pTexture = NULL;		//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//頂点バッファのポインタ
	GETTYPE m_type;
	D3DXVECTOR3 m_pos;	//位置
	D3DXCOLOR m_col;	    //色
	LPDIRECT3DTEXTURE9 TexNum;
	
	int m_MaxLife;
	int m_Life;
	float m_Height;
	float m_Enagy;
	float m_MaxEnagy;
};
#endif