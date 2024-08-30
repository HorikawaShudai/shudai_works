//=========================================================================================================
//
//2D専用のポリゴンの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Object2D.h"
#include "Renderer.h"
#include "Manager.h"
#include "Player.h"
#include "Bg.h"
#include "Bullet.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Effect.h"
#include "Score.h"
#include "Block.h"

const float POLYGON_HEIGHT	(30.0f);
const float POLYGON_WIDTH	(50.0f);

//====================================================
//コンストラクタ
//====================================================
CObject2D::CObject2D(int nPriority):CObject(nPriority)
{
	//m_pTexture = nullptr;
	m_pVtxBuff = nullptr;
	m_moveTex = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//====================================================
//デストラクタ
//====================================================
CObject2D::~CObject2D()
{

}


//====================================================
//ポリゴンの初期化処理
//====================================================
HRESULT CObject2D::Init(void)
{
	//m_pos = D3DXVECTOR3(640.0f, 600.0f, 0.0f);

	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - POLYGON_HEIGHT, m_pos.y - POLYGON_WIDTH, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + POLYGON_HEIGHT, m_pos.y - POLYGON_WIDTH, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - POLYGON_HEIGHT, m_pos.y + POLYGON_WIDTH, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + POLYGON_HEIGHT, m_pos.y + POLYGON_WIDTH, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	return S_OK;
}

//====================================================
//ポリゴンの終了処理
//====================================================
void CObject2D::Uninit(void)
{
	//if (m_pTexture != nullptr)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = nullptr;
	//}
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//====================================================
//ポリゴンの描画処理
//====================================================
void CObject2D::Draw(void)
{
	
	CTexture *pTexture = CManager::Get()->GetpTexture();
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	pDevice = pRenderer->GetDevice();
	if (pDevice != nullptr)
	{


		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		pDevice->SetFVF(FVF_VERTEX_2D);

		if (m_TexId != -1)
		{
			pDevice->SetTexture(0, pTexture->GetAddress(m_TexId));
		}
		else
		{
			pDevice->SetTexture(0, nullptr);
		}

		if (m_bAlpha == true)
		{
			//αブレンディングを加算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}

		//ポリゴン
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		if (m_bAlpha == true)
		{
			//αブレンディングから戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}

//====================================================
//ポリゴンの更新処理
//====================================================
void CObject2D::Update(void)
{

}

//====================================================
//ポリゴンの位置の設定
//====================================================
void CObject2D::SetPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x- Height, m_pos.y- Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x+ Height, m_pos.y- Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x- Height, m_pos.y+ Width, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x+ Height, m_pos.y+ Width, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//====================================================
//ポリゴンの位置の設定
//====================================================
void CObject2D::SetPlayerPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - Height, m_pos.y - Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + Height, m_pos.y - Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - Height, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + Height, m_pos.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}


//====================================================
//ポリゴンの向きの設定
//====================================================
void CObject2D::SetRot(float rot)
{
	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - (cosf(D3DX_PI *rot)* POLYGON_HEIGHT), m_pos.y-(cosf(D3DX_PI * rot)* POLYGON_WIDTH), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (cosf(D3DX_PI *rot)* POLYGON_HEIGHT), m_pos.y-(cosf(D3DX_PI * rot)* POLYGON_WIDTH), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (cosf(D3DX_PI *rot)* POLYGON_HEIGHT), m_pos.y+(cosf(D3DX_PI * rot)* POLYGON_WIDTH), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (cosf(D3DX_PI *rot)* POLYGON_HEIGHT), m_pos.y+(cosf(D3DX_PI * rot)* POLYGON_WIDTH), 0.0f);
	float  frot  = sinf(D3DX_PI *rot)* POLYGON_HEIGHT;
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//====================================================
//オブジェクトの生成処理
//====================================================
CObject2D *CObject2D::Create()
{
	CObject2D *pObject2D = nullptr;

	pObject2D = new CObject2D;

	return pObject2D;
}

//====================================================
//テクスチャの設定処理
//====================================================
void CObject2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//m_pTexture = pTexture;
}

//====================================================
//テクスチャ座標の設定処理
//====================================================
void CObject2D::SetAnim(int xCount,int xPuttern,int yCount,int yPuttern)
{
	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	

	//テクスチャ座標の設定 
	pVtx[0].tex = D3DXVECTOR2(0.0f +            1.0f / xPuttern*xCount, 0.0f			+ 1.0f / yPuttern*yCount);
	pVtx[1].tex = D3DXVECTOR2(1.0f / xPuttern + 1.0f / xPuttern*xCount, 0.0f			+ 1.0f / yPuttern*yCount);
	pVtx[2].tex = D3DXVECTOR2(0.0f +			1.0f / xPuttern*xCount, 1.0f / yPuttern + 1.0f / yPuttern*yCount);
	pVtx[3].tex = D3DXVECTOR2(1.0f / xPuttern + 1.0f / xPuttern*xCount, 1.0f / yPuttern + 1.0f / yPuttern*yCount);
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//====================================================
//位置の取得処理
//====================================================
D3DXVECTOR3 CObject2D::GetPos(void)
{
	return m_pos;
}

//====================================================
//テクスチャの自動遷移
//====================================================
void CObject2D::AutoScroll(float hMoveTex, float wMoveTex)
{
	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定 
	pVtx[0].tex = D3DXVECTOR2(0.0f + hMoveTex, 0.0f + wMoveTex);
	pVtx[1].tex = D3DXVECTOR2(1.0f + hMoveTex, 0.0f + wMoveTex);
	pVtx[2].tex = D3DXVECTOR2(0.0f + hMoveTex, 1.0f + wMoveTex);
	pVtx[3].tex = D3DXVECTOR2(1.0f + hMoveTex, 1.0f + wMoveTex);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CObject2D::SetSize(float Height, float Width)
{

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - Height, m_pos.y - Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + Height, m_pos.y - Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - Height, m_pos.y + Width, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + Height, m_pos.y + Width, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CObject2D::SetCol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].col = D3DXCOLOR(col);
	pVtx[1].col = D3DXCOLOR(col);
	pVtx[2].col = D3DXCOLOR(col);
	pVtx[3].col = D3DXCOLOR(col);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

