//=========================================================================================================
//
//メイン処理
//Author:堀川萩大
//
//=========================================================================================================
#include "main.h"
#include <stdio.h>
#include "input.h"
#include "Camera.h"
#include "Bullet.h"
#include "Player.h"
#include "Game.h"
#include "Fade.h"
#include "Title.h"
#include "Result.h"
#include "Sound.h"
#include "Tutorial.h"

//マクロ定義
#define CLASS_NAME "WindowClass"		 //ウィンドウクラスの名前
#define WINDOW_NAME "CYBER SHOT"	 //ウィンドウの名前
#define ID_BUTTON_FINISH		(101)	 //終了ボタン

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance ,HWND hWnd,BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);
void DrawCntCamera(void);
void DrawCameraPos(void);
void DrawDestPos(void);

//グローバル変数宣言
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
LPD3DXFONT g_pFont = NULL;
int g_nCountFPS = 0;
MODE g_mode = MODE_TITLE;	//初期段階モード


//=========================================================================================================
//メイン関数
//=========================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,						//ウィンドウのスタイル
		WindowProc,						//ウィンドウプロシージャ
		0,								//0にする
		0,								//0にする
		hInstance,						//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION), //タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),		//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 0),		//クライアント領域の背景色
		NULL,							//メニューバー
		CLASS_NAME,						//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)	//ファイルのアイコン
	};

	HWND hWnd;	//ウィンドウハンドル(識別子)
	MSG msg;	//メッセージを格納する変数

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
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
	DWORD dwFrameCount;				//フレームのカウント
	DWORD dwFPSLastTime;			//最後に計測した時刻

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return - 1;
	}
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExectLastTime = timeGetTime();
	dwFrameCount  = 0;
	dwFPSLastTime = timeGetTime();

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
while (1)
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
	{//windowの処理
		if (msg.message == WM_QUIT)
		{
			break;
		}
		else
		{
			//メッセージ設定
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else
	{//DirectXの処理
		if ((dwCurrentTime - dwFPSLastTime) >= 500)
		{//0.5秒経過
			//FPS計測
			g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
			dwFPSLastTime = dwExectLastTime;
			dwFrameCount = 0;
		}
		dwCurrentTime = timeGetTime();
		if ((dwCurrentTime - dwExectLastTime) >= (1000 / 60))
		{
			dwExectLastTime = dwCurrentTime;
			//更新処理
			Update();
			//描画処理
			Draw();
			dwFrameCount++;
		}
	}
}
//ウィンドウクラスの登録解除
UnregisterClass(CLASS_NAME, wcex.hInstance);

return(int)msg.wParam;
}

//=========================================================================================================
//ウィンドウプロシージャ
//=========================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	int nAnswer = 0;

	switch (uMsg)
	{
	case WM_DESTROY://ウィンドウ破棄のメッセージ
					//WM_QUITにメッセージを送る
		PostQuitMessage(0);
		break;
		//case WM_CREATE://ボタンウィンドウ生成
		//	SetTimer(hWnd, ID_TIMER, TIMER_INTERVAL, NULL);
		//	break;

	case WM_KEYDOWN://キーが押された時
		switch (wParam)
		{
		case VK_ESCAPE: //ESCが押されたとき
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
			if (nID == IDYES)
			{//YESが押された場合
			 //ウィンドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
				break;
			}
		}
		break;

	case WM_CLOSE://×ボタンが押されたとき
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);
		if (nID == IDYES)
		{//YESが押された場合
		 //ウィンドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
		}
		else
		{//それ以外
			return 0;
		}
		break;

	case WM_LBUTTONDOWN: //マウスクリックのメッセージ
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);//既定の処理を返す
}
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
	return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp,sizeof(d3dpp));								//パラメータをゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;							//バックバッファの形式
	d3dpp.BackBufferCount = 1;										//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;							//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//デプスバッファとして16bitを使用する
	d3dpp.Windowed = bWindow;										//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//インターバル

	//Direct3Dデバイスを生成
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
		//レンダーステートの設定
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		
		//デバッグ表示用フォントの生成
		D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
		
		//キーボードの初期化処理
		if (FAILED(InitKeyboard(hInstance, hWnd)))
		{
			return E_FAIL;
		}
		//モードの設定
		InitSound(hWnd);

		InitFade(g_mode);

	
	return S_OK;
}

//終了処理
void Uninit(void)
{
	//分解能を戻す
	timeEndPeriod(1);

	//各種オブジェクトの終了処理

	UninitTitle();
	UninitFade();
	UninitGame();
	UninitTutorial();
	UninitResult();
	UninitKeyboard();

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//更新処理
void Update(void)
{
	UpdateKeyboard();
	UpdateFade();
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_TUTORIAL:
		UpdateTutorial();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	}
}

//描画処理
void Draw(void)
{
	//画面クリア(バックバッファとZバッファのクリア)
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_TUTORIAL:
			DrawTutorial();
			break;
		case MODE_GAME:
			DrawGame();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		}
		DrawFade();
	 //各種オブジェクトの描画処理


#ifdef _DEBUG
		//FPSの表示
		DrawFPS();
		//DrawCntCamera();
		//DrawCameraPos();
		//DrawDestPos();
#endif
		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//デバイス取得処理
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

void DrawFPS(void)
{
#if 0
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	//文字列に代入
	wsprintf(&aStr[0], "FPS:%d", g_nCountFPS);

	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
#endif
}

//=========================================================================================================
//視点操作方法の描画処理
//=========================================================================================================
void DrawCntCamera(void)
{
	RECT rect = { 0,20,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "====モデル操作====\nWASD:移動\nJ:回避ダッシュ\nSPACE:攻撃\n\n====注視点操作====\n←→\nI:向き固定");


	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=========================================================================================================
//FPSの描画処理
//=========================================================================================================
void DrawCameraPos(void)
{
	LPD3DXFONT pFont = GetFont();
	Camera aCamera = GetCamera();
	int UseBullet = GetUseBullet();

	RECT rect = {600 ,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[1024];

	//文字列に代入
	sprintf(&aStr[0], "注視点位置　X%.3f  Y%.3f Z%.3f \n 視点位置　X%.3f  Y%.3f Z%.3f\n視点と注視点の距離　%.3f\nカメラの向き　X%.3f  Y%.3f Z%.3f\nカメラの目標の向き　X%.3f  Y%.3f Z%.3f\n\n 使用中の弾数　%d"
		, aCamera.posR.x, aCamera.posR.y, aCamera.posR.z, aCamera.posV.x, aCamera.posV.y, aCamera.posV.z,aCamera.Length, aCamera.rot.x, aCamera.rot.y, aCamera.Destrot.z, aCamera.Destrot.x, aCamera.Destrot.y, aCamera.rot.z,UseBullet);
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));

}

void DrawDestPos(void)
{
	LPD3DXFONT pFont = GetFont();
	PLAYER aPlayer = GetPlayer();

	RECT rect = { 600 ,125,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[1024];

	//文字列に代入
	sprintf(&aStr[0], "モデルの向き　Y%.3f\nモデルの目標向き　Y%.3f \nモデルの位置X%.3f　Y%.3f　Z%.3f \nプレイヤーのHP:%2d"
		, aPlayer.rot.y,aPlayer.Diffrot.y, aPlayer.pos.x, aPlayer.pos.y, aPlayer.pos.z, aPlayer.nLife);
	pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));

}

LPD3DXFONT GetFont(void)
{
	return g_pFont;
}


//=========================================================================================================
//モード設定
//=========================================================================================================
void SetMode(MODE mode)
{
	//現在のモードの終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_TUTORIAL:
		UninitTutorial();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	}
	//新しい画面（モード）の初期化処理
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_TUTORIAL:
		InitTutorial();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	}
	g_mode = mode;//モードを設定
}


MODE GetMode(void)
{
	return g_mode;
}