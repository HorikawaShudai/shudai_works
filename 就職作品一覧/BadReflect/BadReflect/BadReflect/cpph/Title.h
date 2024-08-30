//=============================================================
//
//ÉäÉUÉãÉg
//Autor:ñxêÏîãëÂ
//
//=============================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "Object.h"
#include "Object2D.h"
#include "Scene.h"

const float FADESPEED(0.01f);
const float SELECTFADESPEED(0.2f);


class CTitle :public CScene
{
public:
	CTitle();
	~CTitle();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void changecol(void);
private:
	CObject2D* m_pLogo;
	CObject2D* m_pButton;
	D3DXCOLOR m_col;
	float m_fadespeed;
	int m_fadestop;
};
#endif