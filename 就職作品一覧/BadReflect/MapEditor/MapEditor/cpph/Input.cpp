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
LPDIRECTINPUT8 CInput:: m_pInput = NULL;

//============================================================
//コンストラクタ
//============================================================
CInput :: CInput()
{
	m_pDevice = NULL;
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
	if (m_pInput == NULL)
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
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================派生クラス=============================================
//============================================================
//コンストラクタ
//============================================================
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyState[0], 0, NUM_KEY_MAX);
	memset(&m_aKeyStateTrigger[0], 0, NUM_KEY_MAX);
	/*ZeroMemory(&m_aKeyState, sizeof(BYTE));
	ZeroMemory(&m_aKeyStateTrigger, sizeof(BYTE));*/
}
//============================================================
//デストラクタ
//============================================================
CInputKeyboard::~CInputKeyboard()
{

}

//============================================================
//キーボードの初期化処理
//============================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
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
//キーボードの終了処理
//============================================================
void CInputKeyboard::Uninit(void)
{

}

//============================================================
//キーボードの更新処理
//============================================================
void CInputKeyboard :: Update(void) 
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
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//============================================================
//入力情報の取得
//============================================================
bool CInputKeyboard ::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}
bool CInputKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//============================================================
//ゲームパッド
//============================================================
#if 0
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
#endif