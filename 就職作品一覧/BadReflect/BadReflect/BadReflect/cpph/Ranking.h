//=============================================================
//
//�����L���O�̏���
//Autor:�x�씋��
//
//=============================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "Score.h"
#include "sound.h"

//�}�N����`
const int NUM_RANKING	(6); //�X�R�A�̕\����
const int NUM_RANKUI	(5); //�X�R�A�̕\����
const int NUM_TEXTURE	(2); //�X�R�A�̕\����


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
	static int g_nTitleCnt;									//�X�R�A�̒l

};
#endif