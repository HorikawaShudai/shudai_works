//=============================================================
//
//ƒŠƒUƒ‹ƒg
//Autor:–xì”‹‘å
//
//=============================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "Object.h"
#include "Object2D.h"
#include "Scene.h"

class CTutorial :public CScene
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void)   override;
private:
	CObject2D* m_pPoly;

};
#endif