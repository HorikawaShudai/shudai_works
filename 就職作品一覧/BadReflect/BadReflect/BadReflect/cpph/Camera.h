//===========================================================
//
//�J�����̏�������
//Author:�x�씋��
//
//===========================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"


class CCamera
{
public:
	typedef enum
	{
		STATE_NONE  = 0,
		STATE_MOVE,
		STATE_STAY,
		STATE_WAVE,
		STATE_MAX
	}CAMSTATE;
	CCamera();
	~CCamera();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 m_posV;			//���_
	float m_ViewCamera;
	float GetRot();
private:
	D3DXVECTOR3 m_posR;			//�����_
	D3DXVECTOR3 m_DostposR;		//�����_
	D3DXVECTOR3 m_DiffposR;		//�����_
	D3DXVECTOR3 m_posU;			//������x�N�g��
	D3DXVECTOR3 m_moveR;		//������x�N�g��
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_Destrot;		//�ڕW����
	D3DXVECTOR3 m_Diffrot;		//�ڕW����
	float m_Length;				//�����_�Ǝ��_�̋���
	float m_LengthR;			//�����_�Ǝ��_�̋���
	float m_Angle;				//�p�x
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			//�r���[�}�g���b�N�X
	bool m_bMatrix;				//���e���@�ύX
	CAMSTATE m_State;
};
#endif