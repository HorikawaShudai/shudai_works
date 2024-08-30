//=========================================================================================================
//
//マネージャーの処理
//Author:堀川萩大
//
//=========================================================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "Input.h"
#include "Camera.h"
#include "Light.h"
#include "Field.h"
#include "3DPlayer.h"
#include "Texture.h"

class CManager
{
public:
	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance ,HWND hWd, BOOL hWinfow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRenderer *GetRenderer(void);
	static CCamera *GetCamera(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CTexture *GetpTexture(void);
	static LPDIRECT3DTEXTURE9 m_aTexturePlayer;


private:
	static CRenderer *m_pRenderer;
	static CInputKeyboard *m_pInputKeyboard;
	static CLight   *m_pLight;
	static CCamera  *m_pCamera;
	static CField  *m_pField;
	static CTexture  *m_pTexture;
};

#endif