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
#include "goomba.h"
#include "mushroom.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework
{
	Mushroom::Mushroom()
	{

	}

	Mushroom::~Mushroom()
	{

	}
	void Mushroom::UpData(Mario mario, Map map)
	{
		Collision(map);
		if (isCollision == true)
		{
			horizontalSpeed *= -1;
			isCollision = false;
		}
		charactor.SetTopLeft(charactor.GetLeft() + horizontalSpeed, charactor.GetTop() + verticalSpeed);
	}
	void Mushroom::Collision(Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int mario_y = charactor.GetTop() / 64;

		//left collision
		if (horizontalSpeed > 0)
		{
			int mario_x = (charactor.GetLeft() - map.GetLeft()) / 64;
			if (map_vector[mario_y][mario_x + 1] != 0)
			{
				isCollision = true;
			}
		}//right collision
		else if (horizontalSpeed < 0)
		{
			int mario_x = (charactor.GetLeft() - map.GetLeft()) / 64;
			if (map_vector[mario_y][mario_x] != 0)
			{
				isCollision = true;
			}
		}
	}

	void Mushroom::Load()
	{
		charactor.LoadBitmapByString({
			"resources/mushroom.bmp",
			"resources/empty.bmp"
			}, RGB(146, 144, 255));
	}

}