//===========================================================
//
//���f���e�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "ModelBullet.h"
#include "Camera.h"
//#include "Shadow.h"
#include "Bullet.h"
#include "MeshWall.h"
#include "Game.h"
#include "Fade.h"
#include "Sound.h"
#include "Player.h"
#include "Object.h"

#define MODBULL_MAX (40)

//�O���[�o���ϐ��錾
MODBULL g_ModBull[MODBULL_MAX];
LPD3DXBUFFER	g_pVtxBuffMatModBull[MODBULL_MAX] = {};

void SetModBullSize(int nNumModBull);
void ColisionOBWALL(int nCnt);
//=========================================================================================================
//����������
//=========================================================================================================
void InitModBull(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nModBull = 0; nModBull < MODBULL_MAX; nModBull++)
	{
		g_ModBull[nModBull].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ModBull[nModBull].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ModBull[nModBull].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ModBull[nModBull].nIdxShadow = -1;
		g_ModBull[nModBull].pTEXtureModBull[250] = {};
		g_ModBull[nModBull].bUse = false;
		g_ModBull[nModBull].dwNumMatModBull = 0;
		g_ModBull[nModBull].pMeshModBull = NULL;
		g_ModBull[nModBull].VtxMinModBull = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ModBull[nModBull].VtxMaxModBull = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_ModBull[nModBull].col[256] = {};
		g_ModBull[nModBull].type = BULLETTYPE_ENEMY;
		//g_ModBull[nModBull].aModBullModel[2] = {};
	}


}

//=========================================================================================================
//�G�̏I������
//=========================================================================================================
void UninitModBull(void)
{
	for (int nModBull = 0; nModBull < MODBULL_MAX; nModBull++)
	{
		if (g_ModBull[nModBull].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < 50; nCntMat++)
			{
				if (g_ModBull[nModBull].pTEXtureModBull[nCntMat] != NULL)
				{
					g_ModBull[nModBull].pTEXtureModBull[nCntMat]->Release();
					g_ModBull[nModBull].pTEXtureModBull[nCntMat] = NULL;
				}

			}
			if (g_ModBull[nModBull].pMeshModBull != NULL)
			{
				g_ModBull[nModBull].pMeshModBull->Release();
				g_ModBull[nModBull].pMeshModBull = NULL;
			}
			if (g_pVtxBuffMatModBull[nModBull] != NULL)
			{
				g_pVtxBuffMatModBull[nModBull]->Release();
				g_pVtxBuffMatModBull[nModBull] = NULL;
			}
			g_ModBull[nModBull].bUse = false;
		}
	}


}

//=========================================================================================================
//�G�̍X�V����
//=========================================================================================================
void UpdateModBull(void)
{
	for (int nModBull = 0; nModBull < MODBULL_MAX; nModBull++)
	{
		if (g_ModBull[nModBull].bUse == true)
		{
			g_ModBull[nModBull].posOld = g_ModBull[nModBull].pos;
			if (g_ModBull[nModBull].rot.y > 0)
			{
				g_ModBull[nModBull].pos.z -= sinf(g_ModBull[nModBull].rot.y)* g_ModBull[nModBull].move.z;
				g_ModBull[nModBull].pos.x += cosf(g_ModBull[nModBull].rot.y)* g_ModBull[nModBull].move.z;
			}
			if (g_ModBull[nModBull].rot.y <= 0)
			{
				g_ModBull[nModBull].pos.z -= sinf(g_ModBull[nModBull].rot.y)* g_ModBull[nModBull].move.z;
				g_ModBull[nModBull].pos.x += cosf(g_ModBull[nModBull].rot.y)* g_ModBull[nModBull].move.z;
			}

			ColisionOBWALL(nModBull);


		}
	}

}

//=========================================================================================================
//�G�̕`�揈��
//=========================================================================================================
void DrawModBull(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nModBull = 0; nModBull < MODBULL_MAX; nModBull++)
	{
		if (g_ModBull[nModBull].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
			D3DMATERIAL9 matDef;
			D3DXMATERIAL *pMat;

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_ModBull[nModBull].mtxWorldModBull);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ModBull[nModBull].rot.y, g_ModBull[nModBull].rot.x, g_ModBull[nModBull].rot.z);
			D3DXMatrixMultiply(&g_ModBull[nModBull].mtxWorldModBull, &g_ModBull[nModBull].mtxWorldModBull, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_ModBull[nModBull].pos.x, g_ModBull[nModBull].pos.y, g_ModBull[nModBull].pos.z);
			D3DXMatrixMultiply(&g_ModBull[nModBull].mtxWorldModBull, &g_ModBull[nModBull].mtxWorldModBull, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_ModBull[nModBull].mtxWorldModBull);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pVtxBuffMatModBull[nModBull]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ModBull[nModBull].dwNumMatModBull; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_ModBull[nModBull].pTEXtureModBull[nCntMat]);

				//���f���i�p�[�c�j�̕`��
				g_ModBull[nModBull].pMeshModBull->DrawSubset(nCntMat);
			}
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=========================================================================================================
//�G�̐ݒu����
//=========================================================================================================
void SetModBull(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, char *pModBullename)
{

	for (int nModBull = 0; nModBull < MODBULL_MAX; nModBull++)
	{
		if (g_ModBull[nModBull].bUse == false)
		{
			//�f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			g_ModBull[nModBull].pos = pos;
			g_ModBull[nModBull].rot = rot;
			g_ModBull[nModBull].move = move;

			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(pModBullename,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pVtxBuffMatModBull[nModBull],
				NULL,
				&g_ModBull[nModBull].dwNumMatModBull,
				&g_ModBull[nModBull].pMeshModBull);

			D3DXMATERIAL *pMat;

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pVtxBuffMatModBull[nModBull]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_ModBull[nModBull].dwNumMatModBull; nCntMat++)
			{
				g_ModBull[nModBull].col[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_ModBull[nModBull].pTEXtureModBull[nCntMat]);
				}
			}
			//g_ModBull[nModBull].nIdxShadow = SetShadow(20.0f,g_ModBull[nModBull].pos);

			SetModBullSize(nModBull);

			g_ModBull[nModBull].bUse = true;
			break;
		}
	}
}

//=========================================================================================================
//�T�C�Y�̌v�Z����
//=========================================================================================================
void SetModBullSize(int nNumModBull)
{
	int nNumVtx;

	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	//���_���̎擾
	nNumVtx = g_ModBull[nNumModBull].pMeshModBull->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(g_ModBull[nNumModBull].pMeshModBull->GetFVF());

	//���_�o�b�t�@�����b�N
	g_ModBull[nNumModBull].pMeshModBull->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (vtx.x > g_ModBull[nNumModBull].VtxMaxModBull.x)
		{
			g_ModBull[nNumModBull].VtxMaxModBull.x = vtx.x;
		}
		if (vtx.x < g_ModBull[nNumModBull].VtxMinModBull.x)
		{
			g_ModBull[nNumModBull].VtxMinModBull.x = vtx.x;
		}
		if (vtx.z > g_ModBull[nNumModBull].VtxMaxModBull.z)
		{
			g_ModBull[nNumModBull].VtxMaxModBull.z = vtx.z;
		}
		if (vtx.z < g_ModBull[nNumModBull].VtxMinModBull.z)
		{
			g_ModBull[nNumModBull].VtxMinModBull.z = vtx.z;
		}
		pVtxBuff += dwSizeFVF;
	}
}

//=========================================================================================================
//�v���C���[�Ƃ̓����蔻��
//=========================================================================================================
bool ColissionModBull(D3DXVECTOR3 pos, D3DXVECTOR3 posOld)
{
	bool bHit = false;

	for (int nModBull = 0; nModBull < MODBULL_MAX; nModBull++)
	{
		if (g_ModBull[nModBull].bUse == true)
		{
		
			if (pos.x >= (g_ModBull[nModBull].pos.x + g_ModBull[nModBull].VtxMinModBull.x) && pos.z <= (g_ModBull[nModBull].pos.z + g_ModBull[nModBull].VtxMaxModBull.z) &&
				pos.x <= (g_ModBull[nModBull].pos.x + g_ModBull[nModBull].VtxMaxModBull.x) && pos.z >= (g_ModBull[nModBull].pos.z + g_ModBull[nModBull].VtxMinModBull.z))
			{
				g_ModBull[nModBull].bUse = false;
				bHit = true;
			}
		}
	}
	return bHit;
}



//=========================================================================================================
//���f���o���b�g�ƃI�u�W�F�N�g�܂��͕ǂ̔���
//=========================================================================================================
void ColisionOBWALL(int nCnt)
{

	//�I�u�W�F�N�g�Ƃ̓����蔻��
	{
		if (ColissionBullet(D3DXVECTOR3((g_ModBull[nCnt].pos.x + (cosf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMaxModBull.x)), g_ModBull[nCnt].pos.y, (g_ModBull[nCnt].pos.z + (sinf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMaxModBull.z))),g_ModBull[nCnt].posOld, g_ModBull[nCnt].move, g_ModBull[nCnt].type)==true)
		{																																																																					  
			//FinishShadow(g_ModBull[nCnt].nIdxShadow);		
			//g_ModBull[nCnt].nIdxShadow = -1;
			g_ModBull[nCnt].bUse = false;																																																													  
		}																																																																					  
		if (ColissionBullet(D3DXVECTOR3((g_ModBull[nCnt].pos.x + (cosf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMinModBull.x)), g_ModBull[nCnt].pos.y, (g_ModBull[nCnt].pos.z + (sinf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMaxModBull.z))),g_ModBull[nCnt].posOld, g_ModBull[nCnt].move, g_ModBull[nCnt].type)==true)
		{																																																																					  
			//FinishShadow(g_ModBull[nCnt].nIdxShadow);																																																										  
			//g_ModBull[nCnt].nIdxShadow = -1;
			g_ModBull[nCnt].bUse = false;
		}																																																																					  
		if (ColissionBullet(D3DXVECTOR3((g_ModBull[nCnt].pos.x + (cosf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMaxModBull.x)), g_ModBull[nCnt].pos.y, (g_ModBull[nCnt].pos.z + (sinf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMinModBull.z))),g_ModBull[nCnt].posOld, g_ModBull[nCnt].move, g_ModBull[nCnt].type)==true)
		{																																																																					  
			//FinishShadow(g_ModBull[nCnt].nIdxShadow);																																																										  
			//g_ModBull[nCnt].nIdxShadow = -1;
			g_ModBull[nCnt].bUse = false;
		}																																																																					  
		if (ColissionBullet(D3DXVECTOR3((g_ModBull[nCnt].pos.x + (cosf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMinModBull.x)), g_ModBull[nCnt].pos.y, (g_ModBull[nCnt].pos.z + (sinf(g_ModBull[nCnt].rot.y)*g_ModBull[nCnt].VtxMinModBull.z))),g_ModBull[nCnt].posOld, g_ModBull[nCnt].move, g_ModBull[nCnt].type)==true)
		{
			//FinishShadow(g_ModBull[nCnt].nIdxShadow);
			//g_ModBull[nCnt].nIdxShadow = -1;
			g_ModBull[nCnt].bUse = false;
		}
	}

	{
		if (g_ModBull[nCnt].pos.x  > 1700.0f)
		{
			//FinishShadow(g_ModBull[nCnt].nIdxShadow);
			//g_ModBull[nCnt].nIdxShadow = -1;
			g_ModBull[nCnt].bUse = false;
		}
		if (g_ModBull[nCnt].pos.x  < -1700.0f)
		{
/*			FinishShadow(g_ModBull[nCnt].nIdxShadow);
			g_ModBull[nCnt].nIdxShadow = -1*/;
			g_ModBull[nCnt].bUse = false;
		}
		if (g_ModBull[nCnt].pos.z  > 1700.0f)
		{
			//FinishShadow(g_ModBull[nCnt].nIdxShadow);
			//g_ModBull[nCnt].nIdxShadow = -1;
			g_ModBull[nCnt].bUse = false;
		}
		if (g_ModBull[nCnt].pos.z  < -1700.0f)
		{
		/*	FinishShadow(g_ModBull[nCnt].nIdxShadow);
			g_ModBull[nCnt].nIdxShadow = -1;*/
			g_ModBull[nCnt].bUse = false;
		}
	}
}
