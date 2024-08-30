//=============================================================
//
//ƒŠƒUƒ‹ƒg
//Autor:–xì”‹‘å
//
//=============================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "Object.h"
#include "Object2D.h"
#include "Scene.h"

class CResult :public CScene
{
public:
	CResult();
	~CResult();

	 HRESULT Init(void)override;
	 void Uninit(void)override;
	 void Update(void)override;
	 void Draw(void)override;
private:
	CObject2D* m_pPoly;
};
#endif