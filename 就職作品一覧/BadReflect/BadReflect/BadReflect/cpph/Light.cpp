//===========================================================
//
//���C�g�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Light.h"
#include "Renderer.h"
#include "Manager.h"



CLight::CLight()
{

}
CLight::~CLight()
{

}

//=========================================================================================================
//����������
//=========================================================================================================
void CLight:: Init(void)
{
	
	CRenderer *pRenderer = CManager::Get()->GetRenderer();
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXVECTOR3 vecDir;//�ݒ�p�����x�N�g��

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̕�����ݒ�
		switch (nCntLight)
		{
		case 1:
			vecDir = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
			//���C�g�̊g�U����ݒ�
			m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case 2:
			vecDir = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
			//���C�g�̊g�U����ݒ�
			m_light[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
			break;
		case 3:
			vecDir = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
			//���C�g�̊g�U����ݒ�
			m_light[nCntLight].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
			break;
		}

		//���C�g�̕�����ݒ�
		//vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g���𐳋K��
		m_light[nCntLight].Direction = vecDir;

		//���C�g�̕�����ݒ肷��
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);
		//���C�g��L��������
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=========================================================================================================
//���C�g�̏I������
//=========================================================================================================
void CLight:: Uninit(void)
{

}

//=========================================================================================================
//���C�g�̍X�V����
//=========================================================================================================
void CLight:: Updata(void)
{

}
