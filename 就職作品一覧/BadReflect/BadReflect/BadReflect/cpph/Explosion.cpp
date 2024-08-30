//=========================================================================================================
//
//2D専用の爆発の処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Explosion.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Player.h"

#define BULLET_HEIGHT	(30.0f)
#define BULLET_WIDTH	(30.0f)

D3DXVECTOR3 CExplosion::m_pos;
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture;
//====================================================
//コンストラクタ
//====================================================
CExplosion::CExplosion()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;
	m_nCntPattern = 0;

}
//====================================================
//デストラクタ
//====================================================
CExplosion::~CExplosion()
{

}


//====================================================
//爆発の初期化処理
//====================================================
HRESULT CExplosion::Init(void)
{

	CObject2D::Init();


	m_move = D3DXVECTOR3(5.0f, 0.0f, 0.0f);

	SetPos(m_pos, BULLET_HEIGHT, BULLET_WIDTH);

	CTexture *pTexture = CManager::Get()->GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\explosion000.png");

	SetAnim(m_nCntPattern, 8, 0, 1);
	SetType(TYPE_EXPLOSION);


	return S_OK;
}

//====================================================
//爆発の終了処理
//====================================================
void CExplosion::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//====================================================
//爆発の更新処理
//====================================================
void CExplosion::Update(void)
{
	m_nCntAnim++;
	if (m_nCntAnim % 10 == 0)
	{
		m_nCntPattern++;
		SetAnim(m_nCntPattern,8,0,1);
	}
	if (m_nCntPattern > 8)
	{
		Release();
	}
}

//====================================================
//爆発の描画処理
//====================================================
void CExplosion::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//爆発の生成処理
//====================================================
void CExplosion::Create(D3DXVECTOR3 pos)
{
	m_pos = pos;

	CObject2D::Create();

}
