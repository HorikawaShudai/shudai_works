//===========================================================
//
//playerÇÃèàóùëÄçÏ
//Author:ñxêÏîãëÂ
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

		PLAYER_MODEL_NUM1 = 0,
		PLAYER_MODEL_NUM2,
		PLAYER_MODEL_NUM3,
		PLAYER_MODEL_NUM4,
		PLAYER_MODEL_NUM5,
		PLAYER_MODEL_NUM6,
		PLAYER_MODEL_NUM7,
		PLAYER_MODEL_NUM8,
		PLAYER_MODEL_NUM9,
		PLAYER_MODEL_NUM10,
		PLAYER_MODEL_NUM11,
		PLAYER_MODEL_NUM12,
		PLAYER_MODEL_NUM13,
		PLAYER_MODEL_NUM14,

		ENEMY_MODEL_NUM1,
		ENEMY_MODEL_NUM2,
		ENEMY_MODEL_NUM3,
		ENEMY_MODEL_NUM4,
		ENEMY_MODEL_NUM5,
		ENEMY_MODEL_NUM6,
		ENEMY_MODEL_NUM7,
		ENEMY_MODEL_NUM8,
		ENEMY_MODEL_NUM9,
		ENEMY_MODEL_NUM10,
		ENEMY_MODEL_NUM11,
		ENEMY_MODEL_NUM12,
		ENEMY_MODEL_NUM13,
		ENEMY_MODEL_NUM14,
		ENEMY_MODEL_NUM15,

		BOSS_MODEL_NUM1,
		BOSS_MODEL_NUM2,
		BOSS_MODEL_NUM3,
		BOSS_MODEL_NUM4,
		BOSS_MODEL_NUM5,
		BOSS_MODEL_NUM6,
		BOSS_MODEL_NUM7,
		BOSS_MODEL_NUM8,
		BOSS_MODEL_NUM9,
		BOSS_MODEL_NUM10,
		BOSS_MODEL_NUM11,

		OBJECT_MODEL_NUM1,
	}MODELNAME;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetPos(void);
	static CModel *CreateModel(int ModelNum);
	void SetParent(CModel *pModel);
	D3DMATRIX GetMtxWorld(void);
	LPD3DXMESH m_pMeshModel = NULL;

private:
	typedef struct
	{
		char* pFilename;	// ÉtÉ@ÉCÉãñº
	} MDOELINFO;
	static int m_Num;
	int m_NumModel;
	static MDOELINFO m_Info[OBJECT_MODEL_NUM1];
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX  m_mtxWorld;
	LPD3DXBUFFER m_pBuffMatModel = NULL;
	DWORD m_dwNumMatModel = 0;
	LPDIRECT3DTEXTURE9 m_apTEXtureModel[50] = {};
	CModel *m_pParent;
};
#endif
