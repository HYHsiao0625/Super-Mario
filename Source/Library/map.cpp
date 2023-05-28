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
#include <random>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>


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

		int mario_x = (mario.GetLeft() - GetLeft()) / 64;
		int mario_y = (mario.GetTop() - 4) / 64;
		if (mario.IsHitbox() == true)
		{
			if (map_vector[mario_y][mario_x] == 2 || map_vector[mario_y -1][mario_x] == 2) {
				charactor[mario_y-1][mario_x].SetFrameIndexOfBitmap(1);
				charactor[mario_y][mario_x].SetFrameIndexOfBitmap(1);
			}
			else if (map_vector[mario_y][mario_x + 1] == 2 || map_vector[mario_y - 1][mario_x+1] == 2) {
				charactor[mario_y-1][mario_x + 1].SetFrameIndexOfBitmap(1);
				charactor[mario_y][mario_x + 1].SetFrameIndexOfBitmap(1);
			}
		}
		if (mario.GetHorizontalSpeed() > 0)
		{
			if (GetWidth() + GetLeft() > 1600 && mario.GetLeft() > 480)
			{
				mario.SetTopLeft(mario.GetLeft(), mario.GetTop());
				SetTopLeft(GetLeft() - mario.GetHorizontalSpeed(), GetTop());
			}
		}
		else if (mario.GetHorizontalSpeed() < 0)
		{
			if (GetLeft() < 0 && mario.GetLeft() < 256)
			{
				mario.SetTopLeft(mario.GetLeft(), mario.GetTop());
				SetTopLeft(GetLeft() - mario.GetHorizontalSpeed(), GetTop());
			}
		}
	}

	vector<vector<int>> Map::GetMap()
	{
		return map_vector;
	}
	vector<vector<CMovingBitmap>> Map::GetMapcharactor() {
		return charactor;
	}
	CMovingBitmap Map::GetMapCharactor(int x, int y)
	{
		return charactor[x][y];
	}

#include <fstream>
#include <vector>

	void Map::Load(int world, int level)
	{
		CMovingBitmap block;
		if (world == 1 && level == 1)
		{
			std::ifstream ifs("resources/map/1-1.map");
			std::string line;
			while (std::getline(ifs, line))
			{
				std::vector<int> row;
				std::istringstream iss(line);
				int value;
				while (iss >> value)
				{
					row.push_back(value);
				}
				map_vector.push_back(row);
				charactor.push_back(std::vector<CMovingBitmap>(row.size(), block));
			}
			ifs.close();

			// 设置每个字符的位图和位置
			for (unsigned int i = 0; i < map_vector.size(); i++)
			{
				for (unsigned int j = 0; j < map_vector[i].size(); j++)
				{
					
					switch (map_vector[i][j])
					{
					case 0:
						charactor[i][j].LoadBitmapByString({
							"resources/empty.bmp",
							"resources/empty.bmp"
							}, RGB(146, 144, 255));
						break;
					case 1:
						charactor[i][j].LoadBitmapByString({
							"resources/block.bmp"
							}, RGB(148, 148, 255));
						break;
					case 2:
						charactor[i][j].LoadBitmapByString({
							"resources/block2.bmp",
							"resources/block2_2.bmp"
							}, RGB(148, 148, 255));
						break;
					case 3:
						charactor[i][j].LoadBitmapByString({
							"resources/block3.bmp"
							}, RGB(148, 148, 255));
						break;
					case 4:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe1.bmp"
							}, RGB(148, 148, 255));
						break;
					case 5:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe2.bmp"
							}, RGB(148, 148, 255));
						break;
					case 6:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe3.bmp"
							}, RGB(148, 148, 255));
						break;
					case 7:
						charactor[i][j].LoadBitmapByString({
							"resources/pipe4.bmp"
							}, RGB(148, 148, 255));
						break;
					case 8:
						charactor[i][j].LoadBitmapByString({
							"resources/flag1.bmp"
							}, RGB(148, 148, 255));
						break;
					case 9:
						charactor[i][j].LoadBitmapByString({
							"resources/flag2.bmp"
							}, RGB(148, 148, 255));
						break;
					default:
						break;
					charactor[i][j].SetTopLeft(j * 64, i * 64);
					}
				}
			}
		}
	}


	void Map::Show()
	{
		for (int i = 0; i < height + 2; i++)
		{
			for (unsigned int j = 0; j < map_vector[0].size(); j++)
			{
				charactor[i][j].ShowBitmap();
			}
		}
	}
	void Map::initalize()
	{
		for (int i = 0; i < height + 2; i++)
		{
			for (unsigned int j = 0; j < map_vector[0].size(); j++)
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
		for (int i = 0; i < height + 2; i++)
		{
			for (unsigned int j = 0; j < map_vector[0].size(); j++)
			{
				charactor[i][j].SetTopLeft(x + j * 64, y + i * 64);
			}
		}
	}
}