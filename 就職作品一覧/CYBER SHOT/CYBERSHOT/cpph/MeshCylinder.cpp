//===========================================================
//
//シリンダーの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "MeshCylinder.h"

#define MAX_CYLINDER  (64)			//分割数
#define CYLINDER_SIZE (3500.0f)		//距離
#define CYLINDER_HEIGHT (500.0f)	//高さ


//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 rot;
//	D3DXMATRIX  mtxWorld;
//	bool bUse;
//}FIELD;

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;		//頂点バッファポイント
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;			//テクスチャポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;
D3DXVECTOR3 g_MeshCylinderpos;
D3DXVECTOR3 g_MeshCylinderrot;
D3DXVECTOR3 g_MeshCylinderLength;
D3DXMATRIX g_MeshCylindermtxWorld;

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitMeshCylinder(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	g_MeshCylinderpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinderrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((MAX_CYLINDER+1)*2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\sky001.jpg",
		&g_pTextureMeshCylinder);


	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定

	for (int nCnt = 0; nCnt <(MAX_CYLINDER + 1) * 2; nCnt++)
	{
		pVtx[nCnt].pos.z = sinf((D3DX_PI*(1.0f - ((1.0f/(MAX_CYLINDER/2))*(nCnt % (MAX_CYLINDER + 1)))) + g_MeshCylinderrot.y))* CYLINDER_SIZE;
		pVtx[nCnt].pos.x = cosf((D3DX_PI*(1.0f - ((1.0f/(MAX_CYLINDER/2))*(nCnt % (MAX_CYLINDER + 1)))) + g_MeshCylinderrot.y))* CYLINDER_SIZE;
		pVtx[nCnt].pos.y = CYLINDER_HEIGHT -(CYLINDER_HEIGHT*(nCnt / (MAX_CYLINDER + 1)));
		//norの設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//頂点カラー
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[nCnt].tex = D3DXVECTOR2((0.0f+(0.125f*(nCnt% (MAX_CYLINDER + 1)))), (0.0f+(1.0f*(nCnt/ (MAX_CYLINDER + 1)))));
	}
	//頂点バッファをアンロックする
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
	//地面を設置
	//SetMeshCylinder(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=========================================================================================================
//地面の終了処理
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
//地面の更新処理
//=========================================================================================================
void UpdateMeshCylinder(void)
{

}

//=========================================================================================================
//地面の描画処理
//=========================================================================================================
void DrawMeshCylinder(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_MeshCylindermtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshCylinderrot.y, g_MeshCylinderrot.x, g_MeshCylinderrot.z);
	D3DXMatrixMultiply(&g_MeshCylindermtxWorld, &g_MeshCylindermtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_MeshCylinderpos.x, g_MeshCylinderpos.y, g_MeshCylinderpos.z);
	D3DXMatrixMultiply(&g_MeshCylindermtxWorld, &g_MeshCylindermtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshCylindermtxWorld);

	pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//頂点バッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	pDevice->SetFVF(FVF_VERTEX_3D);


	//pDevice->SetTexture(0, NULL);
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//地面
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MAX_CYLINDER + 1) * 2, 0, MAX_CYLINDER*2);
}