//=========================================================================================================
//
//2Dê—p‚Ìƒ|ƒŠƒSƒ“‚Ìˆ—
//Author:–xì”‹‘å
//
//=========================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "Object2D.h"


class CPlayer : public CObject2D
{
public:
	CPlayer();
	~CPlayer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void PlayerContoroll(void);
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posOld;

private:
	D3DXVECTOR3 m_move;
	int m_nCntAnim;
	int m_nCntPattern;
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif