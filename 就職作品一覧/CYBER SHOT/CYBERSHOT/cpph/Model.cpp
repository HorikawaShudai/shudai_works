//===========================================================
//
//���f���̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Model.h"
#include "Camera.h"
#include "Shadow.h"
#include "Bullet.h"
#include "MeshWall.h"

#define MODEL_NAME "data\\MODEL\\camera.x"

//�O���[�o���ϐ��錾
LPD3DXMESH g_pMeshModel = NULL;
LPD3DXBUFFER g_pBuffMatModel = NULL;
DWORD g_dwNumMatModel = 0;
MODEL g_Model;
LPDIRECT3DTEXTURE9 g_apTEXtureModel[50] = {};

//=========================================================================================================
//����������
//=========================================================================================================
void InitModel(void)
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_Model.pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Model.Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Model.moveP = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Model.nIdxShadow = 0;

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME,
		D3DXMESH_SYSTEMMEM, 
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL, 
		&g_dwNumMatModel, 
		&g_pMeshModel);

	D3DXMATERIAL *pMat;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTEXtureModel[nCntMat]);
		}
	}



}

//=========================================================================================================
//�|���S���̏I������
//=========================================================================================================
void UninitModel(void)
{
	for (int nCntMat = 0; nCntMat < 50; nCntMat++)
	{
		if (g_apTEXtureModel[nCntMat] != NULL)
		{
			g_apTEXtureModel[nCntMat]->Release();
			g_apTEXtureModel[nCntMat] = NULL;
		}
	}
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//=========================================================================================================
//�|���S���̍X�V����
//=========================================================================================================
void UpdateModel(void)
{
	Camera aCamera = GetCamera();
	g_Model.Oldpos = g_Model.pos;

	if (GetKeyboardPress(DIK_W) == true)
	{//U�̂݉����ꂽ�ꍇ
		if (GetKeyboardPress(DIK_A) == true)
		{//H�̂݉����ꂽ�ꍇ
			g_Model.moveP.x += cosf(D3DX_PI * 0.25f + aCamera.rot.y) * 0.5f;
			g_Model.moveP.z += sinf(D3DX_PI * 0.25f + aCamera.rot.y) * 0.5f;
			g_Model.Destrot.y = -D3DX_PI * 0.25f - aCamera.rot.y;
			if (g_Model.rot.y < -D3DX_PI)
			{
				g_Model.rot.y = D3DX_PI;
			}
			else if (g_Model.rot.y > D3DX_PI)
			{
				g_Model.rot.y = -D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//K�̂݉����ꂽ�ꍇ
			g_Model.moveP.x += cosf(-D3DX_PI * 0.25f + aCamera.rot.y) * 0.5f;
			g_Model.moveP.z += sinf(-D3DX_PI * 0.25f + aCamera.rot.y) * 0.5f;
			g_Model.Destrot.y = D3DX_PI * 0.25f - aCamera.rot.y;
			if (g_Model.rot.y < -D3DX_PI)
			{
				g_Model.rot.y = D3DX_PI;
			}
			else if (g_Model.rot.y > D3DX_PI)
			{
				g_Model.rot.y = -D3DX_PI;
			}
		}
		else
		{
			g_Model.moveP.x += cosf(D3DX_PI * 0.0f + aCamera.rot.y) * 0.5f;
			g_Model.moveP.z += sinf(D3DX_PI * 0.0f + aCamera.rot.y) * 0.5f;
			g_Model.Destrot.y = +D3DX_PI * 0.0f - aCamera.rot.y;
			if (g_Model.rot.y < -D3DX_PI)
			{
				g_Model.rot.y = D3DX_PI;
			}
			else if (g_Model.rot.y > D3DX_PI)
			{
				g_Model.rot.y = -D3DX_PI;
			}
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//J�̂݉����ꂽ�ꍇ
		if (GetKeyboardPress(DIK_A) == true)
		{//H�̂݉����ꂽ�ꍇ
			g_Model.moveP.x += cosf(D3DX_PI * 0.75f + aCamera.rot.y) * 0.5f;
			g_Model.moveP.z += sinf(D3DX_PI * 0.75f + aCamera.rot.y) * 0.5f;
			g_Model.Destrot.y = -D3DX_PI * 0.75f - aCamera.rot.y;
			if (g_Model.rot.y < -D3DX_PI)
			{
				g_Model.rot.y = D3DX_PI;
			}
			else if (g_Model.rot.y > D3DX_PI)
			{
				g_Model.rot.y = -D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//K�̂݉����ꂽ�ꍇ
			g_Model.moveP.x += cosf(-D3DX_PI * 0.75f + aCamera.rot.y) * 0.5f;
			g_Model.moveP.z += sinf(-D3DX_PI * 0.75f + aCamera.rot.y) * 0.5f;
			g_Model.Destrot.y = D3DX_PI * 0.75f - aCamera.rot.y;
			if (g_Model.rot.y < -D3DX_PI)
			{
				g_Model.rot.y = D3DX_PI;
			}
			else if (g_Model.rot.y > D3DX_PI)
			{
				g_Model.rot.y = -D3DX_PI;
			}
		}
		else
		{
			g_Model.moveP.x += cosf(+D3DX_PI * 1.0f + aCamera.rot.y) * 0.5f;
			g_Model.moveP.z += sinf(+D3DX_PI * 1.0f + aCamera.rot.y) * 0.5f;
			g_Model.Destrot.y = -D3DX_PI * 1.0f - aCamera.rot.y;
			if (g_Model.rot.y < -D3DX_PI)
			{
				g_Model.rot.y = D3DX_PI;
			}
			else if (g_Model.rot.y > D3DX_PI)
			{
				g_Model.rot.y = -D3DX_PI;
			}
		}
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{//H�̂݉����ꂽ��
		g_Model.moveP.x += cosf(D3DX_PI *0.5f + aCamera.rot.y) * 0.5f;
		g_Model.moveP.z += sinf(D3DX_PI *0.5f + aCamera.rot.y) * 0.5f;
		g_Model.Destrot.y = -D3DX_PI * 0.5f - aCamera.rot.y;
		if (g_Model.rot.y < -D3DX_PI)
		{
			g_Model.rot.y = D3DX_PI;
		}
		else if (g_Model.rot.y > D3DX_PI)
		{
			g_Model.rot.y = -D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//K�̂݉����ꂽ�ꍇ
		g_Model.moveP.x += cosf(-D3DX_PI *0.5f + aCamera.rot.y) * 0.5f;
		g_Model.moveP.z += sinf(-D3DX_PI *0.5f + aCamera.rot.y) * 0.5f;
		g_Model.Destrot.y = D3DX_PI * 0.5f - aCamera.rot.y;
		if (g_Model.rot.y < -D3DX_PI)
		{
			g_Model.rot.y = D3DX_PI;
		}
		else if (g_Model.rot.y > D3DX_PI)
		{
			g_Model.rot.y = -D3DX_PI;
		}
	}

	//if (GetKeyboardPress(DIK_E) == true)
	//{
	//	g_Model.Destrot.y += 0.05f;
	//}
	//else if (GetKeyboardPress(DIK_Q) == true)
	//{
	//	g_Model.Destrot.y -= 0.05f;
	//}
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		SetBullet(g_Model.pos, D3DXVECTOR3(0.0f, 0.0f, 0.5f), g_Model.rot, BULLETTYPE_PLAYER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//���f���̌���
	{
		g_Model.Diffrot.y = g_Model.Destrot.y - g_Model.rot.y;

		if (g_Model.Diffrot.y > D3DX_PI)
		{
			g_Model.Diffrot.y -= D3DX_PI * 2;
		}
		else if (g_Model.Diffrot.y < -D3DX_PI)
		{
			g_Model.Diffrot.y += D3DX_PI * 2;

		}

		g_Model.rot.y += (g_Model.Diffrot.y)*0.1f;

		if (g_Model.rot.y > D3DX_PI)
		{
			g_Model.rot.y -= D3DX_PI * 2;
		}
		else if (g_Model.rot.y < -D3DX_PI)
		{
			g_Model.rot.y += D3DX_PI * 2;
		}
	}
	g_Model.moveP *= 0.9f;
	g_Model.pos += g_Model.moveP;


	SetPositionShadow(g_Model.nIdxShadow, D3DXVECTOR3(g_Model.pos.x, 0.0f, g_Model.pos.z));
}

//=========================================================================================================
//�|���S���̕`�揈��
//=========================================================================================================
void DrawModel(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Model.mtxWorldModel);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);
	D3DXMatrixMultiply(&g_Model.mtxWorldModel, &g_Model.mtxWorldModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);
	D3DXMatrixMultiply(&g_Model.mtxWorldModel, &g_Model.mtxWorldModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Model.mtxWorldModel);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTEXtureModel[nCntMat]);

		//���f���i�p�[�c�j�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);

}

MODEL GetModel(void)
{
	return g_Model;
}
