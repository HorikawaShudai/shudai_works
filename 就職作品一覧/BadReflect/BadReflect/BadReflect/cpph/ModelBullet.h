//===========================================================
//
//playerÇÃèàóùëÄçÏ
//Author:ñxêÏîãëÂ
//
//===========================================================
#ifndef _MODEL_BULLET_H_
#define _MODEL_BULLET_H_
#include "main.h"
#include "Object.h"

class CModelBullet:public CObject
{
public:
	typedef enum
	{
		PLAYER_BULLET = 0,
		ENEMY_BULLET,
		BULLET_MAX
	}BULLETTYPE;

	CModelBullet(int nPriority = 2);
	~CModelBullet();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos, float Height, float Width);
	D3DXVECTOR3 GetPos(void);
	static void CreateModel(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type);
	void SetObjectSize(void);
	void SetBulletType(BULLETTYPE type);
private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_move;
	D3DXMATRIX  m_mtxWorld;
	LPD3DXMESH m_pMeshModel = NULL;
	LPD3DXBUFFER m_pBuffMatModel = NULL;
	DWORD m_dwNumMatModel = 0;
	D3DXVECTOR3 m_VtxMaxObject;
	D3DXVECTOR3 m_VtxMinObject;
	LPDIRECT3DTEXTURE9 m_apTEXtureModel[50] = {};
	BULLETTYPE m_Bullettype;
};
#endif
