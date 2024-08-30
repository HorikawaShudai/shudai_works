//============================================================================
//
//CSVファイルのデータ読み込みと出力
//Author:堀川萩大
//
//============================================================================
#include "CreateMap.h"
#include "Item.h"
#include "Block.h"
#include "Player.h"
#include <stdio.h>

#define CSVMAP "data\\MAP\\Map.csv"

//列挙型のデータ宣言
typedef enum
{
	MAP_NONE = 0,	//空気
	MAP_FLORE,		//床
	MAP_SAW,		//ダメージブロック
	MAP_JUMP,		//ジャンプ床
	MAP_LADDER,		//梯子
	MAP_ORI,		//梯子
	MAP_GOAL,		//ゴール
	MAP_KEY,		//ゴール
	MAP_PLAYER,		//プレイヤー
	MAP_MAX,
}MAP_KIND;

typedef struct
{
	int mapData[ MAX_WHIGHT];
}DATA;

//グローバル変数宣言
DATA g_aData[MAX_DATA];


//============================================================================
//読み込み処理
//============================================================================
void LoadMap(void)
{
	int DataCnt = 0;
	int cnt = 0;
	int Cnt = 0;
	FILE *pFile;

	pFile = fopen(CSVMAP, "r");
	if (pFile != NULL)
	{
			for (; fscanf(pFile, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", 
				&g_aData[Cnt].mapData[0], &g_aData[Cnt].mapData[1], &g_aData[Cnt].mapData[2], &g_aData[Cnt].mapData[3], &g_aData[Cnt].mapData[4], &g_aData[Cnt].mapData[5]
			, &g_aData[Cnt].mapData[6], &g_aData[Cnt].mapData[7], &g_aData[Cnt].mapData[8], &g_aData[Cnt].mapData[9], &g_aData[Cnt].mapData[10], &g_aData[Cnt].mapData[11],
				&g_aData[Cnt].mapData[12], &g_aData[Cnt].mapData[13], &g_aData[Cnt].mapData[14], &g_aData[Cnt].mapData[15], &g_aData[Cnt].mapData[16], &g_aData[Cnt].mapData[17]
			, &g_aData[Cnt].mapData[18], &g_aData[Cnt].mapData[19], &g_aData[Cnt].mapData[20], &g_aData[Cnt].mapData[21], &g_aData[Cnt].mapData[22]
				, &g_aData[Cnt].mapData[23], &g_aData[Cnt].mapData[24], &g_aData[Cnt].mapData[25], &g_aData[Cnt].mapData[26], &g_aData[Cnt].mapData[27]
				, &g_aData[Cnt].mapData[28], &g_aData[Cnt].mapData[29], &g_aData[Cnt].mapData[30], &g_aData[Cnt].mapData[31], &g_aData[Cnt].mapData[32]
				, &g_aData[Cnt].mapData[33], &g_aData[Cnt].mapData[34]) != EOF;)
			{
				Cnt++;
				if (Cnt==MAX_DATA)
				{
					fclose(pFile);
					break;
				}
			}
	}
	else
	{

	}
	CreateMap();

}

void CreateMap(void)
{
	for (int cnt = 0; cnt < MAX_DATA; cnt++)
	{
		for (int Cnt = 0; Cnt <  MAX_WHIGHT; Cnt++)
		{
			switch (g_aData[cnt].mapData[Cnt])
			{
			case MAP_NONE:
				break;
			case MAP_FLORE:
				break;
			case MAP_SAW:
				break;
			case MAP_JUMP:
				break;
			case MAP_LADDER:
				break;
			case MAP_ORI:
				break;
			case MAP_GOAL:
				break;
			case MAP_KEY:
				break;
			case MAP_PLAYER:
				SetPlayer((60.0f + (Cnt*60.0f)), (cnt*60.0f));
				break;
			}
		}
	}
	for (int cnt = 0; cnt < MAX_DATA; cnt++)
	{
		for (int Cnt = 0; Cnt <  MAX_WHIGHT; Cnt++)
		{
			switch (g_aData[cnt].mapData[Cnt])
			{
				case MAP_NONE:
					break;
				case MAP_FLORE:
					SetBlock(D3DXVECTOR3((60.0f+(Cnt*60.0f)) ,(cnt*60.0f), 0.0f), 60.0f, 60.0f, BLOCKTYPE_NONE);
					break;
				case MAP_SAW:
					SetBlock(D3DXVECTOR3((60.0f+(Cnt*60.0f)) ,(cnt*60.0f), 0.0f), 60.0f, 60.0f, BLOCKTYPE_SAW);
					break;
				case MAP_JUMP:
					SetBlock(D3DXVECTOR3((60.0f+(Cnt*60.0f)) ,(cnt*60.0f), 0.0f), 60.0f, 60.0f, BLOCKTYPE_JUMP);
					break;
				case MAP_LADDER:
					SetBlock(D3DXVECTOR3((60.0f+(Cnt*60.0f)), (cnt*60.0f), 0.0f), 60.0f, 60.0f, BLOCKTYPE_LADDER);
					break;
				case MAP_ORI:
					SetBlock(D3DXVECTOR3((60.0f + (Cnt*60.0f)), (cnt*60.0f), 0.0f), 60.0f, 60.0f, BLOCKTYPE_ORI);
					break;
				case MAP_GOAL:
					SetItem(D3DXVECTOR3((60.0f+(Cnt*60.0f)),  (cnt*60.0f), 0.0f), ITEM_GOAL);
					break;
				case MAP_KEY:
					SetItem(D3DXVECTOR3((60.0f + (Cnt*60.0f)), (cnt*60.0f), 0.0f), ITEM_KEY);
					break;
				case MAP_PLAYER:
					break;
			}
		}
	}

	SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}