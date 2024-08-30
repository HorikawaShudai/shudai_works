//=========================================================================================================
//
//2DêÍópÇÃíeÇÃèàóù
//Author:ñxêÏîãëÂ
//
//=========================================================================================================
#include "Bullet.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Player.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Effect.h"
#include "Score.h"
#include "Block.h"

#define BULLET_HEIGHT	(30.0f)	//íeÇÃâ°ïù
#define BULLET_WIDTH	(30.0f)	//íeÇÃècïù

D3DXVECTOR3 CBullet::m_pos;
D3DXVECTOR3 CBullet::m_posOld;
LPDIRECT3DTEXTURE9 CBullet::m_pTexture;
//====================================================
//ÉRÉìÉXÉgÉâÉNÉ^
//====================================================
CBullet::CBullet()
{

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Life = BULLET_LIFE;

}
//====================================================
//ÉfÉXÉgÉâÉNÉ^
//====================================================
CBullet::~CBullet()
{

}


//====================================================
//íeÇÃèâä˙âªèàóù
//====================================================
HRESULT CBullet::Init(void)
{

	CObject2D::Init();
	m_move = D3DXVECTOR3(5.0f, 0.0f, 0.0f);

	SetPos(m_pos, BULLET_HEIGHT, BULLET_WIDTH);

	CTexture *pTexture = CManager::Get()->GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\Bullet.png");
	//BindTexture(m_pTexture);
	SetType(TYPE_BULLET);

	return S_OK;
}

//====================================================
//íeÇÃèIóπèàóù
//====================================================
void CBullet::Uninit(void)
{
 	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//====================================================
//íeÇÃçXêVèàóù
//====================================================
void CBullet::Update(void)
{
	m_posOld = GetPos();
	m_pos = GetPos();
	
	m_move.y += 0.05f;
	m_pos += m_move;

	SetPos(m_pos, BULLET_HEIGHT, BULLET_WIDTH);
	CEffect::Create(m_pos);
	m_Life--;
	if (m_Life <= 0)
	{
		CExplosion::Create(m_pos);
		Release();
	}


	else if (CBlock::CollisionBlock(m_posOld, m_pos, BULLET_HEIGHT, BULLET_WIDTH) == TRUE)
	{
		Release();

	}
	else if (CBlock::HCollisionBlock(m_posOld, m_pos, BULLET_HEIGHT, BULLET_WIDTH) == TRUE)
	{
		Release();

	}
	else
	{
		CollisionEnemy(m_pos);
	}
}

//====================================================
//íeÇÃï`âÊèàóù
//====================================================
void CBullet::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//íeÇÃê∂ê¨èàóù
//====================================================
void CBullet::Create(D3DXVECTOR3 pos)
{
	m_pos = pos;

	CObject2D::Create();

}

//====================================================
//íeÇÃìñÇΩÇËîªíË
//====================================================
bool CBullet::CollisionEnemy(D3DXVECTOR3 pos)
{
	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < NUM_POLYGON; nCntObj++)
		{
			CObject *pObj;
			pObj = GetObject(nCntPri,nCntObj);
			if (pObj != NULL)
			{
				TYPE type;
				type = pObj->GetType();
				if (type == TYPE_ENEMY)
				{
					D3DXVECTOR3 Epos = pObj->GetPos();
					if (pos.x >= Epos.x - 30.0f && pos.x <= Epos.x + 30.0f  &&
						pos.y >= Epos.y - 30.0f && pos.y <= Epos.y + 30.0f)
					{

						pObj->Release();
						Release();
						CExplosion::Create(pos);
						//CScore::AddScore(253);
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

