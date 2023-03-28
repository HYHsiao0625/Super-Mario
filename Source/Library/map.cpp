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
		for (int i = 0; i < 211; i++)
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
			for (int j = 0; j < 211; j++)
			{
				switch (map1_1[i][j])
				{
				case 0:
					charactor[i][j].LoadBitmapByString({
						"resources/reject.bmp",
						}, RGB(92,148,252));
					charactor[i][j].SetTopLeft(j * 64 , i * 64);
				case 1:
					charactor[i][j].LoadBitmapByString({
						"resources/block.bmp"
						});
					charactor[i][j].SetTopLeft(j * 64, i * 64);
				case 2:
					charactor[i][j].LoadBitmapByString({
						"resources/block2.bmp"
						});
					charactor[i][j].SetTopLeft(j * 64, i * 64);
				case 3:
					charactor[i][j].LoadBitmapByString({
						"resources/block3.bmp"
						});
					charactor[i][j].SetTopLeft(j * 64, i * 64);
				case 4:
					charactor[i][j].LoadBitmapByString({
						"resources/pipe_1.bmp"
						},RGB(92,148,252));
					charactor[i][j].SetTopLeft(j * 64, i * 64);
				case 5:
					charactor[i][j].LoadBitmapByString({
						"resources/pipe_2.bmp"
						}, RGB(92, 148, 252));
					charactor[i][j].SetTopLeft(j * 64, i * 64);
				case 6:
					charactor[i][j].LoadBitmapByString({
						"resources/pipe_3.bmp"
						}, RGB(92, 148, 252));
					charactor[i][j].SetTopLeft(j * 64, i * 64);
				case 7:
					charactor[i][j].LoadBitmapByString({
						"resources/pipe_4.bmp"
						}, RGB(92, 148, 252));
					charactor[i][j].SetTopLeft(j * 64, i * 64);
				case 8:
					charactor[i][j].LoadBitmapByString({
						"resources/flag_1.bmp"
						}, RGB(92, 148, 252));
					charactor[i][j].SetTopLeft(j * 64, i * 64);
				case 9:
					charactor[i][j].LoadBitmapByString({
						"resources/flag_2.bmp"
						}, RGB(92, 148, 252));
					charactor[i][j].SetTopLeft(j * 64, i * 64);
				case 10:
					charactor[i][j].LoadBitmapByString({
						"resources/flag_3.bmp"
						}, RGB(92, 148, 252));
					charactor[i][j].SetTopLeft(j * 64, i * 64);
				case 11:
					charactor[i][j].LoadBitmapByString({
						"resources/flag_4.bmp"
						}, RGB(92, 148, 252));
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
			for (int j = 0; j < 211; j++)
			{
				charactor[i][j].ShowBitmap();
			}
		}
	}

	void Map::SetTopLeft(int x, int y)
	{
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 211; j++)
			{
				charactor[i][j].SetTopLeft(charactor[i][j].GetLeft() - x, charactor[i][j].GetTop() - y);
			}
		}
	}
	bool Map::Isoverlamp(Mario mario ,CMovingBitmap floor)
	{
		int mario_y = mario.GetTop() / 64;
		int mario_x = (-1 * floor.GetLeft() + mario.GetLeft())/ 64;
		if (mario.GetStatus()=="rightwalk") {
			if (map1_1[mario_y][mario_x+1] == 0) {
				return false;
			}
		}
		if (mario.GetStatus() == "leftwalk") {
			if (map1_1[mario_y][mario_x] == 0) {
				return false;
			}
		}
		if (mario.GetStatus() == "jump") {
			if (map1_1[mario_y][mario_x-1] == 0 ||map1_1[mario_y][mario_x] == 0) {
				return false;
			}
		}
		return true;
		
	}
}