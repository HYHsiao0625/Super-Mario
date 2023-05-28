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
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework
{
	Goomba::Goomba() : Enemy()
	{

	}
	Goomba::~Goomba()
	{

	}
	void Goomba::UpData(vector<Enemy*> monster_list, Mario mario, Map map)
	{
		Collision(map);
		Collision(monster_list);

		OnGround(map);
		if (isCollision == true)
		{
			horizontalSpeed *= -1;
			isCollision = false;
		}
		if (-10 <= mario.GetTop() + mario.GetHeight() - GetTop()
			&& mario.GetTop() + mario.GetHeight() - GetTop() <= 0
			&& mario.GetLeft() + mario.GetWidth() > GetLeft()
			&& mario.GetLeft() < GetLeft() + GetWidth() && isDead == false
			) {
			horizontalSpeed = 0;
			Die();
		}
		if (isOnGround == true)
		{
			verticalSpeed = 0;
		}
		else
		{
			verticalSpeed += 1;
		}
		if (mario.GetHorizontalSpeed() > 0)
		{
			if (map.GetWidth() + map.GetLeft() > 1600 && mario.GetLeft() > 480)
			{
				SetTopLeft(GetLeft() - mario.GetHorizontalSpeed(), GetTop());
			}
		}
		else if (mario.GetHorizontalSpeed() < 0)
		{
			if (map.GetLeft() < 0 && mario.GetLeft() < 256)
			{
				SetTopLeft(GetLeft() - mario.GetHorizontalSpeed(), GetTop());
			}
		}
		charactor.SetTopLeft(charactor.GetLeft() + horizontalSpeed, charactor.GetTop() + verticalSpeed);

	}

	void Goomba::Reset()
	{

	}

	void Goomba::Load()
	{
		charactor.LoadBitmapByString({
			"resources/goomba1.bmp",
			"resources/goomba2.bmp",
			"resources/goomba3.bmp",
			"resources/empty.bmp"
			}, RGB(146, 144, 255));

	}

	void Goomba::Die()
	{
		//charactor.SetFrameIndexOfBitmap(3);
		isDead = true;
	}

	bool Goomba::IsDead()
	{
		return isDead;
	}
	void Goomba::Collision(Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int mario_y = GetTop() / 64;

		//left collision
		if (horizontalSpeed > 0)
		{
			int mario_x = (GetLeft() - map.GetLeft()) / 64;
			if (map_vector[mario_y][mario_x + 1] != 0)
			{
				isCollision = true;
			}
		}//right collision
		else if (horizontalSpeed < 0)
		{
			int mario_x = (GetLeft() - map.GetLeft()) / 64;
			if (map_vector[mario_y][mario_x] != 0)
			{
				isCollision = true;
			}
		}
	}
	void Goomba::Collision(vector<Enemy*> monster_list)
	{

		for (auto enemy : monster_list) {
			if (charactor.IsOverlap(charactor, enemy->charactor) && (charactor.GetLeft() != enemy->GetLeft()) && enemy->IsDead() == false)
			{
				if (enemy->charactor.GetFrameIndexOfBitmap() == 2) {
					horizontalSpeed = 0;
					Die();
				}
				else if (enemy->IsDead() == false) {
					isCollision = true;
				}
			}
		}
	}
	void Goomba::OnGround(Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int goomba_x = (GetLeft() - map.GetLeft() - 48) / 64;
		int goomba_y = GetTop() / 64;
		if (GetTop() < 770) {
			if (map_vector[goomba_x + 1][goomba_y] != 0)
			{
				isOnGround = true;
			}
			else if (map_vector[goomba_y + 1][goomba_x + 1] != 0 && map_vector[goomba_y][goomba_x + 1] == 0)
			{
				isOnGround = true;
			}
			else
			{
				isOnGround = false;
			}
		}
	}


}