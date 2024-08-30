//=============================================================
//
//敵の処理
//Author:堀川萩大
//
//=============================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"


//敵の状態の列挙型宣言
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//通常状態
	ENEMYSTATE_DAMAGE,		//ダメージ状態
	ENEMYSTATE_MAX,			//状態異常の最大種類数
}ENEMYSTATE;

//敵の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;		//敵の位置
	D3DXVECTOR3 Farstpos;   //敵の初期位置
	float fsize;			//敵のサイズ
	int nType;				//敵の種類
	int EneBullet;			//敵の弾
	int EneBtCnt;			//敵の弾カウンター
	int nLife;				//敵の体力
	int nLifeHarf;			//敵の最大体力
	D3DXCOLOR col;			//敵の色
	ENEMYSTATE state;		//敵の状態
	int nCounterstate;		//状態管理カウンター
	bool bUse;				//敵の使用の有無
}Enemy;

//マクロ定義
#define MAX_ENEMY (128)

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdataEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pose, int Type,float size );
void HitEnemy(int nCntEnemy, int nDamage);
Enemy *GetEnemy(void);
int *GetNumEnemy(void);
int *Getg_killNum(void);


#endif