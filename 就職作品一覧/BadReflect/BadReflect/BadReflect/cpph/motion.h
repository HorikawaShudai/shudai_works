//===========================================================
//
//playerÇÃèàóùëÄçÏ
//Author:ñxêÏîãëÂ
//
//===========================================================
#ifndef _MOTION_H_
#define _MOTION_H_
#include "main.h"
#include "Object.h"
#include "Model.h"

#define MAX_KEY (20)
#define MAX_PARTS (15)

class CMotion
{
public:

	typedef enum
	{
		STATE_WATE = 0,
		STATE_RUN,
		STATE_ATTACK,
		STATE_STAMP,
		STATE_MAX
	}MOTIONSTATE;

	CMotion();
	~CMotion();
	HRESULT Init(void);
	void Update(void);
	static CMotion* Create(void);
	void LoadMotion(char* pMotionText);
	void SetModel(int nNum, CModel** pmodel);
	void SetState(MOTIONSTATE state);
	bool GetFinish(void) {return m_motionfinish; };
	float Normalize(float rot);
private:


	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}KEYMOTION;
	typedef struct
	{
		int bLoop;
		int bNumKey;
		int Frame;
		KEYMOTION mParts[MAX_PARTS];
	}MOTIONASSETS;

	MOTIONASSETS m_motion[STATE_MAX][MAX_KEY];
	KEYMOTION m_InitMotion[MAX_PARTS];
	int nMotionCnt;
	int  m_numModel;
	bool m_motionfinish;
	CModel** pModel;
	MOTIONSTATE m_MotionState;
	int nKey;
};

#endif