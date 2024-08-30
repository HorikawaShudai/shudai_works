//=============================================================
//
//�t�F�[�h�̏���
//Autor:�x�씋��
//
//=============================================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "manager.h"

class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,	//�������Ă��Ȃ����
		FADE_IN,		//�t�F�[�h�C�����
		FADE_OUT,		//	�t�F�[�h�A�E�g���
		FADE_MAX,
	}FADE;
	CFade();
	~CFade();
	 HRESULT Init(void);
	 void Uninit(void);
	 void Update(void);
	 void Draw(void);
	void SetFade(CScene::MODE ModeNext, float Fade);
	FADE GetFade(void);
	static CFade *Create(void);

private:
	//�O���[�o���ϐ��錾
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffFade;  //�t�F�[�h�̐��̒��_�o�b�t�@
	FADE m_Fade;
	float m_FadeCount;
	D3DXCOLOR m_ColorFade;
	CScene::MODE  m_ModeNext;
	CObject2D* m_pPoly;
};



#endif