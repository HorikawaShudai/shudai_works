//=============================================================
//
//�G�̏���
//Author:�x�씋��
//
//=============================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"


//�G�̏�Ԃ̗񋓌^�錾
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//�ʏ���
	ENEMYSTATE_DAMAGE,		//�_���[�W���
	ENEMYSTATE_MAX,			//��Ԉُ�̍ő��ސ�
}ENEMYSTATE;

//�G�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�G�̈ʒu
	D3DXVECTOR3 Farstpos;   //�G�̏����ʒu
	float fsize;			//�G�̃T�C�Y
	int nType;				//�G�̎��
	int EneBullet;			//�G�̒e
	int EneBtCnt;			//�G�̒e�J�E���^�[
	int nLife;				//�G�̗̑�
	int nLifeHarf;			//�G�̍ő�̗�
	D3DXCOLOR col;			//�G�̐F
	ENEMYSTATE state;		//�G�̏��
	int nCounterstate;		//��ԊǗ��J�E���^�[
	bool bUse;				//�G�̎g�p�̗L��
}Enemy;

//�}�N����`
#define MAX_ENEMY (128)

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdataEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pose, int Type,float size );
void HitEnemy(int nCntEnemy, int nDamage);
Enemy *GetEnemy(void);
int *GetNumEnemy(void);
int *Getg_killNum(void);


#endif