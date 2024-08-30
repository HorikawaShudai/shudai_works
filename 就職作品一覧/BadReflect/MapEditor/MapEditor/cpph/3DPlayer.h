//===========================================================
//
//ÉvÉåÉCÉÑÅ[ÇÃèàóùëÄçÏ
//Author:ñxêÏîãëÂ
//
//===========================================================
#ifndef _3D_PLAYER_H_
#define _3D_PLAYER_H_
#include "main.h"
#include "Object.h"
#include "Model.h"
#include "Object3D.h"
#include  "3DBlock.h"

class CPlayer3D:public CObject3D
{
public:

	CPlayer3D(int nPriority = 5);
	~CPlayer3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos, float Height, float Width);
	D3DXVECTOR3 GetPos(void);
	void PlayerContoroll(void);
	static CPlayer3D *Create(void);
	void SetObjectSize(void);
private:
	static D3DXVECTOR3 m_Length;
	static D3DXVECTOR3 m_pos;
	static D3DXVECTOR3 m_rot;
	int m_Num;
	static C3DBlock* m_pObject;

	LPD3DXMESH m_pMeshModel = NULL;
	LPD3DXBUFFER m_pBuffMatModel = NULL;
	DWORD m_dwNumMatModel = 0;
	D3DXMATRIX  m_mtxWorld;
	LPDIRECT3DTEXTURE9 m_apTEXtureModel[50] = {};
	int  m_nNumModel;
	static D3DXVECTOR3 m_VtxMaxObject;
	static D3DXVECTOR3 m_VtxMinObject;
};
#endif
