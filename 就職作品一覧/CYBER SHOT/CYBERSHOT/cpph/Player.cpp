//===========================================================
//
//player�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Player.h"
#include "Camera.h"
#include "Shadow.h"
#include "Bullet.h"
#include "Object.h"
#include "MeshWall.h"
#include "Item.h"
#include "Fade.h"
#include "Game.h"
#include "Sound.h"
#include "Enemy.h"
#include "ModelBullet.h"
#include "effect.h"

#define MODEL_NAME "data\\MODEL\\Player.x"
#define MODEL_NAMEEND "data\\MODEL\\Player_end.x"
#define MODEL_NAMECLEAR "data\\MODEL\\Player_Clear.x"
#define MOVE_SPEED (0.7f)
#define GRAVITY (1.8f)
#define ENAGY (3)
#define MAX_MAT (256) 
#define MAX_LIFE (10)

//�O���[�o���ϐ��錾
LPD3DXMESH g_pMeshPlayer = NULL;
LPD3DXBUFFER g_pBuffMatPlayer = NULL;
DWORD g_dwNumMatPlayer = 0;
PLAYER g_Player;
LPDIRECT3DTEXTURE9 g_apTEXturePlayer[MAX_MAT] = {};

void PlayerMod(void);
void PlayerEnemy(void);
//=========================================================================================================
//����������
//=========================================================================================================
void InitPlayer(void)
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_Player.pos = D3DXVECTOR3(-1650.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.moveP = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nIdxShadow = -1;
	g_Player.VtxMaxPlayer = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_Player.VtxMinPlayer = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_Player.aModel[5] = {};
	g_Player.col[MAX_MAT] = {};
	g_Player.nLife = 10;
	g_Player.nEnagy = ENAGY;
	g_Player.EngCnt = 0;
	g_Player.CameraLock = false;


	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL* pMat;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		g_Player.col[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTEXturePlayer[nCntMat]);
		}
	}


	int nNumVtx;
	DWORD dwSizeFVF;
	BYTE* pVtxBuff;

	//���_���̎擾
	nNumVtx = g_pMeshPlayer->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer->GetFVF());

	//���_�o�b�t�@�����b�N
	g_pMeshPlayer->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (vtx.x > g_Player.VtxMaxPlayer.x)
		{
			g_Player.VtxMaxPlayer.x = vtx.x;
		}
		if (vtx.z > g_Player.VtxMaxPlayer.z)
		{
			g_Player.VtxMaxPlayer.z = vtx.z;
		}
		if (vtx.x < g_Player.VtxMinPlayer.x)
		{
			g_Player.VtxMinPlayer.x = vtx.x;
		}

		if (vtx.z < g_Player.VtxMinPlayer.z)
		{
			g_Player.VtxMinPlayer.z = vtx.z;
		}
		if (vtx.y > g_Player.VtxMaxPlayer.y)
		{
			g_Player.VtxMaxPlayer.y = vtx.y;
		}
		if (vtx.y < g_Player.VtxMinPlayer.y)
		{
			g_Player.VtxMinPlayer.y = vtx.y;
		}
		pVtxBuff += dwSizeFVF;
	}
	g_Player.nIdxShadow = SetShadow(15.0f, g_Player.pos);

	g_Player.bUse = true;
}

//=========================================================================================================
//����������
//=========================================================================================================
void InitEndPlayer(void)
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_Player.pos = D3DXVECTOR3(-1650.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.moveP = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nIdxShadow = -1;
	g_Player.aModel[5] = {};
	g_Player.nLife = 1;


	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAMEEND,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL* pMat;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		g_Player.col[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTEXturePlayer[nCntMat]);
		}
	}
	g_Player.nIdxShadow = SetShadow(15.0f, g_Player.pos);

	g_Player.bUse = true;
}

//=========================================================================================================
//����������
//=========================================================================================================
void InitClearPlayer(void)
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_Player.pos = D3DXVECTOR3(-1650.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.moveP = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nIdxShadow = -1;
	g_Player.aModel[5] = {};
	g_Player.nLife = 1;


	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAMECLEAR,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL* pMat;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		g_Player.col[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTEXturePlayer[nCntMat]);
		}
	}
	g_Player.nIdxShadow = SetShadow(15.0f, g_Player.pos);

	g_Player.bUse = true;
}



//=========================================================================================================
//�v���C���[�̏I������
//=========================================================================================================
void UninitPlayer(void)
{
	for (int nCntMat = 0; nCntMat < MAX_MAT; nCntMat++)
	{
		if (g_apTEXturePlayer[nCntMat] != NULL)
		{
			g_apTEXturePlayer[nCntMat]->Release();
			g_apTEXturePlayer[nCntMat] = NULL;
		}
	}
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
	StopSound();
}

//=========================================================================================================
//�v���C���[�̍X�V����
//=========================================================================================================
void UpdatePlayer(void)
{
	Camera aCamera = GetCamera();
	g_Player.posOld = g_Player.pos;

	MODE aMode = GetMode();
	if (aMode == MODE_TUTORIAL)
	{
		if (GetKeyboardPress(DIK_8) == true)
		{
			g_Player.nLife = 10;
			g_Player.bUse = true;
		}
	}

	if (g_Player.bUse == true)
	{

		//�ړ�����
		PlayerMove();

		//�_�b�V������
		PlayerEnagy();
		if (g_Player.CameraLock == true)
		{
			EnemyLockOn();
		}
		{//�U������
			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{
				PlaySound(SOUND_LABEL_SE_SHOT);
				SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 40.0f, g_Player.pos.z - (cosf(g_Player.rot.y) * 10.0f)), D3DXVECTOR3(0.0f, 0.0f, 0.5f), g_Player.rot, BULLETTYPE_PLAYER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
		if (GetKeyboardTrigger(DIK_I) == true)
		{
			switch (g_Player.CameraLock)
			{
			case true:
				SetHoming(false);
				g_Player.CameraLock = false;
				break;
			case false:
				SetHoming(true);
				g_Player.CameraLock = true;
				break;
			}
		}

		//�v���C���[�̌����␳
		{
			{
				g_Player.Diffrot.y = g_Player.Destrot.y - g_Player.rot.y;

				if (g_Player.Diffrot.y > D3DX_PI)
				{
					g_Player.Diffrot.y -= D3DX_PI * 2;
				}
				else if (g_Player.Diffrot.y < -D3DX_PI)
				{
					g_Player.Diffrot.y += D3DX_PI * 2;

				}

				g_Player.rot.y += (g_Player.Diffrot.y) * 0.1f;

				if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y -= D3DX_PI * 2;
				}
				else if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y += D3DX_PI * 2;
				}
			}
		}

		//�ʒu�X�V
		{
			g_Player.moveP.y -= GRAVITY;
			g_Player.moveP *= 0.9f;
			g_Player.pos += g_Player.moveP;
			if (g_Player.pos.y < 0.0f)
			{
				g_Player.pos.y = 0.0f;
				g_Player.moveP.y = 0.0f;
			}
		}

		if (g_Player.nLife < 10)
		{
			//�A�C�e���̓����蔻��
			ColissionItem(g_Player.pos, g_Player.posOld, g_Player.moveP);
		}
		//�I�u�W�F�N�g�Ƃ̓����蔻��
		PlayerObject();

		//�ǂƂ̓����蔻��
		PlayerWall();

		PlayerMod();
		PlayerEnemy();

		//�v���C���[�̑J�ڏ��
		PlayerState();

		SetPositionShadow(g_Player.nIdxShadow, D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z));
	}
}

//=========================================================================================================
//�v���C���[�̕`�揈��
//=========================================================================================================
void DrawPlayer(void)
{
	if (g_Player.bUse == true)
	{
		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
		D3DMATERIAL9 matDef;
		D3DXMATERIAL* pMat;

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.mtxWorldPlayer);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
		D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
		D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorldPlayer);

		//���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);
		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTEXturePlayer[nCntMat]);

			//�v���C���[�i�p�[�c�j�̕`��
			g_pMeshPlayer->DrawSubset(nCntMat);
		}
		pDevice->SetMaterial(&matDef);
	}
}

//=========================================================================================================
//�v���C���[�̒e�̓����蔻��
//=========================================================================================================
bool ColissionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 pMove)
{
	bool bHit = false;
	D3DXVECTOR3 RPos;
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecTopos;
	D3DXVECTOR3 vecmove;
	RPos = pos;
	vecmove = pos - posOld;




	if (g_Player.bUse == true)
	{
		{//��_����
		 //vecLine.x = g_Player.VtxMaxPlayer.x - g_Player.VtxMinPlayer.x;
		 //vecLine.z = g_Player.VtxMaxPlayer.z - g_Player.VtxMaxPlayer.z;
		 //vecTopos = pos - D3DXVECTOR3(g_Player.VtxMinPlayer.x, 0.0f, g_Player.VtxMaxPlayer.z);


		 //Playerpos[0] = (vecTopos.z*vecmove.x) - (vecTopos.x*vecmove.z);
		 //Playerpos[1] = (vecLine.z*vecmove.x) - (vecLine.x*vecmove.z);
		 //Playerpos[2] = Playerpos[0] / Playerpos[1];
		 //if (Playerpos[2] >= 0.0f&&Playerpos[2] <= 1.0f)
		 //{
		 //	RPos = D3DXVECTOR3(0.0f, 300.0f, 500.0f);
		 //}
		}

		if (pos.x >= (g_Player.pos.x + g_Player.VtxMinPlayer.x) && pos.z <= (g_Player.pos.z + g_Player.VtxMaxPlayer.z) &&
			pos.x <= (g_Player.pos.x + g_Player.VtxMaxPlayer.x) && pos.z >= (g_Player.pos.z + g_Player.VtxMinPlayer.z) &&
			pos.y <= (g_Player.pos.y + g_Player.VtxMaxPlayer.y) && pos.y >= (g_Player.pos.y + g_Player.VtxMinPlayer.y))
		{
			HitPlayer(1);
			bHit = true;
		}
	}

	return bHit;
}

//=========================================================================================================
//�v���C���[�̃q�b�g����
//=========================================================================================================
void HitPlayer(int nDamage)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	if (g_Player.state != PLAYERSTATE_DUSH)
	{

		if (g_Player.state == PLAYERSTATE_NORMAL)
		{
			PlaySound(SOUND_LABEL_SE_HIT);
			g_Player.nLife -= nDamage;
		}
		if (g_Player.nLife < 1)
		{
			g_Player.bUse = false;
			FADE fFade = GetFade();
			if (g_Player.nLife <= 0 && fFade == FADE_NONE)
			{
				MODE aMode = GetMode();
				if (aMode == MODE_GAME)
				{
					SetGamemode(GAMEMODE_GAMEOVER);
					//PlaySound(SOUND_LABEL_SE_DECISION);
					SetFade(MODE_RESULT, 0.05f);
				}
			}
		}
		else
		{

			if (g_Player.state == PLAYERSTATE_NORMAL)
			{
				g_Player.state = PLAYERSTATE_DAMAGE;

				D3DXMATERIAL* pMat;

				//�}�e���A���f�[�^�ւ̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++, pMat++)
				{
					pMat->MatD3D.Diffuse = { 1.0f,0.0f,0.0f,1.0f };
				}
				g_Player.nCntState = 60;
			}

		}
	}

}

//=========================================================================================================
//�G�̏�ԑJ�ڏ���
//=========================================================================================================
void HitItem(ITEM aItem)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	if (aItem.nType == ITEM_KIND_000)
	{
		g_Player.nLife += 10;
		if (g_Player.nLife > MAX_LIFE)
		{
			g_Player.nLife = MAX_LIFE;
		}
	}
}

//=========================================================================================================
//�v���C���[���̎擾����
//=========================================================================================================
PLAYER GetPlayer(void)
{
	return g_Player;
}

//=========================================================================================================
//�v���C���[�̈ړ�����
//=========================================================================================================
void PlayerMove(void)
{
	//�ړ�����
	{
		Camera aCamera = GetCamera();

		if (GetKeyboardPress(DIK_W) == true)
		{//W�̂݉����ꂽ�ꍇ
			if (GetKeyboardPress(DIK_A) == true)
			{//A�̂݉����ꂽ�ꍇ
				g_Player.moveP.x += cosf(D3DX_PI * 0.25f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.moveP.z += sinf(D3DX_PI * 0.25f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.Destrot.y = -D3DX_PI * 0.25f - aCamera.rot.y;
				if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y = D3DX_PI;
				}
				else if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y = -D3DX_PI;
				}
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{//D�̂݉����ꂽ�ꍇ
				g_Player.moveP.x += cosf(-D3DX_PI * 0.25f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.moveP.z += sinf(-D3DX_PI * 0.25f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.Destrot.y = D3DX_PI * 0.25f - aCamera.rot.y;
				if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y = D3DX_PI;
				}
				else if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y = -D3DX_PI;
				}
			}
			else
			{
				g_Player.moveP.x += cosf(D3DX_PI * 0.0f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.moveP.z += sinf(D3DX_PI * 0.0f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.Destrot.y = +D3DX_PI * 0.0f - aCamera.rot.y;
				if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y = D3DX_PI;
				}
				else if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y = -D3DX_PI;
				}
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//S�̂݉����ꂽ�ꍇ
			if (GetKeyboardPress(DIK_A) == true)
			{//A�̂݉����ꂽ�ꍇ
				g_Player.moveP.x += cosf(D3DX_PI * 0.75f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.moveP.z += sinf(D3DX_PI * 0.75f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.Destrot.y = -D3DX_PI * 0.75f - aCamera.rot.y;
				if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y = D3DX_PI;
				}
				else if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y = -D3DX_PI;
				}
			}
			else if (GetKeyboardPress(DIK_D) == true)
			{//D�̂݉����ꂽ�ꍇ
				g_Player.moveP.x += cosf(-D3DX_PI * 0.75f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.moveP.z += sinf(-D3DX_PI * 0.75f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.Destrot.y = D3DX_PI * 0.75f - aCamera.rot.y;
				if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y = D3DX_PI;
				}
				else if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y = -D3DX_PI;
				}
			}
			else
			{
				g_Player.moveP.x += cosf(+D3DX_PI * 1.0f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.moveP.z += sinf(+D3DX_PI * 1.0f + aCamera.rot.y) * MOVE_SPEED;
				g_Player.Destrot.y = -D3DX_PI * 1.0f - aCamera.rot.y;
				if (g_Player.rot.y < -D3DX_PI)
				{
					g_Player.rot.y = D3DX_PI;
				}
				else if (g_Player.rot.y > D3DX_PI)
				{
					g_Player.rot.y = -D3DX_PI;
				}
			}
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{//A�̂݉����ꂽ��
			g_Player.moveP.x += cosf(D3DX_PI * 0.5f + aCamera.rot.y) * MOVE_SPEED;
			g_Player.moveP.z += sinf(D3DX_PI * 0.5f + aCamera.rot.y) * MOVE_SPEED;
			g_Player.Destrot.y = -D3DX_PI * 0.5f - aCamera.rot.y;
			if (g_Player.rot.y < -D3DX_PI)
			{
				g_Player.rot.y = D3DX_PI;
			}
			else if (g_Player.rot.y > D3DX_PI)
			{
				g_Player.rot.y = -D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//D�̂݉����ꂽ�ꍇ
			g_Player.moveP.x += cosf(-D3DX_PI * 0.5f + aCamera.rot.y) * MOVE_SPEED;
			g_Player.moveP.z += sinf(-D3DX_PI * 0.5f + aCamera.rot.y) * MOVE_SPEED;
			g_Player.Destrot.y = D3DX_PI * 0.5f - aCamera.rot.y;
			if (g_Player.rot.y < -D3DX_PI)
			{
				g_Player.rot.y = D3DX_PI;
			}
			else if (g_Player.rot.y > D3DX_PI)
			{
				g_Player.rot.y = -D3DX_PI;
			}
		}


	}
}

//=========================================================================================================
//�v���C���[�̃_�b�V������
//=========================================================================================================
void PlayerEnagy(void)
{
	if (GetKeyboardTrigger(DIK_K) == true && g_Player.nEnagy > 0)
	{//E�̂݉����ꂽ�ꍇ
		g_Player.nEnagy -= 1;
		g_Player.state = PLAYERSTATE_DUSH;
		g_Player.nCntState = 20;
		g_Player.moveP.x += cosf(g_Player.rot.y) * 20.0f;
		g_Player.moveP.z -= sinf(g_Player.rot.y) * 20.0f;

		D3DXMATERIAL* pMat;
		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++, pMat++)
		{
			pMat->MatD3D.Diffuse = { 0.0f,1.0f,0.0f,0.8f };
		}
	}
	if (g_Player.nEnagy < ENAGY)
	{
		g_Player.EngCnt++;
		if (g_Player.EngCnt % 120 == 0)
		{
			g_Player.nEnagy++;
		}
	}
	if (g_Player.nEnagy >= ENAGY)
	{
		g_Player.EngCnt = 0;
	}
}

//=========================================================================================================
//�v���C���[�ƕǂ̓����蔻��
//=========================================================================================================
void PlayerWall(void)
{

	//D3DXVECTOR3 HitWall = ColissionWall(g_Player.pos, g_Player.posOld, &g_Player.moveP);
	//
	//g_Player.pos = HitWall;
	{//+X�̕�
		if (g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x) > 1700.0f)
		{
			g_Player.pos.x = 1700.0f - (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x);
			g_Player.moveP.x = 0.0f;
		}
		else if (g_Player.pos.x + cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x > 1700.0f)
		{
			g_Player.pos.x = 1700.0f - (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x);
			g_Player.moveP.x = 0.0f;
		}
		if (g_Player.pos.x + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z) > 1700.0f)
		{
			g_Player.pos.x = 1700.0f - (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z);
			g_Player.moveP.x = 0.0f;
		}
		else if (g_Player.pos.x + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z) > 1700.0f)
		{
			g_Player.pos.x = 1700.0f - (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z);
			g_Player.moveP.x = 0.0f;
		}
	}

	{//-X�̕�
		if (g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x) < -1700.0f)
		{
			g_Player.pos.x = -1700.0f - (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x);
			g_Player.moveP.x = 0.0f;
		}
		else if (g_Player.pos.x + cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x < -1700.0f)
		{
			g_Player.pos.x = -1700.0f - (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x);
			g_Player.moveP.x = 0.0f;
		}
		else if (g_Player.pos.x + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z) < -1700.0f)
		{
			g_Player.pos.x = -1700.0f - (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z);
			g_Player.moveP.x = 0.0f;
		}
		else if (g_Player.pos.x + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z) < -1700.0f)
		{
			g_Player.pos.x = -1700.0f - (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z);
			g_Player.moveP.x = 0.0f;
		}
	}

	{//+Z�̕�
		if (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x) > 1990.0f)
		{
			g_Player.pos.z = 1990.0f - (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x);
			g_Player.moveP.z = 0.0f;
		}
		else if (g_Player.pos.z + sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.x > 1990.0f)
		{
			g_Player.pos.z = 1990.0f - (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.x);
			g_Player.moveP.z = 0.0f;
		}
		else if (g_Player.pos.z + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.z) > 1700.0f)
		{
			g_Player.pos.z = 1700.0f - (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.z);
			g_Player.moveP.z = 0.0f;
		}
		else if (g_Player.pos.z + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z) > 1700.0f)
		{
			g_Player.pos.z = 1700.0f - (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z);
			g_Player.moveP.z = 0.0f;
		}

	}
	{//-Z�̕�
		if ((g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)) < -1700.0f)
		{
			g_Player.pos.z = (-1700.0f + (-sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x));
			g_Player.moveP.z = 0.0f;
		}
		else if ((g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)) < -1700.0f)
		{
			g_Player.pos.z = (-1700.0f + (-sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.x));
			g_Player.moveP.z = 0.0f;
		}
		else if ((g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z)) < -1990.0f)
		{
			g_Player.pos.z = (-1990.0f - (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z));
			g_Player.moveP.z = 0.0f;
		}
		else if ((g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z)) < -1990.0f)
		{
			g_Player.pos.z = (-1990.0f - (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z));
			g_Player.moveP.z = 0.0f;
		}

	}
}

//=========================================================================================================
//�v���C���[�ƃI�u�W�F�N�g�̓����蔻��
//=========================================================================================================
void PlayerObject(void)
{
	D3DXVECTOR3 HitObject;
	HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	g_Player.pos = HitObject;
	HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	g_Player.pos = HitObject;
	HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	g_Player.pos = HitObject;
	HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	g_Player.pos = HitObject;
	//HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y)*g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (cosf(g_Player.rot.y)*g_Player.VtxMinPlayer.x))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	//g_Player.pos = HitObject;
	//HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y)*g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (cosf(g_Player.rot.y)*g_Player.VtxMaxPlayer.x))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	//g_Player.pos = HitObject;
	//HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y)*g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (cosf(g_Player.rot.y)*g_Player.VtxMinPlayer.x))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	//g_Player.pos = HitObject;
	//HitObject = ColissionObject(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y)*g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (cosf(g_Player.rot.y)*g_Player.VtxMaxPlayer.x))), g_Player.pos, g_Player.posOld, &g_Player.moveP);
	//g_Player.pos = HitObject;
}

void PlayerMod(void)
{
	if (ColissionModBull(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
	if (ColissionModBull(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
	if (ColissionModBull(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
	if (ColissionModBull(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
}

void PlayerEnemy(void)
{
	if (ColPlayEnemy(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
	if (ColPlayEnemy(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMaxPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
	if (ColPlayEnemy(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMaxPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
	if (ColPlayEnemy(D3DXVECTOR3((g_Player.pos.x + (cosf(g_Player.rot.y) * g_Player.VtxMinPlayer.x)), g_Player.pos.y, (g_Player.pos.z + (sinf(g_Player.rot.y) * g_Player.VtxMinPlayer.z))), g_Player.posOld) == true)
	{
		HitPlayer(1);
	}
}

//=========================================================================================================
//�v���C���[�̑J�ڏ��
//=========================================================================================================
void PlayerState(void)
{
	switch (g_Player.state)
	{
	case PLAYERSTATE_NORMAL:
		D3DXMATERIAL* pMat;

		//�}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++, pMat++)
		{
			pMat->MatD3D.Diffuse = g_Player.col[nCntMat];

		}
		break;

	case PLAYERSTATE_DAMAGE:
		g_Player.nCntState--;
		if (g_Player.nCntState <= 0)
		{
			g_Player.state = PLAYERSTATE_NORMAL;
		}
		break;
	case PLAYERSTATE_DUSH:
		g_Player.nCntState--;
		SetEffect(g_Player.pos, D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f), 15.0f, 10, EFFECT_KIND_SANDDUST);
		if (g_Player.nCntState <= 0)
		{
			g_Player.state = PLAYERSTATE_NORMAL;
		}
		break;
	}
}

void SetPosition(D3DXVECTOR3 pos)
{
	g_Player.pos = pos;
}

void EnemyLockOn(void)
{

	if (GetKeyboardPress(DIK_J) == true)
	{
		g_Player.rot.y -= 0.02f;
		if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y = -D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_L) == true)
	{
		g_Player.rot.y += 0.02f;
		if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y = D3DX_PI;
		}

	}
	ENEMY aEnemy = GetEnemy();
	g_Player.rot = g_Player.rot;
	g_Player.Destrot = g_Player.rot;
	//g_Player.rot = D3DXVECTOR3(0.0f, -atan2f((aEnemy.pos.x), (aEnemy.pos.z)), 0.0f);
}