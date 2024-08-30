//=============================================================
//
//�t�F�[�h�̏���
//Autor:�x�씋��
//
//=============================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"
#include "Object.h"
#include "Object2D.h"

//�@�}�N����`
const int NUM_PAUSE(3);				//�|�[�Y���j���[�̍ő吔


class CPause
{

public:
	typedef enum
	{
		PAUSE_CONTENU = 0,	//�Q�[���ɖ߂�
		PAUSE_RETRY,		//��蒼��
		PAUSE_QUIT,			//�^�C�g���ɖ߂�
		PAUSE_MAX,
	}PAUSE_MENU;
	CPause(int nPriority = 6);
	~CPause();

	HRESULT Init(void);
	void Update(void);
	void Uninit(void);
	void Draw(void);
	void Select(void);
	void Changecol(void);
	static CPause* Create(void);
	D3DXVECTOR3 GetPos(void);
private:
	//�O���[�o���ϐ��錾
	PAUSE_MENU PauseMenu;
	D3DXCOLOR ColSelect;
	D3DXCOLOR ColNoSelect;
	bool m_PressP;
	CObject2D* m_pPauseBg;
	CObject2D* m_pPauseObject[PAUSE_MAX];
};
#endif