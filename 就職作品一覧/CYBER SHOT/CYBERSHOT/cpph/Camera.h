//===========================================================
//
//カメラの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

typedef struct
{
	D3DXVECTOR3 posV;			//視点
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 DostposR;		//注視点
	D3DXVECTOR3 DiffposR;		//注視点
	D3DXVECTOR3 posU;			//上方向ベクトル
	D3DXVECTOR3 moveR;			//上方向ベクトル
	D3DXVECTOR3 rot;			//向き
	D3DXVECTOR3 Destrot;		//目標向き
	D3DXVECTOR3 Diffrot;		//目標向き
	float Length;				//注視点と視点の距離
	float LengthR;				//注視点と視点の距離
	float Angle;				//角度
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
}Camera;

typedef struct
{
	bool Homing;
}BoolCamera;

//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void TitleCamera(void);
void EndCamera(void);
void SetCamera(void);
void SetEndCam(void);
Camera GetCamera(void);
void SetPosCamera(D3DXVECTOR3 posV, D3DXVECTOR3 posR);
void SetHoming(bool onoff);
#endif