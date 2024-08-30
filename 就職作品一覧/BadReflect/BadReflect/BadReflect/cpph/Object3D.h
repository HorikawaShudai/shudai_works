//=========================================================================================================
//
//2D専用のポリゴンの処理
//Author:堀川萩大
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

	HRESULT Init(void) = 0;		//初期化処理
	void Uninit(void);			//終了処理
	void Update(void) = 0;		//更新処理
	void Draw(void) = 0;		//描画処理

	void SetPos(D3DXVECTOR3 pos, float Height, float Width);	//位置設定
	void SetSize(float Height, float Width);					//幅設定
	static CObject3D *Create(D3DXVECTOR3 pPos,float Scale, TYPE type3D, int nDate);	//生成処理
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);				//テクスチャ設定
	D3DXVECTOR3 GetPos(void);									//位置取得処理
	LPDIRECT3DTEXTURE9 m_pTexture;								//テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//頂点バッファ
protected:
private:
	D3DXVECTOR3 m_pos;
	int m_nNumObject3D;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX  m_mtxWorld;
};

#endif