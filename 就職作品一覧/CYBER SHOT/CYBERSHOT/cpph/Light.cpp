//===========================================================
//
//���C�g�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Light.h"

#define MAX_LIGHT (3)

//�O���[�o���ϐ��錾
D3DLIGHT9 g_light[MAX_LIGHT];

//=========================================================================================================
//����������
//=========================================================================================================
void InitLight(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;//�ݒ�p�����x�N�g��

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&g_light[nCntLight], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		g_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̕�����ݒ�
		switch (nCntLight)
		{
		case 1:
			vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
			//���C�g�̊g�U����ݒ�
			g_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case 2:
			vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
			//���C�g�̊g�U����ݒ�
			g_light[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			break;
		case 3:
			vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
			//���C�g�̊g�U����ݒ�
			g_light[nCntLight].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
			break;
		}

		//���C�g�̕�����ݒ�
		//vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g���𐳋K��
		g_light[nCntLight].Direction = vecDir;

		//���C�g�̕�����ݒ肷��
		pDevice->SetLight(nCntLight, &g_light[nCntLight]);
		//���C�g��L��������
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=========================================================================================================
//���C�g�̏I������
//=========================================================================================================
void UninitLight(void)
{

}

//=========================================================================================================
//���C�g�̍X�V����
//=========================================================================================================
void UpdateLight(void)
{

}
