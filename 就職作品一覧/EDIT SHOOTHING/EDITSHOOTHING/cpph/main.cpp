//=========================================================================================================
//
//ポリゴンの描画処理
//Author:堀川萩大
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


//マクロ定義
#define CLASS_NAME "WindowClass"		 //ウィンドウクラスの名前
#define WINDOW_NAME "EDIT SHOOTHING"	 //ウィンドウの名前
#define ID_BUTTON_FINISH		(101)	 //終了ボタン

//プロトタイプ宣言
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

//グローバル変数宣言
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
LPD3DXFONT g_pFont = NULL;
int g_nCountFPS = 0;
int g_NumEne = 0;
bool g_bDispDebug = false;
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
	RECT nrect = { 0,50,SCREEN_WIDTH,SCREEN_HEIGHT };
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
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExectLastTime = timeGetTime();

	//デバッグ表示の数値設定
	dwFrameCount = 0;
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
			g_NumEne = *GetNumEnemy();
		}
	}
	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);
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

//=========================================================================================================
//初期化処理
//=========================================================================================================
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

		//サンプラーステートの設定
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		
		//テクスチャステージステートの設定
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

		//デバッグ表示用フォントの生成
		D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
		
		//キーボードの初期化処理
		if (FAILED(InitKeyboard(hInstance, hWnd)))
		{
			return E_FAIL;
		}
		
		//音楽の初期化処理
		InitSound(hWnd);

		//モードの設定
		InitFade(g_mode);
	return S_OK;
}

//=========================================================================================================
//終了処理
//=========================================================================================================
void Uninit(void)
{
	//各種オブジェクトの終了処理
	UninitTitle();
	UninitFade();
	UninitEdMd();
	UninitGame();
	UninitResult();

	//キーボードの終了処理
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
	UninitSound();
}

//=========================================================================================================
//更新処理
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
//描画処理
//=========================================================================================================
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
			//FPSの表示
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
		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=========================================================================================================
//デバイス取得処理
//=========================================================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=========================================================================================================
//FPSの描画処理
//=========================================================================================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=========================================================================================================
//敵数の描画処理
//=========================================================================================================
void DrawNumEnemy(void)
{

	RECT nrect = { 0,50,SCREEN_WIDTH,SCREEN_HEIGHT };
	char nStr[256];

	//文字列に代入
	wsprintf(&nStr[0], "敵数:%d\n", g_NumEne);

	g_pFont->DrawText(NULL, &nStr[0], -1, &nrect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=========================================================================================================
//獲得pt数の描画処理
//=========================================================================================================
void Drawpt(void)
{
	Player aplayer = *GetPlayer();

	RECT nrect = { 0,25,SCREEN_WIDTH,SCREEN_HEIGHT };
	char nStr[256];

	//文字列に代入
	wsprintf(&nStr[0], "pt:%d %d %d %d\n", aplayer.Attackpt[0], aplayer.Attackpt[1], aplayer.Attackpt[2], aplayer.Attackpt[3]);

	g_pFont->DrawText(NULL, &nStr[0], -1, &nrect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
//=========================================================================================================
//獲得pt数の描画処理
//=========================================================================================================
void DrawAtpt(void)
{
	Player aplayer = *GetPlayer();
	RECT nrect = { 0,75,SCREEN_WIDTH,SCREEN_HEIGHT };
	char nStr[256];

	//文字列に代入
	wsprintf(&nStr[0], "Edpt:%d %d %d %d\n", aplayer.EditNum[0], aplayer.EditNum[1], aplayer.EditNum[2], aplayer.EditNum[3]);

	g_pFont->DrawText(NULL, &nStr[0], -1, &nrect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
//=========================================================================================================
//ポーズ表示ボタンの描画処理
//=========================================================================================================
void DrawPousCntr(void)
{

	RECT nrect = { 0,20,SCREEN_WIDTH,SCREEN_HEIGHT };
	char nStr[256];

	//文字列に代入
	wsprintf(&nStr[0], "P:ポーズメニュー表示\n");

	g_pFont->DrawText(NULL, &nStr[0], -1, &nrect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
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
	//新しい画面（モード）の初期化処理
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
	g_mode = mode;//モードを設定
}

//=========================================================================================================
//モード情報の取得処理
//=========================================================================================================
MODE GetMode(void)
{
	return g_mode;
}