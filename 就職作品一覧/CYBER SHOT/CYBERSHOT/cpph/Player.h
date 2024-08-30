//===========================================================
//
//プレイヤーの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "model.h"
#include "Item.h"

typedef enum
{
	PLAYERSTATE_NORMAL = 0,	//通常状態
	PLAYERSTATE_DAMAGE,		//ダメージ状態
	PLAYERSTATE_DUSH,		//ダッシュ状態
	PLAYERSTATE_MAX,		//状態異常の最大種類数
}PLAYERSTATE;


typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;
	D3DCOLORVALUE col[256];
	D3DXVECTOR3 Destrot;
	D3DXVECTOR3 Diffrot;
	D3DXVECTOR3 moveP;
	D3DXVECTOR3 moveR;
	D3DXVECTOR3 VtxMinPlayer;
	D3DXVECTOR3 VtxMaxPlayer;
	D3DXMATRIX  mtxWorldPlayer;
	PLAYERSTATE state;
	bool CameraLock;
	bool  bUse;
	int nLife;
	int nEnagy;
	int EngCnt;
	int nIdxShadow;
	int nCntState;		//状態管理カウンター
	MODEL aModel[5];
}PLAYER;

//プロトタイプ宣言
void InitPlayer(void);
void InitEndPlayer(void);
void InitClearPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER GetPlayer(void);
void HitPlayer(int nDamage);
bool ColissionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 pMove);
void HitItem(ITEM aItem);
void PlayerEnagy(void);
void PlayerMove(void);
void PlayerWall(void);
void PlayerObject(void);
void PlayerState(void);
void SetPosition(D3DXVECTOR3 pos);
void EnemyLockOn(void);
#endif
