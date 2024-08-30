//=============================================================
//
//弾の処理
//Autor:堀川萩大
//
//=============================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//弾の種類の列挙型宣言
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//プレイヤーの弾
	BULLETTYPE_ENEMY,		//敵の弾
	BULLETTYPE_HORMING,
	BULLETTYPE_MAX,			//種類の最大値
}BULLETTYPE;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdataBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot,BULLETTYPE type,D3DXCOLOR col);

#endif