//=========================================================================================================
//
//2Dê—p‚Ìƒ|ƒŠƒSƒ“‚Ìˆ—
//Author:–xì”‹‘å
//
//=========================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "Object2D.h"



class CEnemy : public CObject2D
{
public:
	CEnemy();
	~CEnemy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static D3DXVECTOR3 m_pos;
	static void HitEnemy(int nDamage);
	int m_nLife;
	static void Create(D3DXVECTOR3 pos);
private:
	D3DXVECTOR3 m_move;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif