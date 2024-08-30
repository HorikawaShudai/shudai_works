//===========================================================
//
//�G�̏�������
//Author:�x�씋��
//
//===========================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "model.h"

//�G�̏�Ԃ̗񋓌^�錾
typedef enum
{
	ENEMYSTATE_NORMAL = 0,	//�ʏ���
	ENEMYSTATE_DAMAGE,		//�_���[�W���
	ENEMYSTATE_MAX,			//��Ԉُ�̍ő��ސ�
}ENEMYSTATE;

//�G�̏�Ԃ̗񋓌^�錾
typedef enum
{
	BOSSMODE_FIRST = 0,	//���i�K
	BOSSMODE_SECOND,	//���i�K
	BOSSMODE_FINAL,		//��O�i�K
	BOSSMODE_MAX,
}BOSSMODE;

typedef enum
{
	ENEMY_MOB =0,
	ENEMY_BOSS,
}ENEMYTYPE;

typedef struct
{
	D3DXVECTOR3		pos;
	D3DXVECTOR3		rot;
	D3DXVECTOR3		Destrot;
	D3DXVECTOR3		Diffrot;
	D3DXVECTOR3		move;
	D3DXVECTOR3		VtxMinEnemy;
	D3DXVECTOR3		VtxMaxEnemy;
	D3DXMATRIX		mtxWorldEnemy;
	DWORD			dwNumMatEnemy;
	LPD3DXMESH		pMeshEnemy;
	int				nIdxShadow;
	int				nLife;
	int				nCntState;
	int				nCntAttack;
	bool			bUse;
	LPDIRECT3DTEXTURE9 pTEXtureEnemy[50];
	D3DCOLORVALUE col[256];
	ENEMYSTATE state;
	ENEMYTYPE type;
	BOSSMODE AttackPatarn;
	//MODEL aEnemyModel[2];
}ENEMY;

//�v���g�^�C�v�錾
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, char *pEnemyename);
ENEMY GetEnemy(void);
D3DXVECTOR3 ColissionEnemy(D3DXVECTOR3 possize, D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *pMove);
bool ColissionEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 pMove);
ENEMY GetEnemy(void);
void AttackPart(void);
void AttackMob(int nNum);
bool ColPlayEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 posOld);
#endif
