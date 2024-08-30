//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "ModelBullet.h"
#include "Renderer.h"
#include "Manager.h"
#include <string.h>
#include "Boss.h"
#include "Fade.h"
#include "Score.h"
#include "Game.h"

CModelBullet::CModelBullet(int nPriority) :CObject(nPriority)
{
	//m_pos = D3DXVECTOR3(5.0f, 5.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}
CModelBullet::~CModelBullet()
{

}
//=========================================================================================================
//初期化処理
//=========================================================================================================
HRESULT CModelBullet::Init(void)
{

	int nNumVtx;
	//DWORD dwSizeFVF;
	//BYTE *pVtxBuff;

	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\Bull.x",
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
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_apTEXtureModel[nCntMat]);
		}
	}
	SetType(CObject::TYPE_BULLET);
	return S_OK;
}

//=========================================================================================================
//ポリゴンの終了処理
//=========================================================================================================
void CModelBullet::Uninit(void)
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
void CModelBullet::Update(void)
{
	m_pos += m_move;
	//m_move.y -= 0.05f;


	CCamera *pCamera = CManager::Get()->GetCamera();
	CObject *pObj;
	D3DXVECTOR3 pPos;

	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < NUM_POLYGON; nCntObj++)
		{
			pObj = CObject::GetObject(nCntPri, nCntObj);
			if (pObj != NULL)
			{
				CObject::TYPE type;
				type = pObj->GetType();
				if (type == CObject::TYPE_PLAYER)
				{
					pPos = pObj->GetPos();
				}

			}
		}
	}

	CPlayer3D::PLAYERSTATE state;
	state = CPlayer3D::GetState();
	if (state == CPlayer3D::PLAYERSTATE::STATE_ATTACK)
	{
		if (CPlayer3D::isWithinAttackRange(m_pos.x, m_pos.z) == true)
		{
			D3DXVECTOR3 rot = CPlayer3D::GetRot();
			
			if (rot.y == D3DX_PI * 0.5f) // s
			{
				m_rot.y = D3DX_PI * 1.0f;
			}
			else if (rot.y == D3DX_PI * 1.0f) // a
			{
				m_rot.y = D3DX_PI * 0.5f;
			}
			else if (rot.y == D3DX_PI * 0.0f) // d
			{
				m_rot.y = -D3DX_PI * 0.5f;
			}
			else if (rot.y == -D3DX_PI * 0.5f) // w
			{
				m_rot.y = D3DX_PI * 0.0f;
			}
			else if (rot.y == -D3DX_PI * 0.75f) // d
			{
				m_rot.y = D3DX_PI * 0.25f;
			}
			else if (rot.y == D3DX_PI * 0.25f) // w
			{
				m_rot.y = -D3DX_PI * 0.75f;
			}
			else
			{
				m_rot = rot;

			}

			m_move.x = 4.0f * cosf(m_rot.y);
			m_move.y = 0.0f;
			m_move.z = 4.0f * sinf(m_rot.y);

			SetBulletType(PLAYER_BULLET);
		}
	}



	if (m_Bullettype == ENEMY_BULLET)
	{
		if (CPlayer3D::ColissionModBull(m_pos) == true)
		{
			for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
			{
				for (int nCntObj = 0; nCntObj < NUM_POLYGON; nCntObj++)
				{
					pObj = CObject::GetObject(nCntPri, nCntObj);
					if (pObj != NULL)
					{
						CObject::TYPE type;
						type = pObj->GetType();
						if (type == CObject::TYPE_PLAYER)
						{
							CPlayer3D::AddLife(-1);
							int m_Life = CPlayer3D::GetLife();
							
							if (m_Life <= 0)
							{
								pObj->Release();

								CFade* pFade = CManager::Get()->GetpFade();

								CFade::FADE StateFade;
								StateFade = pFade->GetFade();
								if (StateFade == CFade::FADE_NONE)
								{
									CScore* pScore;
									pScore = CGame::GetpScore();
									pScore->CScore::KightTxt(pScore->GetScore());
									pFade->SetFade(CScene::MODE_RANKING, 0.001f);
								}
							}
						}
					}
				}
			}
			Release();
		}

		//else if (m_pos.z < pCamera->m_posV.z - SCREEN_WIDTH / pCamera->m_ViewCamera)
		//{
		//	Release();
		//}
		//else if (m_pos.z > pCamera->m_posV.z + SCREEN_WIDTH / pCamera->m_ViewCamera)
		//{
		//	Release();
		//}
		//else if (m_pos.y < pCamera->m_posV.y - SCREEN_HEIGHT / pCamera->m_ViewCamera)
		//{
		//	Release();
		//}
		//else if (m_pos.y > pCamera->m_posV.y + SCREEN_HEIGHT / pCamera->m_ViewCamera)
		//{
		//	Release();
		//}
	}

	if (m_Bullettype == PLAYER_BULLET)
	{
		//敵の当たり判定
		for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
		{
			for (int nCntObj = 0; nCntObj < NUM_POLYGON; nCntObj++)
			{
				pObj = CObject::GetObject(nCntPri, nCntObj);
				if (pObj != NULL)
				{
					CObject::TYPE type;
					type = pObj->GetType();
					if (type == CObject::TYPE_ENEMY)
					{
						D3DXVECTOR3 E_Pos = pObj->GetPos();
						if (CEnemy3D::ColissionModBull(E_Pos, m_pos) == true)
						{
							pObj->nLife--;
							if (pObj->nLife <= 0)
							{
								pObj->Release();
								CScore* pScore;
								pScore = CGame::GetpScore();
								pScore->AddScore(50);
							}
							//Release();
						}
					}
				}
			}
		}

		if (CBoss3D::ColissionModBull(m_pos) == true)
		{
			for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
			{
				for (int nCntObj = 0; nCntObj < NUM_POLYGON; nCntObj++)
				{
					pObj = CObject::GetObject(nCntPri, nCntObj);
					if (pObj != NULL)
					{
						CObject::TYPE type;
						type = pObj->GetType();
						if (type == CObject::TYPE_BOSS)
						{
							pObj->nLife--;
							if (pObj->nLife <= 0)
							{
								pObj->Release();
								CFade *pFade = CManager::Get()->GetpFade();

								CFade::FADE StateFade;
								StateFade = pFade->GetFade();
								if (StateFade == CFade::FADE_NONE)
								{

									pFade->SetFade(CScene::MODE_CLEAR, 0.001f);
								}
							}
						}
					}
				}
			}
			Release();
		}
	}
	/*for (int nCnt = 0; nCnt < 50; nCnt++)
	{
		CEnemy3D *pEnemy3D = NULL;
		if (pEnemy3D != NULL)
		{
			if (m_Bullettype == PLAYER_BULLET)
			{
				if (pEnemy3D->ColissionModBull(m_pos) == true)
				{
					Release();
					break;
				}
			}
		}
	}*/
	//if (m_Bullettype == PLAYER_BULLET)
	//{
	//	if (m_pos.z < pCamera->m_posV.z - SCREEN_WIDTH / pCamera->m_ViewCamera)
	//	{
	//		Release();
	//	}
	//	else if (m_pos.z > pCamera->m_posV.z + SCREEN_WIDTH / pCamera->m_ViewCamera)
	//	{
	//		Release();
	//	}
	//	else if (m_pos.y < pCamera->m_posV.y - SCREEN_HEIGHT / pCamera->m_ViewCamera)
	//	{
 // 			Release();
	//	}
	//	else if (m_pos.y > pCamera->m_posV.y + SCREEN_HEIGHT / pCamera->m_ViewCamera)
	//	{
 // 			Release();
	//	}
	//}
}

//=========================================================================================================
//ポリゴンの描画処理
//=========================================================================================================
void CModelBullet::Draw(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxParts;	//計算用マトリックス
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
void CModelBullet::CreateModel(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type)
{
	CModelBullet *pObject = NULL;

	pObject = DBG_NEW CModelBullet;

	pObject->Init();

	pObject->m_pos = pos;
	pObject->m_move = move;
	pObject->m_Bullettype = type;
}

//====================================================
//位置設定処理
//====================================================
void CModelBullet::SetPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;
}

//====================================================
//位置取得処理
//====================================================
D3DXVECTOR3 CModelBullet::GetPos(void)
{
	return m_pos;
}

//=========================================================================================================
//サイズの計算処理
//=========================================================================================================
void CModelBullet::SetObjectSize(void)
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
		if (vtx.x > m_VtxMaxObject.x)
		{
			m_VtxMaxObject.x = vtx.x;
		}
		if (vtx.x < m_VtxMinObject.x)
		{
			m_VtxMinObject.x = vtx.x;
		}
		if (vtx.z > m_VtxMaxObject.z)
		{
			m_VtxMaxObject.z = vtx.z;
		}
		if (vtx.z < m_VtxMinObject.z)
		{
			m_VtxMinObject.z = vtx.z;
		}
		if (vtx.y> m_VtxMaxObject.y)
		{
			m_VtxMaxObject.y = vtx.y;
		}
		if (vtx.y < m_VtxMinObject.y)
		{
			m_VtxMinObject.y = vtx.y;
		}
		pVtxBuff += dwSizeFVF;
	}
}

void CModelBullet::SetBulletType(BULLETTYPE type)
{
	m_Bullettype = type;
}
