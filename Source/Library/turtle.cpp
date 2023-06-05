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
#include "Turtle.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework
{
	Turtle::Turtle() : Enemy() {
	}
	Turtle::~Turtle() {
	}
	void Turtle::UpData(vector<Enemy*> monster_list, Mario mario, Map map)
	{
		int x, y;
		Collision(map);
		OnGround(map);
		Collision(monster_list);

		if (isCollision == true)
		{
			if (isDead == false)
			{
				horizontalSpeed *= -1;
				isCollision = false;
			}
			else
			{
				horizontalSpeed = 0;
				Die();
				charactor.SetFrameIndexOfBitmap(3);
			}
		}
		if (-10 <= mario.GetTop() + mario.GetHeight() - GetTop()
			&& mario.GetTop() + mario.GetHeight() - GetTop() <= 0
			&& mario.GetLeft() + mario.GetWidth() > GetLeft()
			&& mario.GetLeft() < GetLeft() + GetWidth() && isKickAble == false)
		{
			charactor.SetFrameIndexOfBitmap(2);
			isKickAble = true;
			SetTopLeft(GetLeft(), GetTop() + 16);
			horizontalSpeed = 0;
		}
		if (isKickAble == true) {
			if (mario.charactor.IsOverlap(charactor, mario.charactor)) 
			{
				if (isKickAble == true)
				{
					if (mario.GetLeft() < GetLeft())
					{
						horizontalSpeed = 12;
					}
					else if (mario.GetLeft() > GetLeft()) {
						horizontalSpeed = -12;
					}
					isDead = true;
				}
			}
			if (horizontalSpeed == 12 || horizontalSpeed == -12) 
			{
				for (auto enemy : monster_list) 
				{
					if (enemy->charactor.IsOverlap(enemy->charactor, charactor) && (charactor.GetLeft() != enemy->GetLeft())) 
					{
						enemy->Die();
						Die();
					}
				}
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
			if (isKickAble == false)
			{
				y = ((charactor.GetTop() + verticalSpeed) / 32) * 32 + 16;
			}
			else
			{
				y = ((charactor.GetTop() + verticalSpeed) / 32) * 32;
			}
			
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

	void Turtle::Reset()
	{

	}

	void Turtle::Load()
	{
		charactor.LoadBitmapByString({
			"resources/turtle1.bmp",
			"resources/turtle2.bmp",
			"resources/turtle3.bmp",
			"resources/empty.bmp"
			}, RGB(146, 144, 255));
	}

	void Turtle::Die()
	{
		charactor.SetFrameIndexOfBitmap(3);
		isdead = true;
	}

	bool Turtle::IsDead()
	{
		return isdead;
	}

	void Turtle::Collision(Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int turtle_y = GetTop() / 32;

		//left collision
		if (horizontalSpeed > 0)
		{
			int turtle_x = (GetLeft() - map.GetLeft()) / 32;
			if (map_vector[turtle_y][turtle_x + 1] != 0)
			{
				isCollision = true;
			}
			if (GetLeft() - map.GetLeft() == 0)
			{
				isCollision = true;
			}
		}//right collision
		else if (horizontalSpeed < 0)
		{
			int turtle_x = (GetLeft() - map.GetLeft()) / 32;

			if (map_vector[turtle_y][turtle_x] != 0)
			{
				isCollision = true;
			}
			if (GetLeft() - map.GetLeft() == 0)
			{
				isCollision = true;
			}
		}
	}
	void Turtle::Collision(vector<Enemy*> monster_list) {
		for (auto enemy : monster_list) {
			if (charactor.IsOverlap(charactor, enemy->charactor) && (charactor.GetLeft() != enemy->GetLeft()) && enemy->IsDead() == false)
			{
				isCollision = true;
			}
		}
	}
	void Turtle::OnGround(Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int turtle_x = (GetLeft() - map.GetLeft()) / 32;
		int turtle_y = (GetTop() + 16) / 32;
		
		if (map_vector[turtle_y + 1][turtle_x] != 0)
		{
			isOnGround = true;
		}
		else if (map_vector[turtle_y + 1][turtle_x + 1] != 0 && map_vector[turtle_y][turtle_x + 1] == 0)
		{
			isOnGround = true;
		}
		else
		{
			isOnGround = false;
		}
	}
}