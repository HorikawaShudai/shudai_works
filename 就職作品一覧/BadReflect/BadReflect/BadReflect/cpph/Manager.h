//=========================================================================================================
//
//ÉåÉìÉ_ÉâÅ[ÇÃèàóù
//Author:ñxêÏîãëÂ
//
//=========================================================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

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
#include "Scene.h"
#include "pause.h"

class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance ,HWND hWd, BOOL hWinfow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CRenderer *GetRenderer(void);
	CCamera *GetCamera(void);
	CKeyboard* GetInputKeyboard(void);
	CGamepad* GetInputGamepad(void);
	CTexture *GetpTexture(void);
	CFade *GetpFade(void);
	CPause* GetpPause(void);
	CScene* GetpScene(void);
	void SetMode(CScene::MODE mode);
	CScene::MODE GetMode(void);
	static void SetPause(bool PouseNext);
	static bool GetPause(void) { return bPause; };
	static CManager* Get(void);
	static CManager* Create(void);
private:
	CRenderer *m_pRenderer;
	CKeyboard* m_pInputKeyboard;
	CGamepad *m_pInputGamepad;
	CLight   *m_pLight;
	CCamera  *m_pCamera;
	CField  *m_pField;
	CTexture  *m_pTexture;
	CScene *m_pScene;
	CFade* m_pFade;
	CPause* m_pPause;
	static CManager* m_pManager;
	static bool bPause;
	
};





#endif