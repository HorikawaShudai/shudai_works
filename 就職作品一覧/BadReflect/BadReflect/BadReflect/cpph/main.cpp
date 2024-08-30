//=========================================================================================================
//
//プロジェクト応用
//Author:堀川萩大
//
//=========================================================================================================
#include "main.h"
#include "Object.h"
#include "Object2D.h"
#include "Renderer.h"
#include "Manager.h"

//マクロ定義
#define CLASS_NAME "WindowClass"		 //ウィンドウクラスの名前
#define WINDOW_NAME "BAD REFLECT"	 //ウィンドウの名前
#define ID_BUTTON_FINISH		(101)	 //終了ボタン

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void Uninit(void);
void Update(void);
void Draw(void);



//=========================================================================================================
//メイン関数
//=========================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	//終了時にメモリリークを出力
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);



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

	RECT rect = { 0,0,SCREEN_HEIGHT,SCREEN_WIDTH};
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

	CManager::Create();

	//初期化処理
	if (FAILED(CManager::Get()->Init(hInstance,hWnd, TRUE)))
	{
		return - 1;
	}
	timeBeginPeriod(1);
	dwCurrentTime = 0;
	dwExectLastTime = timeGetTime();
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
		dwCurrentTime = timeGetTime();
		if ((dwCurrentTime - dwExectLastTime) >= (1000 / 60))
		{
			//更新処理
			Update();
			CManager::Get()->Update();
			//描画処理
			Draw();
			CManager::Get()->Draw();
		}
	}
}

if (CManager::Get() != nullptr)
{
	CManager::Get()->Uninit();
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

//====================================================
//終了処理
//====================================================
void Uninit(void)
{
	//分解能を戻す
	timeEndPeriod(1);
	//各種オブジェクトの終了処理
}

//====================================================
//更新処理
//====================================================
void Update(void)
{
	
}

//====================================================
//描画処理
//====================================================
void Draw(void)
{

}