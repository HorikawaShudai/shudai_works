//=========================================================================================================
//
//���͏���
//Author:�x�씋��
//
//=========================================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"
#include "Xinput.h"
#pragma comment (lib, "xinput.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#define DIRECTINPUT_VERSION (0x0800) //�r���h���̌x���Ώ��p�r���h
#include "dinput.h"

//�}�N����`
#define NUM_KEY_MAX (256)		//�L�[�̍ő吔
#define GAMEPAD_LSTICK_DEADZONE 7849		// L�X�e�B�b�N���̗͂V�т̒l
#define GAMEPAD_RSTICK_DEADZONE 8689		// R�X�e�B�b�N���̗͂V�т̒l

class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;

private:
};


class CKeyboard : public CInput
{
public:
	CKeyboard();
	~CKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetKeep(int nKey);

private:
	BYTE m_aKeyState[256];
	BYTE m_aKeyStateTrigger[256];
	BYTE m_aKeyStateKeep[256];
	BYTE m_aKeyStateRelease[256];
};
class CGamepad : public CInput
{
public:
	CGamepad();
	~CGamepad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);

	void Uninit(void);
	void Update(void);
	bool GetPress(WORD nButton);
	bool GetTrigger(WORD nButton);
	bool GetRStickX(int nDeadZone);
	bool GetRStickY(int nDeadZone);
	bool GetLStickX(int nDeadZone);
	bool GetLStickY(int nDeadZone);

private:
	XINPUT_STATE g_aGamePadState;

};
#endif