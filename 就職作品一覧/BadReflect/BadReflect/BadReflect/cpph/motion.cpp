//===========================================================
//
//モーションの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "motion.h"
#include "Renderer.h"
#include "Manager.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//===========================================================================
//コンストラクタ
//===========================================================================
CMotion::CMotion()
{
	for (int nState = 0; nState < STATE_MAX; nState++)
	{
		for (int nCnt = 0; nCnt < MAX_KEY; nCnt++)
		{
			m_motion[nState][nCnt].bLoop = false;
			m_motion[nState][nCnt].bNumKey = 0;
			m_motion[nState][nCnt].Frame = -1;
			for (int nParts = 0; nParts < MAX_PARTS; nParts++)
			{
				m_motion[nState][nCnt].mParts[nParts].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_motion[nState][nCnt].mParts[nParts].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}
	m_InitMotion[15];
	nMotionCnt = 0;
	m_numModel = -1;
	m_motionfinish = false;
	pModel = nullptr;
	m_MotionState = STATE_WATE;
	nKey = -1;
}
//===========================================================================
//デストラクタ
//===========================================================================
CMotion::~CMotion()
{

}

//===========================================================================
//初期化処理
//===========================================================================
HRESULT CMotion::Init(void)
{
	for (int nState = 0; nState < STATE_MAX; nState++)
	{
		for (int nCnt = 0; nCnt < MAX_KEY; nCnt++)
		{
			m_motion[nState][nCnt].bLoop = false;
			m_motion[nState][nCnt].bNumKey = 0;
			m_motion[nState][nCnt].Frame = -1;
			for (int nParts = 0; nParts < MAX_PARTS; nParts++)
			{
				m_motion[nState][nCnt].mParts[nParts].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_motion[nState][nCnt].mParts[nParts].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}
	for (int nParts = 0; nParts < MAX_PARTS; nParts++)
	{
		m_InitMotion[nParts].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_InitMotion[nParts].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	 nMotionCnt  = 0;
	 m_numModel = -1;
	 m_motionfinish = false;
	 pModel = nullptr;
	 m_MotionState = STATE_WATE;
	 nKey = -1;


	return S_OK;
}

//====================================================
// 更新処理
//====================================================
void CMotion::Update(void)
{
	D3DXVECTOR3 rot, pos;
	int nextkey;
	m_motionfinish = false;

	if (m_motion[m_MotionState][nKey].Frame == 0)
	{
		nKey = 0;
	}
	for (int nCnt = 0; nCnt < m_numModel; nCnt++)
	{
		nextkey = nKey + 1;
		if (nextkey == m_motion[m_MotionState][0].bNumKey)
		{
			nextkey = 0;
		}
		rot.x = m_motion[m_MotionState][nKey].mParts[nCnt].rot.x + (m_motion[m_MotionState][nextkey].mParts[nCnt].rot.x - m_motion[m_MotionState][nKey].mParts[nCnt].rot.x) * (float)nMotionCnt / (float)m_motion[m_MotionState][nKey].Frame;
		rot.y = m_motion[m_MotionState][nKey].mParts[nCnt].rot.y + (m_motion[m_MotionState][nextkey].mParts[nCnt].rot.y - m_motion[m_MotionState][nKey].mParts[nCnt].rot.y) * (float)nMotionCnt / (float)m_motion[m_MotionState][nKey].Frame;
		rot.z = m_motion[m_MotionState][nKey].mParts[nCnt].rot.z + (m_motion[m_MotionState][nextkey].mParts[nCnt].rot.z - m_motion[m_MotionState][nKey].mParts[nCnt].rot.z) * (float)nMotionCnt / (float)m_motion[m_MotionState][nKey].Frame;
		rot.x = Normalize(rot.x);
		rot.y = Normalize(rot.y);
		rot.z = Normalize(rot.z);
	

		pos.x = m_InitMotion[nCnt].pos.x + m_motion[m_MotionState][nKey].mParts[nCnt].pos.x + (m_motion[m_MotionState][nextkey].mParts[nCnt].pos.x - m_motion[m_MotionState][nKey].mParts[nCnt].pos.x) * (float)nMotionCnt / (float)m_motion[m_MotionState][nKey].Frame;
		pos.y = m_InitMotion[nCnt].pos.y + m_motion[m_MotionState][nKey].mParts[nCnt].pos.y + (m_motion[m_MotionState][nextkey].mParts[nCnt].pos.y - m_motion[m_MotionState][nKey].mParts[nCnt].pos.y) * (float)nMotionCnt / (float)m_motion[m_MotionState][nKey].Frame;
		pos.z = m_InitMotion[nCnt].pos.z + m_motion[m_MotionState][nKey].mParts[nCnt].pos.z + (m_motion[m_MotionState][nextkey].mParts[nCnt].pos.z - m_motion[m_MotionState][nKey].mParts[nCnt].pos.z) * (float)nMotionCnt / (float)m_motion[m_MotionState][nKey].Frame;

		pModel[nCnt]->SetPos(pos);
		pModel[nCnt]->SetRot(rot);

	}
	nMotionCnt++;
	if (nKey == m_motion[m_MotionState][0].bNumKey - 1)
	{
		if (m_motion[m_MotionState][0].bLoop == 1)
		{
			nKey = 0;
		}
		else if (m_motion[m_MotionState][0].bLoop == 0)
		{
			m_motionfinish = true;
		}
	}
	if (nMotionCnt % m_motion[m_MotionState][nKey].Frame == 0 && nMotionCnt > 0)
	{
		nKey++;
		nMotionCnt = 0;
	}
}

//====================================================
// 親子関係を設定
//====================================================
void CMotion::SetModel(int nNum, CModel** pmodel)
{
	pModel = pmodel;
	m_numModel = nNum;
}

//====================================================
// 読み込み処理
//====================================================
void CMotion::LoadMotion(char* pMotionText)
{
	FILE* pFile = nullptr;
	pFile = fopen(pMotionText, "r");

	if (pFile != nullptr)
	{
		char Dustchar[255];
		char startMotion[225];
		char Motion[225];
		char Key[225];
		int nCntKey, nCntParts, nTypeMove, nIndex;

		nTypeMove = 0;
		do
		{
			fscanf(pFile, "%s", &startMotion[0]);
			if (strcmp(&startMotion[0], "CHARACTERSET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &Motion[0]);
					if (strcmp(&Motion[0], "PARTSSET") == 0)
					{

						do
						{
							fscanf(pFile, "%s", &Key[0]);
							if (strcmp(&Key[0], "INDEX") == 0)
							{
								fscanf(pFile, "%s", &Dustchar[0]);
								fscanf(pFile, "%d", &nIndex);
							}
							if (strcmp(&Key[0], "POS") == 0)
							{
								fscanf(pFile, "%s", &Dustchar[0]);
								fscanf(pFile, "%f", &m_InitMotion[nIndex].pos.x);
								fscanf(pFile, "%f", &m_InitMotion[nIndex].pos.y);
								fscanf(pFile, "%f", &m_InitMotion[nIndex].pos.z);
							}
							if (strcmp(&Key[0], "ROT") == 0)
							{
								fscanf(pFile, "%s", &Dustchar[0]);
								fscanf(pFile, "%f", &m_InitMotion[nIndex].rot.x);
								fscanf(pFile, "%f", &m_InitMotion[nIndex].rot.y);
								fscanf(pFile, "%f", &m_InitMotion[nIndex].rot.z);
							}
						} while (strcmp(&Key[0], "END_PARTSSET") != 0);
						pModel[nIndex]->SetPos(m_InitMotion[nIndex].pos);
						pModel[nIndex]->SetRot(m_InitMotion[nIndex].rot);
					}
				} while (strcmp(&Motion[0], "END_CHARACTERSET") != 0);

			}

			if (strcmp(&startMotion[0], "MOTIONSET") == 0)
			{
				do
				{
					fscanf(pFile, "%s", &Motion[0]);
					if (strcmp(&Motion[0], "LOOP") == 0)
					{
						fscanf(pFile, "%s", &Dustchar[0]);
						fscanf(pFile, "%d", &m_motion[nTypeMove][0].bLoop);
					}
					if (strcmp(&Motion[0], "NUM_KEY") == 0)
					{
						fscanf(pFile, "%s", &Dustchar[0]);
						fscanf(pFile, "%d", &m_motion[nTypeMove][0].bNumKey);
					}
					if (strcmp(&Motion[0], "KEYSET") == 0)
					{
						nCntKey = 0;
						nCntParts = 0;
						do
						{

							fscanf(pFile, "%s", &Key[0]);
							if (strcmp(&Key[0], "FRAME") == 0)
							{
								fscanf(pFile, "%s", &Dustchar[0]);
								fscanf(pFile, "%d", &m_motion[nTypeMove][nCntKey].Frame);
							}
							if (strcmp(&Key[0], "POS") == 0)
							{
								fscanf(pFile, "%s", &Dustchar[0]);
								fscanf(pFile, "%f", &m_motion[nTypeMove][nCntKey].mParts[nCntParts].pos.x);
								fscanf(pFile, "%f", &m_motion[nTypeMove][nCntKey].mParts[nCntParts].pos.y);
								fscanf(pFile, "%f", &m_motion[nTypeMove][nCntKey].mParts[nCntParts].pos.z);
							}
							if (strcmp(&Key[0], "ROT") == 0)
							{
								fscanf(pFile, "%s", &Dustchar[0]);
								fscanf(pFile, "%f", &m_motion[nTypeMove][nCntKey].mParts[nCntParts].rot.x);
								fscanf(pFile, "%f", &m_motion[nTypeMove][nCntKey].mParts[nCntParts].rot.y);
								fscanf(pFile, "%f", &m_motion[nTypeMove][nCntKey].mParts[nCntParts].rot.z);
							}
							if (strcmp(&Key[0], "END_KEY") == 0)
							{
								nCntParts++;
							}
							if (strcmp(&Key[0], "END_KEYSET") == 0)
							{
								nCntKey++;
								nCntParts = 0;
							}

							if (nCntKey > 100)
							{
								int sample = 0;
							}
						} while (nCntKey != m_motion[nTypeMove][0].bNumKey);

					}
					if (strcmp(&Motion[0], "END_MOTIONSET") == 0)
					{
						nTypeMove++;

					}
				} while (strcmp(&Motion[0], "END_MOTIONSET") != 0);

			}

		} while (strcmp(&startMotion[0], "END_SCRIPT") != 0);


		fclose(pFile);
	}
	else
	{ // ファイルが開けなかった場合

		// 停止
		assert(false);
	}
}

//====================================================
// モーションの状態
//====================================================
void CMotion::SetState(MOTIONSTATE state)
{

	if (m_MotionState != state)
	{
		m_MotionState = state;
		nMotionCnt = 0;
		nKey = 0;

	}
}


//====================================================
// 生成処理
//====================================================
CMotion* CMotion::Create(void)
{
	CMotion* pMotion;
	pMotion = nullptr;
	if (pMotion == nullptr)
	{
		pMotion = DBG_NEW CMotion;
	}
	else
	{
		assert(false);
		return nullptr;
	}
	if (pMotion != nullptr)
	{
		pMotion->Init();

	}
	return pMotion;
}

//====================================================
// 正規化処理
//====================================================
float CMotion::Normalize(float rot)
{
	if (rot > D3DX_PI)
	{ // 向きが3.14fを超えていた場合

		// 向きを補正する
		rot -= D3DX_PI * 2;
	}
	else if (rot < -D3DX_PI)
	{ // 向きが-3.14fを超えていた場合

		// 向きを補正する
		rot += D3DX_PI * 2;
	}
	return rot;
}