//===========================================================
//
//���͂̏�������
//Author:�x�씋��
//
//===========================================================
#include "Input.h"


//=============================================��{�N���X=============================================
//============================================================
//�ÓI�����o�ϐ�
//============================================================
LPDIRECTINPUT8 CInput:: m_pInput = nullptr;

//============================================================
//�R���X�g���N�^
//============================================================
CInput :: CInput()
{
	m_pDevice = nullptr;
}
//============================================================
//�f�X�g���N�^
//============================================================
CInput :: ~CInput()
{

}

//============================================================
//����������
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
//�I������
//============================================================
void  CInput::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}

//=============================================�h���N���X=============================================
//============================================================
// �R���X�g���N�^
//============================================================
CKeyboard::CKeyboard()
{
	memset(m_aKeyState, 0, sizeof(m_aKeyState));
	memset(m_aKeyStateTrigger, 0, sizeof(m_aKeyStateTrigger));
	memset(m_aKeyStateKeep, 0, sizeof(m_aKeyStateKeep));
	memset(m_aKeyStateRelease, 0, sizeof(m_aKeyStateRelease));
}
//============================================================
// �f�X�g���N�^
//============================================================
CKeyboard::~CKeyboard()
{

}

//============================================================
// ����������
//============================================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);


	//Direct�I�u�W�F�N�g�̐���

	//���̓f�o�C�X�̐ݒ�
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();
	return S_OK;
}

//============================================================
// �I������
//============================================================
void CKeyboard::Uninit(void)
{

}

//============================================================
// �X�V����
//============================================================
void CKeyboard :: Update(void) 
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
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

//============================================ ���͏��̎擾 ============================================

//============================================================
// �v���X����
//============================================================
bool CKeyboard::GetPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}
//============================================================
// �g���K�[����
//============================================================
bool CKeyboard::GetTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//============================================================
// �����[�X����
//============================================================
bool CKeyboard::GetRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
//============================================================
// �L�[�v����
//============================================================
bool CKeyboard::GetKeep(int nKey)
{
	return (m_aKeyStateKeep[nKey] & 0x80) ? true : false;
}

//============================================ �Q�[���p�b�h============================================

//============================================================
// �R���X�g���N�^
//============================================================
CGamepad::CGamepad()
{

}

//============================================================
// �f�X�g���N�^
//============================================================
CGamepad::~CGamepad()
{

}

//============================================================
// ����������
//============================================================
HRESULT CGamepad::Init(HINSTANCE hInstance, HWND hWnd)
{
	XInputEnable(true);
	return S_OK;

}

//============================================================
// �I������
//============================================================
void CGamepad::Uninit(void)
{
	XInputEnable(false);
}

//============================================================
// �X�V����
//============================================================
void CGamepad::Update(void)
{

	ZeroMemory(&g_aGamePadState, sizeof(XINPUT_STATE));

	DWORD dwResult = XInputGetState(0, &g_aGamePadState);
}

//============================================================
// �v���X����
//============================================================
bool CGamepad::GetPress(WORD nButton)
{
	return (g_aGamePadState.Gamepad.wButtons & nButton) ? true : false;

}

//============================================================
// �g���K�[����
//============================================================
bool CGamepad::GetTrigger(WORD nButton)
{
	return (nButton & 0x80) ? true : false;
}


//============================================ �X�e�B�b�N���͎擾============================================
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