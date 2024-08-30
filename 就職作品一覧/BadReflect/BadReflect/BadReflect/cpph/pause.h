//=============================================================
//
//フェードの処理
//Autor:堀川萩大
//
//=============================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"
#include "Object.h"
#include "Object2D.h"

//　マクロ定義
const int NUM_PAUSE(3);				//ポーズメニューの最大数


class CPause
{

public:
	typedef enum
	{
		PAUSE_CONTENU = 0,	//ゲームに戻る
		PAUSE_RETRY,		//やり直す
		PAUSE_QUIT,			//タイトルに戻る
		PAUSE_MAX,
	}PAUSE_MENU;
	CPause(int nPriority = 6);
	~CPause();

	HRESULT Init(void);
	void Update(void);
	void Uninit(void);
	void Draw(void);
	void Select(void);
	void Changecol(void);
	static CPause* Create(void);
	D3DXVECTOR3 GetPos(void);
private:
	//グローバル変数宣言
	PAUSE_MENU PauseMenu;
	D3DXCOLOR ColSelect;
	D3DXCOLOR ColNoSelect;
	bool m_PressP;
	CObject2D* m_pPauseBg;
	CObject2D* m_pPauseObject[PAUSE_MAX];
};
#endif