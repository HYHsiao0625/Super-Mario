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
#include "Axe.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework
{
	void Axe::UpData(Mario& mario, Map& map)
	{
		int x, y;
		Collision(map);
		if (cd != 0) {
			cd--;
		}
		if (cd >= 5) {
			verticalSpeed = -20;
		}
		else {
			verticalSpeed = 2;
		}
		if (charactor.GetLeft() == 0)
		{
			Die();
		}
		if (isCollision == true)
		{
			Die();
		}

		x = charactor.GetLeft() + horizontalSpeed;
		y = charactor.GetTop() + verticalSpeed;
		charactor.SetTopLeft(x, y);

	}

	void Axe::Reset()
	{

	}

	void Axe::Load()
	{
		charactor.LoadBitmapByString({
			"resources/axe1.bmp",
			"resources/axe2.bmp",
			"resources/axe3.bmp",
			"resources/axe4.bmp",
			}, RGB(146, 144, 255));
		charactor.SetAnimation(100, false);
	}

	void Axe::Die()
	{
		isdead = true;
	}

	bool Axe::IsDead()
	{
		return isdead;
	}

	void Axe::Collision(Map& map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int mario_x = (GetLeft() - map.GetLeft()) / 32;
		int mario_y = GetTop() / 32;
		if (mario_x > 0 && mario_y > 0) {
			//left collision
			if (horizontalSpeed > 0)
			{
				int mario_x = (GetLeft() - map.GetLeft()) / 32;
				if (map_vector[mario_y][mario_x + 1] != 0)
				{
					isCollision = true;
				}
			}//right collision
			else if (horizontalSpeed < 0)
			{
				int mario_x = (GetLeft() - map.GetLeft()) / 32;
				if (map_vector[mario_y][mario_x] != 0)
				{
					isCollision = true;
				}
			}
		}
	}


}