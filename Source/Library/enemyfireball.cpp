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
#include "EnemyFireBall.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework
{
	void EnemyFireBall::UpData(Mario mario, Map map)
	{
		int x, y;
		Collision(map);
		if (cd != 0) {
			cd--;
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
		y = charactor.GetTop();
		charactor.SetTopLeft(x, y);

	}

	void EnemyFireBall::Reset()
	{

	}

	void EnemyFireBall::Load()
	{
		charactor.LoadBitmapByString({
			"resources/enemyfireball.bmp",
			}, RGB(146, 144, 255));
		charactor.SetAnimation(100, false);
	}

	void EnemyFireBall::Die()
	{
		isdead = true;
	}

	bool EnemyFireBall::IsDead()
	{
		return isdead;
	}

	void EnemyFireBall::Collision(Map map)
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