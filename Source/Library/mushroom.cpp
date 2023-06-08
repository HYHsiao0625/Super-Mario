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
#include "Mushroom.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework
{
	void Mushroom::UpData(Mario mario, Map map)
	{
		int x, y;
		Collision(map);
		OnGround(map);
		if (isCollision == true)
		{
			horizontalSpeed *= -1;
			isCollision = false;
		}
		if (mario.GetLeft() + mario.GetWidth() > GetLeft()
			&& mario.GetLeft() < GetLeft() + GetWidth()
			&& mario.GetTop() + mario.GetHeight() > GetTop()
			&& mario.GetTop() < GetTop() + GetHeight()) {
			cd--;
			horizontalSpeed = 0;
			isDead = true;
			if (cd == 0) {
				Die();
			}
		}

		if (isOnGround == true)
		{
			verticalSpeed = 0;
		}
		else
		{
			verticalSpeed += 1;
		}

		if (verticalSpeed > 16)
		{
			verticalSpeed = 16;
		}

		x = charactor.GetLeft() + horizontalSpeed;

		if (isOnGround == true)
		{
			y = ((charactor.GetTop() + verticalSpeed) / 32) * 32;
		}
		else
		{
			y = charactor.GetTop() + verticalSpeed;
		}

		if (GetTop() > 480)
		{
			Die();
		}

		charactor.SetTopLeft(x, y);

	}

	void Mushroom::Reset()
	{

	}

	void Mushroom::Load()
	{
		charactor.LoadBitmapByString({
			"resources/Mushroom.bmp",
			}, RGB(146, 144, 255));
	}

	void Mushroom::Die()
	{
		isdead = true;
	}

	bool Mushroom::IsDead()
	{
		return isdead;
	}

	void Mushroom::Collision(Map map)
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
	void Mushroom::OnGround(Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int mushroom_x = (GetLeft() - map.GetLeft()) / 32;
		int mushroom_y = GetTop() / 32;
		
		if (map_vector[mushroom_y + 1][mushroom_x] != 0)
		{
			isOnGround = true;
		}
		else if (map_vector[mushroom_y + 1][mushroom_x + 1] != 0 && map_vector[mushroom_y][mushroom_x + 1] == 0)
		{

			isOnGround = true;
		}
		else
		{
			isOnGround = false;
		}
		
	}

	
}