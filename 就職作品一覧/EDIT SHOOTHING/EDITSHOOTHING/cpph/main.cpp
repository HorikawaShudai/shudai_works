//=========================================================================================================
//
//�|���S���̕`�揈��
//Author:�x�씋��
//
//=========================================================================================================
#include "main.h"
#include "input.h"
#include "sound.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "enemy.h"
#include "player.h"
#include "edit_mode.h"


//�}�N����`
#define CLASS_NAME "WindowClass"		 //�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "EDIT SHOOTHING"	 //�E�B���h�E�̖��O
#define ID_BUTTON_FINISH		(101)	 //�I���{�^��

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance ,HWND hWnd,BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);
void DrawNumEnemy(void);
void Drawpt(void);
void DrawAtpt(void);
void DrawPousCntr(void);

//�O���[�o���ϐ��錾
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
LPD3DXFONT g_pFont = NULL;
int g_nCountFPS = 0;
int g_NumEne = 0;
bool g_bDispDebug = false;
MODE g_mode = MODE_TITLE;	//�����i�K���[�h


//=========================================================================================================
//���C���֐�
//=========================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
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

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT nrect = { 0,50,SCREEN_WIDTH,SCREEN_HEIGHT };
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
	DWORD dwFrameCount;				//�t���[���̃J�E���g
	DWORD dwFPSLastTime;			//�Ō�Ɍv����������

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExectLastTime = timeGetTime();

	//�f�o�b�O�\���̐��l�ݒ�
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

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
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS�v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwExectLastTime;
				dwFrameCount = 0;
			}
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExectLastTime) >= (1000 / 60))
			{
				dwExectLastTime = dwCurrentTime;
				//�X�V����
				Update();
				//�`�揈��
				Draw();
				dwFrameCount++;
			}
			g_NumEne = *GetNumEnemy();
		}
	}
	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);
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

//=========================================================================================================
//����������
//=========================================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
	return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp,sizeof(d3dpp));								//�p�����[�^���[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;										//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;							//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//�f�v�X�o�b�t�@�Ƃ���16bit���g�p����
	d3dpp.Windowed = bWindow;										//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//�C���^�[�o��

	//Direct3D�f�o�C�X�𐶐�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
		//�����_�[�X�e�[�g�̐ݒ�
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//�T���v���[�X�e�[�g�̐ݒ�
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		
		//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

		//�f�o�b�O�\���p�t�H���g�̐���
		D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
		
		//�L�[�{�[�h�̏���������
		if (FAILED(InitKeyboard(hInstance, hWnd)))
		{
			return E_FAIL;
		}
		
		//���y�̏���������
		InitSound(hWnd);

		//���[�h�̐ݒ�
		InitFade(g_mode);
	return S_OK;
}

//=========================================================================================================
//�I������
//=========================================================================================================
void Uninit(void)
{
	//�e��I�u�W�F�N�g�̏I������
	UninitTitle();
	UninitFade();
	UninitEdMd();
	UninitGame();
	UninitResult();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	UninitSound();
}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void Update(void)
{
	UpdateKeyboard();
	UpdateFade();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_EDIT:
		UpdataEdMd();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	}
}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
		
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_EDIT:
			DrawEdMd();
			break;
		case MODE_GAME:
			DrawGame();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		}

		if (g_bDispDebug == true)
		{
			DrawPousCntr();
#ifdef _DEBUG
			//FPS�̕\��
			DrawFPS();
			DrawNumEnemy();
			Drawpt();
			DrawAtpt();
#endif
		}

		if (GetKeyboardTrigger(DIK_F1) == true)
		{
			if (g_bDispDebug == false)
			{
				g_bDispDebug = true;
			}
			else if (g_bDispDebug == true)
			{
				g_bDispDebug = false;
			}
		}
		DrawFade();
		//�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=========================================================================================================
//�f�o�C�X�擾����
//=========================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=========================================================================================================
//FPS�̕`�揈��
//=========================================================================================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=========================================================================================================
//�G���̕`�揈��
//=========================================================================================================
void DrawNumEnemy(void)
{

	RECT nrect = { 0,50,SCREEN_WIDTH,SCREEN_HEIGHT };
	char nStr[256];

	//������ɑ��
	wsprintf(&nStr[0], "�G��:%d\n", g_NumEne);

	g_pFont->DrawText(NULL, &nStr[0], -1, &nrect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=========================================================================================================
//�l��pt���̕`�揈��
//=========================================================================================================
void Drawpt(void)
{
	Player aplayer = *GetPlayer();

	RECT nrect = { 0,25,SCREEN_WIDTH,SCREEN_HEIGHT };
	char nStr[256];

	//������ɑ��
	wsprintf(&nStr[0], "pt:%d %d %d %d\n", aplayer.Attackpt[0], aplayer.Attackpt[1], aplayer.Attackpt[2], aplayer.Attackpt[3]);

	g_pFont->DrawText(NULL, &nStr[0], -1, &nrect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
//=========================================================================================================
//�l��pt���̕`�揈��
//=========================================================================================================
void DrawAtpt(void)
{
	Player aplayer = *GetPlayer();
	RECT nrect = { 0,75,SCREEN_WIDTH,SCREEN_HEIGHT };
	char nStr[256];

	//������ɑ��
	wsprintf(&nStr[0], "Edpt:%d %d %d %d\n", aplayer.EditNum[0], aplayer.EditNum[1], aplayer.EditNum[2], aplayer.EditNum[3]);

	g_pFont->DrawText(NULL, &nStr[0], -1, &nrect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
//=========================================================================================================
//�|�[�Y�\���{�^���̕`�揈��
//=========================================================================================================
void DrawPousCntr(void)
{

	RECT nrect = { 0,20,SCREEN_WIDTH,SCREEN_HEIGHT };
	char nStr[256];

	//������ɑ��
	wsprintf(&nStr[0], "P:�|�[�Y���j���[�\��\n");

	g_pFont->DrawText(NULL, &nStr[0], -1, &nrect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=========================================================================================================
//���[�h�ݒ�
//=========================================================================================================
void SetMode(MODE mode)
{	
	//���݂̃��[�h�̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_EDIT:
		UninitEdMd();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	}
	//�V������ʁi���[�h�j�̏���������
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_EDIT:
		InitEdMd();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	}
	g_mode = mode;//���[�h��ݒ�
}

//=========================================================================================================
//���[�h���̎擾����
//=========================================================================================================
MODE GetMode(void)
{
	return g_mode;
}