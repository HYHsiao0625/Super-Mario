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
#include "mario.h"
#include "goomba.h"
#include "Shlwapi.h"
#include "Enemyfactor.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>
#include <typeinfo>


namespace game_framework
{
	Mario::Mario() :
		isCrouching(false),
		dead(false),
		isFlipped(false),
		isOnGround(false),
		horizontalSpeed(0),
		verticalSpeed(0),
		jump_timer(0),
		growth_timer(0),
		invincible_timer(0)
	{

	}

	bool Mario::GetDead() const
	{
		return dead;
	}

	int Mario::GetX()
	{
		return charactor.GetLeft();
	}

	int Mario::GetY()
	{
		return charactor.GetTop();
	}

	void Mario::UpData(Mario mario, Map map, Enemyfactor enemyfactor)
	{
		int mario_x = (map.GetLeft() - mario.GetLeft()) / 64;
		int mario_y = mario.GetTop() / 64;
		Collision(mario, map);
		//Collision(mario, goomba);
		Collision(enemyfactor);
		OnGround(mario, map);
		HitBox(mario, map);

		if (isHitbox == true)
		{
			verticalSpeed = 0;
			verticalSpeed += GRAVITY;
		}

		if (isOnGround == true)
		{
			verticalSpeed = 0;
		}
		else
		{
			if (GetStatus() == "jump")
			{
				verticalSpeed = -16;
			}
			else
			{
				verticalSpeed += GRAVITY;
				//verticalSpeed = 16;
			}
		}



		if (isCollision == true)
		{
			horizontalSpeed = 0;
		}

		if (isOnGround == true && mario.GetStatus() != "jump") {
			y = ((charactor.GetTop() + verticalSpeed) / 64) * 64;
		}
		else
		{
			y = charactor.GetTop() + verticalSpeed;
		}

		if (mario.GetTop() > 960)
		{
			mario.Die();
		}

		x = charactor.GetLeft() + horizontalSpeed;
		charactor.SetTopLeft(x, y);
	}

	void Mario::Reset()
	{
		dead = false;
	}
	void Mario::Show()
	{
		charactor.ShowBitmap();
	}

	void Mario::Load(vector<string> filepaths, COLORREF color)
	{
		charactor.LoadBitmapByString(filepaths, color);
	}

	int Mario::GetFrameIndexOfBitmap()
	{
		return charactor.GetFrameIndexOfBitmap();
	}

	void Mario::SetFrameIndexOfBitmap(int frameIndex)
	{
		charactor.SetFrameIndexOfBitmap(frameIndex);
	}

	void Mario::SetAnimation(int delay, bool _once)
	{
		charactor.SetAnimation(delay, _once);
	}
	void Mario::SetTopLeft(int x, int y)
	{
		charactor.SetTopLeft(x, y);
	}

	void Mario::SetStatus(string flags)
	{
		status = flags;
	}

	int Mario::GetTop()
	{
		return charactor.GetTop();
	}

	int Mario::GetLeft()
	{
		return charactor.GetLeft();
	}
	int Mario::GetHeight()
	{
		return charactor.GetHeight();
	}

	int Mario::GetWidth()
	{
		return charactor.GetWidth();
	}

	void Mario::SetVerticalSpeed(int value)
	{
		verticalSpeed = value;
	}

	void Mario::SetHorizontalSpeed(int value)
	{
		horizontalSpeed = value;
	}


	void Mario::Die()
	{
		dead = true;
	}

	int Mario::GetVerticalSpeed()
	{
		return verticalSpeed;
	}
	int Mario::GetHorizontalSpeed()
	{
		return horizontalSpeed;
	}

	int Mario::GetPressedKey()
	{
		return pressedKey;
	}

	string Mario::GetStatus()
	{
		return status;
	}

	bool Mario::IsKeyPressed()
	{
		return isKeyPressed;
	}

	void Mario::Collision(Mario mario, Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();

		int mario_x = (mario.GetLeft() - map.GetLeft()) / 64;
		int mario_y = mario.GetTop() / 64;

		//left collision
		if (mario.GetHorizontalSpeed() > 0)
		{
			int mario_x = (mario.GetLeft() - map.GetLeft()) / 64;
			if (map_vector[mario_y][mario_x + 1] != 0)
			{
				isCollision = true;
			}
		}//right collision
		else if (mario.GetHorizontalSpeed() < 0)
		{
			int mario_x = (mario.GetLeft() - map.GetLeft() - 16) / 64;
			if (map_vector[mario_y][mario_x] != 0)
			{
				isCollision = true;
			}
		}
		else
		{
			isCollision = false;
		}
	}
	/*void Mario::Collision(Mario mario, Goomba goomba)
	{
		if (goomba.charactor.IsOverlap(charactor, goomba.charactor) && goomba.GetStatus() != "dead") {
			if (-10 <= GetTop() + GetHeight() - goomba.GetTop()
				&& GetTop() + GetHeight() - goomba.GetTop() <= 0
				&& GetLeft() + GetWidth() > goomba.GetLeft()
				&& GetLeft() < goomba.GetLeft() + goomba.GetWidth()
				)
			{
				goomba.SetStatus("dead");
				goomba.SetFrameIndexOfBitmap(2);
			}
			else
			{
				Die();
			}
		}
	}
	*/
	void Mario::Collision(Enemyfactor enemyfactor) {
		std::vector<Enemy*>enemylist = enemyfactor.GetMonsterlist();
		if (GetY() > 960)
		{
			Die();
		}

		else {
			for (int i = 0; i < 5; i++) {
				if (enemylist[i]->charactor.IsOverlap(charactor, enemylist[i]->charactor) && enemylist[i]->GetStatus() != "dead") {
					if (-10 <= GetTop() + GetHeight() - enemylist[i]->GetTop()
						&& GetTop() + GetHeight() - enemylist[i]->GetTop() <= 0
						&& GetLeft() + GetWidth() > enemylist[i]->GetLeft()
						&& GetLeft() < enemylist[i]->GetLeft() + enemylist[i]->GetWidth()
						) {
					}
					else {
						Die();
					}
				}
			}
		}
	}

	void Mario::OnGround(Mario mario, Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int mario_x = (mario.GetLeft() - map.GetLeft()) / 64;
		int mario_y = mario.GetTop() / 64;
		if (mario.GetStatus() != "jump")
		{
			if (map_vector[mario_y + 1][mario_x] != 0)
			{
				isOnGround = true;
			}
			else if (map_vector[mario_y + 1][mario_x + 1] != 0 && map_vector[mario_y][mario_x + 1] == 0)
			{
				isOnGround = true;
			}
			else
			{
				isOnGround = false;
			}
		}
		else
		{
			isOnGround = false;
		}
	}

	void Mario::HitBox(Mario mario, Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int mario_x = (mario.GetLeft() - map.GetLeft()) / 64;
		int mario_y = (mario.GetTop() - 4) / 64;
		if (isOnGround == false)
		{
			if (map_vector[mario_y][mario_x] != 0)
			{
				isHitbox = true;
				SetStatus("hitbox");
			}
			else if (map_vector[mario_y][mario_x + 1] != 0 && map_vector[mario_y + 1][mario_x + 1] == 0)
			{
				isHitbox = true;
				SetStatus("hitbox");
			}
			else
			{
				isHitbox = false;
			}
		}
	}

	bool Mario::IsOnGround()
	{
		return isOnGround;
	}

	bool Mario::IsHitbox()
	{
		return isHitbox;
	}
}