//===========================================================
//
//ビルボードの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Billboard.h"
#include "Renderer.h"
#include "Manager.h"
#include "Texture.h"



CBillboard::CBillboard()
{

}
CBillboard::~CBillboard()
{

}
//=========================================================================================================
//初期化処理
//=========================================================================================================
HRESULT CBillboard::Init(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = D3DXVECTOR3(-200.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Height, m_pos.y+m_Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Height, m_pos.y+m_Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Height, m_pos.y-m_Width, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Height, m_pos.y-m_Width, 0.0f);

	//norの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=========================================================================================================
//ビルボードの終了処理
//=========================================================================================================
void CBillboard::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//=========================================================================================================
//ビルボードの更新処理
//=========================================================================================================
void CBillboard::Update(void)
{
}

//=========================================================================================================
//ビルボードの描画処理
//=========================================================================================================
void CBillboard::Draw(void)
{
	
	CTexture *pTexture = CManager::Get()->GetpTexture();
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxView;		//ビューマトリックスの取得用

	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
	
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);

	if (m_TexId != -1)
	{
		pDevice->SetTexture(0, pTexture->GetAddress(m_TexId));
	}
	else
	{
		pDevice->SetTexture(0, nullptr);
	}

	//ビルボード
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

CObject *CBillboard::CreateBillboard(void)
{
	CObject *pObject = NULL;

	pObject = DBG_NEW CBillboard;
	pObject->Init();

	return pObject;
}
void CBillboard::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;

	VERTEX_3D* pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Height, m_pos.y + m_Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Height, m_pos.y + m_Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Height, m_pos.y - m_Width, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Height, m_pos.y - m_Width, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CBillboard::SetSize(float x, float y)
{
	m_Height = x;
	m_Width = y;

	VERTEX_3D* pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x-m_Height, m_pos.y+m_Width, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x+m_Height, m_pos.y+m_Width, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x-m_Height, m_pos.y-m_Width, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x+m_Height, m_pos.y-m_Width, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

D3DXVECTOR3 CBillboard::GetPos(void)
{
	return m_pos;
}
