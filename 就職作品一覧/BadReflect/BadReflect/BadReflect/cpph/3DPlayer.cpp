//=========================================================================================================
//
// プレイヤーの処理
// Author:堀川萩大
//
//=========================================================================================================
#include "3DPlayer.h"
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
#include "sound.h"

#define PLAYER_SPEED	(2.0f)	// プレイヤーの速度
#define MOVE_DEFINE (0.87f)		//　移動慣性の強さ


D3DXVECTOR3 CPlayer3D::m_VtxMaxObject;
D3DXVECTOR3 CPlayer3D::m_VtxMinObject;
D3DXVECTOR3 CPlayer3D::m_pos;
D3DXVECTOR3 CPlayer3D::m_posOld;
D3DXVECTOR3 CPlayer3D::m_rot;
D3DXVECTOR3 CPlayer3D::m_move;
D3DXVECTOR3 CPlayer3D::m_Moverot;
CLifeGuage* CPlayer3D::m_pGuage;
CModel *CPlayer3D::m_apModel[NUM_PARTS];
CPlayer3D::PLAYERSTATE CPlayer3D::m_State;
int CPlayer3D::m_Life;

//====================================================
//コンストラクタ
//====================================================
CPlayer3D::CPlayer3D(int nPriority) :CObject3D(nPriority)
{
	m_Charge = 1.0f;
	m_Life = 10;
}

//====================================================
//デストラクタ
//====================================================
CPlayer3D::~CPlayer3D()
{

}

//====================================================
// 初期化処理
//====================================================
HRESULT CPlayer3D::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pMotion = nullptr;
	m_pGuage = nullptr;
	m_bMove = false;
	m_State = STATE_WATE;
	nLife = 10;
	
	m_apModel[0]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM1); //腰
	m_apModel[1]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM2); //体
	m_apModel[2]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM3); //頭
	m_apModel[3]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM4); //右腕
	m_apModel[4]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM5); //右手
	m_apModel[5]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM6); //左腕
	m_apModel[6]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM7); //左手
	m_apModel[7]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM8); //右腰
	m_apModel[8]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM9); //右脛
	m_apModel[9]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM10);//右足
	m_apModel[10] = CModel::CreateModel(CModel::PLAYER_MODEL_NUM11);//左腰
	m_apModel[11] = CModel::CreateModel(CModel::PLAYER_MODEL_NUM12);//左脛
	m_apModel[12] = CModel::CreateModel(CModel::PLAYER_MODEL_NUM13);//左足
	m_apModel[13] = CModel::CreateModel(CModel::PLAYER_MODEL_NUM14);//左足


	m_apModel[0] ->SetParent(NULL);			//腰
	m_apModel[1] ->SetParent(m_apModel[0]);	//体
	m_apModel[2] ->SetParent(m_apModel[1]);	//頭
	m_apModel[3] ->SetParent(m_apModel[1]); //右腕
	m_apModel[4] ->SetParent(m_apModel[3]); //右手
	m_apModel[5] ->SetParent(m_apModel[1]); //左腕
	m_apModel[6] ->SetParent(m_apModel[5]); //左手
	m_apModel[7] ->SetParent(m_apModel[0]); //右腰
	m_apModel[8]->SetParent(m_apModel[7]); //右脛
	m_apModel[9]->SetParent(m_apModel[8]);//右足
	m_apModel[10]->SetParent(m_apModel[0]); //左腰
	m_apModel[11]->SetParent(m_apModel[10]);//左脛
	m_apModel[12]->SetParent(m_apModel[11]);//左足
	m_apModel[13]->SetParent(m_apModel[4]);//武器

	SetType(CObject::TYPE_PLAYER);

	m_pMotion = CMotion::Create();
	m_pMotion->SetModel(14, GetModel());
	m_pMotion->LoadMotion("data\\TEXT\\motion.txt");
	SetModeobject(CObject::MODE_OBJECT_GAME);
	SetObjectSize();
	//m_VtxMaxObject.y = 40.0f;
	SetPos(m_pos, 0.0f, 0.0f);
	m_pGuage = CLifeGuage::Create(0);
	m_pGuage->Init();
	return S_OK;
}

//====================================================
// 生成処理
//====================================================
CPlayer3D* CPlayer3D::Create(void)
{
	CPlayer3D* p3DPlayer = NULL;
	p3DPlayer = DBG_NEW CPlayer3D;
	return p3DPlayer;
}

//====================================================
// 終了処理
//====================================================
void CPlayer3D::Uninit(void)
{
	delete m_pMotion;
	m_pMotion = nullptr;

	if (m_pGuage != nullptr)
	{
		m_pGuage->Release();
		m_pGuage = nullptr;
	}
	
	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		if(m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = nullptr;
		}
	}
}

//====================================================
// 更新処理
//====================================================
void CPlayer3D::Update(void)
{
	m_pMotion->Update();
	m_posOld = GetPos();
	m_pos = GetPos();
	
	// プレイヤー操作
	if (m_State != STATE_ATTACK)
	{
		PlayerContoroll();
	}
	m_pos += m_move;
	// 重力
	m_move.y -= GRAVITY;

	// 慣性
	m_move *= MOVE_DEFINE;
	
	// 状態操作
	StateContoroll();

	if (m_pos.y < 0.0f)
	{
		m_move.y = 0.0f;
		m_pos.y = m_posOld.y;
	}

}

//====================================================
// 描画処理
//====================================================
void CPlayer3D::Draw(void)
{
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;	

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

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}

//====================================================
//プレイヤーの操作処理
//====================================================
void CPlayer3D::PlayerContoroll(void)
{
	// 入力デバイスの情報取得
	CKeyboard* pKeyboard = CManager::Get()->GetInputKeyboard();
	CGamepad *pGamepad = CManager::Get()->GetInputGamepad();
	
	// カメラの情報取得
	CCamera *pCamera = CManager::Get()->GetCamera();
	float CameraRot = pCamera->GetRot();

	// 全方向移動プログラム
	if (pKeyboard->GetPress(DIK_D) == true || pGamepad->GetLStickX(GAMEPAD_LSTICK_DEADZONE) == true)
	{
		if (pKeyboard->GetPress(DIK_W) == true || pGamepad->GetLStickY(GAMEPAD_LSTICK_DEADZONE) == true)
		{ // WDを入力
			m_rot.y = D3DX_PI * -0.75f;
		}
		else if (pKeyboard->GetPress(DIK_S) == true || pGamepad->GetLStickY(-GAMEPAD_LSTICK_DEADZONE) == true)
		{ // SDを入力
			m_rot.y = D3DX_PI * -0.25f;
		}
		else
		{ // Dを入力
			m_rot.y = D3DX_PI * -0.5f;
		}
		m_bMove = true;
	}
	else if (pKeyboard->GetPress(DIK_A) == true || pGamepad->GetLStickX(-GAMEPAD_LSTICK_DEADZONE) == true)
	{
		if (pKeyboard->GetPress(DIK_W) == true || pGamepad->GetLStickY(GAMEPAD_LSTICK_DEADZONE) == true)
		{ // WAを入力
			m_rot.y = D3DX_PI * 0.75f;
		}
		else if (pKeyboard->GetPress(DIK_S) == true || pGamepad->GetLStickY(-GAMEPAD_LSTICK_DEADZONE) == true)
		{ // SAを入力
			m_rot.y = D3DX_PI * 0.25f;
		}
		else
		{ // Aを入力
			m_rot.y = D3DX_PI * 0.5f;
		}
		m_bMove = true;
	}
	else if (pKeyboard->GetPress(DIK_W) == true|| pGamepad->GetLStickY(GAMEPAD_LSTICK_DEADZONE) == true)
	{ // Wを入力
		m_rot.y = D3DX_PI * 1.0f;
		m_bMove = true;
	}
	else if (pKeyboard->GetPress(DIK_S) == true || pGamepad->GetLStickY(-GAMEPAD_LSTICK_DEADZONE) == true)
	{ // Sを入絵良く
		m_rot.y = D3DX_PI * 0.0f;
		m_bMove = true;
	}
	else
	{
		m_bMove = false;
	}
	// 移動していた場合
	if (m_bMove == true)
	{
		m_move.x = -sinf(m_rot.y) * PLAYER_SPEED;
		m_move.z = -cosf(m_rot.y) * PLAYER_SPEED;
	}

	// 攻撃
	if (pKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		m_State = STATE_ATTACK;
	}
}



//=========================================================================================================
// サイズの計算処理
//=========================================================================================================
void CPlayer3D::SetObjectSize(void)
{
	int nNumVtx;

	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
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


//====================================================
// 敵弾との当たり判定
//====================================================
bool CPlayer3D::ColissionModBull(D3DXVECTOR3 pos)
{
	bool bHit = false;
	D3DXVECTOR3 pos1, pos2;
	pos1.x = m_pos.x;
	pos1.y = 0.0f;
	pos1.z = m_pos.z;
	pos2.x = pos.x;
	pos2.y = 0.0f;
	pos2.z = pos.z;
	float fDistance = D3DXVec3Length(&(pos1 - pos2));

	if (fDistance <=4.0f)
	{
		bHit = true;

	}

	return bHit;
}

//====================================================
// 状態操作処理
//====================================================
void CPlayer3D::StateContoroll(void)
{
	CKeyboard* pKeyboard = CManager::Get()->GetInputKeyboard();
	if (m_State != STATE_ATTACK)
	{
		if (m_bMove ==true)
		{// 移動していた場合
			m_State = STATE_RUN;
		}
		else
		{
			m_State = STATE_WATE;
		}
	}
	if (m_pMotion->GetFinish() == true)
	{ // モーションが終わっていた場合
		m_State = STATE_WATE;

	}
	m_pMotion->SetState(CMotion::MOTIONSTATE(m_State));

}

//====================================================
// 円の当たり判定
//====================================================
bool CPlayer3D::isWithinAttackRange(float enemyX, float enemyZ) 
{
	if (m_State == PLAYERSTATE::STATE_ATTACK)
	{
		// 敵との距離を計算
		float distance = std::sqrt(std::pow(m_pos.x - enemyX, 2) + std::pow(m_pos.z - enemyZ, 2));

		// 近接攻撃の有効範囲内かどうかを判定
		if (distance <= ATTACK_RANGE)
		{
			CSound::Play(CSound::SOUND_LABEL_SE001);
			return true;
		}
		else
		{
			return false;

		}
	}
	return false;
}

//====================================================
// 向きを補正
//====================================================
float CPlayer3D:: Normalize(float rot)
{
	if (rot > D3DX_PI)
	{ // 向きが3.14fを超えていた場合

		// 向きを補正する
		rot -= D3DX_PI * 2;
	}
	else if (rot < -D3DX_PI)
	{ // 向きが-3.14fを超えていた場合

		// 向きを補正する
		rot += D3DX_PI * 2;
	}
	return rot;
}

//============================================== 設定処理 ==============================================

//====================================================
// 位置設定処理
//====================================================
void CPlayer3D::SetPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;
}

//====================================================
// 移動量を設定
//====================================================
void CPlayer3D::SetMove(D3DXVECTOR3 move, char* CMove)
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

//====================================================
// プレイヤーの状態を設定
//====================================================
void CPlayer3D::SetPlayerState(PLAYERSTATE state)
{
	m_State = state;
}

//====================================================
// 親子関係を設定
//====================================================
void CPlayer3D::SetModelParts(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int PartsNum)
{
	if (PartsNum == 0)
	{
		m_apModel[PartsNum]->SetRot(rot);
		m_apModel[PartsNum]->SetPos(pos);

	}
	else
	{
		m_apModel[PartsNum]->SetRot(rot);

	}
}

//============================================== 取得処理 ==============================================

//====================================================
// 位置取得処理
//====================================================
D3DXVECTOR3 CPlayer3D::GetPos(void)
{
	return m_pos;
}

//====================================================
// 過去の位置を取得
//====================================================
D3DXVECTOR3 CPlayer3D::GetPosOld(void)
{
	return m_posOld;
}

//====================================================
// 向きを取得
//====================================================
D3DXVECTOR3 CPlayer3D::GetRot(void)
{
	return m_rot;
}