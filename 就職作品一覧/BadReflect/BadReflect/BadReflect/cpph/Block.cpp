//=========================================================================================================
//
//2D専用のブロックの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Block.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Player.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Effect.h"
#include "Score.h"

#define BLOCK_HEIGHT	(20.0f)	//弾の横幅
#define BLOCK_WIDTH		(50.0f)	//弾の縦幅

D3DXVECTOR3 CBlock::m_pos;
LPDIRECT3DTEXTURE9 CBlock::m_pTexture;
//====================================================
//コンストラクタ
//====================================================
CBlock::CBlock()
{

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}
//====================================================
//デストラクタ
//====================================================
CBlock::~CBlock()
{

}


//====================================================
//ブロックの初期化処理
//====================================================
HRESULT CBlock::Init(void)
{

	CObject2D::Init();
	m_move = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	SetPos(m_pos, BLOCK_HEIGHT, BLOCK_WIDTH);

	CTexture *pTexture = CManager::Get()->GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\tuti001.jpg");
	//BindTexture(m_pTexture);
	SetType(TYPE_BLOCK);

	return S_OK;
}

//====================================================
//ブロックの終了処理
//====================================================
void CBlock::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//====================================================
//ブロックの更新処理
//====================================================
void CBlock::Update(void)
{

}

//====================================================
//ブロックの描画処理
//====================================================
void CBlock::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//ブロックの生成処理
//====================================================
void CBlock::Create(D3DXVECTOR3 pos)
{
	m_pos = pos;

	CObject2D::Create();

}

//====================================================
//縦の当たり判定
//====================================================
bool CBlock::CollisionBlock(D3DXVECTOR3 oldpos, D3DXVECTOR3 pos,float Height,float Width)
{
	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < NUM_POLYGON; nCntObj++)
		{
			CObject *pObj;
			pObj = GetObject(nCntPri, nCntObj);
			if (pObj != NULL)
			{
				TYPE type;
				type = pObj->GetType();
				if (type == TYPE_BLOCK)
				{
					D3DXVECTOR3 p_pos = pObj->GetPos();

					//着地
					if ((p_pos.y-BLOCK_WIDTH) <= pos.y&& (p_pos.x - BLOCK_HEIGHT) <= pos.x && (p_pos.x + BLOCK_HEIGHT) >= pos.x && (p_pos.y - BLOCK_WIDTH) >=oldpos.y)
					{
						return TRUE;
					}
					//頭ぶつける
					else if ((p_pos.y + BLOCK_WIDTH) >= pos.y- Width && (p_pos.x - BLOCK_HEIGHT) <= pos.x && (p_pos.x + BLOCK_HEIGHT) >= pos.x && (p_pos.y + BLOCK_WIDTH) <= oldpos.y - Width)
					{
						return TRUE;
					}

					//着地
					if ((p_pos.y - BLOCK_WIDTH) <= pos.y && (p_pos.x - BLOCK_HEIGHT) <= pos.x - Height && (p_pos.x + BLOCK_HEIGHT) >= pos.x- Height && (p_pos.y - BLOCK_WIDTH) >= oldpos.y)
					{
						return TRUE;
					}

					//頭ぶつける
					else if ((p_pos.y + BLOCK_WIDTH) >= pos.y - Width && (p_pos.x - BLOCK_HEIGHT) <= pos.x - Height && (p_pos.x + BLOCK_HEIGHT) >= pos.x - Height && (p_pos.y + BLOCK_WIDTH) <= oldpos.y - Width)
					{
						return TRUE;
					}

					//着地
					if ((p_pos.y - BLOCK_WIDTH) <= pos.y && (p_pos.x - BLOCK_HEIGHT) <= pos.x + Height && (p_pos.x + BLOCK_HEIGHT) >= pos.x + Height && (p_pos.y - BLOCK_WIDTH) >= oldpos.y)
					{
						return TRUE;
					}
					//頭ぶつける
					else if ((p_pos.y + BLOCK_WIDTH) >= pos.y - Width && (p_pos.x - BLOCK_HEIGHT) <= pos.x + Height && (p_pos.x + BLOCK_HEIGHT) >= pos.x + Height && (p_pos.y + BLOCK_WIDTH) <= oldpos.y - Width)
					{
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;

}

//====================================================
//横の当たり判定
//====================================================
bool CBlock::HCollisionBlock(D3DXVECTOR3 oldpos, D3DXVECTOR3 pos, float Height, float Width)
{
	for (int nCntPri = 0; nCntPri < PRIORITY_MAX; nCntPri++)
	{
		for (int nCntObj = 0; nCntObj < NUM_POLYGON; nCntObj++)
		{
			CObject *pObj;
			pObj = GetObject(nCntPri, nCntObj);
			if (pObj != NULL)
			{
				TYPE type;
				type = pObj->GetType();
				if (type == TYPE_BLOCK)
				{
					D3DXVECTOR3 p_pos = pObj->GetPos();
					if ((p_pos.y - BLOCK_WIDTH) <= pos.y && (p_pos.y + BLOCK_WIDTH) >= pos.y && (p_pos.x + BLOCK_HEIGHT) >= pos.x - Height && (p_pos.x + BLOCK_HEIGHT) <= oldpos.x- Height)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) <= pos.y && (p_pos.y + BLOCK_WIDTH) >= pos.y && (p_pos.x - BLOCK_HEIGHT) <= pos.x + Height &&  (p_pos.x - BLOCK_HEIGHT) >= oldpos.x + Height)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) <= pos.y- Width && (p_pos.y + BLOCK_WIDTH) >= pos.y- Width && (p_pos.x + BLOCK_HEIGHT) >= pos.x - Height && (p_pos.x + BLOCK_HEIGHT) <= oldpos.x - Height)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) <= pos.y - Width && (p_pos.y + BLOCK_WIDTH) >= pos.y - Width && (p_pos.x - BLOCK_HEIGHT) <= pos.x + Height && (p_pos.x - BLOCK_HEIGHT) >= oldpos.x + Height)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) <= (pos.y - (Width / 3)) && (p_pos.y + BLOCK_WIDTH) >= (pos.y - (Width / 3)) && (p_pos.x + BLOCK_HEIGHT) >= pos.x - Height && (p_pos.x + BLOCK_HEIGHT) <= oldpos.x - Height)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) <= (pos.y - (Width / 3)) && (p_pos.y + BLOCK_WIDTH) >= (pos.y - (Width / 3)) && (p_pos.x - BLOCK_HEIGHT) <= pos.x + Height && (p_pos.x - BLOCK_HEIGHT) >= oldpos.x + Height)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) <= (pos.y - (Width / 2)) && (p_pos.y + BLOCK_WIDTH) >= (pos.y - (Width / 2)) && (p_pos.x + BLOCK_HEIGHT) >= pos.x - Height && (p_pos.x + BLOCK_HEIGHT) <= oldpos.x - Height)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) <= (pos.y - (Width / 2)) && (p_pos.y + BLOCK_WIDTH) >= (pos.y - (Width / 2)) && (p_pos.x - BLOCK_HEIGHT) <= pos.x + Height && (p_pos.x - BLOCK_HEIGHT) >= oldpos.x + Height)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) <= (pos.y - (Width / 4)) && (p_pos.y + BLOCK_WIDTH) >= (pos.y - (Width / 4)) && (p_pos.x + BLOCK_HEIGHT) >= pos.x - Height && (p_pos.x + BLOCK_HEIGHT) <= oldpos.x - Height)
					{
						return TRUE;
					}
					else if ((p_pos.y - BLOCK_WIDTH) <= (pos.y - (Width / 4)) && (p_pos.y + BLOCK_WIDTH) >= (pos.y - (Width / 4)) && (p_pos.x - BLOCK_HEIGHT) <= pos.x + Height && (p_pos.x - BLOCK_HEIGHT) >= oldpos.x + Height)
					{
						return TRUE;
					}

				}
			}
		}
	}
	return FALSE;

}

