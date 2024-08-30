//=============================================================
//
//フェードの処理
//Autor:堀川萩大
//
//=============================================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"

class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,	//何もしていない状態
		FADE_IN,		//フェードイン状態
		FADE_OUT,		//	フェードアウト状態
		FADE_MAX,
	}FADE;
	CFade();
	~CFade();
	 HRESULT Init(void);
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	void SetFade(CScene::MODE ModeNext, float Fade);
	FADE GetFade(void);
	static CFade *Create(void);

private:
	//グローバル変数宣言
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade;  //フェードの数の頂点バッファ
	FADE m_Fade;
	float m_FadeCount;
	D3DXCOLOR m_ColorFade;
	CScene::MODE  m_ModeNext;
	CObject2D* m_pPoly;
};



#endif