//=========================================================================================================
//
//2D専用のポリゴンの処理
//Author:堀川萩大
//
//=========================================================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "Object2D.h"

//マクロ定義
const int NUM_PLACE(8); //スコアの最大数
const float ALPHASPEED(0.01f);

class CScore :public CObject
{
public:
	CScore();
	~CScore();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore* pCreate(D3DXVECTOR3 pos);
	void SetScore(int nScore);
	void AddScore(int nValue);
	void SetPos(D3DXVECTOR3 pos, float Height, float Width) { m_pos = pos; };
	D3DXVECTOR3 GetPos(void) { return m_pos; };
	int GetScore(void);
	void KightTxt(int nScore);
	void FadeScore(void);

private:
	CObject2D* m_pNumber[NUM_PLACE];
	static D3DXVECTOR3 m_pos;
	int m_Score;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXCOLOR m_col;
	float m_fadespeed;
	int m_fadestop;

};
#endif