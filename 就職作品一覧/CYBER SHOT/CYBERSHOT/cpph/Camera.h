//===========================================================
//
//�J�����̏�������
//Author:�x�씋��
//
//===========================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

typedef struct
{
	D3DXVECTOR3 posV;			//���_
	D3DXVECTOR3 posR;			//�����_
	D3DXVECTOR3 DostposR;		//�����_
	D3DXVECTOR3 DiffposR;		//�����_
	D3DXVECTOR3 posU;			//������x�N�g��
	D3DXVECTOR3 moveR;			//������x�N�g��
	D3DXVECTOR3 rot;			//����
	D3DXVECTOR3 Destrot;		//�ڕW����
	D3DXVECTOR3 Diffrot;		//�ڕW����
	float Length;				//�����_�Ǝ��_�̋���
	float LengthR;				//�����_�Ǝ��_�̋���
	float Angle;				//�p�x
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
}Camera;

typedef struct
{
	bool Homing;
}BoolCamera;

//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void TitleCamera(void);
void EndCamera(void);
void SetCamera(void);
void SetEndCam(void);
Camera GetCamera(void);
void SetPosCamera(D3DXVECTOR3 posV, D3DXVECTOR3 posR);
void SetHoming(bool onoff);
#endif