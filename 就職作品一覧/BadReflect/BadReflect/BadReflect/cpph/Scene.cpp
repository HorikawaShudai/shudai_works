//=============================================================
//
//ゲームモード
//Autor:堀川萩大
//
//=============================================================
#include "Scene.h"
#include "Game.h"
#include "Title.h"
#include "Ranking.h"
#include "Result.h"
#include "Tutorial.h"

//====================================================
//コンストラクタ
//====================================================
CScene::CScene()
{
}

//====================================================
//デストラクタ
//====================================================
CScene::~CScene()
{

}
HRESULT CScene::Init(void)
{
	return S_OK;
}
void CScene::Uninit(void)
{

}
void CScene::Update(void)
{

}
void CScene::Draw(void)
{

}

CScene* CScene::Create(CScene::MODE mode)
{
	CScene* pObject = nullptr;
	switch (mode)
	{

	case MODE_TITLE:
		pObject = DBG_NEW CTitle;
		break;

	case MODE_TUTORIAL:
		pObject = DBG_NEW CTutorial;
		break;

	case MODE_GAME:
		pObject = DBG_NEW CGame;
		break;

	case MODE_CLEAR:
		pObject = DBG_NEW CResult;
		break;

	case MODE_END:
		pObject = DBG_NEW CResult;
		break;

	case MODE_RANKING:
		pObject = DBG_NEW CRanking;
		break;
	};

	return pObject;

}
D3DXVECTOR3 CScene::GetPos(void)
{
	D3DXVECTOR3 Nullpos;
	return Nullpos;

}