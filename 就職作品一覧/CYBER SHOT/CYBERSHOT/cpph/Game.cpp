//=============================================================================
//
//�Q�[����ʏ��� [game.h]
// Author : �x�씋��
//
//=============================================================================
#include "game.h"
#include "input.h"
#include "Light.h"
#include "MeshIndex.h"
#include "Camera.h"
#include "Player.h"
#include "Shadow.h"
#include "MeshWall.h"
#include "Item.h"
#include "Bullet.h"
#include "Explosion.h"
#include "effect.h"
#include "MeshIndex.h"
//#include "MeshCylinder.h"
#include "Object.h"
#include "Enemy.h"
#include "Pause.h"
#include "Enagy.h"
#include "LifeGuage.h"
#include "Sound.h"
#include "ModelBullet.h"


//�O���[�o���ϐ��錾
bool g_bPause;
int g_nCntFade;
GAMEMODE g_Gamemode;

//=========================================================================================================
//�Q�[����ʂ̏���������
//=========================================================================================================
void InitGame(void)
{
	//�T�E���h�̏���������
	PlaySound(SOUND_LABEL_BGM000);
	g_bPause = false;
	g_nCntFade = 0;
	g_Gamemode = GAMEMODE_NONE;

	//�J�����̏���������
	InitCamera();
	//���C�g�̏���������
	InitLight();
	//�e�̏���������
	InitShadow();
	//�v���C���[�̏���������
	InitPlayer();
	//�e�̏���������
	InitBullet();
	//�e�̏���������
	InitModBull();
	//�����̏���������
	InitExplosion();
	//�G�̏���������
	InitEnemy();
	//�G�ݒu
	SetEnemy(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\Enemy000.x");
	//�G�t�F�N�g�̏���������
	InitEffect();
	//�A�C�e���̏���������
	InitItem();
	//���̏���������
	//InitMeshCylinder();
	//�n�ʂ̏���������
	InitMeshIndex();
	//�ǂ̏���������
	InitMeshWall();
	//�I�u�W�F�N�g�̏���������
	InitObject();
	{//�I�u�W�F�N�g�ݒu
		SetObject(D3DXVECTOR3(1100.0f, 50.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(-1100.0f, 50.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(500.0f, 50.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(-500.0f, 50.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(-800.0f, 50.0f, 1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(-800.0f, 50.0f, -1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(800.0f, 50.0f, 1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		SetObject(D3DXVECTOR3(800.0f, 50.0f, -1200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		//SetObject(D3DXVECTOR3(-1100.0f, 50.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		//SetObject(D3DXVECTOR3(-1200.0f, 50.0f, -1500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");
		//SetObject(D3DXVECTOR3(1200.0f, 50.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\contena.x");

		SetObject(D3DXVECTOR3(1470.0f, 0.0f, -1470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\WoodBox.x");
		SetObject(D3DXVECTOR3(-1470.0f, 0.0f, -1470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\WoodBox.x");
		SetObject(D3DXVECTOR3(1470.0f, 0.0f, 1470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\WoodBox.x");
		SetObject(D3DXVECTOR3(-1470.0f, 0.0f, 1470.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), "data\\MODEL\\WoodBox.x");
	}
	//�|�[�Y�̏���������
	InitPause();
	//�G�i�W�[�̏���������
	InitEnagy();
	//���C�t�Q�[�W�̏���������
	InitLifeGuage();
}

//=========================================================================================================
//�Q�[����ʂ̏I������
//=========================================================================================================
void UninitGame(void)
{
	//�J�����̏I������
	UninitCamera();
	//�e�̏I������
	UninitBullet();
	UninitModBull();
	//�G�̏I������
	UninitEnemy();
	//�����̏I������
	UninitExplosion();
	//�|���S���̏I������
	UninitPlayer();
	//�G�t�F�N�g�̏I������
	UninitEffect();
	//�A�C�e���̏I������
	UninitItem();
	//�n�ʂ̏I������
	UninitMeshIndex();
	//�ǂ̏I������
	UninitMeshWall();
	//���̏I������
	//UninitMeshCylinder();
	//���C�g�̏I������
	UninitLight();
	//�I�u�W�F�N�g�̏I������
	UninitObject();
	//�e�̏I������
	UninitShadow();
	//�|�[�Y�̏I������
	UninitPause();
	//�G�i�W�[�̏I������
	UninitEnagy();
	//���C�t�Q�[�W�̏I������
	UninitLifeGuage();
	//�T�E���h�̒�~
	StopSound();
}

//=========================================================================================================
//�Q�[����ʂ̍X�V����
//=========================================================================================================
void UpdateGame(void)
{
	UpdatePause();
	if (g_bPause == false)
	{
		UpdateCamera();
		//UpdateMeshCylinder();
		UpdateLight();
		UpdateShadow();
		UpdateBullet();
		UpdateModBull();
		UpdateExplosion();
		UpdateEffect();
		UpdateMeshWall();
		UpdateMeshIndex();
		UpdatePlayer();
		UpdateObject();
		UpdateEnemy();
		UpdateItem();
		UpdateEnagy();
		UpdatePlayerGuage();
		UpdateEnemyGuage();
	}
}

//=========================================================================================================
//�Q�[����ʂ̕`�揈��
//=========================================================================================================
void DrawGame(void)
{
	SetCamera();
	DrawMeshIndex();
	//DrawMeshCylinder();
	DrawMeshWall();
	DrawEffect();
	DrawBullet();
	DrawModBull();
	DrawExplosion();
	DrawObject();
	DrawPlayer();
	DrawEnemy();
	DrawItem();
	DrawEnagy();
	DrawLifeGuage();
	DrawShadow();

	if (g_bPause == true)
	{
		DrawPause();
	}
}


GAMEMODE GetGamemode(void)
{
	return g_Gamemode;
}

void SetGamemode(GAMEMODE mode)
{
	g_Gamemode = mode;
}

void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}

bool GetPouse(void)
{
	return g_bPause;
}