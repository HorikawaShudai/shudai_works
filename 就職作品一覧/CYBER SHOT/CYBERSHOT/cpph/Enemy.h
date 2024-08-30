//===========================================================
//
//敵の処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "model.h"

//敵の状態の列挙型宣言
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//通常状態
	ENEMYSTATE_DAMAGE,		//ダメージ状態
	ENEMYSTATE_MAX,			//状態異常の最大種類数
}ENEMYSTATE;

//敵の状態の列挙型宣言
typedef enum
{
	BOSSMODE_FIRST = 0,	//第一段階
	BOSSMODE_SECOND,	//第二段階
	BOSSMODE_FINAL,		//第三段階
	BOSSMODE_MAX,
}BOSSMODE;

typedef enum
{
	ENEMY_MOB =0,
	ENEMY_BOSS,
}ENEMYTYPE;

typedef struct
{
	D3DXVECTOR3		pos;
	D3DXVECTOR3		rot;
	D3DXVECTOR3		Destrot;
	D3DXVECTOR3		Diffrot;
	D3DXVECTOR3		move;
	D3DXVECTOR3		VtxMinEnemy;
	D3DXVECTOR3		VtxMaxEnemy;
	D3DXMATRIX		mtxWorldEnemy;
	DWORD			dwNumMatEnemy;
	LPD3DXMESH		pMeshEnemy;
	int				nIdxShadow;
	int				nLife;
	int				nCntState;
	int				nCntAttack;
	bool			bUse;
	LPDIRECT3DTEXTURE9 pTEXtureEnemy[50];
	D3DCOLORVALUE col[256];
	ENEMYSTATE state;
	ENEMYTYPE type;
	BOSSMODE AttackPatarn;
	//MODEL aEnemyModel[2];
}ENEMY;

//プロトタイプ宣言
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pEnemyename);
ENEMY GetEnemy(void);
D3DXVECTOR3 ColissionEnemy(D3DXVECTOR3 possize, D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *pMove);
bool ColissionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 pMove);
ENEMY GetEnemy(void);
void AttackPart(void);
void AttackMob(int nNum);
bool ColPlayEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 posOld);
#endif
