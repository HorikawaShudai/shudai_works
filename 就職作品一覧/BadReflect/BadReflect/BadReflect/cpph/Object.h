//=========================================================================================================
//
//ƒ|ƒŠƒSƒ“‚Ì‹¤—Lˆ—
//Author:–xì”‹‘å
//
//=========================================================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

const int  NUM_POLYGON(400);

class CObject
{
public:

	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_PLAYER,
		TYPE_BG,
		TYPE_BGS,
		TYPE_BULLET,
		TYPE_EXPLOSION,
		TYPE_ENEMY,
		TYPE_EFFECT,
		TYPE_NUMBER,
		TYPE_BLOCK,
		TYPE_ITEM,
		TYPE_FIELD,
		TYPE_CYLINDER,
		TYPE_SNOWWALL,
		TYPE_3DBLOCK,
		TYPE_PAUSE,
		TYPE_GUAGE,
		TYPE_SCENE,
		TYPE_FADE,
		TYPE_BOSS,
		TYPE_MAX
	}TYPE;

	typedef enum
	{
		PRIORITY_BG = 0,	// ”wŒi
		PRIORITY_LOW,		// 
		PRIORITY_NORMAL,	// 
		PRIORITY_HIGH,		// 
		PRIOTITY_EFFECT,	// ƒGƒtƒFƒNƒg
		PRIORITY_CHARACTER,	// ƒLƒƒƒ‰
		PRIORITY_UI,		// UI
		PRIORITY_FG,		// ‘OŒi
		PRIORITY_MAX		// 
	}PRIORITY;

	typedef enum
	{
		MODE_OBJECT_NONE = 0,
		MODE_OBJECT_SETTING,
		MODE_OBJECT_TITLE,
		MODE_OBJECT_TUTORIAL,
		MODE_OBJECT_GAME,
		MODE_OBJECT_RESULT,
		MODE_OBJECT_RANKING,
		MODE_OBJECT_MAX,
	}MODE_OBJECT;

	CObject(int nPriority = 3);
	virtual ~CObject();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	//virtual void SetRot(float rot) = 0;
	virtual D3DXVECTOR3 GetPos(void) = 0;
	static void ReleaseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	static void ModeRelease(MODE_OBJECT nModeObject);
	void Release(void);
	void SetType(TYPE type) { m_type = type; };
	TYPE GetType(void) { return m_type; };
	static CObject *GetObject(int nPriority,int nIdx) {return m_apObject[nPriority][nIdx];};
	static void Reset(void);
	static void LoadMap(void);
	static int GetLife(int nId, int nPriority) { return m_apObject[nPriority][nId]->nLife; };
	void SetTexId(int nId) { m_TexId = nId; };
	void SetModeobject(MODE_OBJECT nModeObject) { m_ModeObject = nModeObject; };
	int m_TexId;
	int nLife;
	int m_nPriority;
	int m_nID;

protected:

private:
	static CObject *m_apObject[PRIORITY_MAX][NUM_POLYGON];
	static int m_nNumAll;
	TYPE m_type;
	MODE_OBJECT m_ModeObject;
};

#endif