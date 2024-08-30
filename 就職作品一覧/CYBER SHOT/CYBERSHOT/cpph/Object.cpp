//===========================================================
//
//�I�u�W�F�N�g�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Object.h"
#include "Camera.h"
#include "Bullet.h"
#include "MeshWall.h"
#include "Item.h"

#define OBJECT_MAX (20)

//�O���[�o���ϐ��錾
OBJECT g_Object[OBJECT_MAX];
LPD3DXBUFFER	g_pVtxBuffMatObject[OBJECT_MAX] = {};

void SetObjectSize(int nNumObject);

//=========================================================================================================
//����������
//=========================================================================================================
void InitObject(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nObject = 0; nObject < OBJECT_MAX; nObject++)
	{
		g_Object[nObject].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nObject].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Object[nObject].pTEXtureObject[50] = {};
		g_Object[nObject].bUse = false;
		g_Object[nObject].dwNumMatObject = 0;
		g_Object[nObject].pMeshObject = NULL;
		g_Object[nObject].VtxMinObject =  D3DXVECTOR3 (0.0f, 0.0f, 0.0f);
		g_Object[nObject].VtxMaxObject =  D3DXVECTOR3 (0.0f, 0.0f, 0.0f);
	}
}

//=========================================================================================================
//�I�u�W�F�N�g�̏I������
//=========================================================================================================
void UninitObject(void)
{
	for (int nObject = 0; nObject < OBJECT_MAX; nObject++)
	{
		if (g_Object[nObject].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < 50; nCntMat++)
			{
				if (g_Object[nObject].pTEXtureObject[nCntMat] != NULL)
				{
					g_Object[nObject].pTEXtureObject[nCntMat]->Release();
					g_Object[nObject].pTEXtureObject[nCntMat] = NULL;
				}

			}
			if (g_Object[nObject].pMeshObject != NULL)
			{
				g_Object[nObject].pMeshObject->Release();
				g_Object[nObject].pMeshObject = NULL;
			}
			if (g_pVtxBuffMatObject[nObject] != NULL)
			{
				g_pVtxBuffMatObject[nObject]->Release();
				g_pVtxBuffMatObject[nObject] = NULL;
			}
			g_Object[nObject].bUse = false;
		}
	}


}

//=========================================================================================================
//�I�u�W�F�N�g�̍X�V����
//=========================================================================================================
void UpdateObject(void)
{

}

//=========================================================================================================
//�I�u�W�F�N�g�̕`�揈��
//=========================================================================================================
void DrawObject(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nObject = 0; nObject < OBJECT_MAX; nObject++)
	{
		if (g_Object[nObject].bUse == true)
		{
			D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
			D3DMATERIAL9 matDef;
			D3DXMATERIAL *pMat;

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Object[nObject].mtxWorldObject);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object[nObject].rot.y, g_Object[nObject].rot.x, g_Object[nObject].rot.z);
			D3DXMatrixMultiply(&g_Object[nObject].mtxWorldObject, &g_Object[nObject].mtxWorldObject, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Object[nObject].pos.x, g_Object[nObject].pos.y, g_Object[nObject].pos.z);
			D3DXMatrixMultiply(&g_Object[nObject].mtxWorldObject, &g_Object[nObject].mtxWorldObject, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Object[nObject].mtxWorldObject);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);
			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pVtxBuffMatObject[nObject]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Object[nObject].dwNumMatObject; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_Object[nObject].pTEXtureObject[nCntMat]);

				//���f���i�p�[�c�j�̕`��
				  g_Object[nObject].pMeshObject->DrawSubset(nCntMat);
			}
			pDevice->SetMaterial(&matDef);
		}
	}
}

//=========================================================================================================
//�I�u�W�F�N�g�̐ݒu����
//=========================================================================================================
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pObjectename)
{

	for (int nObject = 0; nObject < OBJECT_MAX; nObject++)
	{
		if (g_Object[nObject].bUse == false)
		{
			//�f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			g_Object[nObject].pos = pos;
			g_Object[nObject].rot = rot;
			if (pObjectename == "data\\MODEL\\WoodBox.x")
			{
				g_Object[nObject].ObjectCode = OBJECT_KIND_001;
			}
			else 
			{
				g_Object[nObject].ObjectCode = OBJECT_KIND_000;
			}

			//X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(pObjectename,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pVtxBuffMatObject[nObject],
				NULL,
				&g_Object[nObject].dwNumMatObject,
				&  g_Object[nObject].pMeshObject);

			D3DXMATERIAL *pMat;

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pVtxBuffMatObject[nObject]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat <(int)g_Object[nObject].dwNumMatObject; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_Object[nObject].pTEXtureObject[nCntMat]);
				}
			}

			SetObjectSize(nObject);

			g_Object[nObject].bUse = true;
			break;
		}
	}
}

//=========================================================================================================
//�T�C�Y�̌v�Z����
//=========================================================================================================
void SetObjectSize(int nNumObject)
{
	int nNumVtx;

	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	//���_���̎擾
	nNumVtx = g_Object[nNumObject].pMeshObject->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(g_Object[nNumObject].pMeshObject->GetFVF());

	//���_�o�b�t�@�����b�N
	g_Object[nNumObject].pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (vtx.x > g_Object[nNumObject].VtxMaxObject.x)
		{
			g_Object[nNumObject].VtxMaxObject.x = vtx.x;
		}
		if (vtx.x < g_Object[nNumObject].VtxMinObject.x )
		{
			g_Object[nNumObject].VtxMinObject.x = vtx.x;
		}
		if (vtx.z > g_Object[nNumObject].VtxMaxObject.z )
		{
			g_Object[nNumObject].VtxMaxObject.z = vtx.z;
		}
		if (vtx.z < g_Object[nNumObject].VtxMinObject.z )
		{
			g_Object[nNumObject].VtxMinObject.z = vtx.z;
		}
		if (vtx.y> g_Object[nNumObject].VtxMaxObject.y)
		{
			g_Object[nNumObject].VtxMaxObject.y = vtx.y;
		}
		if (vtx.y < g_Object[nNumObject].VtxMinObject.y)
		{
			g_Object[nNumObject].VtxMinObject.y = vtx.y;
		}
		pVtxBuff += dwSizeFVF;
	}
}

//=========================================================================================================
//�I�u�W�F�N�g�̓����蔻��
//=========================================================================================================
D3DXVECTOR3 ColissionObject(D3DXVECTOR3 possize, D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *pMove)
{
	bool bHit = false;
	D3DXVECTOR3 RPos;
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecTopos;
	D3DXVECTOR3 vecmove;
	RPos = pos;
	vecmove = pos - posOld;

	for (int nObject = 0; nObject < OBJECT_MAX; nObject++)
	{
		if (g_Object[nObject].bUse == true)
		{
			{//��_����
				//vecLine.x = g_Object[nObject].VtxMaxObject.x - g_Object[nObject].VtxMinObject.x;
				//vecLine.z = g_Object[nObject].VtxMaxObject.z - g_Object[nObject].VtxMaxObject.z;
				//vecTopos = pos - D3DXVECTOR3(g_Object[nObject].VtxMinObject.x, 0.0f, g_Object[nObject].VtxMaxObject.z);


				//Objectpos[0] = (vecTopos.z*vecmove.x) - (vecTopos.x*vecmove.z);
				//Objectpos[1] = (vecLine.z*vecmove.x) - (vecLine.x*vecmove.z);
				//Objectpos[2] = Objectpos[0] / Objectpos[1];
				//if (Objectpos[2] >= 0.0f&&Objectpos[2] <= 1.0f)
				//{
				//	RPos = D3DXVECTOR3(0.0f, 300.0f, 500.0f);
				//}
			}

			//if (pos.x > (g_Object[nObject].pos.x+g_Object[nObject].VtxMinObject.x) && pos.z < (g_Object[nObject].pos.z + g_Object[nObject].VtxMaxObject.z) &&
			//	pos.x < (g_Object[nObject].pos.x+g_Object[nObject].VtxMaxObject.x) && pos.z >(g_Object[nObject].pos.z + g_Object[nObject].VtxMinObject.z))
			//{
			//		RPos = posOld;
			//	
			//}
			if (possize.x >=(g_Object[nObject].pos.x + g_Object[nObject].VtxMinObject.x) && possize.z <= (g_Object[nObject].pos.z + g_Object[nObject].VtxMaxObject.z) &&
				possize.x <= (g_Object[nObject].pos.x + g_Object[nObject].VtxMaxObject.x) && possize.z >=(g_Object[nObject].pos.z + g_Object[nObject].VtxMinObject.z) &&
				possize.y >=(g_Object[nObject].pos.y + g_Object[nObject].VtxMinObject.y)&& possize.y <=(g_Object[nObject].pos.y + g_Object[nObject].VtxMaxObject.y))
			{
				if (posOld.x >(g_Object[nObject].pos.x + g_Object[nObject].VtxMaxObject.x) )
				{
					RPos.x = posOld.x ;
					pMove->x = 0.0f;
				}
				else if (posOld.x <(g_Object[nObject].pos.x + g_Object[nObject].VtxMinObject.x))
				{
					RPos.x = posOld.x;
					pMove->x = 0.0f;


				}
				else if (posOld.z <(g_Object[nObject].pos.z + g_Object[nObject].VtxMinObject.z))
				{
					RPos.z = posOld.z;

					pMove->z = 0.0f;
				}
				else if (posOld.z >(g_Object[nObject].pos.z + g_Object[nObject].VtxMaxObject.z))
				{
					RPos.z = posOld.z;

					pMove->z = 0.0f;
				}
				if (posOld.y <(g_Object[nObject].pos.y + g_Object[nObject].VtxMinObject.y))
				{
					RPos.y = posOld.y;

					pMove->y = 0.0f;
				}
				else if (posOld.y >= (g_Object[nObject].pos.y + g_Object[nObject].VtxMaxObject.y))
				{
					RPos.y = posOld.y;

					pMove->y = 0.0f;
				}

			}
		}
	}
	return RPos;
}

//=========================================================================================================
//�e�Ƃ̓����蔻��
//=========================================================================================================
bool ColissionBullet(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 pMove,BULLETTYPE nType)
{
	bool bHit = false;
	D3DXVECTOR3 RPos;

	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecTopos;
	D3DXVECTOR3 vecmove;
	RPos = pos;
	vecmove = pos - posOld;

	for (int nObject = 0; nObject < OBJECT_MAX; nObject++)
	{
		if (g_Object[nObject].bUse == true)
		{
			{//��_����
			 //vecLine.x = g_Object[nObject].VtxMaxObject.x - g_Object[nObject].VtxMinObject.x;
			 //vecLine.z = g_Object[nObject].VtxMaxObject.z - g_Object[nObject].VtxMaxObject.z;
			 //vecTopos = pos - D3DXVECTOR3(g_Object[nObject].VtxMinObject.x, 0.0f, g_Object[nObject].VtxMaxObject.z);


			 //Objectpos[0] = (vecTopos.z*vecmove.x) - (vecTopos.x*vecmove.z);
			 //Objectpos[1] = (vecLine.z*vecmove.x) - (vecLine.x*vecmove.z);
			 //Objectpos[2] = Objectpos[0] / Objectpos[1];
			 //if (Objectpos[2] >= 0.0f&&Objectpos[2] <= 1.0f)
			 //{
			 //	RPos = D3DXVECTOR3(0.0f, 300.0f, 500.0f);
			 //}
			}

			//if (pos.x > (g_Object[nObject].pos.x+g_Object[nObject].VtxMinObject.x) && pos.z < (g_Object[nObject].pos.z + g_Object[nObject].VtxMaxObject.z) &&
			//	pos.x < (g_Object[nObject].pos.x+g_Object[nObject].VtxMaxObject.x) && pos.z >(g_Object[nObject].pos.z + g_Object[nObject].VtxMinObject.z))
			//{
			//		RPos = posOld;
			//	
			//}
			if (pos.x >=(g_Object[nObject].pos.x + g_Object[nObject].VtxMinObject.x) && pos.z <= (g_Object[nObject].pos.z + g_Object[nObject].VtxMaxObject.z) &&
				pos.x <= (g_Object[nObject].pos.x + g_Object[nObject].VtxMaxObject.x) && pos.z >=(g_Object[nObject].pos.z + g_Object[nObject].VtxMinObject.z))
			{
				if (nType == BULLETTYPE_PLAYER)
				{
					if (g_Object[nObject].ObjectCode == OBJECT_KIND_001)
					{

						g_Object[nObject].bUse = false;
						SetItem(g_Object[nObject].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\Heart.x");
					}
				}
				bHit = true;
			}
		}
	}
	return bHit;
}
