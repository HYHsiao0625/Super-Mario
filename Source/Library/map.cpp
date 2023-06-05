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
#include "goomba.h"
#include "mushroom.h"
#include "item.h"
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
	void Map::Updata(Mario mario)
	{
		vector<int> map_temp;
		int mario_x = (mario.GetLeft() - GetLeft()) / 32;
		int mario_y = (mario.GetTop() - 4) / 32;
		if (mario.IsHitbox() == true)
		{
			if (map_vector[mario_y][mario_x] == 2) {
				charactor[mario_y][mario_x].SetFrameIndexOfBitmap(1);
				map_temp.push_back(mario_y);
				map_temp.push_back(mario_x);
				resetblock_vector.push_back(map_temp);
			}
			else if (map_vector[mario_y][mario_x + 1] == 2) {
				charactor[mario_y][mario_x + 1].SetFrameIndexOfBitmap(1);
				map_temp.push_back(mario_y);
				map_temp.push_back(mario_x+1);
				resetblock_vector.push_back(map_temp);
			}
		}
	}

	vector<vector<int>> Map::GetMap()
	{
		return map_vector;
	}

	vector<vector<CMovingBitmap>> Map::GetMapcharactor()
	{
		return charactor;
	}

	CMovingBitmap Map::GetMapCharactor(int x, int y)
	{
		return charactor[x][y];
	}

	void Map::Load(int world, int level)
	{
		_world = world;
		_level = level;
		CMovingBitmap block;
		vector<int> map_temp;
		vector<CMovingBitmap> array1;
		if (world == 1 && level == 1)
		{
			width = 128;
			for (int i = 0; i < width; i++)
			{
				map_temp.push_back(0);
				array1.push_back(block);
			}
			for (int i = 0; i < height + 4; i++)
			{
				map_vector.push_back(map_temp);
				charactor.push_back(array1);
			}
			array1.clear();
			map_temp.clear();
			ifstream ifs("resources/map/1-1/1-1.map");
			for (int i = 0; i < height + 4; i++)
			{
				for (int j = 0; j < width; j++)
				{
					ifs >> map_vector[i][j];
					switch (map_vector[i][j])
					{
					case 0:
						charactor[i][j].LoadBitmapByString({
							"resources/empty.bmp",
							"resources/mushroom.bmp"
							}, RGB(146, 144, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 1:
						charactor[i][j].LoadBitmapByString({
							"resources/block.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 2:
						charactor[i][j].LoadBitmapByString({
							"resources/block2.bmp",
							"resources/block2_2.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 3:
						charactor[i][j].LoadBitmapByString({
							"resources/block3.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 4:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe1.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 5:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe2.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 6:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe3.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 7:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe4.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 8:
						charactor[i][j].LoadBitmapByString({
							"resources/flag1.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 9:
						charactor[i][j].LoadBitmapByString({
							"resources/flag2.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 10:
						charactor[i][j].LoadBitmapByString({
							"resources/flag3.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 11:
						charactor[i][j].LoadBitmapByString({
							"resources/flag4.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					default:
						break;
					}
				}
			}
			ifs.close();
		}
		else if (world == 1 && level == 2)
		{
			width = 32;
			for (int i = 0; i < width; i++)
			{
				map_temp.push_back(0);
				array1.push_back(block);
			}
			for (int i = 0; i < height + 4; i++)
			{
				map_vector.push_back(map_temp);
				charactor.push_back(array1);
			}
			array1.clear();
			map_temp.clear();
			ifstream ifs("resources/map/1-2/1-2.map");
			for (int i = 0; i < height + 4; i++)
			{
				for (int j = 0; j < width; j++)
				{
					ifs >> map_vector[i][j];
					switch (map_vector[i][j])
					{
					case 0:
						charactor[i][j].LoadBitmapByString({
							"resources/empty.bmp",
							"resources/mushroom.bmp"
							}, RGB(146, 144, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 1:
						charactor[i][j].LoadBitmapByString({
							"resources/block.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 2:
						charactor[i][j].LoadBitmapByString({
							"resources/block2.bmp",
							"resources/block2_2.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 3:
						charactor[i][j].LoadBitmapByString({
							"resources/block3.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 4:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe1.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 5:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe2.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 6:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe3.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 7:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe4.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 8:
						charactor[i][j].LoadBitmapByString({
							"resources/flag1.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 9:
						charactor[i][j].LoadBitmapByString({
							"resources/flag2.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 10:
						charactor[i][j].LoadBitmapByString({
							"resources/flag3.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					case 11:
						charactor[i][j].LoadBitmapByString({
							"resources/flag4.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 32, i * 32);
					default:
						break;
					}
				}
			}
			ifs.close();
		}
	}

	void Map::Show()
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				charactor[i][j].ShowBitmap();
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
		return width * 32;
	}

	void Map::SetTopLeft(int x, int y)
	{
		for (int i = 0; i < height + 2; i++)
		{
			for (int j = 0; j < width; j++)
			{
				charactor[i][j].SetTopLeft(x + j * 32, y + i * 32);
			}
		}
	}

	void Map::Reset()
	{
		for (int i = 0; i < height + 2; i++)
		{
			for (int j = 0; j < width; j++)
			{
				charactor[i][j].SetTopLeft(j * 32, i * 32);
			}
		}
		for (unsigned int i = 0; i <  resetblock_vector.size(); i++)
		{
			charactor[resetblock_vector[i][0]][resetblock_vector[i][1]].SetFrameIndexOfBitmap(0);
		}
	}

	void Map::Clear()
	{
		charactor.clear();

	}

	int Map::GetWorld()
	{
		return _world;
	}

	int Map::GetLevel()
	{
		return _level;
	}
}