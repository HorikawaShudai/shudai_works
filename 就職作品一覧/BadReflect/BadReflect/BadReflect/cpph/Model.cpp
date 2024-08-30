//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Model.h"
#include "Renderer.h"
#include "Manager.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

CModel::MDOELINFO CModel::m_Info[OBJECT_MODEL_NUM1] =
{
	{ "data\\MODEL\\Player\\00_Player_Hip.x" },		// PLAYER_MODEL1
	{ "data\\MODEL\\Player\\01_Player_Body.x" },	// PLAYER_MODEL2
	{ "data\\MODEL\\Player\\02_Player_Head.x" },	// PLAYER_MODEL3
	{ "data\\MODEL\\Player\\03_Player_Rarm.x" },	// PLAYER_MODEL4
	{ "data\\MODEL\\Player\\04_Player_Rhand.x" },	// PLAYER_MODEL5
	{ "data\\MODEL\\Player\\05_Player_Larm.x" },	// PLAYER_MODEL6
	{ "data\\MODEL\\Player\\06_Player_Lhand.x" },	// PLAYER_MODEL7
	{ "data\\MODEL\\Player\\07_Player_Rthigh.x" },	// PLAYER_MODEL8
	{ "data\\MODEL\\Player\\08_Player_Rshin.x" },	// PLAYER_MODEL9
	{ "data\\MODEL\\Player\\09_Player_Rleg.x" },	// PLAYER_MODEL10
	{ "data\\MODEL\\Player\\10_Player_Lthigh.x" },	// PLAYER_MODEL11
	{ "data\\MODEL\\Player\\11_Player_Lshin.x" },	// PLAYER_MODEL12
	{ "data\\MODEL\\Player\\12_Player_Lleg.x" },	// PLAYER_MODEL13
	{ "data\\MODEL\\Player\\Wapon_Razer.x" },		// PLAYER_MODEL14

	{ "data\\MODEL\\Enemy\\hip.x" },		// ENEMY_MODEL1
	{ "data\\MODEL\\Enemy\\body.x" },		// ENEMY_MODEL2
	{ "data\\MODEL\\Enemy\\Head.x" },		// ENEMY_MODEL3
	{ "data\\MODEL\\Enemy\\R_Shoulder.x" },	// ENEMY_MODEL4
	{ "data\\MODEL\\Enemy\\R_Arm.x" },		// ENEMY_MODEL5
	{ "data\\MODEL\\Enemy\\R_hand.x" },		// ENEMY_MODEL6
	{ "data\\MODEL\\Enemy\\L_Shoulder.x" },	// ENEMY_MODEL7
	{ "data\\MODEL\\Enemy\\L_Arm.x" },		// ENEMY_MODEL8
	{ "data\\MODEL\\Enemy\\L_hand.x" },		// ENEMY_MODEL9
	{ "data\\MODEL\\Enemy\\R_Thigh.x" },	// ENEMY_MODEL10
	{ "data\\MODEL\\Enemy\\R_Shin.x" },		// ENEMY_MODEL11
	{ "data\\MODEL\\Enemy\\R_Leg.x" },		// ENEMY_MODEL12
	{ "data\\MODEL\\Enemy\\L_Thigh.x" },	// ENEMY_MODEL13
	{ "data\\MODEL\\Enemy\\L_Shin.x" },		// ENEMY_MODEL14
	{ "data\\MODEL\\Enemy\\L_Leg.x" },		// ENEMY_MODEL15

	{ "data\\MODEL\\Boss\\Hip.x" },		// MODEL1
	{ "data\\MODEL\\Boss\\Body.x" },	// MODEL2
	{ "data\\MODEL\\Boss\\Face.x" },	// MODEL3
	{ "data\\MODEL\\Boss\\R_Arm.x" },	// MODEL4
	{ "data\\MODEL\\Boss\\R_Hand.x" },	// MODEL5
	{ "data\\MODEL\\Boss\\L_Arm.x" },	// MODEL6
	{ "data\\MODEL\\Boss\\L_Hand.x" },	// MODEL7
	{ "data\\MODEL\\Boss\\R_Thigh.x" },	// MODEL8
	{ "data\\MODEL\\Boss\\R_Leg.x" },	// MODEL9
	{ "data\\MODEL\\Boss\\L_Thigh.x" },	// MODEL10
	{ "data\\MODEL\\Boss\\L_Leg.x" },	// MODEL11
};

int CModel::m_Num;
CModel::CModel()
{
	//m_pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}
CModel::~CModel()
{

}
//=========================================================================================================
//初期化処理
//=========================================================================================================
HRESULT CModel:: Init(void)
{

	m_Num;
	int nNumVtx;
	//DWORD dwSizeFVF;
	//BYTE *pVtxBuff;

	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//Xファイルの読み込み
	D3DXLoadMeshFromX(m_Info[m_Num].pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_dwNumMatModel,
		&m_pMeshModel);

	//頂点数の取得
	nNumVtx = m_pMeshModel->GetNumVertices();

	D3DXMATERIAL *pMat;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != nullptr)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_apTEXtureModel[nCntMat]);
		}
	}
	return S_OK;
}

//=========================================================================================================
//ポリゴンの終了処理
//=========================================================================================================
void CModel:: Uninit(void)
{
	for (int nCntMat = 0; nCntMat < 50; nCntMat++)
	{
		if (m_apTEXtureModel[nCntMat] != nullptr)
		{
			m_apTEXtureModel[nCntMat]->Release();
			m_apTEXtureModel[nCntMat] = nullptr;
		}
	}
	if (m_pMeshModel != nullptr)
	{
		m_pMeshModel->Release();
		m_pMeshModel = nullptr;
	}
	if (m_pBuffMatModel != nullptr)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = nullptr;
	}
}

//=========================================================================================================
//ポリゴンの更新処理
//=========================================================================================================
void CModel:: Update(void)
{
	//CKeyboard *pKeyboard = CManager::GetInputKeyboard();
	//if (pKeyboard->GetPress(DIK_N))
	//{
	//	m_rot.y -= 0.02f;
	//}
	//else if (pKeyboard->GetPress(DIK_M))
	//{
	//	m_rot.y += 0.02f;

	//}
}

//=========================================================================================================
//ポリゴンの描画処理
//=========================================================================================================
void CModel:: Draw(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans,mtxParts;	//計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_pParent != nullptr)
	{
		mtxParts = GetMtxWorld();

	}
	else
	{
		pDevice->GetTransform(D3DTS_WORLD, &mtxParts);
	}
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParts);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);
	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, m_apTEXtureModel[nCntMat]);

		//モデル（パーツ）の描画
		m_pMeshModel->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);

}

//====================================================
//モデル生産処理
//====================================================
CModel *CModel::CreateModel( int ModelNum)
{
	m_Num = ModelNum;
	CModel *pObject = nullptr;

	pObject = DBG_NEW CModel;

	pObject->Init();
	

	return pObject;
}

//====================================================
//位置設定処理
//====================================================
void CModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//====================================================
//位置設定処理
//====================================================
void CModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//====================================================
//位置取得処理
//====================================================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}


D3DMATRIX CModel::GetMtxWorld(void)
{
	return m_pParent->m_mtxWorld;
}