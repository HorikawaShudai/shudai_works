//===========================================================
//
//Blockの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_
//#include "game.h"
#include "main.h"

//マクロ定義

typedef enum
{
	BLOCKTYPE_NONE = 0,	//普通の床
	BLOCKTYPE_RIFT,		//x移動の床
	BLOCKTYPE_ELEVETOR, //y移動の床
	BLOCKTYPE_LADDER,	//梯子
	BLOCKTYPE_ORI,	//梯子
	BLOCKTYPE_JUMP,		//ジャンプ床
	BLOCKTYPE_SAW,		//回転ノコギリ
	BLOCKTYPE_MAX,
}BOLOCKTYPE;

//プレイヤーの構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posold;	//前位置
	D3DXVECTOR3 posworld;	//前位置
	D3DXVECTOR3 move;	//移動量
	float CntMove;
	float fWidth;		//幅
	float fHeight;		//高さ
	int TexNum;
	float nSpan;
	float nCnt;
	BOLOCKTYPE ntype;
	bool bUse;
}Block;



//プロトタイプ宣言
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, float wight, float height, BOLOCKTYPE type);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3*pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight,Block **pBlock);
void DleatBlock(BOLOCKTYPE type);
void ScrollBlockx(float move);
void ScrollBlocky(float move);
#endif