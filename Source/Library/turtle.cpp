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
	void Turtle::UpData(Mario mario, Map map)
	{
		Collision(map);
		if (isCollision == true)
		{
			horizontalSpeed *= -1;
			isCollision = false;
		}
		if (-10 <= mario.GetTop() + mario.GetHeight() - GetTop()
			&& mario.GetTop() + mario.GetHeight() - GetTop() <= 0
			&& mario.GetLeft() + mario.GetWidth() > GetLeft()
			&& mario.GetLeft() < GetLeft() + GetWidth() && status != "dead"
			) {
			status = "dead";
			SetTopLeft(GetLeft(), GetTop() + 32);
			horizontalSpeed = 0;
			Die();
		}
		else if (status == "dead") {
			if (mario.charactor.IsOverlap(charactor, mario.charactor)) {
				if (mario.GetLeft() < GetLeft() && on_kick == 1) {
					horizontalSpeed = 10;
				}
				else if(mario.GetLeft() > GetLeft() && on_kick == 1){
					horizontalSpeed = -10;
				}
				else {
					on_kick = 1;
				}
			}
		}
		charactor.SetTopLeft(charactor.GetLeft() + horizontalSpeed, charactor.GetTop() + verticalSpeed);

	}
	void Turtle::Collision(Map map)
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
		charactor.SetFrameIndexOfBitmap(2);
	}
}