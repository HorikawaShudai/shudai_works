//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
//#include "game.h"
#include "main.h"
#include "block.h"

//マクロ定義
#define PLAYER_WIDTH   (30.0f) //画像の幅
#define PLAYER_HEIGHT (80.0f)


typedef enum
{
	PLAYERSTATE_NORMAL = 0,	//通常状態
	PLAYERSTATE_CATCH,		//ダメージ状態
	PLAYERSTATE_DETH,
	PLAYERSTATE_MAX,		//状態異常の最大種類数
}PLAYERSTATE;

//プレイヤーの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//現在位置
	D3DXVECTOR3 posOld;		//前回位置
	D3DXVECTOR3 Checkpos;	//前回位置
	D3DXVECTOR3 posCheck;	//前回位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//角度
	int nrot;				//向き
	PLAYERSTATE nType;
	int nLifeFly;
	int nCntAnim;
	int nPatternAnim;
	Block *pBlock;
	bool bJump;
	bool bUse;
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
void SetType(PLAYERSTATE ntype);
void SetPlayer(float posx, float posy);
void ScloolWorld(void);
D3DXVECTOR3 GetWorld(void);
void SetPos(D3DXVECTOR3 pos);
#endif