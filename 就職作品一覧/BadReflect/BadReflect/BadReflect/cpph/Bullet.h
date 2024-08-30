//=========================================================================================================
//
//2DêÍópÇÃíeÇÃèàóù
//Author:ñxêÏîãëÂ
//
//=========================================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "Object2D.h"

#define BULLET_LIFE (180)

class CBullet : public CObject2D
{
public:
	CBullet();
	~CBullet();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Create(D3DXVECTOR3 pos);
	bool CollisionEnemy(D3DXVECTOR3 pos);
protected:
	static D3DXVECTOR3 m_pos;
	static D3DXVECTOR3 m_posOld;
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_move;
	int m_Life;
};

#endif#pragma once
