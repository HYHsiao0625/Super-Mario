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
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework
{
	Mario::Mario() :
		crouching(false),
		dead(false),
		flipped(false),
		onGround(false),
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

	void Mario::UpData(Mario mario, Map map)
	{
		int mario_y = mario.GetTop() / 64;
		Collision(mario, map);
		if (onGround == true)
		{
			verticalSpeed = 0;
		}
		else
		{
			if (GetStatus() == "jump" && GetHitbox() == "false")
			{
				verticalSpeed = -32;
			}
			else if (mario.GetHitbox() == "true")
			{
				SetStatus("stand");
				verticalSpeed = 32;
			}
			else
			{
				verticalSpeed += GRAVITY;
			}
		}

		if (isCollision == true)
		{
			horizontalSpeed = 0;
		}

		if (mario.GetTop() > 960)
		{
			mario.SetDie(true);
		}
		if (onGround == true && mario.GetStatus() != "jump") {
			y = (charactor.GetTop() + verticalSpeed) / 64 * 64;
		}
		else 
		{
			y = charactor.GetTop() + verticalSpeed;
		}

		x = charactor.GetLeft() + horizontalSpeed;
		charactor.SetTopLeft(x, y);
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
	bool Mario::GetJump()
	{
		return jump;
	}

	void Mario::SetVerticalSpeed(int value)
	{
		verticalSpeed = value;
	}

	void Mario::SetHorizontalSpeed(int value)
	{
		horizontalSpeed = value;
	}


	void Mario::SetDie(bool flag)
	{
		dead = flag;
	}
	void Mario::SetStatus(string action)
	{
		status = action;
	}
	void Mario::SetJump(bool status) {
		jump = status;
	}

	int Mario::GetVerticalSpeed()
	{
		return verticalSpeed;
	}
	int Mario::GetHorizontalSpeed()
	{
		return horizontalSpeed;
	}

	bool Mario::GetDie()
	{
		return dead;
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

		if (mario.GetHorizontalSpeed() > 0)
		{
			int mario_x = (mario.GetLeft() - map.GetLeft()) / 64;
			if (map_vector[mario_y][mario_x + 1] != 0)
			{
				isCollision = true;
			}
		}
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
		if (mario.GetStatus() != "jump")
		{
			if (map_vector[mario_y + 1][mario_x] != 0 && map_vector[mario_y ][mario_x] == 0)
			{
				onGround = true;
			}
			else if (map_vector[mario_y + 1][mario_x + 1] != 0 && map_vector[mario_y ][mario_x + 1]==0)
			{
				onGround = true;
			}
			else
			{
				onGround = false;
			}
		}
		mario_y = (mario.GetTop() - 16) / 64;
		if (map_vector[mario_y][mario_x] != 0)
		{
			hitbox = true;
		}
		else if (map_vector[mario_y][mario_x + 1] != 0)
		{
			hitbox = true;
		}
		else
		{
			hitbox = false;
		}
	}

	void Mario::SetOnGround(bool status)
	{
		onGround = status;
	}

	string Mario::GetOnGround()
	{
		if (onGround == true)
		{
			return "true";
		}
		else
		{
			return "false";
		}
	}
	void Mario::SetHitbox(bool status)
	{
		hitbox = status;
	}

	string Mario::GetHitbox()
	{
		if (hitbox == true)
		{
			return "true";
		}
		else
		{
			return "false";
		}
	}
}