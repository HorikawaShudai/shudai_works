//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 堀川萩大
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンド一覧
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_BGM005,			// BGM5
	SOUND_LABEL_BGM006,			// BGM6
	SOUND_LABEL_BGM007,			// BGM7
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_SELECT,		// 弾発射音
	SOUND_LABEL_SE_HIT,			// ヒット音
	SOUND_LABEL_SE_NOHIT,
	SOUND_LABEL_SE_EXPLOSION,	// 爆発音
	SOUND_LABEL_SE_DECISION,	// 決定音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
