//===========================================================
//
//�ǂ̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "MeshWall.h"

#define MAX_WALL  (50)
#define FIELD_HEIGHT (2)
#define FIELD_HEIGHT_SIZE (1700.0f)
#define FIELD_WIDTH  (2)
#define FIELD_WIDTH_SIZE  (200.0f)
#define DIVISION	 ((FIELD_WIDTH+1)*(FIELD_HEIGHT+1))
#define FIELF_SIZE (500.0f)


typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtxWorld;
	float Length;
	bool bUse;
}WALL;

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;		//���_�o�b�t�@�|�C���g
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;
WALL g_WallMesh[MAX_WALL];
D3DXMATRIX g_MeshWallmtxWorld;

//=========================================================================================================
//����������
//=========================================================================================================
void InitMeshWall(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		g_WallMesh[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_WallMesh[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_WallMesh[nCnt].bUse = false;
	}


	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * DIVISION*MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall001.jpg",
		&g_pTextureMeshWall);


	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	for (int nWall = 0; nWall < MAX_WALL; nWall++)
	{
		for (int nCnt = 0; nCnt < DIVISION; nCnt++)
		{
			pVtx[nCnt].pos = D3DXVECTOR3((-FIELD_HEIGHT_SIZE + (FIELD_HEIGHT_SIZE*(nCnt % 3))), (FIELD_WIDTH_SIZE - (FIELD_WIDTH_SIZE*(nCnt / 3))), 0.0f);
			//nor�̐ݒ�
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			//���_�J���[
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//�e�N�X�`�����W�̐ݒ�
			pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (0.5f*(nCnt % (FIELD_WIDTH + 1))), 0.0f+(0.5f*(nCnt / (FIELD_HEIGHT + 1))));

		}
		pVtx += DIVISION;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshWall->Unlock();

	pDevice->CreateIndexBuffer(sizeof(WORD) * 14* MAX_WALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	WORD *pIdx;
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);
	for (int nWall = 0; nWall < MAX_WALL; nWall++)
	{
		pIdx[0] = 3;
		pIdx[1] = 0;
		pIdx[2] = 4;
		pIdx[3] = 1;
		pIdx[4] = 5;
		pIdx[5] = 2;
		pIdx[6] = 2;
		pIdx[7] = 6;
		pIdx[8] = 6;
		pIdx[9] = 3;
		pIdx[10] = 7;
		pIdx[11] = 4;
		pIdx[12] = 8;
		pIdx[13] = 5;

		pIdx += 14;
	}

	g_pIdxBuffMeshWall->Unlock();
	//�ǂ�ݒu
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-1700.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI*0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(1700.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI*0.5f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));
}

//=========================================================================================================
//�ǂ̏I������
//=========================================================================================================
void UninitMeshWall(void)
{
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}
}

//=========================================================================================================
//�ǂ̍X�V����
//=========================================================================================================
void UpdateMeshWall(void)
{

}

//=========================================================================================================
//�ǂ̕`�揈��
//=========================================================================================================
void DrawMeshWall(void)
{
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_WallMesh[nCnt].bUse == true)
		{
			//�f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

											//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_MeshWallmtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_WallMesh[nCnt].rot.y, g_WallMesh[nCnt].rot.x, g_WallMesh[nCnt].rot.z);
			D3DXMatrixMultiply(&g_MeshWallmtxWorld, &g_MeshWallmtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_WallMesh[nCnt].pos.x, g_WallMesh[nCnt].pos.y, g_WallMesh[nCnt].pos.z);
			D3DXMatrixMultiply(&g_MeshWallmtxWorld, &g_MeshWallmtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshWallmtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			pDevice->SetFVF(FVF_VERTEX_3D);


			pDevice->SetTexture(0, g_pTextureMeshWall);

			//��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);
		}
	}
}

//=========================================================================================================
//�ǂ̐ݒu����
//=========================================================================================================
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_WallMesh[nCntWall].bUse == false)
		{
			g_WallMesh[nCntWall].pos = pos;
			g_WallMesh[nCntWall].rot = rot;
			g_WallMesh[nCntWall].bUse = true;
			break;
		}
	}
}

//=========================================================================================================
//�ǂ̓����蔻��
//=========================================================================================================
bool ColissionWall(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *pMove)
{
	bool bHit = false;
	D3DXVECTOR3 RPos;
	D3DXVECTOR3 Wallpos[4];
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecTopos;
	RPos = pos;
	Wallpos[0] = D3DXVECTOR3(1700.0f, 0.0f, 0.0f);
	Wallpos[1] = D3DXVECTOR3(-1700.0f, 0.0f, 0.0f);
	Wallpos[2] = D3DXVECTOR3(0.0f, 0.0f, 1700.0f);
	Wallpos[3] = D3DXVECTOR3(0.0f, 0.0f, -1700.0f);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_WallMesh[nCntWall].bUse == true)
		{
			{
				//Wallpos[0] = D3DXVECTOR3(-500.0f, 0.0f, 0.0f) + g_WallMesh[nCntWall].pos;
				//Wallpos[1] = D3DXVECTOR3(500.0f, 0.0f, 0.0f) + g_WallMesh[nCntWall].pos;
				//vecLine = (Wallpos[1] - Wallpos[0]);
				//vecTopos = (pos - Wallpos[0]);

				//if (((vecLine.z*vecTopos.x) - (vecLine.x*vecTopos.z)) < 0.0f)
				//{
				//	bHit = true;
				//}
			}

			//{//��l�̕�
			//	if (Wallpos[0].x <= pos.x)
			//	{//�i+X�����j��
			//		pos.x = Wallpos[0].x - posOld.x;
			//		pMove->x = 0.0f;
			//		bHit = true;
			//	}
			//	else if (Wallpos[1].x >= pos.x)
			//	{//(-X����)��
			//		pos.x = Wallpos[1].x + posOld.x;
			//		pMove->x = 0.0f;
			//		bHit = true;
			//	}
			//	if (Wallpos[2].z <= pos.z)
			//	{//(+Z����)��
			//		pos.z = Wallpos[2].z - posOld.z;
			//		pMove->z = 0.0f;
			//		bHit = true;

			//	}
			//	else if (Wallpos[3].z >= pos.z)
			//	{//(-Z����)��
			//		pos.z = Wallpos[2].z + posOld.z;
			//		pMove->z = 0.0f;
			//		bHit = true;

			//	}
			//}
		}
		pVtx += DIVISION;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshWall->Unlock();

	{//��l�̕�
		if (Wallpos[0].x < pos.x)
		{//�i+X�����j��
			RPos = posOld;
			RPos.x = 1700.0f;
			pMove->x = 0.0f;
			bHit = true;
		}
		else if (Wallpos[1].x > pos.x)
		{//(-X����)��
			RPos = posOld;
			RPos.x = -1700.0f;
			pMove->x = 0.0f;
			bHit = true;
		}
		if (Wallpos[2].z < pos.z)
		{//(+Z����)��
			RPos = posOld;
			RPos.z = 1700.0f;
			pMove->z = 0.0f;
			bHit = true;

		}
		else if (Wallpos[3].z > pos.z)
		{//(-Z����)��
			RPos = posOld;
			RPos.z = -1700.0f;
			pMove->z = 0.0f;
			bHit = true;

		}
	}
	return  bHit;
}