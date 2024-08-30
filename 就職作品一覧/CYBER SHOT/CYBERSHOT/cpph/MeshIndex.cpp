//===========================================================
//
//�n�ʂ̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "MeshIndex.h"

#define MAX_FIELD  (50)
#define FIELF_SIZE (1700.0f)


//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 rot;
//	D3DXMATRIX  mtxWorld;
//	bool bUse;
//}FIELD;

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshIndex = NULL;		//���_�o�b�t�@�|�C���g
LPDIRECT3DTEXTURE9 g_pTextureMeshIndex = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;
D3DXVECTOR3 g_MeshIndexpos;
D3DXVECTOR3 g_MeshIndexrot;
D3DXMATRIX g_MeshIndexmtxWorld;

//=========================================================================================================
//����������
//=========================================================================================================
void InitMeshIndex(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	g_MeshIndexpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshIndexrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshIndex,
		NULL);



	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tuti001.jpg",
		&g_pTextureMeshIndex);


	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffMeshIndex->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�
	for (int nCnt = 0; nCnt < 9; nCnt++)
	{
		pVtx[nCnt].pos = D3DXVECTOR3((-FIELF_SIZE+(FIELF_SIZE*(nCnt%3))), 0.0f, (FIELF_SIZE-(FIELF_SIZE*(nCnt/3))));
		//nor�̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//���_�J���[
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}


	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshIndex->Unlock();

	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	WORD *pIdx;
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx,0);
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
		pIdx[10]= 7;
		pIdx[11]= 4;
		pIdx[12]= 8;
		pIdx[13]= 5;


	g_pIdxBuffMeshField->Unlock();
	//�n�ʂ�ݒu
	//SetMeshIndex(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=========================================================================================================
//�n�ʂ̏I������
//=========================================================================================================
void UninitMeshIndex(void)
{
	if (g_pTextureMeshIndex != NULL)
	{
		g_pTextureMeshIndex->Release();
		g_pTextureMeshIndex = NULL;
	}
	if (g_pVtxBuffMeshIndex != NULL)
	{
		g_pVtxBuffMeshIndex->Release();
		g_pVtxBuffMeshIndex = NULL;
	}
}

//=========================================================================================================
//�n�ʂ̍X�V����
//=========================================================================================================
void UpdateMeshIndex(void)
{

}

//=========================================================================================================
//�n�ʂ̕`�揈��
//=========================================================================================================
void DrawMeshIndex(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshIndexmtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshIndexrot.y, g_MeshIndexrot.x, g_MeshIndexrot.z);
	D3DXMatrixMultiply(&g_MeshIndexmtxWorld, &g_MeshIndexmtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshIndexpos.x, g_MeshIndexpos.y, g_MeshIndexpos.z);
	D3DXMatrixMultiply(&g_MeshIndexmtxWorld, &g_MeshIndexmtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshIndexmtxWorld);

	pDevice->SetStreamSource(0, g_pVtxBuffMeshIndex, 0, sizeof(VERTEX_3D));

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	pDevice->SetFVF(FVF_VERTEX_3D);


	pDevice->SetTexture(0, g_pTextureMeshIndex);

	//�n��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);
}