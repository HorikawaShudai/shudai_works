//=========================================================================================================
//
//2D��p�̃|���S���̏���
//Author:�x�씋��
//
//=========================================================================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "Object.h"



class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);
	~CObject3D();

	HRESULT Init(void) = 0;		//����������
	void Uninit(void);			//�I������
	void Update(void) = 0;		//�X�V����
	void Draw(void) = 0;		//�`�揈��

	void SetPos(D3DXVECTOR3 pos, float Height, float Width);	//�ʒu�ݒ�
	void SetSize(float Height, float Width);					//���ݒ�
	static CObject3D *Create(D3DXVECTOR3 pPos,float Scale, TYPE type3D, int nDate);	//��������
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);				//�e�N�X�`���ݒ�
	D3DXVECTOR3 GetPos(void);									//�ʒu�擾����
	LPDIRECT3DTEXTURE9 m_pTexture;								//�e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//���_�o�b�t�@
protected:
private:
	D3DXVECTOR3 m_pos;
	int m_nNumObject3D;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX  m_mtxWorld;
};

#endif