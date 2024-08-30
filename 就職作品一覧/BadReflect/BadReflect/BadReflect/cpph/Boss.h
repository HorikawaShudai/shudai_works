//===========================================================
//
//ÉâÉXÉ{ÉXÇÃèàóùëÄçÏ
//Author:ñxêÏîãëÂ
//
//===========================================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "main.h"
#include "Object.h"
#include "Model.h"
#include "Object3D.h"
#define  GRAVITY (0.27665f)

class CBoss3D :public CObject3D
{
public:
	typedef enum
	{
		STATE_WATE = 0,
		STATE_RUN,
		STATE_JUMP,
		STATE_STAMP,
		STATE_MAX
	}BOSSSTATE;

	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}KEYMOTION;
	typedef struct
	{
		int bLoop;
		int bNumKey;
		int Frame;
		KEYMOTION mParts[11];
	}BOSSMOTION;
	BOSSMOTION Bossmotion[STATE_MAX][20];
	CBoss3D(int nPriority = 5);
	~CBoss3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetPos(D3DXVECTOR3 pos, float Height, float Width);
	static D3DXVECTOR3 GetPos(void);
	static D3DXVECTOR3 GetPosOld(void);
	static D3DXVECTOR3 GetMove(void) { return m_move; };
	static void SetBossState(BOSSSTATE state);
	static BOSSSTATE GetState() { return m_State; };
	void BossContoroll(void);
	static CBoss3D *Create(D3DXVECTOR3 pos);
	//void LoadMotion(void);
	static void SetMove(D3DXVECTOR3 move, char *CMove);
	void SetObjectSize(void);
	static bool ColissionModBull(D3DXVECTOR3 pos);
	static void SetModelParts(D3DXVECTOR3 rot, int PartsNum);
	void StateContoroll(void);
private:
	static D3DXVECTOR3 m_pos;
	static D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_Diffpos;
	D3DXVECTOR3 m_Destpos;

	static D3DXVECTOR3 m_rot;
	static D3DXVECTOR3 m_move;
	bool bSlow;
	static BOSSSTATE m_State;
	LPD3DXMESH m_pMeshModel = NULL;
	LPD3DXBUFFER m_pBuffMatModel = NULL;
	DWORD m_dwNumMatModel = 0;
	static CModel *m_apModel[11];
	D3DXMATRIX  m_mtxWorld;
	LPDIRECT3DTEXTURE9 m_apTEXtureModel[50] = {};
	int  m_nNumModel;
	static D3DXVECTOR3 m_VtxMaxObject;
	static D3DXVECTOR3 m_VtxMinObject;
};
#endif
