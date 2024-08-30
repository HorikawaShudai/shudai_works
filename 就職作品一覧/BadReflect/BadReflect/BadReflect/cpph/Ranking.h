//=============================================================
//
//ランキングの処理
//Autor:堀川萩大
//
//=============================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "Score.h"
#include "sound.h"

//マクロ定義
const int NUM_RANKING	(6); //スコアの表示数
const int NUM_RANKUI	(5); //スコアの表示数
const int NUM_TEXTURE	(2); //スコアの表示数


class CRanking :public CScene
{
public:
	CRanking();
	~CRanking();
	HRESULT Init(void)override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void)   override;
	static void LordScore(void);
private:

	static CScore* m_pScore[NUM_RANKING];
	static int m_rank[NUM_RANKUI];
	CObject2D* m_rankUi[NUM_RANKUI];
	static int g_nTitleCnt;									//スコアの値

};
#endif