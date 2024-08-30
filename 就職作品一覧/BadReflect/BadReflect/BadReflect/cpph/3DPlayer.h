//===========================================================
//
//playerÇÃèàóùëÄçÏ
//Author:ñxêÏîãëÂ
//
//===========================================================
#ifndef _3D_PLAYER_H_
#define _3D_PLAYER_H_
#include "main.h"
#include "Object.h"
#include "Model.h"
#include "Object3D.h"
#include <iostream>
#include "motion.h"
#include "LifeGuage.h"

#define  GRAVITY (0.27665f)
#define WALLENAGY (6.0f)
#define NUM_PARTS (14)
#define ATTACK_RANGE (25.0f)

class CPlayer3D:public CObject3D
{
public:
	typedef enum
	{
		STATE_WATE = 0,
		STATE_RUN,
		STATE_ATTACK,
		STATE_STAMP,
		STATE_MAX
	}PLAYERSTATE;

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
		KEYMOTION mParts[NUM_PARTS];
	}PLAYERMOTION;
	PLAYERMOTION Playermotion[STATE_MAX][20];
	CPlayer3D(int nPriority =2);
	~CPlayer3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetPos(D3DXVECTOR3 pos, float Height, float Width);
	static D3DXVECTOR3 GetPos(void);
	static D3DXVECTOR3 GetRot(void);
	static D3DXVECTOR3 GetPosOld(void);
	static D3DXVECTOR3 GetMove(void) { return m_move; };
	static void SetPlayerState(PLAYERSTATE state);
	static PLAYERSTATE GetState() {return m_State; };
	void PlayerContoroll(void);
	static CPlayer3D *Create(void);
	static void SetMove(D3DXVECTOR3 move,char *CMove);
	void SetObjectSize(void);
	static bool ColissionModBull(D3DXVECTOR3 pos);
	static void SetModelParts(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int PartsNum);
	CModel** GetModel(void) { return m_apModel; };
	void StateContoroll(void);
	static int GetLife() { return m_Life; };
	static void AddLife(int Damage) { m_Life += Damage; };

	float Normalize(float rot);
	static bool isWithinAttackRange(float enemyX, float enemyZ);
private:
	static D3DXVECTOR3 m_pos;
	static D3DXVECTOR3 m_posOld;
	static D3DXVECTOR3 m_rot;
	static D3DXVECTOR3 m_Moverot;
	static D3DXVECTOR3 m_move;

	static PLAYERSTATE m_State;
	static CLifeGuage* m_pGuage;
	bool m_bMove;
	LPD3DXMESH m_pMeshModel = NULL;
	LPD3DXBUFFER m_pBuffMatModel = NULL;
	DWORD m_dwNumMatModel = 0;
	static CModel *m_apModel[NUM_PARTS];
	D3DXMATRIX  m_mtxWorld;
	LPDIRECT3DTEXTURE9 m_apTEXtureModel[50] = {};
	int  m_nNumModel;
	static int m_Life;
	float m_Charge;
	static D3DXVECTOR3 m_VtxMaxObject;
	static D3DXVECTOR3 m_VtxMinObject;
	CMotion* m_pMotion;
};
#endif
