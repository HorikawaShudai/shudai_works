//=========================================================================================================
//
//2D��p�̓G�̏���
//Author:�x�씋��
//
//=========================================================================================================
#include "3DEnemy.h"
#include "Object3D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Block.h"
#include "Score.h"
#include "ModelBullet.h"
#include "3DBlock.h"
#include "Object.h"
#include "Game.h"
#include "Effect.h"

#define PLAYER_SPEED	(0.2f)


D3DXVECTOR3 CEnemy3D::m_VtxMaxObject;
D3DXVECTOR3 CEnemy3D::m_VtxMinObject;
int CEnemy3D::m_NumEnemy = 0;
//====================================================
//�R���X�g���N�^
//====================================================
CEnemy3D::CEnemy3D(int nPriority) :CObject3D(nPriority)
{
	m_NumEnemy++;

}
//====================================================
//�f�X�g���N�^
//====================================================
CEnemy3D::~CEnemy3D()
{
	m_NumEnemy--;
}


//====================================================
//�G�̏���������
//====================================================
HRESULT CEnemy3D::Init(void)
{
	//m_pos = D3DXVECTOR3(0.0f, 0.0f, 1280.0f);
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_State = STATE_WATE;
	m_Knockback = false;
	m_nCntAttack = 0;
	m_apModel[0] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM1); //��
	m_apModel[1] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM2); //��
	m_apModel[2] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM3); //��
	m_apModel[3] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM4); //�E��
	m_apModel[4] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM5); //�E�r
	m_apModel[5] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM6); //�E��
	m_apModel[6] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM7); //����
	m_apModel[7] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM8); //���r
	m_apModel[8] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM9); //����
	m_apModel[9] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM10);//�E��
	m_apModel[10] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM11);//�E��
	m_apModel[11] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM12);//�E��
	m_apModel[12] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM13);//����
	m_apModel[13] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM14);//����
	m_apModel[14] = CModel::CreateModel(CModel::ENEMY_MODEL_NUM15);//����


	m_apModel[0]->SetParent(NULL);			//��
	m_apModel[1]->SetParent(m_apModel[0]);	//��
	m_apModel[2]->SetParent(m_apModel[1]);	//��
	m_apModel[3]->SetParent(m_apModel[1]); //�E��
	m_apModel[4]->SetParent(m_apModel[3]); //�E�r
	m_apModel[5]->SetParent(m_apModel[4]); //�E��
	m_apModel[6]->SetParent(m_apModel[1]); //����
	m_apModel[7]->SetParent(m_apModel[6]); //���r
	m_apModel[8]->SetParent(m_apModel[7]); //����
	m_apModel[9]->SetParent(m_apModel[0]); //�E��
	m_apModel[10]->SetParent(m_apModel[9]); //�E��
	m_apModel[11]->SetParent(m_apModel[10]);//�E��
	m_apModel[12]->SetParent(m_apModel[0]); //����
	m_apModel[13]->SetParent(m_apModel[12]);//����
	m_apModel[14]->SetParent(m_apModel[13]);//����

	m_pMotion = CMotion::Create();
	m_pMotion->SetModel(15, GetModel());
	m_pMotion->LoadMotion("data\\TEXT\\motione.txt");

	SetType(CObject::TYPE_ENEMY);
	SetObjectSize();
	m_VtxMaxObject.y = 40.0f;
	return S_OK;
}

//====================================================
//�G�̏I������
//====================================================
void CEnemy3D::Uninit(void)
{
	delete m_pMotion;
	m_pMotion = nullptr;
	//CManager::SetEnemyNull(nCntId);
	for (int nCnt = 0; nCnt < 15; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = nullptr;
		}
	}
}

//====================================================
//�G�̍X�V����
//====================================================
void CEnemy3D::Update(void)
{
	int nCnt = 0;
	m_posOld = GetPos();
	m_pos = GetPos();
	AiContoroll();
	m_pos += m_move;
	m_move.y -= GRAVITY;

	m_move *= 0.9f;
	m_pMotion->Update();

	//�m�b�N�o�b�N����
	if (CPlayer3D::isWithinAttackRange(m_pos.x, m_pos.z) == true)
	{
		D3DXVECTOR3 rot = CPlayer3D::GetRot();

		if (rot.y == D3DX_PI * 0.5f) // s
		{
			m_rot.y = D3DX_PI * 1.0f;
		}
		else if (rot.y == D3DX_PI * 1.0f) // a
		{
			m_rot.y = D3DX_PI * 0.5f;
		}
		else if (rot.y == D3DX_PI * 0.0f) // d
		{
			m_rot.y = -D3DX_PI * 0.5f;
		}
		else if (rot.y == -D3DX_PI * 0.5f) // w
		{
			m_rot.y = D3DX_PI * 0.0f;
		}
		else if (rot.y == -D3DX_PI * 0.75f) // d
		{
			m_rot.y = D3DX_PI * 0.25f;
		}
		else if (rot.y == D3DX_PI * 0.25f) // w
		{
			m_rot.y = -D3DX_PI * 0.75f;
		}
		else
		{
			m_rot = rot;

		}
		m_pos.y = 1.0f;
		m_move.x = 4.0f * cosf(m_rot.y);
		m_move.y = 5.0f;
		m_move.z = 4.0f * sinf(m_rot.y);
		m_Knockback = true;

	}

	if (m_pos.y < 0.0f)
	{
		m_move.y = 0.0f;
		m_pos.y = m_posOld.y;
		if (m_Knockback == true)
		{
			//CObject3D::Create(D3DXVECTOR3(0.0f, 0.0f, 40.0f), 1.0f, CObject::TYPE_ENEMY, 0);

			CScore* pScore;
			pScore = CGame::GetpScore();
			pScore->AddScore(100);
			CEffect::Create(m_pos);
			Release();
		}
	}
}

//====================================================
//�G�̕`�揈��
//====================================================
void CEnemy3D::Draw(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	CTexture *pTexture = CManager::Get()->GetpTexture();

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

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

	for (int nCnt = 0; nCnt < 15; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

	////���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//pDevice->SetFVF(FVF_VERTEX_3D);


	//pDevice->SetTexture(0, pTexture->GetAddress(m_TexId));

	////�n��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//====================================================
//�G�̑��쏈��
//====================================================
void CEnemy3D::AiContoroll(void)
{
	D3DXVECTOR3 pPos;

	pPos = CPlayer3D::GetPos();

	float fDistance = D3DXVec3Length(&(pPos - m_pos));

	m_rot.y = atan2f(pPos.z - m_pos.z, pPos.x - m_pos.x);
	
	//�ړ�AI
	if (fDistance > 180.0f || fDistance < -180.0f)
	{
		m_State = STATE_RUN;
		m_nCntAttack = 0;
		m_move.x += cosf(m_rot.y) * 0.2f;
		m_move.z += sinf(m_rot.y) * 0.2f;
	}
	else
	{
		m_State = STATE_ATTACK;
	}
	if (m_State == STATE_ATTACK)
	{
		m_nCntAttack++;
		if (m_nCntAttack > 0 && m_nCntAttack % 80 == 0)
		{
				CModelBullet::CreateModel(D3DXVECTOR3(m_pos.x, m_pos.y + 10.0f, m_pos.z), D3DXVECTOR3(cosf(m_rot.y), 0.0f, sinf(m_rot.y)), CModelBullet::ENEMY_BULLET);
		}
	}
	m_pMotion->SetState(CMotion::MOTIONSTATE(m_State));


}

//====================================================
//�ʒu�ݒ菈��
//====================================================
void CEnemy3D::SetPos(D3DXVECTOR3 pos, float Height, float Width)
{
	m_pos = pos;
}

//====================================================
//�ʒu�擾����
//====================================================
D3DXVECTOR3 CEnemy3D::GetPos(void)
{
	return m_pos;
}

//====================================================
//��������
//====================================================
CEnemy3D *CEnemy3D::Create(D3DXVECTOR3 pos)
{
	CEnemy3D *p3DEnemy = NULL;
	p3DEnemy = DBG_NEW CEnemy3D;
	//p3DEnemy->Init();
	p3DEnemy->m_pos = pos;
	return p3DEnemy;
}



//=========================================================================================================
//�T�C�Y�̌v�Z����
//=========================================================================================================
void CEnemy3D::SetObjectSize(void)
{
	int nNumVtx;

	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	for (int nCnt = 0; nCnt < 15; nCnt++)
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

//=========================================================================================================
//�G�Ƃ̓����蔻��
//=========================================================================================================
bool CEnemy3D::ColissionModBull(D3DXVECTOR3 pos, D3DXVECTOR3 BullPos)
{
	bool bHit = false;

	if (BullPos.z <= (pos.z + m_VtxMaxObject.z) && BullPos.z >= (pos.z + m_VtxMinObject.z))
	{
		if ((BullPos.x >= (pos.x + m_VtxMinObject.x)) && BullPos.x <= (pos.x + m_VtxMaxObject.x))
		{
			if (BullPos.y <= (pos.y + m_VtxMaxObject.y) && BullPos.y >= (pos.y + m_VtxMinObject.y))
			{
				//CObject::Release();
				CScore* pScore;
				pScore = CGame::GetpScore();
				pScore->AddScore(50);
				bHit = true;
			}
		}
		
	}
	return bHit;
}