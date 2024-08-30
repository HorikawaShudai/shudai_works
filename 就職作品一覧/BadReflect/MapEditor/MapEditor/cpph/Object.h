//=========================================================================================================
//
//オブジェクトの処理
//Author:堀川萩大
//
//=========================================================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

#define NUM_POLYGON (2048)
#define NUM_PRIORITY (8)

class CObject
{
public:

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_FIELD,
		TYPE_3DBLOCK,
		TYPE_OBSTACLEBLOCK,
		TYPE_WALLBLOCK,
		TYPE_RUBBLE,
		TYPE_EDITBLOCK,
		TYPE_MAX
	}TYPE;

	CObject(int nPriority = 3);
	virtual ~CObject();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//virtual void SetPos(D3DXVECTOR3 pos, float Height, float Width) = 0;
	//virtual void SetRot(float rot) = 0;
	virtual D3DXVECTOR3 GetPos(void) = 0;
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	void Release(void);
	void SetType(TYPE type);
	TYPE GetType(void) { return m_type; };
	static CObject *GetObject(int nPriority,int nIdx) {return m_apObject[nPriority][nIdx];};
	static void Reset(void);
	static void Load(void);
	static void WhiteTextMap(void);
	static void LoadMap(void);
	int m_nID;
	int m_nPriority;
protected:
	int m_TexId;

private:
	static CObject *m_apObject[NUM_PRIORITY][NUM_POLYGON];
	static int m_nNumAll;

	TYPE m_type;
};

#endif