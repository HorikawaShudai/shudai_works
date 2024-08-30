//===========================================================
//
//���͂̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"

//�}�N����`
#define NUM_KEY_MAX (256)		//�L�[�̍ő吔

//�O���[�o���ϐ�
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
//�L�[�{�[�h�̏���������
//=========================================================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//Direct�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//���̓f�o�C�X�̐ݒ�
	if (FAILED(g_pInput -> CreateDevice(GUID_SysKeyboard,&g_pDevKeyboard,NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard ->SetDataFormat (&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND|DISCL_NONEXCLUSIVE)))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();
	return S_OK;
}

//=========================================================================================================
//�L�[�{�[�h�̏I������
//=========================================================================================================
void UninitKeyboard(void)
{
//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard -> Unacquire();
		g_pDevKeyboard -> Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=========================================================================================================
//�L�[�{�[�h�̍X�V����
//=========================================================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
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
//���͏��̎擾
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
//�Q�[���p�b�h
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
