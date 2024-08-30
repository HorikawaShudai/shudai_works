//=========================================================================================================
//
//3Dプレイヤーの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "3DPlayer.h"
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Object3D.h"
#include "3DBlock.h"
#include <assert.h>

#define PLAYER_SPEED	(0.2f)
#define MOVE_NONSHIFT (10.0f)

//====================================================
//静的メンバ変数の初期化
//====================================================
D3DXVECTOR3 CPlayer3D::m_VtxMaxObject;
D3DXVECTOR3 CPlayer3D::m_VtxMinObject;
D3DXVECTOR3 CPlayer3D::m_pos;
D3DXVECTOR3 CPlayer3D::m_rot;
D3DXVECTOR3 CPlayer3D::m_Length;
C3DBlock* CPlayer3D::m_pObject = nullptr;

//====================================================
//コンストラクタ
//====================================================
CPlayer3D::CPlayer3D(int nPriority) :CObject3D(nPriority)
{
	m_Num = 0;

}
//====================================================
//デストラクタ
//====================================================
CPlayer3D::~CPlayer3D()
{

}


//====================================================
//初期化処理
//====================================================
HRESULT CPlayer3D::Init(void)
{
	m_Num = 0;
	//DWORD dwSizeFVF;
	//BYTE *pVtxBuff;
	m_pObject = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pObject = C3DBlock::CreateModel(m_pos, 0, CObject::TYPE_EDITBLOCK);

	//Xファイルの読み込み
	SetType(CObject::TYPE_PLAYER);
	return S_OK;
}

//====================================================
//終了処理
//====================================================
void CPlayer3D::Uninit(void)
{

}

//====================================================
//更新処理
//====================================================
void CPlayer3D::Update(void)
{
	int nCnt = 0;
	m_pos = GetPos();
	PlayerContoroll();
}

//====================================================
//描画処理
//====================================================
void CPlayer3D::Draw(void)
{

	{
		//CManager Renderer;
		//CRenderer *pRenderer = Renderer.GetRenderer();
		////デバイスの取得
		//LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		//D3DXMATRIX mtxRot, mtxTrans, mtxParts;	//計算用マトリックス
		//D3DMATERIAL9 matDef;
		//D3DXMATERIAL *pMat;

		////ワールドマトリックスの初期化
		//D3DXMatrixIdentity(&m_mtxWorld);

		////向きを反映
		//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		////位置を反映
		//D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//pDevice->GetTransform(D3DTS_WORLD, &mtxParts);

		////D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParts);

		////ワールドマトリックスの設定
		//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		////現在のマテリアルを取得
		//pDevice->GetMaterial(&matDef);
		////マテリアルデータへのポインタを取得
		//pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

		//for (int nCntMat = 0; nCntMat < (int)m_dwNumMatModel; nCntMat++)
		//{
		//	//マテリアルの設定
		//	pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//	//テクスチャの設定
		//	pDevice->SetTexture(0, m_apTEXtureModel[nCntMat]);

		//	//モデル（パーツ）の描画
		//	m_pMeshModel->DrawSubset(nCntMat);
		//	pMat->MatD3D.Diffuse = { 1.0f,1.0f,1.0f,0.2f };
		//}

		//pDevice->SetMaterial(&matDef);
	}



}

//====================================================
//プレイヤーの操作処理
//====================================================
void CPlayer3D::PlayerContoroll(void)
{
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();


	//ブロックの移動操作
	{
		if (pKeyboard->GetTrigger(DIK_A) == true)
		{//Aのみ押された場合
			m_pos.z += MOVE_NONSHIFT;	//左移動
			
		}
		else if (pKeyboard->GetTrigger(DIK_D) == true)
		{//Dのみ押された場合
			m_pos.z -= MOVE_NONSHIFT;	//右移動
		}
		else if (pKeyboard->GetTrigger(DIK_W) == true)
		{//Wのみ押された場合
			m_pos.y += MOVE_NONSHIFT;	//上移動

		}
		else if (pKeyboard->GetTrigger(DIK_S) == true)
		{//Sのみ押された場合
			m_pos.y -= MOVE_NONSHIFT;	//下移動
		}
		else if (pKeyboard->GetTrigger(DIK_1) == true)
		{//Wのみ押された場合
			m_pos.x += MOVE_NONSHIFT;	//奥に移動

		}
		else if (pKeyboard->GetTrigger(DIK_2) == true)
		{//Sのみ押された場合
			m_pos.x -= MOVE_NONSHIFT;	//手前に移動
		}
		// モデル切り替え
		else if (pKeyboard->GetTrigger(DIK_3) == true)
		{//Wのみ押された場合
			m_Num++;
			if (m_Num > C3DBlock::OBJECT_MODEL_MAX)
			{
				m_Num = 0;
			}
			m_pObject->Release();
			m_pObject = nullptr;
			m_pObject = C3DBlock::CreateModel(m_pos, m_Num, CObject::TYPE_EDITBLOCK);
			SetPos(m_pos, 0.0f, 0.0f);

		}
		else if (pKeyboard->GetTrigger(DIK_4) == true)
		{//Sのみ押された場合
			m_Num--;
			if (m_Num <= 0)
			{
				m_Num = C3DBlock::OBJECT_MODEL_MAX;
			}
			m_pObject->Release();
			m_pObject = nullptr;
			m_pObject = C3DBlock::CreateModel(m_pos, m_Num, CObject::TYPE_EDITBLOCK);
		}
	}
	m_pObject->SetPos(m_pos, 0.0f, 0.0f);
	//ブロックの設置とリセット
	{
		if (pKeyboard->GetTrigger(DIK_RETURN) == true)
		{//Enterのみ押された場合
			CObject3D::Create(m_pos, CObject::TYPE_3DBLOCK, m_Num);
		}
		if (pKeyboard->GetTrigger(DIK_BACKSPACE) == true)
		{//F4のみ押された場合
			C3DBlock::DeleateBlock(m_pos);
		}
	}

	//リセット
	{
		if (pKeyboard->GetTrigger(DIK_R) == true)
		{//Rのみ押された場合
			CObject::Reset();
		}
	}

	//セーブ&ロード
	{
		if (pKeyboard->GetTrigger(DIK_F3) == true)
		{//F3のみ押された場合
			CObject::WhiteTextMap();
		}
		if (pKeyboard->GetTrigger(DIK_F4) == true)
		{//F4のみ押された場合
			CObject::Load();
		}
	}
}

//====================================================
//位置設定処理
//====================================================
void CPlayer3D::SetPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;
}

//====================================================
//位置取得処理
//====================================================
D3DXVECTOR3 CPlayer3D::GetPos(void)
{
	return m_pos;
}

CPlayer3D *CPlayer3D::Create(void)
{
	CPlayer3D *p3DPlayer = NULL;
	p3DPlayer = new CPlayer3D;
	//p3DPlayer->Init();
	return p3DPlayer;
}

//=========================================================================================================
//サイズの計算処理
//=========================================================================================================
void CPlayer3D::SetObjectSize(void)
{
	int nNumVtx;

	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	//頂点数の取得
	nNumVtx = m_pMeshModel->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(m_pMeshModel->GetFVF());

	//頂点バッファをロック
	m_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (vtx.x > m_VtxMaxObject.x)
		{
			m_VtxMaxObject.x = vtx.x;
		}
		if (vtx.x < m_VtxMinObject.x)
		{
			m_VtxMinObject.x = vtx.x;
		}
		if (vtx.z > m_VtxMaxObject.z)
		{
			m_VtxMaxObject.z = vtx.z;
		}
		if (vtx.z < m_VtxMinObject.z)
		{
			m_VtxMinObject.z = vtx.z;
		}
		if (vtx.y> m_VtxMaxObject.y)
		{
			m_VtxMaxObject.y = vtx.y;
		}
		if (vtx.y < m_VtxMinObject.y)
		{
			m_VtxMinObject.y = vtx.y;
		}
		pVtxBuff += dwSizeFVF;
	}
	float fMax, fMin;
	//z軸の幅を調べる
	{
		if (m_VtxMaxObject.z < 0)
		{//値が負の場合正に戻す
			fMax = m_VtxMaxObject.z * -1.0f;
		}
		else
		{
			fMax = m_VtxMaxObject.z;
		}
		if (m_VtxMinObject.z < 0)
		{//値が負の場合正に戻す
			fMin = m_VtxMinObject.z * -1.0f;
		}
		else
		{
			fMin = m_VtxMinObject.z;
		}
		m_Length.z = fMax + fMin;
	}

	//y軸の幅を調べる
	{
		if (m_VtxMaxObject.z < 0)
		{//値が負の場合正に戻す
			fMax = m_VtxMaxObject.y * -1.0f;
		}
		else
		{
			fMax = m_VtxMaxObject.y;
		}
		if (m_VtxMinObject.y < 0)
		{//値が負の場合正に戻す
			fMin = m_VtxMinObject.y * -1.0f;
		}
		else
		{
			fMin = m_VtxMinObject.y;
		}
		m_Length.y = fMax + fMin;
	}

	//x軸の幅を調べる
	{
		if (m_VtxMaxObject.x < 0)
		{//値が負の場合正に戻す
			fMax = m_VtxMaxObject.x * -1.0f;
		}
		else
		{
			fMax = m_VtxMaxObject.x;
		}
		if (m_VtxMinObject.x < 0)
		{//値が負の場合正に戻す
			fMin = m_VtxMinObject.x * -1.0f;
		}
		else
		{
			fMin = m_VtxMinObject.x;
		}
		m_Length.x = fMax + fMin;
	}
}