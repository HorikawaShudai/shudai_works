//===========================================================
//
//3Dブロックの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _BLOCK3D_H_
#define _BLOCK3D_H_
#include "main.h"
#include "Object3D.h"

class C3DBlock	:public CObject3D
{
public:
	C3DBlock(int nPriority = 0);
	~C3DBlock();

	typedef enum
	{

		OBJECT_MODEL_NUM1 = 0,
		OBJECT_MODEL_NUM2,
		OBJECT_MODEL_NUM3,
		OBJECT_MODEL_MAX
	}OBJECTNAME;

	typedef enum
	{
		TYPE_SNOWWALL = 0,
		TYPE_3DBLOCK,
		TYPE_EDITBLOCK,
		TYPE_MAXMODEL
	}MODELTYPE;

	typedef struct
	{
		char* pFilename;	// ファイル名
	} OBJECTINFO;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos, float Height, float Width);
	D3DXVECTOR3 GetPos(void);
	static C3DBlock *CreateModel(D3DXVECTOR3 pos, int nData, TYPE type3D);
	LPD3DXMESH m_pMeshModel = NULL;
	void SetObjectSize(void);
	bool Colission(D3DXVECTOR3 pos);
	void InvisibleBlock(void);
	static void DeleateBlock(D3DXVECTOR3 pos);
private:
	int m_NumModel;
	int m_num;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX  m_mtxWorld;
	LPD3DXBUFFER m_pBuffMatModel = NULL;
	DWORD m_dwNumMatModel = 0;
	static OBJECTINFO m_ObjectInfo[OBJECT_MODEL_MAX];
	LPDIRECT3DTEXTURE9 m_apTEXtureModel[50] = {};
	MODELTYPE m_type;
	bool bInv;
	static D3DXVECTOR3 m_VtxMaxBlock;
	static D3DXVECTOR3 m_VtxMinBlock;
};
#endif
