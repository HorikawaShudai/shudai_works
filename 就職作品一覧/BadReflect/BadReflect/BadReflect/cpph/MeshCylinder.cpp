//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "MeshCylinder.h"
#include "Renderer.h"
#include "Manager.h"



//=========================================================================================================
//初期化処理
//=========================================================================================================
HRESULT CCylinder::Init(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, -600.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((MAX_CYLINDER+1)*2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定

	for (int nCnt = 0; nCnt <(MAX_CYLINDER + 1) * 2; nCnt++)
	{
		pVtx[nCnt].pos.z = sinf((D3DX_PI*(1.0f - ((1.0f/(MAX_CYLINDER/2))*(nCnt % (MAX_CYLINDER + 1)))) + m_rot.y))* CYLINDER_SIZE;
		pVtx[nCnt].pos.x = cosf((D3DX_PI*(1.0f - ((1.0f/(MAX_CYLINDER/2))*(nCnt % (MAX_CYLINDER + 1)))) + m_rot.y))* CYLINDER_SIZE;
		pVtx[nCnt].pos.y = CYLINDER_HEIGHT -(CYLINDER_HEIGHT*(nCnt / (MAX_CYLINDER + 1)));
		//norの設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//頂点カラー
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[nCnt].tex = D3DXVECTOR2((0.0f+(0.125f*(nCnt% (MAX_CYLINDER + 1)))), (0.0f+(1.0f*(nCnt/ (MAX_CYLINDER + 1)))));
	}
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	pDevice->CreateIndexBuffer(sizeof(WORD) * ((MAX_CYLINDER + 1) * 2),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD *pIdx;
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCnt = 0,nIdx= 0;nCnt<(MAX_CYLINDER + 1);nCnt++ )
	{
		pIdx[nIdx]   = nCnt+ (MAX_CYLINDER + 1);
		pIdx[nIdx+1] = nCnt;
		nIdx += 2;
	}

	m_pIdxBuff->Unlock();
	//地面を設置
	//Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	return S_OK;
}

//=========================================================================================================
//地面の終了処理
//=========================================================================================================
void CCylinder::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();

		m_pIdxBuff = m_pIdxBuff;
	}
}

//=========================================================================================================
//地面の更新処理
//=========================================================================================================
void CCylinder::Update(void)
{

}

//=========================================================================================================
//地面の描画処理
//=========================================================================================================
void CCylinder::Draw(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点バッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	pDevice->SetFVF(FVF_VERTEX_3D);


	pDevice->SetTexture(0, NULL);

	//地面
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MAX_CYLINDER + 1) * 2, 0, MAX_CYLINDER*2);
}