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

	vector<vector<int>> Map::GetMap()
	{
		return map;
	}

	void Map::Load(int world, int level)
	{
		CMovingBitmap block;
		if (world == 1 && level == 1)
		{
			for (int i = 0; i < 211; i++)
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
				for (int j = 0; j < 211; j++)
				{
					ifs >> map[i][j];
					switch (map[i][j])
					{
					case 0:
						charactor[i][j].LoadBitmapByString({
							"resources/empty.bmp",
							}, RGB(146, 144, 255));
						charactor[i][j].SetTopLeft(j * 64, i * 64);
					case 1:
						charactor[i][j].LoadBitmapByString({
							"resources/block.bmp"
							}, RGB(148, 148, 255));
						charactor[i][j].SetTopLeft(j * 64, i * 64);
					case 2:
						charactor[i][j].LoadBitmapByString({
							"resources/block2.bmp"
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
							"resources/pipe_4.bmp"
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
			for (int j = 0; j < 211; j++)
			{
				charactor[i][j].ShowBitmap();
			}
		}
	}
	void Map::initalize()
	{
		for (int i = 0; i < 17; i++)
		{
			for (int j = 0; j < 211; j++)
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
			for (int j = 0; j < 211; j++)
			{
				charactor[i][j].SetTopLeft(x + j * 64, y + i * 64);
			}
		}
	}
	/*bool Map::Isoverlamp(Mario mario, CMovingBitmap floor)
	{
		int mario_y = mario.GetTop() / 64;
		int mario_x = (-1 * floor.GetLeft() + mario.GetLeft()) / 64;
		if (mario.GetStatus() == "rightwalk") {
			if (map1_1[mario_y][mario_x + 1] != 0) {
				return true;
			}
		}
		if (mario.GetStatus() == "leftwalk") {
			if (map1_1[mario_y][mario_x] != 0) {
				return true;
			}
		}
		if (mario.GetJump()) {
			if (map1_1[mario_y][mario_x+1] != 0 || map1_1[mario_y][mario_x] != 0) {
				return true;
			}
		}
		return false;
	}
	bool Map::Ontheground(Mario mario, CMovingBitmap floor)
	{
		int mario_y = mario.GetTop() / 64;
		int mario_x = (-1 * floor.GetLeft() + mario.GetLeft()) / 64;
		if (map1_1[mario_y+1][mario_x+1] != 0 || map1_1[mario_y+1][mario_x] != 0) {
			return true;
		}
		else {
			return false;
		}
	}*/
}