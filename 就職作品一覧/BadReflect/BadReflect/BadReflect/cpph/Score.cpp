//===========================================================
//
//�X�R�A�̏�������
//Author:�x�씋��
//
//===========================================================

#include "score.h"
#include "input.h"
#include "Manager.h"
#include "Renderer.h"
#include "Object.h"

D3DXVECTOR3 CScore::m_pos = {};
//int CScore::m_Score = 0;

CScore::CScore()
{
	m_Score = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fadespeed = ALPHASPEED;
}
CScore::~CScore()
{

}
//=========================================================================================================
//����������
//=========================================================================================================
HRESULT CScore::Init(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		m_pNumber[nCnt]= CObject2D::Create();

		CTexture* pTexture = CManager::Get()->GetpTexture();


		m_pNumber[nCnt]->Init();
		m_pNumber[nCnt]->SetAlpha(false);
		m_pNumber[nCnt]->BindTexture(pTexture->GetAddress(pTexture->Regist("data\\TEXTURE\\number000.png")));
		m_pNumber[nCnt]->SetTexId(pTexture->Regist("data\\TEXTURE\\number000.png"));
		//m_pNumber[nCnt]->SetTexId(-1);
		m_pNumber[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pNumber[nCnt]->SetPos(D3DXVECTOR3(m_pos.x + nCnt * 30.0f, m_pos.y, m_pos.z), 15.0f, 30.0f);
		m_pNumber[nCnt]->SetModeobject(CObject::MODE_OBJECT_NONE);
	}
	SetModeobject(CObject::MODE_OBJECT_NONE);
	return S_OK;

}

//=========================================================================================================
//�I������
//=========================================================================================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		m_pNumber[nCnt]->Release();
		m_pNumber[nCnt] = nullptr;

	}
}

//=========================================================================================================
//�X�V����
//=========================================================================================================
void CScore::Update(void)
{

}

//=========================================================================================================
//�`�揈��
//=========================================================================================================
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
	{
		if (m_pNumber[nCnt]->m_pVtxBuff != nullptr)
		{
			m_pNumber[nCnt]->Draw();
		}
	}
}

//=========================================================================================================
//�X�R�A�̐ݒ菈��
//=========================================================================================================
void CScore::SetScore(int nScore)
{
	int aTexU[NUM_PLACE];
	m_Score = nScore;

	if (m_Score <= 0)
	{
		m_Score = 0;
	}

	for (int nCount = 0, Max = 100000000, Min = 10000000; nCount < NUM_PLACE; nCount++, Max /= 10, Min /= 10)
	{
		aTexU[nCount] = m_Score % Max / Min;
		m_pNumber[nCount]->SetAnim(aTexU[nCount], 10, 0, 1);
	}

	
}

//=========================================================================================================
//�X�R�A�̌v�Z����
//=========================================================================================================
void CScore::AddScore(int nValue)
{
	int aTexU[NUM_PLACE];
	m_Score += nValue;

	if (m_Score > 99999999)
	{
		m_Score = 99999999;
	}
	if (m_Score < 0)
	{
		m_Score = 0;
	}

	for (int nCount = 0, Max = 100000000, Min = 10000000; nCount < NUM_PLACE; nCount++, Max /= 10, Min /= 10)
	{
		aTexU[nCount] = m_Score % Max / Min;
		m_pNumber[nCount]->SetAnim(aTexU[nCount], 10, 0, 1);
	}
}

int CScore::GetScore(void)
{
	return m_Score;
}

CScore* CScore::pCreate(D3DXVECTOR3 pos)
{
	CScore* pScore = nullptr;
	pScore = new CScore;
	pScore->m_pos = pos;
	pScore->Init();

	return pScore;
}
void CScore::KightTxt(int nScore)
{
	int aScore[6] = {};
	FILE* pLoadFile = NULL;
	FILE* pSaveFile = NULL;

	aScore[5] = nScore;

	// �t�@�C����ǂݍ��݃��[�h�ŊJ��
	pLoadFile = fopen("data\\TEXT\\Score.txt", "r");
	if (pLoadFile != NULL) {
		for (int nCount = 0; nCount < 5; nCount++) 
		{
			fscanf(pLoadFile, "%d", &aScore[nCount]);
		}
		fclose(pLoadFile);
	}
	else {
	}



	for (int nCount = 0; nCount < 5; nCount++)
	{
		for (int nResCnt = nCount + 1; nResCnt < 6; nResCnt++)
		{
			if (aScore[nCount] < aScore[nResCnt])
			{//nCount�̃f�[�^�̕����Ⴉ�����ꍇ
				int nTemp = aScore[nCount];			//�R�s�[�p��nCount�̃f�[�^����
				aScore[nCount] = aScore[nResCnt];	//nResCnt�̕����ړ�
				aScore[nResCnt] = nTemp;			//nResCnt�̕��ɃR�s�[�f�[�^����
			}
		}
	}
	aScore[5] = nScore;

	// �t�@�C�����������݃��[�h�ŊJ��
	pSaveFile = fopen("data\\TEXT\\Score.txt", "w");
	if (pSaveFile != NULL) {
		for (int nCount = 0; nCount < 6; nCount++) {
			fprintf(pSaveFile, "%d\n", aScore[nCount]);
		}
		fprintf(pSaveFile, "%d\n", nScore);

		fclose(pSaveFile);
	}
	else {

	}
}

void CScore::FadeScore(void)
{
	m_col.a += m_fadespeed;
	if (m_fadestop <= 0)
	{
		m_col.a += m_fadespeed;
		if (m_col.a <= 0.0f && m_fadespeed == -ALPHASPEED)
		{
			m_fadespeed = ALPHASPEED;
		}
		else if (m_col.a >= 1.0f && m_fadespeed == ALPHASPEED)
		{
			m_fadestop = 120;
			m_fadespeed = -ALPHASPEED;
		}
		for (int nCnt = 0; nCnt < NUM_PLACE; nCnt++)
		{
			m_pNumber[nCnt]->SetCol(m_col);

		}
	}
	else
	{
		m_fadestop--;
	}

}