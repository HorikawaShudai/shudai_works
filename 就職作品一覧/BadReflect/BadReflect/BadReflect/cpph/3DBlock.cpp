//===========================================================
//
//3Dブロックの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "3DBlock.h"
#include "Renderer.h"
#include "Manager.h"
#include <string.h>


C3DBlock::OBJECTINFO C3DBlock::m_ObjectInfo[OBJECT_MODEL_MAX] =
{
	{ "data\\MODEL\\floor.x" },
	{ "data\\MODEL\\train.x" },
	{ "data\\MODEL\\rubble.x" },
};

C3DBlock::C3DBlock(int nPriority) :CObject3D(nPriority)
{
	//m_pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	nLife = 8;
	m_VtxMinBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMaxBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
C3DBlock::~C3DBlock()
{

}
//=========================================================================================================
//初期化処理
//=========================================================================================================
HRESULT C3DBlock::Init(void)
{

	int nNumVtx;
	//DWORD dwSizeFVF;
	//BYTE *pVtxBuff;
	m_VtxMinBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMaxBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(m_ObjectInfo[m_num].pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_dwNumMatModel,
		&m_pMeshModel);

		SetType(CObject::TYPE_3DBLOCK);

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
	SetScale(m_Scale);
	SetObjectSize();
	
	if(CManager::Get()->GetMode() == CScene::MODE_TITLE)
	{
		SetModeobject(CObject::MODE_OBJECT::MODE_OBJECT_TITLE);

	}
	if (CManager::Get()->GetMode() == CScene::MODE_GAME)
	{
		SetModeobject(CObject::MODE_OBJECT::MODE_OBJECT_GAME);

	}
	if (CManager::Get()->GetMode() == CScene::MODE_RANKING)
	{
		SetModeobject(CObject::MODE_OBJECT::MODE_OBJECT_RANKING);

	}

	return S_OK;
}

//=========================================================================================================
//ポリゴンの終了処理
//=========================================================================================================
void C3DBlock::Uninit(void)
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
void C3DBlock::Update(void)
{
	D3DXVECTOR3 pPos,pPosOld;


	pPos = CPlayer3D::GetPos();
	pPosOld = CPlayer3D::GetPosOld();

	if (Colission(pPos)== true)
	{
		CPlayer3D::SetPos(D3DXVECTOR3(pPosOld.x, pPosOld.y, pPosOld.z), 0.0f, 0.0f);

	}


	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < NUM_POLYGON; nCntObj++)
		{
			CObject *pObj;
			pObj = GetObject(nCntPri, nCntObj);
			if (pObj != NULL)
			{
				TYPE type;
				type = pObj->GetType();
				if (type  == CObject::TYPE_BULLET)
				{
					D3DXVECTOR3 BPos;
					BPos = pObj->GetPos();
					if (Colission(BPos) == true)
					{
							pObj->Release();
					}
				}
			}
		}

	}

}

//=========================================================================================================
//ポリゴンの描画処理
//=========================================================================================================
void C3DBlock::Draw(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParts,mtxScale;	//計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//倍率の反映
	D3DXMatrixScaling(&mtxScale, 1.0f, m_Scale, 1.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	


	pDevice->GetTransform(D3DTS_WORLD, &mtxParts);

	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParts);

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
C3DBlock *C3DBlock::CreateModel( D3DXVECTOR3 pos, int nData,MODELTYPE type,float fScale)
{
	C3DBlock *pObject = nullptr;

	pObject = DBG_NEW C3DBlock;
	pObject->m_Scale = fScale;
	pObject->m_type = type;
	pObject->m_num = nData;
	pObject->Init();

	pObject->m_pos = pos;

	return pObject;
}

//====================================================
//位置設定処理
//====================================================
void C3DBlock::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//====================================================
//位置取得処理
//====================================================
D3DXVECTOR3 C3DBlock::GetPos(void)
{
	return m_pos;
}

//=========================================================================================================
//サイズの計算処理
//=========================================================================================================
void C3DBlock::SetObjectSize(void)
{
	int nNumVtx;

	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	//頂点数の取得
	nNumVtx = m_pMeshModel->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(m_pMeshModel->GetFVF());

	//頂点バッファをロック
	m_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		vtx.y *= m_Scale;
		if (vtx.x > m_VtxMaxBlock.x)
		{
			m_VtxMaxBlock.x = vtx.x;
		}
		if (vtx.x < m_VtxMinBlock.x)
		{
			m_VtxMinBlock.x = vtx.x;
		}
		if (vtx.z > m_VtxMaxBlock.z)
		{
			m_VtxMaxBlock.z = vtx.z;
		}
		if (vtx.z < m_VtxMinBlock.z)
		{
			m_VtxMinBlock.z = vtx.z;
		}
		if (vtx.y> m_VtxMaxBlock.y)
		{
			m_VtxMaxBlock.y = vtx.y;
		}
		if (vtx.y < m_VtxMinBlock.y)
		{
			m_VtxMinBlock.y = vtx.y;
		}
		pVtxBuff += dwSizeFVF;
	}
}


//=========================================================================================================
//プレイヤーとの当たり判定
//=========================================================================================================
bool C3DBlock::Colission(D3DXVECTOR3 pos)
{
	bool bHit = false;

	// X座標の判定
	if (pos.x >= (m_pos.x + m_VtxMinBlock.x) && pos.x <= (m_pos.x + m_VtxMaxBlock.x))
	{
		// Z座標の判定
		if (pos.z >= (m_pos.z + m_VtxMinBlock.z) && pos.z <= (m_pos.z + m_VtxMaxBlock.z))
		{
			bHit = true;

		}
	}

	return bHit;
}

void C3DBlock::AiJump(D3DXVECTOR3 *pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *move)
{
	if (m_type == TYPE_SNOWWALL)
	{
		if (posOld.y > m_pos.y + 39.0f)
		{
			*pos = D3DXVECTOR3(pos->x, m_pos.y + m_VtxMaxBlock.y, pos->z);
			move->y = 0.0f;


		}
		else if (posOld.z > m_pos.z + 4.9f)
		{
			*pos = D3DXVECTOR3(posOld.x, pos->y, m_pos.z + m_VtxMaxBlock.z);
			move->z = 0.0f;
			move->y += 15.0f;


		}
		else if (posOld.z < m_pos.z - 4.9f)
		{
			*pos = D3DXVECTOR3(posOld.x, pos->y, m_pos.z + m_VtxMinBlock.z);
			move->z = 0.0f;
			move->y += 15.0f;


		}
	}
	else if (m_type == TYPE_3DBLOCK)
	{
		if (posOld.y > m_pos.y - 0.1f)
		{
			*pos = D3DXVECTOR3(pos->x, m_pos.y + m_VtxMaxBlock.y + 0.1f, pos->z);
			move->y = 0.0f;



		}
		else if (posOld.z > m_pos.z + m_VtxMaxBlock.z)
		{
			*pos = D3DXVECTOR3(posOld.x, pos->y, posOld.z);
			move->z = 0.0f;
			move->y += 15.0f;


		}
		else if (posOld.z < m_pos.z - m_VtxMinBlock.z)
		{
			*pos = D3DXVECTOR3(posOld.x, pos->y, posOld.z);
			move->z = 0.0f;
			move->y += 15.0f;


		}
	}

	if (Colission(D3DXVECTOR3(pos->x, pos->y + 30.0f, pos->z)) == true)
	{

		if (m_type == TYPE_SNOWWALL)
		{
			if (posOld.z > m_pos.z + 4.0f)
			{
				*pos = D3DXVECTOR3(posOld.x, pos->y, posOld.z);
				move->z = 0.0f;
				move->y += 15.0f;


			}
			else if (posOld.z < m_pos.z - 4.0f)
			{
				*pos = D3DXVECTOR3(posOld.x, pos->y, posOld.z);
				move->z = 0.0f;
				move->y += 15.0f;


			}
		}
		else if (m_type == TYPE_3DBLOCK)
		{
			if (posOld.z > m_pos.z + m_VtxMaxBlock.z)
			{
				*pos = D3DXVECTOR3(posOld.x, pos->y, posOld.z);
				move->z = 0.0f;
				move->y += 15.0f;


			}
			else if (posOld.z < m_pos.z - m_VtxMinBlock.z)
			{
				*pos = D3DXVECTOR3(posOld.x, pos->y, posOld.z);
				move->z = 0.0f;
				move->y += 15.0f;


			}
		}
	}
	if (Colission(D3DXVECTOR3(pos->x, pos->y + 10.0f, pos->z)) == true)
	{

		if (m_type == TYPE_SNOWWALL)
		{
			if (posOld.z > m_pos.z + 4.0f)
			{
				*pos = D3DXVECTOR3(posOld.x, pos->y, posOld.z);
				move->z = 0.0f;
				move->y += 15.0f;


			}
			else if (posOld.z < m_pos.z - 4.0f)
			{
				*pos = D3DXVECTOR3(posOld.x, pos->y, posOld.z);
				move->z = 0.0f;
				move->y += 15.0f;


			}
		}
		else if (m_type == TYPE_3DBLOCK)
		{
			if (posOld.z > m_pos.z + m_VtxMaxBlock.z)
			{
				*pos = D3DXVECTOR3(posOld.x, pos->y, posOld.z);
				move->z = 0.0f;
				move->y += 15.0f;


			}
			else if (posOld.z < m_pos.z - m_VtxMinBlock.z)
			{
				*pos = D3DXVECTOR3(posOld.x, pos->y, posOld.z);
				move->z = 0.0f;
				move->y += 15.0f;
			}
		}
	}
}

void C3DBlock::SetScale(float Scale)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxScale;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//倍率の反映
	D3DXMatrixScaling(&mtxScale, 1.0f, m_Scale, 1.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

}