//#define	 INITGUID
#include "stdafx.h"
#include "../Core/game.h"
#include "../Core/MainFrm.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <direct.h>
#include <string.h>
#include "audio.h"
#include "gameutil.h"
#include "gamecore.h"
#include "map.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework
{
	Map::Map()
	{

	}

	Map::~Map()
	{

	}
	void Map::Updata()
	{
		
	}

	void Map::Load()
	{
		CMovingBitmap block;
		for (int i = 0; i < 64; i++)
		{
			array1.push_back(block);
		}
		for (int i = 0; i < 15; i++)
		{
			charactor.push_back(array1);
		}
		array1.clear();
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 64; j++)
			{
				switch (map1_1[i][j])
				{
				case 0:
					charactor[i][j].LoadBitmapByString({
						"resources/reject.bmp",
						}, RGB(146, 144, 255));
					charactor[i][j].SetTopLeft(j * 64 , i * 64);
				case 1:
					charactor[i][j].LoadBitmapByString({
						"resources/block.bmp"
						});
					charactor[i][j].SetTopLeft(j * 64, i * 64);
				default:
					break;
				}
				wight = j;
			}
		}
		
	}

	void Map::Show()
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 64; j++)
			{
				charactor[i][j].ShowBitmap();
			}
		}
	}

	void Map::SetTopLeft(int x, int y)
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 64; j++)
			{
				charactor[i][j].SetTopLeft(charactor[i][j].GetLeft() - x, charactor[i][j].GetTop() - y);
			}
		}
	}
}