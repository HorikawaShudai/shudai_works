//=========================================================================================================
//
// �v���C���[�̏���
// Author:�x�씋��
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

#define PLAYER_SPEED	(2.0f)	// �v���C���[�̑��x
#define MOVE_DEFINE (0.87f)		//�@�ړ������̋���


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
//�R���X�g���N�^
//====================================================
CPlayer3D::CPlayer3D(int nPriority) :CObject3D(nPriority)
{
	m_Charge = 1.0f;
	m_Life = 10;
}

//====================================================
//�f�X�g���N�^
//====================================================
CPlayer3D::~CPlayer3D()
{

}

//====================================================
// ����������
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
	
	m_apModel[0]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM1); //��
	m_apModel[1]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM2); //��
	m_apModel[2]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM3); //��
	m_apModel[3]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM4); //�E�r
	m_apModel[4]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM5); //�E��
	m_apModel[5]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM6); //���r
	m_apModel[6]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM7); //����
	m_apModel[7]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM8); //�E��
	m_apModel[8]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM9); //�E��
	m_apModel[9]  = CModel::CreateModel(CModel::PLAYER_MODEL_NUM10);//�E��
	m_apModel[10] = CModel::CreateModel(CModel::PLAYER_MODEL_NUM11);//����
	m_apModel[11] = CModel::CreateModel(CModel::PLAYER_MODEL_NUM12);//����
	m_apModel[12] = CModel::CreateModel(CModel::PLAYER_MODEL_NUM13);//����
	m_apModel[13] = CModel::CreateModel(CModel::PLAYER_MODEL_NUM14);//����


	m_apModel[0] ->SetParent(NULL);			//��
	m_apModel[1] ->SetParent(m_apModel[0]);	//��
	m_apModel[2] ->SetParent(m_apModel[1]);	//��
	m_apModel[3] ->SetParent(m_apModel[1]); //�E�r
	m_apModel[4] ->SetParent(m_apModel[3]); //�E��
	m_apModel[5] ->SetParent(m_apModel[1]); //���r
	m_apModel[6] ->SetParent(m_apModel[5]); //����
	m_apModel[7] ->SetParent(m_apModel[0]); //�E��
	m_apModel[8]->SetParent(m_apModel[7]); //�E��
	m_apModel[9]->SetParent(m_apModel[8]);//�E��
	m_apModel[10]->SetParent(m_apModel[0]); //����
	m_apModel[11]->SetParent(m_apModel[10]);//����
	m_apModel[12]->SetParent(m_apModel[11]);//����
	m_apModel[13]->SetParent(m_apModel[4]);//����

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
// ��������
//====================================================
CPlayer3D* CPlayer3D::Create(void)
{
	CPlayer3D* p3DPlayer = NULL;
	p3DPlayer = DBG_NEW CPlayer3D;
	return p3DPlayer;
}

//====================================================
// �I������
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
// �X�V����
//====================================================
void CPlayer3D::Update(void)
{
	m_pMotion->Update();
	m_posOld = GetPos();
	m_pos = GetPos();
	
	// �v���C���[����
	if (m_State != STATE_ATTACK)
	{
		PlayerContoroll();
	}
	m_pos += m_move;
	// �d��
	m_move.y -= GRAVITY;

	// ����
	m_move *= MOVE_DEFINE;
	
	// ��ԑ���
	StateContoroll();

	if (m_pos.y < 0.0f)
	{
		m_move.y = 0.0f;
		m_pos.y = m_posOld.y;
	}

}

//====================================================
// �`�揈��
//====================================================
void CPlayer3D::Draw(void)
{
	CRenderer *pRenderer = CManager::Get()->GetRenderer();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;	

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}

//====================================================
//�v���C���[�̑��쏈��
//====================================================
void CPlayer3D::PlayerContoroll(void)
{
	// ���̓f�o�C�X�̏��擾
	CKeyboard* pKeyboard = CManager::Get()->GetInputKeyboard();
	CGamepad *pGamepad = CManager::Get()->GetInputGamepad();
	
	// �J�����̏��擾
	CCamera *pCamera = CManager::Get()->GetCamera();
	float CameraRot = pCamera->GetRot();

	// �S�����ړ��v���O����
	if (pKeyboard->GetPress(DIK_D) == true || pGamepad->GetLStickX(GAMEPAD_LSTICK_DEADZONE) == true)
	{
		if (pKeyboard->GetPress(DIK_W) == true || pGamepad->GetLStickY(GAMEPAD_LSTICK_DEADZONE) == true)
		{ // WD�����
			m_rot.y = D3DX_PI * -0.75f;
		}
		else if (pKeyboard->GetPress(DIK_S) == true || pGamepad->GetLStickY(-GAMEPAD_LSTICK_DEADZONE) == true)
		{ // SD�����
			m_rot.y = D3DX_PI * -0.25f;
		}
		else
		{ // D�����
			m_rot.y = D3DX_PI * -0.5f;
		}
		m_bMove = true;
	}
	else if (pKeyboard->GetPress(DIK_A) == true || pGamepad->GetLStickX(-GAMEPAD_LSTICK_DEADZONE) == true)
	{
		if (pKeyboard->GetPress(DIK_W) == true || pGamepad->GetLStickY(GAMEPAD_LSTICK_DEADZONE) == true)
		{ // WA�����
			m_rot.y = D3DX_PI * 0.75f;
		}
		else if (pKeyboard->GetPress(DIK_S) == true || pGamepad->GetLStickY(-GAMEPAD_LSTICK_DEADZONE) == true)
		{ // SA�����
			m_rot.y = D3DX_PI * 0.25f;
		}
		else
		{ // A�����
			m_rot.y = D3DX_PI * 0.5f;
		}
		m_bMove = true;
	}
	else if (pKeyboard->GetPress(DIK_W) == true|| pGamepad->GetLStickY(GAMEPAD_LSTICK_DEADZONE) == true)
	{ // W�����
		m_rot.y = D3DX_PI * 1.0f;
		m_bMove = true;
	}
	else if (pKeyboard->GetPress(DIK_S) == true || pGamepad->GetLStickY(-GAMEPAD_LSTICK_DEADZONE) == true)
	{ // S����G�ǂ�
		m_rot.y = D3DX_PI * 0.0f;
		m_bMove = true;
	}
	else
	{
		m_bMove = false;
	}
	// �ړ����Ă����ꍇ
	if (m_bMove == true)
	{
		m_move.x = -sinf(m_rot.y) * PLAYER_SPEED;
		m_move.z = -cosf(m_rot.y) * PLAYER_SPEED;
	}

	// �U��
	if (pKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		m_State = STATE_ATTACK;
	}
}



//=========================================================================================================
// �T�C�Y�̌v�Z����
//=========================================================================================================
void CPlayer3D::SetObjectSize(void)
{
	int nNumVtx;

	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	for (int nCnt = 0; nCnt < NUM_PARTS; nCnt++)
	{

		//���_���̎擾
		nNumVtx = m_apModel[nCnt]->m_pMeshModel->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		dwSizeFVF = D3DXGetFVFVertexSize(m_apModel[nCnt]->m_pMeshModel->GetFVF());

		//���_�o�b�t�@�����b�N
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
// �G�e�Ƃ̓����蔻��
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
// ��ԑ��쏈��
//====================================================
void CPlayer3D::StateContoroll(void)
{
	CKeyboard* pKeyboard = CManager::Get()->GetInputKeyboard();
	if (m_State != STATE_ATTACK)
	{
		if (m_bMove ==true)
		{// �ړ����Ă����ꍇ
			m_State = STATE_RUN;
		}
		else
		{
			m_State = STATE_WATE;
		}
	}
	if (m_pMotion->GetFinish() == true)
	{ // ���[�V�������I����Ă����ꍇ
		m_State = STATE_WATE;

	}
	m_pMotion->SetState(CMotion::MOTIONSTATE(m_State));

}

//====================================================
// �~�̓����蔻��
//====================================================
bool CPlayer3D::isWithinAttackRange(float enemyX, float enemyZ) 
{
	if (m_State == PLAYERSTATE::STATE_ATTACK)
	{
		// �G�Ƃ̋������v�Z
		float distance = std::sqrt(std::pow(m_pos.x - enemyX, 2) + std::pow(m_pos.z - enemyZ, 2));

		// �ߐڍU���̗L���͈͓����ǂ����𔻒�
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
// ������␳
//====================================================
float CPlayer3D:: Normalize(float rot)
{
	if (rot > D3DX_PI)
	{ // ������3.14f�𒴂��Ă����ꍇ

		// ������␳����
		rot -= D3DX_PI * 2;
	}
	else if (rot < -D3DX_PI)
	{ // ������-3.14f�𒴂��Ă����ꍇ

		// ������␳����
		rot += D3DX_PI * 2;
	}
	return rot;
}

//============================================== �ݒ菈�� ==============================================

//====================================================
// �ʒu�ݒ菈��
//====================================================
void CPlayer3D::SetPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;
}

//====================================================
// �ړ��ʂ�ݒ�
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
// �v���C���[�̏�Ԃ�ݒ�
//====================================================
void CPlayer3D::SetPlayerState(PLAYERSTATE state)
{
	m_State = state;
}

//====================================================
// �e�q�֌W��ݒ�
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

//============================================== �擾���� ==============================================

//====================================================
// �ʒu�擾����
//====================================================
D3DXVECTOR3 CPlayer3D::GetPos(void)
{
	return m_pos;
}

//====================================================
// �ߋ��̈ʒu���擾
//====================================================
D3DXVECTOR3 CPlayer3D::GetPosOld(void)
{
	return m_posOld;
}

//====================================================
// �������擾
//====================================================
D3DXVECTOR3 CPlayer3D::GetRot(void)
{
	return m_rot;
}