//=============================================================
//
//攻撃選択の処理
//Autor:堀川萩大
//
//=============================================================
#ifndef _EDITMODE_H_
#define _EDITMODE_H_
#include "main.h"

typedef enum
{
	SHOT_NUM1 = 0,	//攻撃力アップ
	SHOT_NUM2,		//右上攻撃
	SHOT_NUM3,		//右下攻撃
	SHOT_NUM4,		//マル秘攻撃（回復）
	SHOT_MAX,
}NUM_EDIT;
typedef enum
{
	PWUP_NUM1 = 0,	//強化１
	PWUP_NUM2,		//強化２
	PWUP_NUM3,		//強化３
	PWUP_NUM4,		//強化４
	PWUP_MAX,
}NUM_PWUP;

//攻撃選択の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 size;	//拡大縮小
	D3DXCOLOR  col;
	int TexNum;
}EDIT;


//プロトタイプ宣言
void InitEdMd(void);
void UninitEdMd(void);
void UpdataEdMd(void);
void DrawEdMd(void);
int *GetNumEdMd(int Num);

#endif