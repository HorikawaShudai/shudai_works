//=========================================================================================================
//
//2Dプレイヤーの処理
//Author:堀川萩大
//
//=========================================================================================================
#include "Player.h"
#include "Object2D.h"
#include "Manager.h"
#include "Renderer.h"
#include "Input.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Block.h"
#include "Score.h"

#define PLAYER_HEIGHT	(30.0f)
#define PLAYER_WIDTH	(100.0f)
#define PLAYER_SPEED	(6.2f)

LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;

//====================================================
//コンストラクタ
//====================================================
CPlayer::CPlayer()
{
	m_pos = D3DXVECTOR3(640.0f, 600.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntAnim = 0;
	m_nCntPattern = 0;
	m_pTexture = NULL;

}
//====================================================
//デストラクタ
//====================================================
CPlayer::~CPlayer()
{

}


//====================================================
// 初期化処理
//====================================================
HRESULT CPlayer::Init(void)
{
	CObject2D::Init();
	SetAnim(m_nCntPattern % 4, 4, 0, 2);
	SetPlayerPos(m_pos, PLAYER_HEIGHT, PLAYER_WIDTH);
	CTexture *pTexture = CManager::Get()->GetpTexture();
	m_TexId = pTexture->Regist("data\\TEXTURE\\player001.png");

	SetType(TYPE_PLAYER);

	return S_OK;
}

//====================================================
// 終了処理
//====================================================
void CPlayer::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

}

//====================================================
// 更新処理
//====================================================
void CPlayer::Update(void)
{
	m_posOld = GetPos();

	m_pos = GetPos();
	PlayerContoroll();

	m_move.y += GRAVITY;
	
	m_pos += m_move;


	if (m_pos.y > 720.0f)
	{
		m_move.y = 0.0f;
		m_pos.y = m_posOld.y;
	}
	if (m_pos.y - PLAYER_WIDTH < 0.0f)
	{
		m_move.y = 0.0f;
		m_pos.y = m_posOld.y;
	}
	if (m_pos.x - PLAYER_HEIGHT < 0.0f)
	{
		m_move.x = 0.0f;
		m_pos.x = m_posOld.x;
	}
	if (m_pos.x + PLAYER_HEIGHT > 1280.0f)
	{
		m_move.x = 0.0f;
		m_pos.x = m_posOld.x;
	}
	if (CBlock::CollisionBlock(m_posOld, m_pos,PLAYER_HEIGHT, PLAYER_WIDTH) == TRUE)
	{
		m_move.y = 0.0f;

		m_pos.y = m_posOld.y;

	}
	if (CBlock::HCollisionBlock(m_posOld, m_pos, PLAYER_HEIGHT, PLAYER_WIDTH) == TRUE)
	{
		m_move.x = 0.0f;

		m_pos.x = m_posOld.x;

	}
	SetPlayerPos(m_pos, PLAYER_HEIGHT, PLAYER_WIDTH);
	m_move.x *= 0.05f;
	
	m_nCntAnim++;
	if (m_nCntAnim % 30 == 0)
	{
		m_nCntPattern++;
		SetAnim(m_nCntPattern%4,4,0,2);
	}
}

//====================================================
// 描画処理
//====================================================
void CPlayer::Draw(void)
{
	CObject2D::Draw();
}

//====================================================
//プレイヤーの操作処理
//====================================================
void CPlayer::PlayerContoroll(void)
{
	CKeyboard *pKeyboard = CManager::Get()->GetInputKeyboard();
	
	if (pKeyboard->GetPress(DIK_A) == true)
	{//Aを入力
		m_move.x += cosf(D3DX_PI *1.0f)*PLAYER_SPEED;
		m_move.y += sinf(D3DX_PI *1.0f)*PLAYER_SPEED;
	}
	else if (pKeyboard->GetPress(DIK_D) == true)
	{//Dを入力
		m_move.x += cosf(D3DX_PI *0.0f)*PLAYER_SPEED;
		m_move.y += sinf(D3DX_PI *0.0f)*PLAYER_SPEED;
	}
	if (pKeyboard->GetTrigger(DIK_W) == true)
	{//Wを入力
		m_move.y -= 15.0f;
	}

	if (pKeyboard->GetTrigger(DIK_SPACE) == true)
	{//SPACEを入力
		CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y-70.0f, m_pos.z));
	}
	if (pKeyboard->GetTrigger(DIK_E) == true)
	{//Eを入力
		CEnemy::Create(D3DXVECTOR3(m_pos.x + 50.0f, m_pos.y-PLAYER_WIDTH/2, m_pos.z));
	}
	if (pKeyboard->GetTrigger(DIK_B) == true)
	{//Bを入力
		CBlock::Create(D3DXVECTOR3(m_pos.x+70.0f, m_pos.y-50.0f, m_pos.z));
	}
	if (pKeyboard->GetTrigger(DIK_R) == true)
	{//Rを入力
		CObject::Reset();
		CEnemy::Create(D3DXVECTOR3(900.0f, 500.0f, 0.0f));
		//CScore::SetScore(-99999999);

	}
}