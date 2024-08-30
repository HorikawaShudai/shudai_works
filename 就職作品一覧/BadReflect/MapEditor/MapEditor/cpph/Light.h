//===========================================================
//
//ライトの処理
//Author:堀川萩大
//
//===========================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "main.h"


#define MAX_LIGHT (3)

class CLight
{
public:
	CLight();
	~CLight();
	void Init(void);
	void Uninit(void);
	void Updata(void);
private:

	D3DLIGHT9 m_light[MAX_LIGHT];
};

//プロトタイプ宣言

#endif
