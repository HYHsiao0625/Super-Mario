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
#include "Fireball.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework
{
	void Fireball::UpData(Mario mario, Map map)
	{
		int x, y;
		Collision(map);
		if (cd != 0) {
			cd--;
		}
		if (isCollision == true)
		{
			Die();
		}

		x = charactor.GetLeft() + horizontalSpeed;
		y = charactor.GetTop();
		charactor.SetTopLeft(x, y);

	}

	void Fireball::Reset()
	{

	}

	void Fireball::Load()
	{
		charactor.LoadBitmapByString({
			"resources/Mushroom.bmp",
			"resources/empty.bmp"
			}, RGB(146, 144, 255));
	}

	void Fireball::Die()
	{
		charactor.SetFrameIndexOfBitmap(1);
		isdead = true;
	}

	bool Fireball::IsDead()
	{
		return isdead;
	}

	void Fireball::Collision(Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int mario_y = GetTop() / 32;

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