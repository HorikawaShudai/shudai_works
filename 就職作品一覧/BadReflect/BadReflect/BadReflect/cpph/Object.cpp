//=========================================================================================================
//
//ポリゴンの共有処理
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
#include "fade.h"

CObject  *CObject:: m_apObject[PRIORITY_MAX][NUM_POLYGON] = {};
int CObject :: m_nNumAll = 0;

//====================================================
//コンストラクタ
//====================================================
CObject::CObject(int nPriority)
{
	m_TexId = -1;
	m_nPriority = nPriority;
	for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
	{
		if (m_apObject[m_nPriority][nCntObject] == nullptr)
		{
			m_apObject[m_nPriority][nCntObject] = this;
			m_nID = nCntObject;
			m_nNumAll++;

			switch (CManager::Get()->GetMode())
			{
			case CScene::MODE_GAME:
				SetModeobject(CObject::MODE_OBJECT_GAME);
				break;
			case CScene::MODE_TITLE:
				SetModeobject(CObject::MODE_OBJECT_TITLE);
				break;
			case CScene::MODE_CLEAR:
				SetModeobject(CObject::MODE_OBJECT_RESULT);
				break;
			case CScene::MODE_END:
				SetModeobject(CObject::MODE_OBJECT_RESULT);
				break;
			case CScene::MODE_RANKING:
				SetModeobject(CObject::MODE_OBJECT_RANKING);
				break;
			default:
				SetModeobject(CObject::MODE_OBJECT_SETTING);
				break;
			}
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
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				m_apObject[nCntPriority][nCntObject]->Release();
				m_apObject[nCntPriority][nCntObject] = nullptr;
			}
		}
	}
}

//====================================================
//	モードごとにオブジェクトの破棄
//====================================================
void CObject::ModeRelease(MODE_OBJECT nModeObject)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				if (m_apObject[nCntPriority][nCntObject]->m_ModeObject == nModeObject)
				{
					if (m_apObject[nCntPriority][nCntObject]->m_ModeObject != MODE_OBJECT_SETTING)
					{
						m_apObject[nCntPriority][nCntObject]->Release();
						m_apObject[nCntPriority][nCntObject] = nullptr;
					}
					
				}
			}
		}
	}
}

//====================================================
//すべてのオブジェクトの更新処理
//====================================================
void CObject::UpdateAll(void)
{

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
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
	CCamera *pCamera = CManager::Get()->GetCamera();
	if (pCamera != nullptr)
	{
		pCamera->SetCamera();

	}

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
			if (m_apObject[nCntPriority][nCntObject]->m_type != TYPE_PAUSE)
			{
			if (m_apObject[nCntPriority][nCntObject]->m_ModeObject != MODE_OBJECT_SETTING)
			{
			if (m_apObject[nCntPriority][nCntObject]->m_ModeObject != MODE_OBJECT_TITLE)
			{
			if (m_apObject[nCntPriority][nCntObject]->m_ModeObject != MODE_OBJECT_NONE)
			{
					m_apObject[nCntPriority][nCntObject]->Draw();
			}
			}
			}
			}
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
	if (m_apObject[nPriority][nVtx] != nullptr)
	{
		if (m_apObject[nPriority][nVtx]->m_type != TYPE_SCENE)
		{
			m_apObject[nPriority][nVtx]->Uninit();

			delete m_apObject[nPriority][nVtx];
			m_apObject[nPriority][nVtx] = nullptr;
			m_nNumAll--;
		}
	}
}

void CObject::Reset(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		for (int nCntObject = 0; nCntObject < NUM_POLYGON; nCntObject++)
		{
			
			if (m_apObject[nCntPriority][nCntObject] != nullptr)
			{
				if (m_apObject[nCntPriority][nCntObject]->m_type != TYPE_PLAYER && m_apObject[nCntPriority][nCntObject]->m_type != TYPE_NUMBER && m_apObject[nCntPriority][nCntObject]->m_type != TYPE_BGS && m_apObject[nCntPriority][nCntObject]->m_type != TYPE_BG)
				{
					m_apObject[nCntPriority][nCntObject]->Release();

				}
			}
		}
	}
}


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
						C3DBlock::CreateModel(Pos, nNum,C3DBlock::TYPE_3DBLOCK,1.0f);
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