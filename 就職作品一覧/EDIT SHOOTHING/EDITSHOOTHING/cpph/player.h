//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "game.h"

//マクロ定義
#define PLAYER_WIDTH   (60.0f) //画像の幅
#define PLAYER_HEIGHT  (60.0f) //画像の高さ

typedef enum
{
	PLAYERSTATE_NORMAL = 0,	//通常状態
	PLAYERSTATE_DAMAGE,		//ダメージ状態
	PLAYERSTATE_MAX,		//状態異常の最大種類数
}PLAYERSTATE;

//プレイヤーの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR3 rot;	//角度
	D3DXVECTOR3 size;	//拡大縮小
	PLAYERSTATE state;
	int life;			//体力
	int Attackpt[4];
	int EditNum[4];
	int nPoint;
	int nCounterstate;		//状態管理カウンター
	bool bUse;
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdataPlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
void HitPlayer(int nDamage);
void GetItem(int Point);
#endif