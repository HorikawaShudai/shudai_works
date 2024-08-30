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
LPDIRECTINPUT8 CInput:: m_pInput = NULL;

//============================================================
//�R���X�g���N�^
//============================================================
CInput :: CInput()
{
	m_pDevice = NULL;
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
//�I������
//============================================================
void  CInput::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================�h���N���X=============================================
//============================================================
//�R���X�g���N�^
//============================================================
CInputKeyboard::CInputKeyboard()
{
	memset(&m_aKeyState[0], 0, NUM_KEY_MAX);
	memset(&m_aKeyStateTrigger[0], 0, NUM_KEY_MAX);
	/*ZeroMemory(&m_aKeyState, sizeof(BYTE));
	ZeroMemory(&m_aKeyStateTrigger, sizeof(BYTE));*/
}
//============================================================
//�f�X�g���N�^
//============================================================
CInputKeyboard::~CInputKeyboard()
{

}

//============================================================
//�L�[�{�[�h�̏���������
//============================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
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
//�L�[�{�[�h�̏I������
//============================================================
void CInputKeyboard::Uninit(void)
{

}

//============================================================
//�L�[�{�[�h�̍X�V����
//============================================================
void CInputKeyboard :: Update(void) 
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
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//============================================================
//���͏��̎擾
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
//�Q�[���p�b�h
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

	//�Q�[���p�b�h���ڑ�����Ă�����
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