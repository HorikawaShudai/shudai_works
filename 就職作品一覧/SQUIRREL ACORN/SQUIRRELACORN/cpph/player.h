//===========================================================
//
//player�̏�������
//Author:�x�씋��
//
//===========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
//#include "game.h"
#include "main.h"
#include "block.h"

//�}�N����`
#define PLAYER_WIDTH   (30.0f) //�摜�̕�
#define PLAYER_HEIGHT (80.0f)


typedef enum
{
	PLAYERSTATE_NORMAL = 0,	//�ʏ���
	PLAYERSTATE_CATCH,		//�_���[�W���
	PLAYERSTATE_DETH,
	PLAYERSTATE_MAX,		//��Ԉُ�̍ő��ސ�
}PLAYERSTATE;

//�v���C���[�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//���݈ʒu
	D3DXVECTOR3 posOld;		//�O��ʒu
	D3DXVECTOR3 Checkpos;	//�O��ʒu
	D3DXVECTOR3 posCheck;	//�O��ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//�p�x
	int nrot;				//����
	PLAYERSTATE nType;
	int nLifeFly;
	int nCntAnim;
	int nPatternAnim;
	Block *pBlock;
	bool bJump;
	bool bUse;
}Player;

//�v���g�^�C�v�錾
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