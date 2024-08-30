//=============================================================
//
//�U���I���̏���
//Autor:�x�씋��
//
//=============================================================
#ifndef _EDITMODE_H_
#define _EDITMODE_H_
#include "main.h"

typedef enum
{
	SHOT_NUM1 = 0,	//�U���̓A�b�v
	SHOT_NUM2,		//�E��U��
	SHOT_NUM3,		//�E���U��
	SHOT_NUM4,		//�}����U���i�񕜁j
	SHOT_MAX,
}NUM_EDIT;
typedef enum
{
	PWUP_NUM1 = 0,	//�����P
	PWUP_NUM2,		//�����Q
	PWUP_NUM3,		//�����R
	PWUP_NUM4,		//�����S
	PWUP_MAX,
}NUM_PWUP;

//�U���I���̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 size;	//�g��k��
	D3DXCOLOR  col;
	int TexNum;
}EDIT;


//�v���g�^�C�v�錾
void InitEdMd(void);
void UninitEdMd(void);
void UpdataEdMd(void);
void DrawEdMd(void);
int *GetNumEdMd(int Num);

#endif