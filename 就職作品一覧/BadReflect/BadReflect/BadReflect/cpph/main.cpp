//=========================================================================================================
//
//�v���W�F�N�g���p
//Author:�x�씋��
//
//=========================================================================================================
#include "main.h"
#include "Object.h"
#include "Object2D.h"
#include "Renderer.h"
#include "Manager.h"

//�}�N����`
#define CLASS_NAME "WindowClass"		 //�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "BAD REFLECT"	 //�E�B���h�E�̖��O
#define ID_BUTTON_FINISH		(101)	 //�I���{�^��

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void Uninit(void);
void Update(void);
void Draw(void);



//=========================================================================================================
//���C���֐�
//=========================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	//�I�����Ƀ��������[�N���o��
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);



	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						//�E�B���h�E�̃X�^�C��
		WindowProc,						//�E�B���h�E�v���V�[�W��
		0,								//0�ɂ���
		0,								//0�ɂ���
		hInstance,						//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION), //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),		//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 0),		//�N���C�A���g�̈�̔w�i�F
		NULL,							//���j���[�o�[
		CLASS_NAME,						//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)	//�t�@�C���̃A�C�R��
	};

	HWND hWnd;	//�E�B���h�E�n���h��(���ʎq)
	MSG msg;	//���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0,0,SCREEN_HEIGHT,SCREEN_WIDTH};
	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);
	DWORD dwCurrentTime;
	DWORD dwExectLastTime;

	CManager::Create();

	//����������
	if (FAILED(CManager::Get()->Init(hInstance,hWnd, TRUE)))
	{
		return - 1;
	}
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExectLastTime = timeGetTime();
	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	

	//���b�Z�[�W���[�v
while (1)
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
	{//window�̏���
		if (msg.message == WM_QUIT)
		{
			break;
		}
		else
		{
			//���b�Z�[�W�ݒ�
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else
	{//DirectX�̏���
		dwCurrentTime = timeGetTime();
		if ((dwCurrentTime - dwExectLastTime) >= (1000 / 60))
		{
			//�X�V����
			Update();
			CManager::Get()->Update();
			//�`�揈��
			Draw();
			CManager::Get()->Draw();
		}
	}
}

if (CManager::Get() != nullptr)
{
	CManager::Get()->Uninit();
}



//�E�B���h�E�N���X�̓o�^����
UnregisterClass(CLASS_NAME, wcex.hInstance);
return(int)msg.wParam;
}

//=========================================================================================================
//�E�B���h�E�v���V�[�W��
//=========================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	int nAnswer = 0;

	switch (uMsg)
	{
	case WM_DESTROY://�E�B���h�E�j���̃��b�Z�[�W
					//WM_QUIT�Ƀ��b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;
		//case WM_CREATE://�{�^���E�B���h�E����
		//	SetTimer(hWnd, ID_TIMER, TIMER_INTERVAL, NULL);
		//	break;

	case WM_KEYDOWN://�L�[�������ꂽ��
		switch (wParam)
		{
		case VK_ESCAPE: //ESC�������ꂽ�Ƃ�
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
			if (nID == IDYES)
			{//YES�������ꂽ�ꍇ
			 //�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
				break;
			}
		}
		break;

	case WM_CLOSE://�~�{�^���������ꂽ�Ƃ�
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);
		if (nID == IDYES)
		{//YES�������ꂽ�ꍇ
		 //�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
		}
		else
		{//����ȊO
			return 0;
		}
		break;

	case WM_LBUTTONDOWN: //�}�E�X�N���b�N�̃��b�Z�[�W
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//����̏�����Ԃ�
}

//====================================================
//�I������
//====================================================
void Uninit(void)
{
	//����\��߂�
	timeEndPeriod(1);
	//�e��I�u�W�F�N�g�̏I������
}

//====================================================
//�X�V����
//====================================================
void Update(void)
{
	
}

//====================================================
//�`�揈��
//====================================================
void Draw(void)
{

}