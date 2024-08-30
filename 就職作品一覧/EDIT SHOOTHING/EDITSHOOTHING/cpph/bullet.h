//=============================================================
//
//�e�̏���
//Autor:�x�씋��
//
//=============================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//�e�̎�ނ̗񋓌^�錾
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//�v���C���[�̒e
	BULLETTYPE_ENEMY,		//�G�̒e
	BULLETTYPE_HORMING,
	BULLETTYPE_MAX,			//��ނ̍ő�l
}BULLETTYPE;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdataBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot,BULLETTYPE type,D3DXCOLOR col);

#endif