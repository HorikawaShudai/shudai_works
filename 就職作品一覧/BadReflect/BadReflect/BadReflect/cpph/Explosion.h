//=========================================================================================================
//
//2Dê—p‚Ìƒ|ƒŠƒSƒ“‚Ìˆ—
//Author:–xì”‹‘å
//
//=========================================================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "Object2D.h"

class CExplosion : public CObject2D
{
public:
	CExplosion();
	~CExplosion();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_move;
	int m_nCntAnim;
	int m_nCntPattern;
};

#endif#pragma once
