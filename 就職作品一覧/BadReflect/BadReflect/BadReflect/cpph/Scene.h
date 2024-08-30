//=========================================================================================================
//
//ÉåÉìÉ_ÉâÅ[ÇÃèàóù
//Author:ñxêÏîãëÂ
//
//=========================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
#include "Object2D.h"
#include "Input.h"
#include "Camera.h"
#include "Light.h"
#include "Field.h"
#include "Texture.h"
#include "3DPlayer.h"
#include "3DEnemy.h"
#include <iostream>
#include <cmath>


class CScene
{
public:
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_CLEAR,
		MODE_END,
		MODE_RANKING,
		MODE_MAX
	}MODE;
	CScene();
	~CScene();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	D3DXVECTOR3 GetPos(void);
	static CScene* Create(CScene::MODE mode);
	MODE m_mode;
private:
};

#endif