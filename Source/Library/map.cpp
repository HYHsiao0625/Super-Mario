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
#include <fstream>
#include <random>


namespace game_framework
{
	Map::Map()
	{

	}

	Map::~Map()
	{

	}
	void Map::Updata(int mario_x,int mario_y)
	{

	}

	vector<vector<int>> Map::GetMap()
	{
		return map;
	}
	vector<vector<CMovingBitmap>> Map::GetMapCharactor()
	{
		return charactor;
	}

	void Map::Load(int world, int level)
	{
		CMovingBitmap block;
		if (world == 1 && level == 1)
		{
			for (int i = 0; i < 16; i++)
			{
				map_temp.push_back(0);
				array1.push_back(block);
			}
			for (int i = 0; i < 17; i++)
			{
				map.push_back(map_temp);
				charactor.push_back(array1);
			}
			array1.clear();
			map_temp.clear();
			ifstream ifs("resources/map/1-1.map");
			for (int i = 0; i < 17; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					ifs >> map[i][j];
					switch (map[i][j])
					{
					case 0:
						charactor[i][j].LoadBitmapByString({
							"resources/empty.bmp",
							"resources/mushroom.bmp"
							}, RGB(146, 144, 255));
						charactor[i][j].SetTopLeft(j * 64, i * 64);
					case 1:
						charactor[i][j].LoadBitmapByString({
							"resources/block.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 64, i * 64);
					case 2:
						charactor[i][j].LoadBitmapByString({
							"resources/block2.bmp",
							"resources/block2_2.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 64, i * 64);
					case 3:
						charactor[i][j].LoadBitmapByString({
							"resources/block3.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 64, i * 64);
					case 4:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe1.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 64, i * 64);
					case 5:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe2.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 64, i * 64);
					case 6:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe3.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 64, i * 64);
					case 7:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe4.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 64, i * 64);
					case 8:
						charactor[i][j].LoadBitmapByString({
							"resources/flag1.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 64, i * 64);
					case 9:
						charactor[i][j].LoadBitmapByString({
							"resources/flag2.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 64, i * 64);
					default:
						break;
					}
					width = j;
				}
				
			}
			ifs.close();
		}
	}

	void Map::Show()
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				charactor[i][j].ShowBitmap();
			}
		}
	}
	void Map::initalize()
	{
		for (int i = 0; i < 17; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				charactor[i][j].SetTopLeft(j * 64, i * 64);
			}
		}
	}
	int Map::GetTop()
	{
		return charactor[0][0].GetTop();
	}

	int Map::GetLeft()
	{
		return charactor[0][0].GetLeft();
	}

	int Map::GetWidth()
	{
		return width * 64;
	}

	void Map::SetTopLeft(int x, int y)
	{
		for (int i = 0; i < 17; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				charactor[i][j].SetTopLeft(x + j * 64, y + i * 64);
			}
		}
	}
}