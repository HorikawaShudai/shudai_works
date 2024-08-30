//=========================================================================================================
//
//2D専用の敵の処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Enemy.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"

#define ENEMY_HEIGHT	(30.0f)	//敵の横幅
#define ENEMY_WIDTH		(30.0f)	//敵の縦幅
#define ENEMY_SPEED		(0.8f)	//敵の移動速度

LPDIRECT3DTEXTURE9 CEnemy::m_pTexture = NULL;
D3DXVECTOR3 CEnemy::m_pos = {};
//====================================================
//コンストラクタ
//====================================================
CEnemy::CEnemy()
{
	//m_pos = D3DXVECTOR3(900.0f, 500.0f, 0.0f);
	m_move = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SetType(TYPE_ENEMY);
	m_pTexture = NULL;
	m_nLife = 1;
}
//====================================================
//デストラクタ
//====================================================
CEnemy::~CEnemy()
{

}


//====================================================
//敵の初期化処理
//====================================================
HRESULT CEnemy::Init(void)
{
	

	CObject2D::Init();


	CTexture *pTexture = CManager::Get()->GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\enemy004.png");

	SetPos(m_pos, ENEMY_HEIGHT, ENEMY_WIDTH);

	return S_OK;
}

//====================================================
//敵の終了処理
//====================================================
void CEnemy::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//====================================================
//敵の更新処理
//====================================================
void CEnemy::Update(void)
{
	if (m_nLife <= 0)
	{

		Release();
	}
}

//====================================================
//敵の描画処理
//====================================================
void CEnemy::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//敵のヒット処理
//====================================================
void CEnemy::HitEnemy(int nDamage)
{

}

//====================================================
//敵の生成処理
//====================================================
void CEnemy::Create(D3DXVECTOR3 pos)
{
	m_pos = pos;

	CObject2D::Create();
}