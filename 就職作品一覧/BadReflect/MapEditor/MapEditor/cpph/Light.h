//===========================================================
//
//���C�g�̏���
//Author:�x�씋��
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

//�v���g�^�C�v�錾

#endif
