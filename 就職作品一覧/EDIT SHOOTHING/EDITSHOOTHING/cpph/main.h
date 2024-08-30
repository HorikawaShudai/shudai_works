//===========================================================
//
//���C������
//Author:�x�씋��
//
//===========================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800) //�r���h���̌x���Ώ��p�r���h
#include "dinput.h"
#include "xaudio2.h"

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")	//�V�X�e�������̎擾
#pragma comment(lib,"dinput8.lib")

#define SCREEN_WIDTH			(1280)	 //�E�B���h�E�T�C�Y�i���j
#define SCREEN_HEIGHT			(720)	 //�E�B���h�E�T�C�Y�i�����j
#define FVF_VERTEX_2D (D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_TEX1) //���_�t�H�[�}�b�g

typedef struct
{
	D3DXVECTOR3 pos; //���_���W	
	float rhw;		 //���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;	 //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_2D;

//��ʃ��[�h�̎��
typedef enum
{
	MODE_TITLE = 0,	//�^�C�g�����
	MODE_EDIT,		//�U���I�����
	MODE_GAME,		//�Q�[�����
	MODE_RESULT,	//���U���g���
	MODE_MAX
}MODE;

//�v���^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
#endif

