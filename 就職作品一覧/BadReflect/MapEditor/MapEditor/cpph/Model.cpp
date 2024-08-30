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

//====================================================
//静的メンバ変数の初期化
//====================================================
CModel::PLAYERINFO CModel::m_aModelInfo[MODEL_MAX] =
{
	{ "data\\MODEL\\Player\\hip.x" },		// MODEL1
	{ "data\\MODEL\\Player\\body.x" },		// MODEL2
	{ "data\\MODEL\\Player\\Head.x" },		// MODEL3
	{ "data\\MODEL\\Player\\R_Shoulder.x" },// MODEL4
	{ "data\\MODEL\\Player\\R_Arm.x" },		// MODEL5
	{ "data\\MODEL\\Player\\R_hand.x" },	// MODEL6
	{ "data\\MODEL\\Player\\L_Shoulder.x" },// MODEL7
	{ "data\\MODEL\\Player\\L_Arm.x" },		// MODEL8
	{ "data\\MODEL\\Player\\L_hand.x" },	// MODEL9
	{ "data\\MODEL\\Player\\R_Thigh.x" },	// MODEL10
	{ "data\\MODEL\\Player\\R_Shin.x" },	// MODEL11
	{ "data\\MODEL\\Player\\R_Leg.x" },		// MODEL12
	{ "data\\MODEL\\Player\\L_Thigh.x" },	// MODEL13
	{ "data\\MODEL\\Player\\L_Shin.x" },	// MODEL14
	{ "data\\MODEL\\Player\\L_Leg.x" },		// MODEL15

};
CModel::ENEMYINFO CModel::m_aEnemyInfo[MODEL_MAX] =
{
	{ "data\\MODEL\\Enemy\\hip.x" },		// MODEL1
	{ "data\\MODEL\\Enemy\\body.x" },		// MODEL2
	{ "data\\MODEL\\Enemy\\Head.x" },		// MODEL3
	{ "data\\MODEL\\Enemy\\R_Shoulder.x" },// MODEL4
	{ "data\\MODEL\\Enemy\\R_Arm.x" },		// MODEL5
	{ "data\\MODEL\\Enemy\\R_hand.x" },	// MODEL6
	{ "data\\MODEL\\Enemy\\L_Shoulder.x" },// MODEL7
	{ "data\\MODEL\\Enemy\\L_Arm.x" },		// MODEL8
	{ "data\\MODEL\\Enemy\\L_hand.x" },	// MODEL9
	{ "data\\MODEL\\Enemy\\R_Thigh.x" },	// MODEL10
	{ "data\\MODEL\\Enemy\\R_Shin.x" },	// MODEL11
	{ "data\\MODEL\\Enemy\\R_Leg.x" },		// MODEL12
	{ "data\\MODEL\\Enemy\\L_Thigh.x" },	// MODEL13
	{ "data\\MODEL\\Enemy\\L_Shin.x" },	// MODEL14
	{ "data\\MODEL\\Enemy\\L_Leg.x" },		// MODEL15

};
int CModel::m_Num;

//====================================================
//コンストラクタ
//====================================================
CModel::CModel()
{
	//m_pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//====================================================
//デストラクタ
//====================================================
CModel::~CModel()
{

}

//=========================================================================================================
//初期化処理
//=========================================================================================================
HRESULT CModel::Init(void)
{

	m_Num;
	int nNumVtx;
	//DWORD dwSizeFVF;
	//BYTE *pVtxBuff;

	CManager Renderer;
	CRenderer *pRenderer = Renderer.GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (m_type == TYPE_PLAYERMODEL)
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX(m_aModelInfo[m_Num].pFilename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMatModel,
			NULL,
			&m_dwNumMatModel,
			&m_pMeshModel);
	}
	else
	{
		//Xファイルの読み込み
		D3DXLoadMeshFromX(m_aEnemyInfo[m_Num].pFilename,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMatModel,
			NULL,
			&m_dwNumMatModel,
			&m_pMeshModel);
	}
	//頂点数の取得
	nNumVtx = m_pMeshModel->GetNumVertices();

	D3DXMATERIAL *pMat;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
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
//終了処理
//=========================================================================================================
void CModel:: Uninit(void)
{
	for (int nCntMat = 0; nCntMat < 50; nCntMat++)
	{
		if (m_apTEXtureModel[nCntMat] != NULL)
		{
			m_apTEXtureModel[nCntMat]->Release();
			m_apTEXtureModel[nCntMat] = NULL;
		}
	}
	if (m_pMeshModel != NULL)
	{
		m_pMeshModel->Release();
		m_pMeshModel = NULL;
	}
	if (m_pBuffMatModel != NULL)
	{
		m_pBuffMatModel->Release();
		m_pBuffMatModel = NULL;
	}
}

//=========================================================================================================
//更新処理
//=========================================================================================================
void CModel:: Update(void)
{
	//CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();
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
//描画処理
//=========================================================================================================
void CModel:: Draw(void)
{
	CManager Renderer;
	CRenderer *pRenderer = Renderer.GetRenderer();
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

	if (m_pParent != NULL)
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
//モデルの生成処理
//====================================================
CModel *CModel::CreateModel( int ModelNum,D3DXVECTOR3 pos, MODELTYPE type)
{
	m_Num = ModelNum;
	CModel *pObject = NULL;

	pObject = new CModel;
	pObject->m_type = type;
	pObject->Init();
	
	pObject->m_pos = pos;
	return pObject;
}

//====================================================
//位置設定処理
//====================================================
void CModel::SetPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;
}

//====================================================
//位置取得処理
//====================================================
D3DXVECTOR3 CModel::GetPos(void)
{
	return m_pos;
}

//====================================================
//親子関係の設定
//====================================================
void CModel::SetParent(CModel *pModel)
{
	m_pParent = pModel;
}

//====================================================
//マトリックスの取得
//====================================================
D3DMATRIX CModel::GetMtxWorld(void)
{
	return m_pParent->m_mtxWorld;
}