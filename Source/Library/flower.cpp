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
#include "Flower.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>
#include <ctime>

namespace game_framework
{
	void Flower::UpData(Mario mario, Map map)
	{
		//Collision(map);
		int mario_x = (mario.GetLeft() - map.GetLeft()) / 64;
		int mario_y = (mario.GetTop() - 4) / 64;
		int enemy_x = (GetLeft() - map.GetLeft()) / 64;
		int enemy_y = GetTop() / 64;
		if (abs(mario_x - enemy_x)<=1 && abs(mario_y - enemy_y) <= 1)
		{
			trigger = 1;
		}
		if (trigger == 1) {
			if (GetTop() == 570 && active == 1) {
				verticalSpeed = -1;
			}
			else if (GetTop() == 510) {
				verticalSpeed = 1;
				active = 0;
			}
			else if (GetTop() == 570 && active == 0) {
				verticalSpeed = 0;
			}
			charactor.SetTopLeft(charactor.GetLeft(), charactor.GetTop() + verticalSpeed);
		}
	}
	void Flower::Collision(Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int enemy_x = (x - map.GetLeft()) / 64;
		int enemy_y = y / 64;

		if (horizontalSpeed > 0)
		{
			if (map_vector[enemy_y][enemy_x + 1] != 0)
			{
				isCollision = true;
			}

		}
		else if (horizontalSpeed < 0)
		{
			if (map_vector[enemy_y][enemy_x] != 0)
			{
				isCollision = true;
			}
		}
		else
		{
			isCollision = false;
		}
	}

	void Flower::Load()
	{
		charactor.LoadBitmapByString({
			"resources/goomba1.bmp",
			"resources/goomba2.bmp",
			"resources/goomba3.bmp",
			"resources/empty.bmp"
			}, RGB(146, 144, 255));
	}
}