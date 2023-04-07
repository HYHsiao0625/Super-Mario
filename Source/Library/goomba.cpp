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
	void Goomba::UpData(Mario mario,Map map)
	{
		//Collision(map);
		
		if (this->y - mario.GetLeft() <= 512 && status != "dead")
		{
			horizontalSpeed=-4;
		}
		else
		{
			horizontalSpeed=0;
		}
		if (isCollision == true) {
			horizontalSpeed *= -1;
		}
		charactor.SetTopLeft(charactor.GetLeft() + horizontalSpeed, charactor.GetTop() + verticalSpeed);
	}
	void Goomba::Collision(Map map)
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
}