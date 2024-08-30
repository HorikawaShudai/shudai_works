//===========================================================
//
//Block�̏�������
//Author:�x�씋��
//
//===========================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_
//#include "game.h"
#include "main.h"

//�}�N����`

typedef enum
{
	BLOCKTYPE_NONE = 0,	//���ʂ̏�
	BLOCKTYPE_RIFT,		//x�ړ��̏�
	BLOCKTYPE_ELEVETOR, //y�ړ��̏�
	BLOCKTYPE_LADDER,	//��q
	BLOCKTYPE_ORI,	//��q
	BLOCKTYPE_JUMP,		//�W�����v��
	BLOCKTYPE_SAW,		//��]�m�R�M��
	BLOCKTYPE_MAX,
}BOLOCKTYPE;

//�v���C���[�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posold;	//�O�ʒu
	D3DXVECTOR3 posworld;	//�O�ʒu
	D3DXVECTOR3 move;	//�ړ���
	float CntMove;
	float fWidth;		//��
	float fHeight;		//����
	int TexNum;
	float nSpan;
	float nCnt;
	BOLOCKTYPE ntype;
	bool bUse;
}Block;



//�v���g�^�C�v�錾
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