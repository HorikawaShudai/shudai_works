//===========================================================
//
//エフェクトの処理操作
//Author:堀川萩大
//
//===========================================================
#include "Effect.h"
#include "Player.h"
#include "Renderer.h"
#include "Manager.h"
#include "Billboard.h"

LPDIRECT3DTEXTURE9 CEffect::m_pTexture = nullptr;

//====================================================
//コンストラクタ
//====================================================
CEffect::CEffect(int nPriority)
{
	m_fRadius = 10.0f;
	m_nLife = 80;
	m_col = D3DXCOLOR(0.2f,0.0f,1.0f,1.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//====================================================
//デストラクタ
//====================================================
CEffect::~CEffect()
{

}

//=========================================================================================================
//初期化処理
//=========================================================================================================
HRESULT CEffect::Init(void)
{

	CBillboard::Init();
	SetType(TYPE_EFFECT);
	return S_OK;

}

//=========================================================================================================
//終了処理
//=========================================================================================================
void CEffect::Uninit(void)
{

}

//=========================================================================================================
//更新処理
//=========================================================================================================
void CEffect::Update(void)
{
	//m_fRadius -= 0.01f;
	m_col.a -= 0.008f;
	SetSize( m_fRadius, m_fRadius);
	//SetCol(m_col);

	m_nLife--;
	if (m_nLife <= 0 || m_fRadius <= 0.0f || m_col.a <=0.0f)
	{
		//Release();
	}
}

//=========================================================================================================
//描画処理
//=========================================================================================================
void CEffect::Draw(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CBillboard::Draw();


	//αブレンディングから戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//====================================================
//エフェクトの生成処理
//====================================================
CEffect* CEffect::Create(D3DXVECTOR3 pos)
{
	CEffect* pObject;
	pObject = new CEffect;
	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetPos(pos);
		return pObject;
	}
}