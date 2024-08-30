//=========================================================================================================
//
//2DêÍópÇÃÉ|ÉäÉSÉìÇÃèàóù
//Author:ñxêÏîãëÂ
//
//=========================================================================================================
#ifndef _TEXTURES_H_
#define _TEXTURES_H_

#include "main.h"
#include "Object.h"
#include "Object2D.h"

#define MAX_BG (3)


class CTextures : public CObject
{
public:
	CTextures();
	~CTextures();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObject2D *Create(TYPE type2D);
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	static CObject2D *m_apObject[MAX_BG];
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_BG];
	LPDIRECT3DTEXTURE9 m_apTexture;
	static D3DXVECTOR3 m_pTexmove[MAX_BG];
	static void Load(void);
private:
	static int NumTexAll;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_Texpos;
	int m_nTexId;
};
#endif