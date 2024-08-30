//=========================================================================================================
//
//2Dê—p‚Ìƒ|ƒŠƒSƒ“‚Ìˆ—
//Author:–xì”‹‘å
//
//=========================================================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "Effect.h"


class CParticle : public CEffect
{
public:

	typedef enum
	{
		TYPE_DETH = 0,
		TYPE_MAX

	}PARTICLE_TYPE;

	CParticle();
	~CParticle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void Create(D3DXVECTOR3 pos, PARTICLE_TYPE type);
private:
	//void InitDeth(void);
};
#endif