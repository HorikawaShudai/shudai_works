//=========================================================================================================
//
//エフェクトの処理
//Author:堀川萩大
//
//=========================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "Object2D.h"
#include "Billboard.h"


class CEffect : public CBillboard
{
public:
	CEffect(int nPriority = 5);
	~CEffect();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect* Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_move;
	D3DXCOLOR m_col;	    //色
	float m_fRadius;		//半径
	int m_nLife;			//寿命
};
#endif