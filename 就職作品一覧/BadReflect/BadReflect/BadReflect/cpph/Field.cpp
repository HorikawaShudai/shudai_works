//===========================================================
//
//3Dポリゴンの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Field.h"
#include "Renderer.h"
#include "Manager.h"





LPDIRECT3DTEXTURE9 CField::m_pTexture = nullptr;

//====================================================
//コンストラクタ
//====================================================
CField::CField(int nPriority) :CObject3D(nPriority)
{

}
//====================================================
//デストラクタ
//====================================================
CField::~CField()
{

}
//=========================================================================================================
//初期化処理
//=========================================================================================================
HRESULT CField::Init(void)
{

	CObject3D::Init();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//地面を設置
	SetPos(m_pos, FIELF_SIZE, FIELF_SIZE);

	CTexture *pTexture = CManager::Get()->GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\tuti001.jpg");
	return S_OK;

}

//=========================================================================================================
//地面の終了処理
//=========================================================================================================
void CField:: Uninit(void)
{

}

//=========================================================================================================
//地面の更新処理
//=========================================================================================================
void CField:: Update(void)
{

}

//=========================================================================================================
//地面の描画処理
//=========================================================================================================
void CField::Draw(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	CTexture *pTexture = CManager::Get()->GetpTexture();

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

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);


	pDevice->SetTexture(0, pTexture->GetAddress(m_TexId));

	//地面
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
void CField::UnLoad(void)
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}
