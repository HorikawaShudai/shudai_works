//===========================================================
//
//player�̏�������
//Author:�x�씋��
//
//===========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "game.h"

//�}�N����`
#define PLAYER_WIDTH   (60.0f) //�摜�̕�
#define PLAYER_HEIGHT  (60.0f) //�摜�̍���

typedef enum
{
	PLAYERSTATE_NORMAL = 0,	//�ʏ���
	PLAYERSTATE_DAMAGE,		//�_���[�W���
	PLAYERSTATE_MAX,		//��Ԉُ�̍ő��ސ�
}PLAYERSTATE;

//�v���C���[�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR3 rot;	//�p�x
	D3DXVECTOR3 size;	//�g��k��
	PLAYERSTATE state;
	int life;			//�̗�
	int Attackpt[4];
	int EditNum[4];
	int nPoint;
	int nCounterstate;		//��ԊǗ��J�E���^�[
	bool bUse;
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdataPlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
void HitPlayer(int nDamage);
void GetItem(int Point);
#endif