//=========================================================================================================
//
//ƒŒƒ“ƒ_ƒ‰[‚Ìˆ—
//Author:–xì”‹‘å
//
//=========================================================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"


class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWd, BOOL hWinfow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void);

private:

	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
};

#endif