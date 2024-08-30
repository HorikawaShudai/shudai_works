//=============================================================
//
//ÉQÅ[ÉÄÉÇÅ[Éh
//Autor:ñxêÏîãëÂ
//
//=============================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "Object.h"
#include "pause.h"
#include "Score.h"
#include "Scene.h"

class CGame :public CScene
{
public:
	CGame();
	~CGame();

	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void)   override;
	static CScore* GetpScore(void) { return m_pScore; };
private:
	static int m_nCnt;
	static CScore* m_pScore;
	CPause* m_pPause;
};
#endif