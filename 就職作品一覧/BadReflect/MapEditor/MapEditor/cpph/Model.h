//===========================================================
//
//モデルの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "Object.h"

class CModel
{
public:
	CModel();
	~CModel();

	typedef enum
	{
		MODEL_NUM1 = 0,
		MODEL_NUM2,
		MODEL_NUM3,
		MODEL_NUM4,
		MODEL_NUM5,
		MODEL_NUM6,
		MODEL_NUM7,
		MODEL_NUM8,
		MODEL_NUM9,
		MODEL_NUM10,
		MODEL_NUM11,
		MODEL_NUM12,
		MODEL_NUM13,
		MODEL_NUM14,
		MODEL_NUM15,
		MODEL_MAX
	}MODELNUM;

	typedef enum
	{
		TYPE_PLAYERMODEL = 0,
		TYPE_ENEMYMODEL,
		TYPE_MAXMODEL
	}MODELTYPE;
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos, float Height, float Width);
	D3DXVECTOR3 GetPos(void);
	static CModel *CreateModel(int ModelNum, D3DXVECTOR3 pos, MODELTYPE type);
	void SetParent(CModel *pModel);
	D3DMATRIX GetMtxWorld(void);
	LPD3DXMESH m_pMeshModel = NULL;

private:

	typedef struct
	{
		char *pFilename;	// ファイル名
	} ENEMYINFO;
	typedef struct
	{
		char *pFilename;	// ファイル名
	} PLAYERINFO;

	static int m_Num;
	int m_NumModel;
	static PLAYERINFO m_aModelInfo[MODEL_MAX];
	static ENEMYINFO m_aEnemyInfo[MODEL_MAX];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX  m_mtxWorld;
	LPD3DXBUFFER m_pBuffMatModel = NULL;
	DWORD m_dwNumMatModel = 0;
	LPDIRECT3DTEXTURE9 m_apTEXtureModel[50] = {};
	CModel *m_pParent;
	MODELTYPE m_type;
};
#endif
