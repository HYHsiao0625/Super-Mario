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
		std::vector<Enemy*>enemylist = enemyfactor.GetMonsterlist();

		Collision(mario, map);
		Collision(itemfactor);
		Collision(enemyfactor);
		OnGround(mario, map);
		HitBox(mario, map);
		for (unsigned int i = 0; i < fireball.size();)
		{
			if (fireball[i].IsDead() == true)
			{
				fireball.erase(fireball.begin() + i);
			}
			else
			{
				fireball[i].UpData(mario, map);
				for (unsigned int j = 0; j < enemylist.size(); j++) {
					if (fireball[i].charactor.IsOverlap(fireball[i].charactor, enemylist[j]->charactor)) {
						fireball[i].Die();
						enemylist[j]->Die();
					}
				}
				i++;
			}
		}

		if (unbeatable_time != 0) {
			unbeatable_time--;
			isInvincible = true;
		}
		else
		{
			isInvincible = false;
		}

		if (shot_time != 0) {
			shot_time--;
		}
		if (isShot == true && shot_time == 0) {
			fireball.push_back(Fireball());
			fireball.back().Load();
			if (face == 1) {
				fireball.back().SetTopLeft(mario.GetLeft() + 32, mario.GetTop());
			}
			else {
				fireball.back().SetTopLeft(mario.GetLeft() - 32, mario.GetTop());
			}
			fireball.back().SetHorizontalSpeed(16 * face);
			isShot = false;
			shot_time = 15;
		}
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
		fireball.clear();
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
		for (unsigned int i = 0; i < fireball.size(); i++) {
			fireball[i].ShowBitmap();
		}
	}
	void Mario::Die()
	{
		if (unbeatable_time == 0) {
			isDead = true;
		}
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
	void Mario::SetShot(bool x)
	{
		isShot = x;
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
	std::vector<Fireball> Mario::GetFireball()
	{
		return fireball;
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
	int Mario::GetHnbeatable_time()
	{
		return unbeatable_time;
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
							if (GetLeft() > enemylist[i]->GetLeft())
							{
								charactor.SetTopLeft(GetLeft() + 64, GetTop() + 32);
							}
							else
							{
								charactor.SetTopLeft(GetLeft() - 64, GetTop() + 32);
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
		std::vector<int>_itemTemp = itemfactor.GetItemTemp();
		for (unsigned int i = 0; i < _itemList.size(); i++)
		{
			if (GetLeft() + GetWidth() > _itemList[i]->GetLeft()
				&& GetLeft() < _itemList[i]->GetLeft() + _itemList[i]->GetWidth()
				&& GetTop() + GetHeight() > _itemList[i]->GetTop()
				&& GetTop() < _itemList[i]->GetTop() + _itemList[i]->GetHeight())
			{
				if (isCrouching == true)
				{
					switch (_itemTemp[i])
					{
					case 1://蘑菇物件
						charactor.SetTopLeft(GetLeft(), GetTop() - 32);
						charactor.SetFrameIndexOfBitmap(4);
						isCrouching = false;
						break;
					case 2://星星物件
						unbeatable_time = 60;
						break;
					default:
						break;
					}
				}
				else
				{
					switch (_itemTemp[i])
					{
					case 1://蘑菇物件
						break;
					case 2://星星物件
						unbeatable_time = 60;
						break;
					default:
						break;
					}
				}
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
	void Mario::FireballSetTopLeft(int x,int y){
		for (auto fireball : fireball)
		{
			fireball.SetTopLeft(fireball.GetLeft() - x, fireball.GetTop() - y);
		}
	}
}