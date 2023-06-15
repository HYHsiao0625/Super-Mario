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
#include "audio.h"


namespace game_framework
{
	Mario::Mario() :
		isCrouching(true),
		isDead(false),
		isFlipped(false),
		isOnGround(false),
		isInvincible(false),
		isInvincibleMode(false),
		horizontalSpeed(0),
		verticalSpeed(0),
		jump_timer(-5),
		dead_timer(4)
	{

	}

	void Mario::UpData(Mario mario, Map& map, Enemyfactor& enemyfactor, Itemfactor& itemfactor)
	{
		
		int mario_x = (map.GetLeft() - mario.GetLeft()) / 32;
		int mario_y = mario.GetTop() / 32;
		std::vector<Enemy*>& enemylist = enemyfactor.GetMonsterlist();

		Collision(mario, map);
		Collision(itemfactor);
		Collision(enemyfactor,map);
		OnGround(mario, map);
		HitBox(mario, map);
		SetAnimation(10, false);
		if (isCrouching == false && isPowerUP == false)
		{
			MarioSoundEffect->Play(3, false);
			isPowerUP = true;
		}
		else if (isCrouching == true && isPowerUP == true)
		{
			MarioSoundEffect->Play(4, false);
			isPowerUP = false;
		}
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
		if (isInvincibleMode == true)
		{
			unbeatable_time = 100;
			isInvincible = true;
		}
		else if (isInvincibleMode == false && unbeatable_time != 0) 
		{
			unbeatable_time--;
			if (isInvincible == false)
			{
				MarioSoundEffect->Play(6, false);
				isInvincible = true;
			}
		}
		else if (unbeatable_time == 0)
		{
			isInvincible = false;
			MarioSoundEffect->Stop(6);
		}
		
		if (shot_time != 0) {
			shot_time--;
		}
		if (isShot == true && shot_time == 0 && isShotable == true) {
			fireball.push_back(Fireball());
			fireball.back().Load();
			if (face == 1) {
				if (isCrouching == true) {
					fireball.back().SetTopLeft(mario.GetLeft() + 32, mario.GetTop());
				}
				else {
					fireball.back().SetTopLeft(mario.GetLeft() + 32, mario.GetTop()+32);
				}
			}
			else {
				if (isCrouching == true) {
					fireball.back().SetTopLeft(mario.GetLeft() - 32, mario.GetTop());
				}
				else {
					fireball.back().SetTopLeft(mario.GetLeft() - 32, mario.GetTop() + 32);
				}
			}
			fireball.back().SetHorizontalSpeed(16 * face);
			MarioSoundEffect->Play(5, false);
			isShot = false;
			shot_time = 5;
		}
		if (isCollision == true)
		{
			horizontalSpeed = 0;
		}

		if (isOnGround == true)
		{
			verticalSpeed = 0;
			isJump = false;
			isOnJump = false;
			isOnHit = false;
			jump_timer = -5;

			if (horizontalSpeed > 0)
			{
				if (GetFrameIndexOfBitmap() == 4 || GetFrameIndexOfBitmap() == 5)
				{
					SetFrameIndexOfBitmap(1);
				}
			}
			else if (horizontalSpeed < 0)
			{
				if (GetFrameIndexOfBitmap() == 4 || GetFrameIndexOfBitmap() == 5)
				{
					SetFrameIndexOfBitmap(1);
				}
			}
			else
			{
				SetFrameIndexOfBitmap(0);
			}
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
					SetFrameIndexOfBitmap(5);
					
					if (jump_timer < 0)
					{
						verticalSpeed = -16;
						jump_timer++;
						if (isCrouching == true && isOnJump == false)
						{
							MarioSoundEffect->Play(1, false);
						}
						else if (isCrouching == false && isOnJump == false)
						{
							MarioSoundEffect->Play(2, false);
						}
						isOnJump = true;
					}
					else
					{
						verticalSpeed += GRAVITY;
						isJump = false;
					}
				}
				else
				{
					SetFrameIndexOfBitmap(5);
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

		
		SetTopLeft(x, y);
	}

	void Mario::Reset()
	{
		isPowerUP = false;
		isDead = false;
		isCrouching = true;
		SetFrameIndexOfBitmap(0);
		isShotable = false;
		SetTopLeft(0, 0);
		SetVerticalSpeed(0);
		fireball.clear();
		dead_timer = 4;
	}

	void Mario::Load()
	{
		charactor.LoadBitmapByString({
		"resources/mario1.bmp",
		"resources/mario2.bmp",
		"resources/mario3.bmp",
		"resources/mario4.bmp",
		"resources/mario1.bmp",
		"resources/mario6.bmp",
			}, RGB(146, 144, 255));
		charactor_right.LoadBitmapByString({
		"resources/mario1.bmp",
		"resources/mario2.bmp",
		"resources/mario3.bmp",
		"resources/mario4.bmp",
		"resources/mario1.bmp",
		"resources/mario6.bmp",
			}, RGB(146, 144, 255));
		charactor_left.LoadBitmapByString({
		"resources/mario1_left.bmp",
		"resources/mario2_left.bmp",
		"resources/mario3_left.bmp",
		"resources/mario4_left.bmp",
		"resources/mario1_left.bmp",
		"resources/mario6_left.bmp",
			}, RGB(146, 144, 255));
		charactorbig_right.LoadBitmapByString({
		"resources/bigmario1.bmp",
		"resources/bigmario2.bmp",
		"resources/bigmario3.bmp",
		"resources/bigmario4.bmp",
		"resources/bigmario1.bmp",
		"resources/bigmario6.bmp",
			}, RGB(146, 144, 255));
		charactorbig_left.LoadBitmapByString({
		"resources/bigmario1_left.bmp",
		"resources/bigmario2_left.bmp",
		"resources/bigmario3_left.bmp",
		"resources/bigmario4_left.bmp",
		"resources/bigmario1_left.bmp",
		"resources/bigmario6_left.bmp",
			}, RGB(146, 144, 255));
		charactorfire.LoadBitmapByString({
		"resources/firemario1.bmp",
		"resources/firemario2.bmp",
		"resources/firemario3.bmp",
		"resources/firemario4.bmp",
		"resources/firemario1.bmp",
		"resources/firemario6.bmp",
			}, RGB(146, 144, 255));
		charactorfire_left.LoadBitmapByString({
		"resources/firemario1_left.bmp",
		"resources/firemario2_left.bmp",
		"resources/firemario3_left.bmp",
		"resources/firemario4_left.bmp",
		"resources/firemario1_left.bmp",
		"resources/firemario6_left.bmp",
			}, RGB(146, 144, 255));
		charactorbigfire.LoadBitmapByString({
		"resources/firebigmario1.bmp",
		"resources/firebigmario2.bmp",
		"resources/firebigmario3.bmp",
		"resources/firebigmario4.bmp",
		"resources/firebigmario1.bmp",
		"resources/firebigmario6.bmp",
			}, RGB(146, 144, 255));
		charactorbigfire_left.LoadBitmapByString({
		"resources/firebigmario1_left.bmp",
		"resources/firebigmario2_left.bmp",
		"resources/firebigmario3_left.bmp",
		"resources/firebigmario4_left.bmp",
		"resources/firebigmario1_left.bmp",
		"resources/firebigmario6_left.bmp",
			}, RGB(146, 144, 255));

		//Load SoundEffect
		
		MarioSoundEffect->Load(1, "Resources/SoundEffects/Jump.wav");
		MarioSoundEffect->Load(2, "Resources/SoundEffects/BigJump.wav");
		MarioSoundEffect->Load(3, "Resources/SoundEffects/Powerup.wav");
		MarioSoundEffect->Load(4, "Resources/SoundEffects/Thwomp.wav");
		MarioSoundEffect->Load(5, "Resources/SoundEffects/FireBall.wav");
		MarioSoundEffect->Load(6, "Resources/SoundEffects/Invincibility.wav");

	}
	void Mario::Show()
	{
		//charactor.ShowBitmap();
		if (isShotable == false)
		{
			if (face == 1 && isCrouching == true) {
				charactor_right.ShowBitmap();
			}
			else if (face == -1 && isCrouching == true) {
				charactor_left.ShowBitmap();
			}
			else if (face == 1 && isCrouching == false) {
				charactorbig_right.ShowBitmap();
			}
			else if (face == -1 && isCrouching == false) {
				charactorbig_left.ShowBitmap();
			}
		}
		else
		{
			if (face == 1 && isCrouching == true) {
				charactorfire.ShowBitmap();
			}
			else if (face == -1 && isCrouching == true) {
				charactorfire_left.ShowBitmap();
			}
			else if (face == 1 && isCrouching == false) {
				charactorbigfire.ShowBitmap();
			}
			else if (face == -1 && isCrouching == false) {
				charactorbigfire_left.ShowBitmap();
			}
		}
		
		for (unsigned int i = 0; i < fireball.size(); i++) {
			fireball[i].ShowBitmap();
		}

		
	}
	void Mario::Die()
	{
		if (unbeatable_time == 0 || GetTop() > 480) 
		{
			isDead = true;
		}
		
	}
	void Mario::LoadBitmapByString(vector<string> filepaths, COLORREF color)
	{
		charactor.LoadBitmapByString(filepaths, color);	
		charactor_left.LoadBitmapByString(filepaths, color);
		charactor_right.LoadBitmapByString(filepaths, color);
		charactorbig_left.LoadBitmapByString(filepaths, color);
		charactorbig_right.LoadBitmapByString(filepaths, color);
		charactorfire.LoadBitmapByString(filepaths, color);
		charactorfire_left.LoadBitmapByString(filepaths, color);
		charactorbigfire.LoadBitmapByString(filepaths, color);
		charactorbigfire_left.LoadBitmapByString(filepaths, color);
	}
	int Mario::GetFrameIndexOfBitmap()
	{
		return charactor.GetFrameIndexOfBitmap();
	}

	void Mario::SetFrameIndexOfBitmap(int frameIndex)
	{
		charactor.SetFrameIndexOfBitmap(frameIndex);
		charactor_left.SetFrameIndexOfBitmap(frameIndex);
		charactor_right.SetFrameIndexOfBitmap(frameIndex);
		charactorbig_left.SetFrameIndexOfBitmap(frameIndex);
		charactorbig_right.SetFrameIndexOfBitmap(frameIndex);
		charactorfire.SetFrameIndexOfBitmap(frameIndex);
		charactorfire_left.SetFrameIndexOfBitmap(frameIndex);
		charactorbigfire.SetFrameIndexOfBitmap(frameIndex);
		charactorbigfire_left.SetFrameIndexOfBitmap(frameIndex);
	}

	void Mario::SetAnimation(int delay, bool _once)
	{
		charactor.SetAnimation(delay, _once);
		charactor_left.SetAnimation(delay, _once);
		charactor_right.SetAnimation(delay, _once);
		charactorbig_left.SetAnimation(delay, _once);
		charactorbig_right.SetAnimation(delay, _once);
		charactorfire.SetAnimation(delay, _once);
		charactorfire_left.SetAnimation(delay, _once);
		charactorbigfire.SetAnimation(delay, _once);
		charactorbigfire_left.SetAnimation(delay, _once);

	}
	void Mario::SetTopLeft(int x, int y)
	{
		charactor.SetTopLeft(x, y);
		charactor_left.SetTopLeft(x, y);
		charactor_right.SetTopLeft(x, y);
		charactorbig_left.SetTopLeft(x, y);
		charactorbig_right.SetTopLeft(x, y);
		charactorfire.SetTopLeft(x, y);
		charactorfire_left.SetTopLeft(x, y);
		charactorbigfire.SetTopLeft(x, y);
		charactorbigfire_left.SetTopLeft(x, y);
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

	void Mario::Collision(Mario mario, Map& map)
	{
		vector<vector<int>>& map_vector = map.GetMap();
		vector<vector<CMovingBitmap>>& map_characrot = map.GetMapcharactor();
		int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
		int mario_y = mario.GetTop() / 32;
		//left collision
		if (isCrouching == true)
		{
			if (GetHorizontalSpeed() > 0 && mario_y>0)
			{
				int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
				if ((map_vector[mario_y][mario_x+1] != 0 && map_vector[mario_y][mario_x+1] != 15) || (map_vector[mario_y][mario_x+1] == 15 && map_characrot[mario_y][mario_x+1].GetFrameIndexOfBitmap() == 1)) {
					isCollision = true;
				}
				if (map_vector[mario_y][mario_x + 1] == 9 || map_vector[mario_y][mario_x + 1] == 10)
				{
					SetSwitchMap(true);
				}
			}//right collision
			else if (GetHorizontalSpeed() < 0 && mario_y > 0)
			{
				int mario_x = (GetLeft() - map.GetLeft() - 4) / 32;
				if ((map_vector[mario_y][mario_x] != 0 && map_vector[mario_y][mario_x] != 15) || (map_vector[mario_y][mario_x] == 15 && map_characrot[mario_y][mario_x].GetFrameIndexOfBitmap() == 1)) {
				{
					isCollision = true;
				}
				if (map_vector[mario_y][mario_x] == 9 || map_vector[mario_y][mario_x] == 10)
				{
						SetSwitchMap(true);
					}
				}
			}
			else
			{
				isCollision = false;
			}
		}
		else
		{
			if (GetHorizontalSpeed() > 0 && mario_y > 0)
			{
				int mario_x = (GetLeft() - map.GetLeft()) / 32;
				if ((map_vector[mario_y][mario_x + 1] != 0 && map_vector[mario_y][mario_x + 1] != 15) || map_vector[mario_y + 1][mario_x + 1] != 0 || (map_vector[mario_y][mario_x + 1] == 15 && map_characrot[mario_y][mario_x + 1].GetFrameIndexOfBitmap() == 1))
				{
					isCollision = true;
				}
				if ((map_vector[mario_y][mario_x + 1] == 9 || map_vector[mario_y][mario_x + 1] == 10) ||(map_vector[mario_y + 1][mario_x + 1] == 9 || map_vector[mario_y + 1][mario_x + 1] == 10))
				{
					SetSwitchMap(true);
				}
			}
			else if (GetHorizontalSpeed() < 0 && mario_y > 0)
			{
				int mario_x = (GetLeft() - map.GetLeft() - 4) / 32;
				if ((map_vector[mario_y][mario_x] != 0 && map_vector[mario_y][mario_x] != 15) || map_vector[mario_y + 1][mario_x] != 0 || (map_vector[mario_y][mario_x] == 15 && map_characrot[mario_y][mario_x].GetFrameIndexOfBitmap() == 1))
				{
					isCollision = true;
				}
				if ((map_vector[mario_y][mario_x] == 9 || map_vector[mario_y][mario_x] == 10) || (map_vector[mario_y + 1][mario_x] == 9 || map_vector[mario_y + 1][mario_x] == 10))
				{
					SetSwitchMap(true);
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
	void Mario::Collision(Enemyfactor& enemyfactor, Map& map) {
		std::vector<Enemy*>enemylist = enemyfactor.GetMonsterlist();
		std::vector<vector<int>>& mapvector = map.GetMap();
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
				if (enemylist[i]->charactor.IsOverlap(charactorbig_right, enemylist[i]->charactor) && enemylist[i]->IsDead() == false) {
					if (-35 <= charactorbig_right.GetTop() + charactorbig_right.GetHeight() - enemylist[i]->GetTop()
						&& charactorbig_right.GetTop() + charactorbig_right.GetHeight() - enemylist[i]->GetTop() <= 0
						&& charactorbig_right.GetLeft() + charactorbig_right.GetWidth() > enemylist[i]->GetLeft()
						&& charactorbig_right.GetLeft() < enemylist[i]->GetLeft() + enemylist[i]->GetWidth()
						)
					{
					}
					else
					{
						if (enemylist[i]->GetFrameIndexOfBitmap() != 2 && unbeatable_time == 0) {
							if (GetLeft() > enemylist[i]->GetLeft())
							{
								int x = (GetLeft() + 64) / 32;
								int y = (GetTop() + 32) / 32;
								while (mapvector[x][y] != 0) {
									y = (y*32-32)/32;
								}
								SetTopLeft(GetLeft() + 64, y*32);
							}
							else
							{
								SetTopLeft(GetLeft() - 64, GetTop() + 32);
							}
							SetFrameIndexOfBitmap(0);
							isCrouching = true;
							//isShotable = false;
						}
					}
				}
			}
		}
	}

	void Mario::Collision(Itemfactor& itemfactor) {
		std::vector<Item*>& _itemList = itemfactor.GetItemList();
		std::vector<int>&_itemTemp = itemfactor.GetItemTemp();
		for (unsigned int i = 0; i < _itemList.size(); i++)
		{
			if (isCrouching == true)
			{
				if (GetLeft() + GetWidth() > _itemList[i]->GetLeft()
					&& GetLeft() < _itemList[i]->GetLeft() + _itemList[i]->GetWidth()
					&& GetTop() + GetHeight() > _itemList[i]->GetTop()
					&& GetTop() < _itemList[i]->GetTop() + _itemList[i]->GetHeight())
				{

					switch (_itemTemp[i])
					{
					case 1://蘑菇物件

						SetTopLeft(GetLeft(), GetTop() - 32);
						isCrouching = false;
						break;
					case 2://星星物件
						unbeatable_time = 240;
						break;
					case 3://火焰花物件
						isShotable = true;
						break;
					default:
						break;
					}
					_itemList[i]->Die();
				}
			}
			else {
				if (charactorbig_left.GetLeft() + charactorbig_left.GetWidth() > _itemList[i]->GetLeft()
					&& charactorbig_left.GetLeft() < _itemList[i]->GetLeft() + _itemList[i]->GetWidth()
					&& charactorbig_left.GetTop() + charactorbig_left.GetHeight() > _itemList[i]->GetTop()
					&& charactorbig_left.GetTop() < _itemList[i]->GetTop() + _itemList[i]->GetHeight())
				{
					switch (_itemTemp[i])
					{
					case 1://蘑菇物件
						break;
					case 2://星星物件
						unbeatable_time = 240;
						break;
					case 3://火焰花物件
						isShotable = true;
						break;
					default:
						break;
					}
					_itemList[i]->Die();
				}

			}
		}
	}
	void Mario::OnGround(Mario mario, Map& map)
	{
		vector<vector<int>>& map_vector = map.GetMap();
		vector<vector<CMovingBitmap>>& map_characrot = map.GetMapcharactor();
		int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
		int mario_y = (mario.GetTop()) / 32;
		int mario_x_left = (mario.GetLeft() - map.GetLeft() + 4) / 32;
		int mario_x_right = (mario.GetLeft() - map.GetLeft() + 28) / 32;
		int mario_y_bottom = (mario.GetTop() + 32) / 32;

		if (isCrouching == true)
		{
			if (isJump == false && mario_y >= 0)
			{
				if ((map_vector[mario_y_bottom][mario_x_right] != 0 && map_vector[mario_y_bottom][mario_x_right] != 15) || (map_vector[mario_y + 1][mario_x_right]==15 && map_characrot[mario_y_bottom][mario_x_right].GetFrameIndexOfBitmap()==1))
				{
					isOnGround = true;
				}
				else if ((map_vector[mario_y_bottom][mario_x] != 0 && map_vector[mario_y_bottom][mario_x] != 15 ) || (map_vector[mario_y_bottom][mario_x] == 15 && map_characrot[mario_y_bottom][mario_x].GetFrameIndexOfBitmap() == 1))
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
			if (isJump == false && mario_y >= 0)
			{
				if ((map_vector[mario_y_bottom + 1][mario_x_right] != 0 && map_vector[mario_y_bottom + 1][mario_x_right] != 15) || (map_vector[mario_y + 1][mario_x_right] == 15 && map_characrot[mario_y_bottom + 1][mario_x_right].GetFrameIndexOfBitmap() == 1))
				{
					isOnGround = true;
				}
				else if ((map_vector[mario_y_bottom + 1][mario_x] != 0 && map_vector[mario_y_bottom + 1][mario_x] != 15) || (map_vector[mario_y_bottom + 1][mario_x] == 15 && map_characrot[mario_y_bottom + 1][mario_x].GetFrameIndexOfBitmap() == 1))
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

	void Mario::HitBox(Mario mario, Map& map)
	{
		vector<vector<int>>& map_vector = map.GetMap();
		vector<vector<CMovingBitmap>>& map_characrotr = map.GetMapcharactor();
		int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
		int mario_y = (mario.GetTop()) / 32;
		int mario_x_left = (mario.GetLeft() - map.GetLeft() + 4) / 32;
		int mario_x_right = (mario.GetLeft() - map.GetLeft() + 28) / 32;
		int mario_y_hit = (mario.GetTop() - 4) / 32;

		if (mario_x > 0 && mario_y > 0)
		{
			if (isOnGround == false && isHitbox == false && isOnHit == false)
			{
				if (map_vector[mario_y_hit][mario_x_right] != 0)
				{
					if (map_vector[mario_y_hit][mario_x_right] != 15)
					{
						isHitbox = true;
						isOnHit = true;
						isJump = false;
					}
					else if (map_vector[mario_y_hit][mario_x_right] == 15 && verticalSpeed < 0) {
						isHitbox = true;
						isOnHit = true;
						isJump = false;
					}
				}
				else if (map_vector[mario_y_hit][mario_x] != 0)
				{
					if (map_vector[mario_y_hit][mario_x] != 15)
					{
						isHitbox = true;
						isOnHit = true;
						isJump = false;
					}
					else if (map_vector[mario_y_hit][mario_x_right] == 15 && verticalSpeed < 0)
					{
						isHitbox = true;
						isOnHit = true;
						isJump = false;
					}
				}
				else if (map_vector[mario_y_hit][mario_x_left] != 0)
				{
					if (map_vector[mario_y_hit][mario_x_left] != 15)
					{
						isHitbox = true;
						isOnHit = true;
						isJump = false;
					}
					else if (map_vector[mario_y_hit][mario_x_left] == 15 && verticalSpeed < 0) {
						isHitbox = true;
						isOnHit = true;
						isJump = false;
					}
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

	void Mario::SetDown(bool flags)
	{
		isDown = flags;
	}

	bool Mario::IsDown()
	{
		return isDown;
	}

	void Mario::SetSwitchMap(bool flags)
	{
		isSwitchMap = flags;
	}

	bool Mario::IsSwitchMap()
	{
		return isSwitchMap;
	}
	bool Mario::IsInvincible()
	{
		return isInvincible;
	}

	void Mario::SetMode(bool flags)
	{
		isInvincibleMode = flags;
	}
	bool Mario::GetMode()
	{
		return isInvincibleMode;
	}
	int Mario::GetHnbeatable_time()
	{
		return unbeatable_time;
	}
}