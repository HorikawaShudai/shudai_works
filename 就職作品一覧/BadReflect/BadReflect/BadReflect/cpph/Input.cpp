//===========================================================
//
//入力の処理操作
//Author:堀川萩大
//
//===========================================================
#include "Input.h"


//=============================================基本クラス=============================================
//============================================================
//静的メンバ変数
//============================================================
LPDIRECTINPUT8 CInput:: m_pInput = nullptr;

//============================================================
//コンストラクタ
//============================================================
CInput :: CInput()
{
	m_pDevice = nullptr;
}
//============================================================
//デストラクタ
//============================================================
CInput :: ~CInput()
{

}

//============================================================
//初期化処理
//============================================================
HRESULT CInput:: Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == nullptr)
	{
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//============================================================
//終了処理
//============================================================
void  CInput::Uninit(void)
{
	//入力デバイス(キーボード)の破棄
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//=============================================派生クラス=============================================
//============================================================
// コンストラクタ
//============================================================
CKeyboard::CKeyboard()
{
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(m_aKeyStateKeep, 0, sizeof(m_aKeyStateKeep));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
}
//============================================================
// デストラクタ
//============================================================
CKeyboard::~CKeyboard()
{

}

//============================================================
// 初期化処理
//============================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);


	//Directオブジェクトの生成

	//入力デバイスの設定
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}
	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();
	return S_OK;
}

//============================================================
// 終了処理
//============================================================
void CKeyboard::Uninit(void)
{

}

//============================================================
// 更新処理
//============================================================
void CKeyboard :: Update(void) 
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{

			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];

			m_aKeyState[nCntKey] = aKeyState[nCntKey];

			if (GetPress(nCntKey) == false && GetKeep(nCntKey) == true)
			{
				if (GetRelease(nCntKey) == false)
				{
					m_aKeyStateRelease[nCntKey] = ~m_aKeyStateRelease[nCntKey];
				}
			}
			else
			{
				m_aKeyStateRelease[nCntKey] = false;
			}
			m_aKeyStateKeep[nCntKey] = m_aKeyState[nCntKey];

		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//============================================ 入力情報の取得 ============================================

//============================================================
// プレス処理
//============================================================
bool CKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}
//============================================================
// トリガー処理
//============================================================
bool CKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//============================================================
// リリース処理
//============================================================
bool CKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
//============================================================
// キープ処理
//============================================================
bool CKeyboard::GetKeep(int nKey)
{
	return (m_aKeyStateKeep[nKey] & 0x80) ? true : false;
}

//============================================ ゲームパッド============================================

//============================================================
// コンストラクタ
//============================================================
CGamepad::CGamepad()
{

}

//============================================================
// デストラクタ
//============================================================
CGamepad::~CGamepad()
{

}

//============================================================
// 初期化処理
//============================================================
HRESULT CGamepad::Init(HINSTANCE hInstance, HWND hWnd)
{
	XInputEnable(true);
	return S_OK;

}

//============================================================
// 終了処理
//============================================================
void CGamepad::Uninit(void)
{
	XInputEnable(false);
}

//============================================================
// 更新処理
//============================================================
void CGamepad::Update(void)
{

	ZeroMemory(&g_aGamePadState, sizeof(XINPUT_STATE));

	DWORD dwResult = XInputGetState(0, &g_aGamePadState);
}

//============================================================
// プレス処理
//============================================================
bool CGamepad::GetPress(WORD nButton)
{
	return (g_aGamePadState.Gamepad.wButtons & nButton) ? true : false;

}

//============================================================
// トリガー処理
//============================================================
bool CGamepad::GetTrigger(WORD nButton)
{
	return (nButton & 0x80) ? true : false;
}


//============================================ スティック入力取得============================================
#if 1
bool CGamepad::GetRStickX(int nDeadZone)
{
	if (nDeadZone < 0)
	{
		if (g_aGamePadState.Gamepad.sThumbRX < nDeadZone)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (g_aGamePadState.Gamepad.sThumbRX > nDeadZone)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
}
bool CGamepad::GetRStickY(int nDeadZone)
{
	if (nDeadZone < 0)
	{
		if (g_aGamePadState.Gamepad.sThumbRY < nDeadZone)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (g_aGamePadState.Gamepad.sThumbRY > nDeadZone)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool CGamepad::GetLStickX(int nDeadZone)
{
	if (nDeadZone < 0)
	{
		if (g_aGamePadState.Gamepad.sThumbLX < nDeadZone)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (g_aGamePadState.Gamepad.sThumbLX > nDeadZone)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool CGamepad::GetLStickY(int nDeadZone)
{
	if (nDeadZone < 0)
	{
		if (g_aGamePadState.Gamepad.sThumbLY < nDeadZone)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (g_aGamePadState.Gamepad.sThumbLY > nDeadZone)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
#endif