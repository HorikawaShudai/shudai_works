//=========================================================================================================
//
//ボスの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Boss.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Block.h"
#include "Score.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ModelBullet.h"
#include "Object3D.h"

#define BOSS_SPEED	(0.2f)


D3DXVECTOR3 CBoss3D::m_VtxMaxObject;
D3DXVECTOR3 CBoss3D::m_VtxMinObject;
D3DXVECTOR3 CBoss3D::m_pos;
D3DXVECTOR3 CBoss3D::m_posOld;
D3DXVECTOR3 CBoss3D::m_rot;
D3DXVECTOR3 CBoss3D::m_move;
CModel *CBoss3D::m_apModel[11];
CBoss3D::BOSSSTATE CBoss3D::m_State;

//====================================================
//コンストラクタ
//====================================================
CBoss3D::CBoss3D(int nPriority) :CObject3D(nPriority)
{


}
//=============================================6=======
//デストラクタ
//====================================================
CBoss3D::~CBoss3D()
{

}


//====================================================
//ポリゴンの初期化処理
//====================================================
HRESULT CBoss3D::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 900.0f, 600.0f);
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f);
	bSlow = false;
	m_State = STATE_WATE;
	nLife = 10;
	m_apModel[0]  = CModel::CreateModel(CModel::BOSS_MODEL_NUM1); //腰
	m_apModel[1]  = CModel::CreateModel(CModel::BOSS_MODEL_NUM2); //体
	m_apModel[2]  = CModel::CreateModel(CModel::BOSS_MODEL_NUM3); //頭
	m_apModel[3]  = CModel::CreateModel(CModel::BOSS_MODEL_NUM4); //右腕
	m_apModel[4]  = CModel::CreateModel(CModel::BOSS_MODEL_NUM5); //右手
	m_apModel[5]  = CModel::CreateModel(CModel::BOSS_MODEL_NUM6); //左腕
	m_apModel[6]  = CModel::CreateModel(CModel::BOSS_MODEL_NUM7); //左手
	m_apModel[7]  = CModel::CreateModel(CModel::BOSS_MODEL_NUM8); //右腿
	m_apModel[8]  = CModel::CreateModel(CModel::BOSS_MODEL_NUM9); //右足
	m_apModel[9]  = CModel::CreateModel(CModel::BOSS_MODEL_NUM10); //左腿
	m_apModel[10] = CModel::CreateModel(CModel::BOSS_MODEL_NUM11); //左足


	m_apModel[0]->SetParent(NULL);			//腰
	m_apModel[1]->SetParent(m_apModel[0]);	//体
	m_apModel[2]->SetParent(m_apModel[1]);	//頭
	m_apModel[3]->SetParent(m_apModel[1]);  //右腕
	m_apModel[4]->SetParent(m_apModel[3]);  //右手
	m_apModel[5]->SetParent(m_apModel[1]);  //左腕
	m_apModel[6]->SetParent(m_apModel[5]);  //左手
	m_apModel[7]->SetParent(m_apModel[0]);  //右腿
	m_apModel[8]->SetParent(m_apModel[7]);  //右足
	m_apModel[9]->SetParent(m_apModel[0]);  //左腿
	m_apModel[10]->SetParent(m_apModel[9]); //左足

	SetType(CObject::TYPE_BOSS);
	SetObjectSize();
	m_VtxMaxObject.y = 40.0f;

	//LoadMotion();
	return S_OK;
}

//====================================================
//ポリゴンの終了処理
//====================================================
void CBoss3D::Uninit(void)
{
	for (int nCnt = 0; nCnt < 11; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Uninit();
			m_apModel[nCnt] = NULL;
		}
	}
}

//====================================================
//ポリゴンの更新処理
//====================================================
void CBoss3D::Update(void)
{
	int nCnt = 0;
	m_posOld = GetPos();
	m_pos = GetPos();
	BossContoroll();
	m_pos += m_move;
	//m_move.y -= GRAVITY;

	m_move *= 0.87f;
	StateContoroll();

	if (m_pos.y < 0.0f)
	{
	m_move.y = 0.0f;
	m_pos.y = m_posOld.y;
	m_State = STATE_WATE;
	}

}

//====================================================
//ポリゴンの描画処理
//====================================================
void CBoss3D::Draw(void)
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

	for (int nCnt = 0; nCnt < 11; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

	////頂点バッファをデータストリームに設定
	//pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//pDevice->SetFVF(FVF_VERTEX_3D);


	//pDevice->SetTexture(0, pTexture->GetAddress(m_TexId));

	////地面
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//====================================================
//プレイヤーの操作処理
//====================================================
void CBoss3D::BossContoroll(void)
{
	D3DXVECTOR3 pPos;

	pPos = CPlayer3D::GetPos();

	m_Destpos.z = pPos.z;

	m_Diffpos.z = m_Destpos.z - m_pos.z;

	//向きを変える
	if (m_Diffpos.z > 0.0f)
	{
		m_rot.y = D3DX_PI;
	}
	else if (m_Diffpos.z < -0.0f)
	{
		m_rot.y = 0.0f;
	}
}

//====================================================
//位置設定処理
//====================================================
void CBoss3D::SetPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;
}

//====================================================
//位置取得処理
//====================================================
D3DXVECTOR3 CBoss3D::GetPos(void)
{
	return m_pos;
}

CBoss3D *CBoss3D::Create(D3DXVECTOR3 pos)
{
	CBoss3D *p3DBoss = NULL;
	p3DBoss = DBG_NEW CBoss3D;
	p3DBoss->Init();

	SetPos(pos,0.0f,0.0f);
	return p3DBoss;
}

//=========================================================================================================
//サイズの計算処理
//=========================================================================================================
void CBoss3D::SetObjectSize(void)
{
	int nNumVtx;

	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	for (int nCnt = 0; nCnt < 11; nCnt++)
	{

		//頂点数の取得
		nNumVtx = m_apModel[nCnt]->m_pMeshModel->GetNumVertices();

		//頂点フォーマットのサイズを取得
		dwSizeFVF = D3DXGetFVFVertexSize(m_apModel[nCnt]->m_pMeshModel->GetFVF());

		//頂点バッファをロック
		m_apModel[nCnt]->m_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

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
			if (vtx.y > m_VtxMaxObject.y)
			{
				m_VtxMaxObject.y = vtx.y;
			}
			if (vtx.y < m_VtxMinObject.y)
			{
				m_VtxMinObject.y = vtx.y;
			}
			pVtxBuff += dwSizeFVF;
		}
	}
}


//=========================================================================================================
//プレイヤーとの当たり判定
//=========================================================================================================
bool CBoss3D::ColissionModBull(D3DXVECTOR3 pos)
{
	bool bHit = false;

	if (pos.x >= (m_pos.x + m_VtxMinObject.x) && pos.x <= (m_pos.x + m_VtxMaxObject.x) &&
		pos.z >= (m_pos.z + m_VtxMinObject.z) && pos.z <= (m_pos.z + m_VtxMaxObject.z) &&
		pos.y >= (m_pos.y + m_VtxMinObject.y) && pos.y <= (m_pos.y + m_VtxMaxObject.y))
	{
		bHit = true;
	}

	return bHit;
}

D3DXVECTOR3 CBoss3D::GetPosOld(void)
{
	return m_posOld;
}

void CBoss3D::SetMove(D3DXVECTOR3 move, char *CMove)
{
	if (strcmp(CMove, "None") == 0)
	{
		m_move = move;
	}
	else if (strcmp(CMove, "X") == 0)
	{
		m_move.x = move.x;
	}
	else if (strcmp(CMove, "Y") == 0)
	{
		m_move.y = move.y;

	}
	else if (strcmp(CMove, "Z") == 0)
	{
		m_move.z = move.z;

	}
}

void CBoss3D::SetBossState(BOSSSTATE state)
{
	m_State = state;
}

void CBoss3D::SetModelParts(D3DXVECTOR3 rot, int PartsNum)
{
	if (PartsNum == 0)
	{
		m_apModel[PartsNum]->SetRot(rot);

	}
	else
	{
		m_apModel[PartsNum]->SetRot(rot);

	}
}

void CBoss3D::StateContoroll(void)
{
	CKeyboard *pKeyboard = CManager::Get()->GetInputKeyboard();

	if (m_State != STATE_JUMP)
	{
		if (pKeyboard->GetPress(DIK_A) == true || pKeyboard->GetPress(DIK_D) == true)
		{//Wを入力
			m_State = STATE_RUN;
		}
	}
	if (pKeyboard->GetPress(DIK_A) == false && pKeyboard->GetPress(DIK_D) == false && pKeyboard->GetPress(DIK_SPACE) == false)
	{
		m_State = STATE_WATE;
	}
}