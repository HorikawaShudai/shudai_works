//===========================================================
//
//ライトの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Light.h"

#define MAX_LIGHT (3)

//グローバル変数宣言
D3DLIGHT9 g_light[MAX_LIGHT];

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitLight(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;//設定用方向ベクトル

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//ライトの情報をクリアする
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの方向を設定
		switch (nCntLight)
		{
		case 1:
			vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
			//ライトの拡散光を設定
			g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case 2:
			vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
			//ライトの拡散光を設定
			g_light[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			break;
		case 3:
			vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
			//ライトの拡散光を設定
			g_light[nCntLight].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
			break;
		}

		//ライトの方向を設定
		//vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir);		//ベクトルを正規化
		g_light[nCntLight].Direction = vecDir;

		//ライトの方向を設定する
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);
		//ライトを有効化する
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=========================================================================================================
//ライトの終了処理
//=========================================================================================================
void UninitLight(void)
{

}

//=========================================================================================================
//ライトの更新処理
//=========================================================================================================
void UpdateLight(void)
{

}
