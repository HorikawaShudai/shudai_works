//=========================================================================================================
//
//オブジェクトの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Object.h"
#include "Renderer.h"
#include "Camera.h"
#include "Manager.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "3DBlock.h"

CObject  *CObject:: m_apObject[NUM_PRIORITY][NUM_POLYGON] = {};
int CObject :: m_nNumAll = 0;

//====================================================
//コンストラクタ
//====================================================
CObject::CObject(int nPriority)
{
	m_nPriority = nPriority;
	for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
	{
		if (m_apObject[m_nPriority][nCntObject] == nullptr)
		{
			m_apObject[m_nPriority][nCntObject] = this;
			m_nID = nCntObject;
			m_nNumAll++;
			break;
		}
	}
}

//====================================================
//デストラクタ
//====================================================
CObject::~CObject()
{

}

//====================================================
//すべてのオブジェクトの破棄
//====================================================
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				m_apObject[nCntPriority][nCntObject]->Release();
			}
		}
	}
}

//====================================================
//すべてのオブジェクトの更新処理
//====================================================
void CObject::UpdateAll(void)
{

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				m_apObject[nCntPriority][nCntObject]->Update();
			}
		}
	}
}

//====================================================
//すべてのオブジェクトの描画処理
//====================================================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetCamera();
	pCamera->SetCamera();
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				m_apObject[nCntPriority][nCntObject]->Draw();
			}
		}
	}
}

//====================================================
//オブジェクト(自分自身)の破棄
//====================================================
void CObject::Release(void)
{
	int nVtx = m_apObject[m_nPriority][m_nID]->m_nID;
	int nPriority = m_apObject[m_nPriority][m_nID]->m_nPriority;
		if (m_apObject[nVtx] != nullptr)
		{
			m_apObject[nPriority][nVtx]->Uninit();

			delete m_apObject[nPriority][nVtx];
			m_apObject[nPriority][nVtx] = nullptr;
			m_nNumAll--;
		}
}

//====================================================
//マップリセット処理
//====================================================
void CObject::Reset(void)
{
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
		{
			
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				if (m_apObject[nCntPriority][nCntObject]->m_type != TYPE_PLAYER && m_apObject[nCntPriority][nCntObject]->m_type != TYPE_EDITBLOCK)
				{
					m_apObject[nCntPriority][nCntObject]->Release();

				}
			}
		}
	}
}

//====================================================
//読み込み処理
//====================================================
void CObject::Load(void)
{
	// オブジェクトあったら削除
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
		{

			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				if (m_apObject[nCntPriority][nCntObject]->m_type != TYPE_PLAYER)
				{
					m_apObject[nCntPriority][nCntObject]->Release();

				}
			}
		}
	}
	// マップ読み込み
	LoadMap();
}

//====================================================
//書き込み処理
//====================================================
void CObject::WhiteTextMap(void)
{

	FILE *pFile;
	pFile = fopen("data\\TEXT\\SaveMap.txt", "w");

	if (pFile != NULL)
	{
		fprintf(pFile, "MAP_START\n");
		for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
		{
			for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
			{

				if (m_apObject[nCntPriority][nCntObject] != NULL)
				{
					if (m_apObject[nCntPriority][nCntObject]->m_type == TYPE_OBSTACLEBLOCK)
					{
						fprintf(pFile, "MODELSET\n");
						fprintf(pFile, "1\n");
						D3DXVECTOR3 pos;
						pos = m_apObject[nCntPriority][nCntObject]->GetPos();
						fprintf(pFile, "%.1f %.1f %.1f\n", pos.x, pos.y, pos.z);
						fprintf(pFile, "MODELEND\n\n");
					}
					if (m_apObject[nCntPriority][nCntObject]->m_type == TYPE_WALLBLOCK)
					{
						fprintf(pFile, "MODELSET\n");
						fprintf(pFile, "0\n");
						D3DXVECTOR3 pos;
						pos = m_apObject[nCntPriority][nCntObject]->GetPos();
						fprintf(pFile, "%.1f %.1f %.1f\n", pos.x, pos.y, pos.z);
						fprintf(pFile, "MODELEND\n\n");
					}
					if (m_apObject[nCntPriority][nCntObject]->m_type == TYPE_RUBBLE)
					{
						fprintf(pFile, "MODELSET\n");
						fprintf(pFile, "2\n");
						D3DXVECTOR3 pos;
						pos = m_apObject[nCntPriority][nCntObject]->GetPos();
						fprintf(pFile, "%.1f %.1f %.1f\n", pos.x, pos.y, pos.z);
						fprintf(pFile, "MODELEND\n\n");
					}
				}
			}
		}
		fprintf(pFile, "MAP_END\n");

		fprintf(pFile, "END_TEXT");
		fclose(pFile);
	}
}

//====================================================
//マップ読み込み処理
//====================================================
void CObject::LoadMap(void)
{
	FILE *pFile;
	pFile = fopen("data\\TEXT\\Map.txt", "r");

	if (pFile != NULL)
	{
		char start[125];
		char SetModel[125];
		D3DXVECTOR3 Pos;
		int nNum;
		do
		{
			fscanf(pFile, "%s", &start[0]);
			if (strcmp(&start[0], "MAP_START") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &SetModel[0]);
					if (strcmp(&SetModel[0], "MODELSET") == 0)
					{
						fscanf(pFile, "%d", &nNum);
						fscanf(pFile, "%f", &Pos.x);
						fscanf(pFile, "%f", &Pos.y);
						fscanf(pFile, "%f", &Pos.z);
					}
					if (strcmp(&SetModel[0], "MODELEND") == 0)
					{
						C3DBlock::CreateModel(Pos, nNum, CObject::TYPE_3DBLOCK);
					}
				} while (strcmp(&SetModel[0], "MAP_END") != 0);

			}

		} while (strcmp(&start[0], "END_TEXT") != 0);


		fclose(pFile);
	}
	else
	{

	}
}

//====================================================
//タイプ設定処理
//====================================================
void CObject::SetType(TYPE type)
{
	m_apObject[m_nPriority][m_nID]->m_type = type; 
}