//===========================================================
//
//ライトの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Light.h"
#include "Renderer.h"
#include "Manager.h"



CLight::CLight()
{

}
CLight::~CLight()
{

}

//=========================================================================================================
//初期化処理
//=========================================================================================================
void CLight:: Init(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 vecDir;//設定用方向ベクトル

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//ライトの情報をクリアする
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの方向を設定
		switch (nCntLight)
		{
		case 1:
			vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
			//ライトの拡散光を設定
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case 2:
			vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
			//ライトの拡散光を設定
			m_light[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			break;
		case 3:
			vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
			//ライトの拡散光を設定
			m_light[nCntLight].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
			break;
		}

		//ライトの方向を設定
		//vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir);		//ベクトルを正規化
		m_light[nCntLight].Direction = vecDir;

		//ライトの方向を設定する
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);
		//ライトを有効化する
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=========================================================================================================
//ライトの終了処理
//=========================================================================================================
void CLight:: Uninit(void)
{

}

//=========================================================================================================
//ライトの更新処理
//=========================================================================================================
void CLight:: Updata(void)
{

}
