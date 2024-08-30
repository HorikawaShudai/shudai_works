//===========================================================
//
//�V�����_�[�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "MeshCylinder.h"

#define MAX_CYLINDER  (64)			//������
#define CYLINDER_SIZE (3500.0f)		//����
#define CYLINDER_HEIGHT (500.0f)	//����


//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 rot;
//	D3DXMATRIX  mtxWorld;
//	bool bUse;
//}FIELD;

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;		//���_�o�b�t�@�|�C���g
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;
D3DXVECTOR3 g_MeshCylinderpos;
D3DXVECTOR3 g_MeshCylinderrot;
D3DXVECTOR3 g_MeshCylinderLength;
D3DXMATRIX g_MeshCylindermtxWorld;

//=========================================================================================================
//����������
//=========================================================================================================
void InitMeshCylinder(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	g_MeshCylinderpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinderrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((MAX_CYLINDER+1)*2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sky001.jpg",
		&g_pTextureMeshCylinder);


	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�

	for (int nCnt = 0; nCnt <(MAX_CYLINDER + 1) * 2; nCnt++)
	{
		pVtx[nCnt].pos.z = sinf((D3DX_PI*(1.0f - ((1.0f/(MAX_CYLINDER/2))*(nCnt % (MAX_CYLINDER + 1)))) + g_MeshCylinderrot.y))* CYLINDER_SIZE;
		pVtx[nCnt].pos.x = cosf((D3DX_PI*(1.0f - ((1.0f/(MAX_CYLINDER/2))*(nCnt % (MAX_CYLINDER + 1)))) + g_MeshCylinderrot.y))* CYLINDER_SIZE;
		pVtx[nCnt].pos.y = CYLINDER_HEIGHT -(CYLINDER_HEIGHT*(nCnt / (MAX_CYLINDER + 1)));
		//nor�̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//���_�J���[
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex = D3DXVECTOR2((0.0f+(0.125f*(nCnt% (MAX_CYLINDER + 1)))), (0.0f+(1.0f*(nCnt/ (MAX_CYLINDER + 1)))));
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshCylinder->Unlock();

	pDevice->CreateIndexBuffer(sizeof(WORD) * ((MAX_CYLINDER + 1) * 2),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);

	WORD *pIdx;
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCnt = 0,nIdx= 0;nCnt<(MAX_CYLINDER + 1);nCnt++ )
	{
		pIdx[nIdx]   = nCnt+ (MAX_CYLINDER + 1);
		pIdx[nIdx+1] = nCnt;
		nIdx += 2;
	}

	g_pIdxBuffMeshCylinder->Unlock();
	//�n�ʂ�ݒu
	//SetMeshCylinder(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=========================================================================================================
//�n�ʂ̏I������
//=========================================================================================================
void UninitMeshCylinder(void)
{
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}
}

//=========================================================================================================
//�n�ʂ̍X�V����
//=========================================================================================================
void UpdateMeshCylinder(void)
{

}

//=========================================================================================================
//�n�ʂ̕`�揈��
//=========================================================================================================
void DrawMeshCylinder(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshCylindermtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshCylinderrot.y, g_MeshCylinderrot.x, g_MeshCylinderrot.z);
	D3DXMatrixMultiply(&g_MeshCylindermtxWorld, &g_MeshCylindermtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshCylinderpos.x, g_MeshCylinderpos.y, g_MeshCylinderpos.z);
	D3DXMatrixMultiply(&g_MeshCylindermtxWorld, &g_MeshCylindermtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshCylindermtxWorld);

	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	pDevice->SetFVF(FVF_VERTEX_3D);


	//pDevice->SetTexture(0, NULL);
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//�n��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MAX_CYLINDER + 1) * 2, 0, MAX_CYLINDER*2);
}