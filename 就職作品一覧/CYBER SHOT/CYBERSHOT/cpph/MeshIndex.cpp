//===========================================================
//
//地面の処理操作
//Author:堀川萩大
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

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshIndex = NULL;		//頂点バッファポイント
LPDIRECT3DTEXTURE9 g_pTextureMeshIndex = NULL;			//テクスチャポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;
D3DXVECTOR3 g_MeshIndexpos;
D3DXVECTOR3 g_MeshIndexrot;
D3DXMATRIX g_MeshIndexmtxWorld;

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitMeshIndex(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	g_MeshIndexpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshIndexrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshIndex,
		NULL);



	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tuti001.jpg",
		&g_pTextureMeshIndex);


	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffMeshIndex->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	for (int nCnt = 0; nCnt < 9; nCnt++)
	{
		pVtx[nCnt].pos = D3DXVECTOR3((-FIELF_SIZE+(FIELF_SIZE*(nCnt%3))), 0.0f, (FIELF_SIZE-(FIELF_SIZE*(nCnt/3))));
		//norの設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//頂点カラー
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}


	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
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
	//地面を設置
	//SetMeshIndex(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=========================================================================================================
//地面の終了処理
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
//地面の更新処理
//=========================================================================================================
void UpdateMeshIndex(void)
{

}

//=========================================================================================================
//地面の描画処理
//=========================================================================================================
void DrawMeshIndex(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_MeshIndexmtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshIndexrot.y, g_MeshIndexrot.x, g_MeshIndexrot.z);
	D3DXMatrixMultiply(&g_MeshIndexmtxWorld, &g_MeshIndexmtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_MeshIndexpos.x, g_MeshIndexpos.y, g_MeshIndexpos.z);
	D3DXMatrixMultiply(&g_MeshIndexmtxWorld, &g_MeshIndexmtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshIndexmtxWorld);

	pDevice->SetStreamSource(0, g_pVtxBuffMeshIndex, 0, sizeof(VERTEX_3D));

	//頂点バッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	pDevice->SetFVF(FVF_VERTEX_3D);


	pDevice->SetTexture(0, g_pTextureMeshIndex);

	//地面
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);
}