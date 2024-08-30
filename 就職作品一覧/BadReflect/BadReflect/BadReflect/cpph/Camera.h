//===========================================================
//
//カメラの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"


class CCamera
{
public:
	typedef enum
	{
		STATE_NONE  = 0,
		STATE_MOVE,
		STATE_STAY,
		STATE_WAVE,
		STATE_MAX
	}CAMSTATE;
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 m_posV;			//視点
	float m_ViewCamera;
	float GetRot();
private:
	D3DXVECTOR3 m_posR;			//注視点
	D3DXVECTOR3 m_DostposR;		//注視点
	D3DXVECTOR3 m_DiffposR;		//注視点
	D3DXVECTOR3 m_posU;			//上方向ベクトル
	D3DXVECTOR3 m_moveR;		//上方向ベクトル
	D3DXVECTOR3 m_rot;			//向き
	D3DXVECTOR3 m_Destrot;		//目標向き
	D3DXVECTOR3 m_Diffrot;		//目標向き
	float m_Length;				//注視点と視点の距離
	float m_LengthR;			//注視点と視点の距離
	float m_Angle;				//角度
	D3DXMATRIX m_mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			//ビューマトリックス
	bool m_bMatrix;				//投影方法変更
	CAMSTATE m_State;
};
#endif