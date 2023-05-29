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
#include "item.h"
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
		isCrouching(true),
		isDead(false),
		isFlipped(false),
		isOnGround(false),
		horizontalSpeed(0),
		verticalSpeed(0),
		jump_timer(-4)
	{

	}

	void Mario::UpData(Mario mario, Map map, Enemyfactor enemyfactor, Itemfactor itemfactor)
	{
		int mario_x = (map.GetLeft() - mario.GetLeft()) / 32;
		int mario_y = mario.GetTop() / 32;

		Collision(mario, map);
		Collision(itemfactor);
		Collision(enemyfactor);
		OnGround(mario, map);
		HitBox(mario, map);

		if (isCollision == true)
		{
			horizontalSpeed = 0;
		}

		if (isOnGround == true)
		{
			verticalSpeed = 0;
			isJump = false;
			isOnHit = false;
			jump_timer = -4;
		}
		else
		{
			if (isHitbox == true)
			{
				verticalSpeed = 0;
				verticalSpeed += GRAVITY;
			}
			else
			{
				if (isJump == true)
				{
					if (jump_timer < 0)
					{
						verticalSpeed = -16;
						jump_timer++;
					}
					else
					{
						verticalSpeed += GRAVITY;
						isJump = false;
					}
				}
				else
				{
					verticalSpeed += 2 * GRAVITY;
				}
			}
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

	void Mario::Reset()
	{
		isDead = false;
		isCrouching = true;
		charactor.SetFrameIndexOfBitmap(0);
		charactor.SetTopLeft(0, 0);
	}

	void Mario::Load()
	{
		charactor.LoadBitmapByString({
		"resources/mario1.bmp",
		"resources/mario2.bmp",
		"resources/mario3.bmp",
		"resources/mario4.bmp",
		"resources/bigmario1.bmp",
		"resources/bigmario2.bmp",
		"resources/bigmario3.bmp",
		"resources/bigmario4.bmp",
			}/*, RGB(146, 144, 255)*/);
	}
	void Mario::Show()
	{
		charactor.ShowBitmap();
	}
	void Mario::Die()
	{
		isDead = true;
	}
	void Mario::LoadBitmapByString(vector<string> filepaths, COLORREF color)
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

	void Mario::SetVerticalSpeed(int value)
	{
		verticalSpeed = value;
	}

	void Mario::SetHorizontalSpeed(int value)
	{
		horizontalSpeed = value;
	}

	int Mario::GetVerticalSpeed()
	{
		return verticalSpeed;
	}
	int Mario::GetHorizontalSpeed()
	{
		return horizontalSpeed;
	}


	void Mario::Collision(Mario mario, Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();

		int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
		int mario_y = mario.GetTop() / 32;
		//left collision
		if (isCrouching == true)
		{
			if (mario.GetHorizontalSpeed() > 0)
			{
				int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
				if (map_vector[mario_y][mario_x + 1] != 0)
				{
					isCollision = true;
				}
			}//right collision
			else if (mario.GetHorizontalSpeed() < 0)
			{
				int mario_x = (mario.GetLeft() - map.GetLeft() - 4) / 32;
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
		else
		{
			if (mario.GetHorizontalSpeed() > 0)
			{
				int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
				if (map_vector[mario_y][mario_x + 1] != 0 || map_vector[mario_y + 1][mario_x + 1] != 0)
				{
					isCollision = true;
				}
			}
			else if (mario.GetHorizontalSpeed() < 0)
			{
				int mario_x = (mario.GetLeft() - map.GetLeft() - 4) / 32;
				if (map_vector[mario_y][mario_x] != 0 || map_vector[mario_y + 1][mario_x] != 0)
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
		if (isCrouching == true)
		{
			for (unsigned int i = 0; i < enemylist.size(); i++) {
				if (enemylist[i]->charactor.IsOverlap(charactor, enemylist[i]->charactor) && enemylist[i]->IsDead() == false) {
					if (-3 <= GetTop() + GetHeight() - enemylist[i]->GetTop()
						&& GetTop() + GetHeight() - enemylist[i]->GetTop() <= 0
						&& GetLeft() + GetWidth() > enemylist[i]->GetLeft()
						&& GetLeft() < enemylist[i]->GetLeft() + enemylist[i]->GetWidth()
						)
					{
					}
					else
					{
						if (enemylist[i]->GetFrameIndexOfBitmap() != 2) {
							Die();
						}
					}
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < enemylist.size(); i++) {
				if (enemylist[i]->charactor.IsOverlap(charactor, enemylist[i]->charactor) && enemylist[i]->IsDead() == false) {
					if (-18 <= GetTop() + GetHeight() - enemylist[i]->GetTop()
						&& GetTop() + GetHeight() - enemylist[i]->GetTop() <= -14
						&& GetLeft() + GetWidth() > enemylist[i]->GetLeft()
						&& GetLeft() < enemylist[i]->GetLeft() + enemylist[i]->GetWidth()
						) 
					{
					}
					else 
					{
						if (enemylist[i]->GetFrameIndexOfBitmap() != 2) {
							if (GetLeft()> enemylist[i]->GetLeft())
							{
								charactor.SetTopLeft(GetLeft()-32, GetTop() + 32);
							}
							else
							{
								charactor.SetTopLeft(GetLeft() + 32, GetTop() + 32);
							}
							charactor.SetFrameIndexOfBitmap(0);
							isCrouching = true;
						}
					}
				}
			}
		}
	}

	void Mario::Collision(Itemfactor itemfactor) {
		std::vector<Item*>_itemList = itemfactor.GetItemList();
		for (unsigned int i = 0; i < _itemList.size(); i++)
		{
			if (_itemList[i]->charactor.IsOverlap(_itemList[i]->charactor, charactor))
			{
				charactor.SetTopLeft(GetLeft(), GetTop() - 32);
				charactor.SetFrameIndexOfBitmap(4);
				isCrouching = false;
			}
		}
	}
	void Mario::OnGround(Mario mario, Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
		int mario_y = mario.GetTop() / 32;
		if (isCrouching == true)
		{
			if (isJump == false)
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
		else
		{
			if (isJump == false)
			{
				if (map_vector[mario_y + 2][mario_x] != 0)
				{
					isOnGround = true;
				}
				else if (map_vector[mario_y + 2][mario_x + 1] != 0 && map_vector[mario_y + 1][mario_x + 1] == 0)
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
		
	}

	void Mario::HitBox(Mario mario, Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
		int mario_y = (mario.GetTop() - 4) / 32;
		
		if (isOnGround == false && isHitbox == false && isOnHit == false)
		{
			if (map_vector[mario_y][mario_x] != 0)
			{
				isHitbox = true;
				isOnHit = true;
				isJump = false;
			}
			else if (map_vector[mario_y][mario_x + 1] != 0 && map_vector[mario_y + 1][mario_x + 1] == 0)
			{
				isHitbox = true;
				isOnHit = true;
				isJump = false;
			}
			else
			{
				isHitbox = false;
			}
		}
		else if (isOnHit == true)
		{
			isHitbox = false;
		}
		
	}

	bool Mario::IsDead()
	{
		return isDead;
	}

	bool Mario::IsOnGround()
	{
		return isOnGround;
	}

	bool Mario::IsHitbox()
	{
		return isHitbox;
	}

	bool Mario::IsJump()
	{
		return isJump;
	}

	void Mario::SetJump(bool flags)
	{
		isJump = flags;
	}
}