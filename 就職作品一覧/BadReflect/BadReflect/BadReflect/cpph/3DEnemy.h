//===========================================================
//
//playerÇÃèàóùëÄçÏ
//Author:ñxêÏîãëÂ
//
//===========================================================
#ifndef _3D_ENEMY_H_
#define _3D_ENEMY_H_
#include "main.h"
#include "Object.h"
#include "Model.h"
#include "Object3D.h"
#include "motion.h"

class CEnemy3D :public CObject3D
{
public:
	CEnemy3D(int nPriority = 0);
	~CEnemy3D();

	typedef enum
	{
		STATE_WATE = 0,
		STATE_RUN,
		STATE_ATTACK,
		STATE_STAMP,
		STATE_MAX
	}ENEMY_STATE;
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos, float Height, float Width);
	D3DXVECTOR3 GetPos(void);
	void AiContoroll(void);
	static CEnemy3D *Create(D3DXVECTOR3 pos);
	void SetObjectSize(void);
	static bool ColissionModBull(D3DXVECTOR3 pos, D3DXVECTOR3 BullPos);
	static int GetNumEnemy(void) { return m_NumEnemy; };
	CModel** GetModel(void) { return m_apModel; };
private:
	int nCntId;
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_Diffpos;
	D3DXVECTOR3 m_Destpos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_move;
	LPD3DXMESH m_pMeshModel = NULL;
	LPD3DXBUFFER m_pBuffMatModel = NULL;
	DWORD m_dwNumMatModel = 0;
	CModel *m_apModel[15];
	D3DXMATRIX  m_mtxWorld;
	LPDIRECT3DTEXTURE9 m_apTEXtureModel[50] = {};
	int  m_nNumModel;
	int m_nCntAttack;
	bool m_Knockback;
	static int m_NumEnemy;
	ENEMY_STATE m_State;
	CMotion* m_pMotion;

	static D3DXVECTOR3 m_VtxMaxObject;
	static D3DXVECTOR3 m_VtxMinObject;
};
#endif
