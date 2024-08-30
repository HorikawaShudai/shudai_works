#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include "d3dx9.h"

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")	//�V�X�e�������̎擾
#include "xaudio2.h"
#include <assert.h>		// �A�T�[�g�����ɕK�v



#define SCREEN_HEIGHT			(1280)	 //�E�B���h�E�T�C�Y�i���j
#define SCREEN_WIDTH			(720)	 //�E�B���h�E�T�C�Y�i�����j
#define FVF_VERTEX_2D (D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_TEX1) //���_�t�H�[�}�b�g
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)


typedef struct
{
	D3DXVECTOR3 pos; //���_���W	
	float rhw;		 //���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;	 //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	D3DXVECTOR3 nor;		//�@���x�N�g��
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`�����W
}VERTEX_3D;

//�O���錾
class  CRenderer;
class  CObject;
class  CKeyboard;
class CManager;
class CBullet;
class CFade;
//�v���^�C�v�錾
//CRenderer *GetRenderer(void);
//CObject  **GetObject(void);


//���������[�N�o�͗p�}�N��
#define _CRTCBG_MAP_ALLOC
#include <crtdbg.h>	//���������[�N���o�ɕK�v

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif
#endif