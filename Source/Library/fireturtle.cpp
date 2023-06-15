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
#include "FireTurtle.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework
{
	FireTurtle::FireTurtle() : Enemy() {
		showtime = 0;
	}
	FireTurtle::~FireTurtle() {
	}
	void FireTurtle::Show()
	{
		if (horizontalSpeed<0) {
			charactor.ShowBitmap();
		}
		else {
			charactor_right.ShowBitmap();
		}
		for (unsigned int i = 0; i < fireball.size(); i++) {
			fireball[i].ShowBitmap();
		}
	}
	void FireTurtle::SetTopLeft(int x, int y)
	{
		charactor.SetTopLeft(x, y);
		charactor_right.SetTopLeft(x, y);
	}
	void FireTurtle::fireballSetTopLeft(int x, int y)
	{
		for (unsigned int i = 0; i < fireball.size();i++){
			fireball[i].SetTopLeft(fireball[i].GetLeft()-x, fireball[i].GetTop()- y);
		}
	}
	void FireTurtle::UpData(vector<Enemy*>& monster_list, Mario &mario, Map& map, int pos)
	{
		int x, y;
		Collision(map);
		OnGround(map);
		Collision(monster_list, pos);
		std::vector<Fireball>& mario_fireball = mario.GetFireball();
		for (unsigned int i = 0; i < fireball.size();)
		{
			if (fireball[i].IsDead() == true)
			{
				fireball.erase(fireball.begin() + i);
			}
			else
			{
				fireball[i].UpData(mario, map);
				if (fireball[i].charactor.IsOverlap(fireball[i].charactor, mario.charactor)) {
					fireball[i].Die();
					mario.Die();

				}
				for (unsigned int j = 0; j < mario_fireball.size(); j++)
				{
					if (fireball[i].charactor.IsOverlap(fireball[i].charactor, mario_fireball[j].charactor) == true) {
						fireball[i].Die();
						mario_fireball[j].Die();
					}
				}
				i++;
			}
		}
		if (shot_time != 0) {
			shot_time--;
		}
		if (shot_time == 0 && isKickAble == false) {
			fireball.push_back(EnemyFireBall());
			fireball.back().Load();
			int face = 0;
			if (horizontalSpeed > 0) {
				face = 1;
				fireball.back().SetTopLeft(GetLeft() + 32, GetTop() + 16);
			}
			else {
				face = -1;
				fireball.back().SetTopLeft(GetLeft() - 32, GetTop() + 16);
			}
			fireball.back().SetHorizontalSpeed(16 * face);
			shot_time = 20;
		}

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
			}
		}
		if (charactor.IsOverlap(charactor, mario.charactor) && mario.IsInvincible() == true)
		{
			Die();
		}
		else if (mario.isCrouching == true) {
			if (abs(mario.GetTop() + mario.GetHeight() - GetTop() - GetHeight()) < 50
				&& abs(mario.GetTop() + mario.GetHeight() - GetTop() - GetHeight()) > 3
				&& mario.GetLeft() + mario.GetWidth() > GetLeft()
				&& mario.GetLeft() < GetLeft() + GetWidth() && isKickAble == false)
			{
				SetFrameIndexOfBitmap(2);
				isKickAble = true;
				SetTopLeft(GetLeft(), GetTop() + 16);
				horizontalSpeed = 0;
			}
		}

		else {
			if (abs(mario.charactorbig_left.GetTop() + mario.charactorbig_left.GetHeight() - GetTop() - GetHeight()) < 80
				&& abs(mario.charactorbig_left.GetTop() + mario.charactorbig_left.GetHeight() - GetTop() - GetHeight()) > 3
				&& mario.charactorbig_left.GetLeft() + mario.charactorbig_left.GetWidth() > GetLeft()
				&& mario.charactorbig_left.GetLeft() < GetLeft() + GetWidth() && isKickAble == false)
			{
				charactor.SetFrameIndexOfBitmap(2);
				isKickAble = true;
				SetTopLeft(GetLeft(), GetTop() + 16);
				horizontalSpeed = 0;
			}
		}
		if (isKickAble == true) {
			if (mario.charactorbig_left.IsOverlap(charactor, mario.charactorbig_left))
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
		SetTopLeft(x, y);
	}

	void FireTurtle::Reset()
	{
		fireball.clear();
	}

	void FireTurtle::Load()
	{
		charactor.LoadBitmapByString({
			"resources/fireturtle1.bmp",
			"resources/turtle2.bmp",
			"resources/fireturtle3.bmp",
			"resources/empty.bmp"
			}, RGB(146, 144, 255));
		charactor_right.LoadBitmapByString({
			"resources/fireturtle1_right.bmp",
			"resources/turtle2.bmp",
			"resources/fireturtle3.bmp",
			"resources/empty.bmp"
			}, RGB(146, 144, 255));
	}

	void FireTurtle::Die()
	{
		charactor.SetFrameIndexOfBitmap(3);
		charactor_right.SetFrameIndexOfBitmap(3);
		isdead = true;
	}

	bool FireTurtle::IsDead()
	{
		return isdead;
	}

	void FireTurtle::Collision(Map& map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int FireTurtle_x = (GetLeft() - map.GetLeft()) / 32;
		int FireTurtle_y = GetTop() / 32;
		if (FireTurtle_y > 0 && FireTurtle_x > 0) {
			//left collision
			if (horizontalSpeed > 0)
			{
				int FireTurtle_x = (GetLeft() - map.GetLeft()+32) / 32;
				if (map_vector[FireTurtle_y][FireTurtle_x + 1] != 0 || map_vector[FireTurtle_y + 2][FireTurtle_x+1] == 0)
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
				int FireTurtle_x = (GetLeft() - map.GetLeft()) / 32;

				if (map_vector[FireTurtle_y][FireTurtle_x] != 0 || map_vector[FireTurtle_y+2][FireTurtle_x] == 0)
				{
					isCollision = true;
				}
				if (GetLeft() - map.GetLeft() == 0)
				{
					isCollision = true;
				}
			}
		}
		else {
			isCollision = true;
		}
	}
	void FireTurtle::Collision(vector<Enemy*>& monster_list, int pos) {
		if (pos != 0) {
			if (charactor.IsOverlap(charactor, monster_list[pos - 1]->charactor) && (charactor.GetLeft() != monster_list[pos - 1]->GetLeft()) && monster_list[pos - 1]->IsDead() == false)
			{
				if (monster_list[pos - 1]->IsDead() == false) {
					isCollision = true;
				}
			}
		}
		if (pos != monster_list.size() - 1) {
			if (charactor.IsOverlap(charactor, monster_list[pos + 1]->charactor) && (charactor.GetLeft() != monster_list[pos + 1]->GetLeft()) && monster_list[pos + 1]->IsDead() == false)
			{
				if (monster_list[pos + 1]->IsDead() == false) {
					isCollision = true;
				}
			}
		}
		/*
		for (auto enemy : monster_list) {
			if (charactor.IsOverlap(charactor, enemy->charactor) && (charactor.GetLeft() != enemy->GetLeft()) && enemy->IsDead() == false)
			{
				isCollision = true;
			}
		}
		*/
	}
	void FireTurtle::OnGround(Map& map)
	{
		vector<vector<int>>& map_vector = map.GetMap();
		int FireTurtle_x = (GetLeft() - map.GetLeft()) / 32;
		int FireTurtle_y = (GetTop() + 16) / 32;

		if (map_vector[FireTurtle_y + 1][FireTurtle_x] != 0)
		{
			isOnGround = true;
		}
		else if (map_vector[FireTurtle_y + 1][FireTurtle_x + 1] != 0 && map_vector[FireTurtle_y][FireTurtle_x + 1] == 0)
		{
			isOnGround = true;
		}
		else
		{
			isOnGround = false;
		}
	}
}