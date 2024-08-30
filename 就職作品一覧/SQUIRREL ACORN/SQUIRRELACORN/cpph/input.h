//===========================================================
//
//入力の処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "Xinput.h"

#pragma comment (lib, "xinput.lib")

//プロタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);

HRESULT InitGamePad(HINSTANCE hInstance, HWND hWnd);
void UninitGamePad(void);
void UpdateGamePad(void);
#endif