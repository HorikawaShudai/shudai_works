//===========================================================
//
//入力の処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX (256)		//キーの最大数

//グローバル変数
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];
BYTE g_aKeyRepeat[NUM_KEY_MAX];
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];
BYTE LastKey[NUM_KEY_MAX];
int g_nCntRepeat[NUM_KEY_MAX] = {};
XINPUT_STATE g_aGamePadState;

_XINPUT_GAMEPAD g_ButtonState;
//=========================================================================================================
//キーボードの初期化処理
//=========================================================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//Directオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイスの設定
	if (FAILED(g_pInput -> CreateDevice(GUID_SysKeyboard,&g_pDevKeyboard,NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard ->SetDataFormat (&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();
	return S_OK;
}

//=========================================================================================================
//キーボードの終了処理
//=========================================================================================================
void UninitKeyboard(void)
{
//入力デバイス(キーボード)の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard -> Unacquire();
		g_pDevKeyboard -> Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=========================================================================================================
//キーボードの更新処理
//=========================================================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();
	}
	UpdateGamePad();
}

//=========================================================================================================
//入力情報の取得
//=========================================================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}

bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=========================================================================================================
//ゲームパッド
//=========================================================================================================
	
void UninitGamePad(void)
{
	XInputEnable(false);
}
void UpdateGamePad(void)
{

	ZeroMemory(&g_aGamePadState, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &g_aGamePadState);
	
	//ゲームパッドが接続されている状態
	if (dwResult == ERROR_SUCCESS)
	{

	}
	else
	{
		int nData = 0;
	}
}

bool GetGamepadPress(WORD nButton)
{
	return (g_aGamePadState.Gamepad.wButtons & nButton) ? true : false;

}

bool GetGamepadTrigger(WORD nButton)
{
	return (nButton & 0x80) ? true : false;
}
