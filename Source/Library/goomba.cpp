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
		showtime = 0;
	}
	Goomba::~Goomba() 
	{

	}
	void Goomba::Show()
	{
		if (showtime == 0) {
			charactor.ShowBitmap();
		}
	}
	void Goomba::SetTopLeft(int x, int y)
	{
		charactor.SetTopLeft(x, y);
	}
	void Goomba::fireballSetTopLeft(int x, int y)
	{
	}
	void Goomba::UpData(vector<Enemy*>& monster_list, Mario& mario, Map& map, int pos)
	{
		if (abs(mario.GetLeft() - GetLeft()) > 200 && GetTop() <= 0) {

		}
		else {
			int x, y;
			Collision(map);
			Collision(monster_list, pos);
			OnGround(map);
			if (isCollision == true)
			{
				horizontalSpeed *= -1;
				isCollision = false;
			}

			if (charactor.IsOverlap(charactor, mario.charactor) && mario.IsInvincible() == true)
			{
				Die();
			}
			else if (mario.isCrouching == true) 
			{
				if (abs(mario.GetTop() + mario.GetHeight() - GetTop() - GetHeight()) < 30
					&& abs(mario.GetTop() + mario.GetHeight() - GetTop() - GetHeight()) > 3
					&& mario.GetLeft() + mario.GetWidth() > GetLeft()
					&& mario.GetLeft() < GetLeft() + GetWidth() && isDead == false
					) {
					horizontalSpeed = 0;
					Die();
				}
			}
			else {
				if (abs(mario.charactorbig_left.GetTop() + mario.charactorbig_left.GetHeight() - GetTop() - GetHeight()) < 50
					&& abs(mario.charactorbig_left.GetTop() + mario.charactorbig_left.GetHeight() - GetTop() - GetHeight()) > 3
					&& mario.charactorbig_left.GetLeft() + mario.charactorbig_left.GetWidth() > GetLeft()
					&& mario.charactorbig_left.GetLeft() < GetLeft() + GetWidth() && isDead == false
					) {
					horizontalSpeed = 0;
					Die();
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
		charactor_right.LoadBitmapByString({
		"resources/goomba1.bmp",
		"resources/goomba2.bmp",
		"resources/goomba3.bmp",
		"resources/empty.bmp"
			}, RGB(146, 144, 255));
	}

	void Goomba::Die()
	{
		isDead = true;
	}

	bool Goomba::IsDead()
	{
		return isDead;
	}
	void Goomba::Collision(Map& map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int mario_y = GetTop() / 32;
		int mario_x = (GetLeft() - map.GetLeft()) / 32;
		if (mario_y > 0 && mario_x > 0) {
		//left collision
		if (GetLeft() - map.GetLeft() == 0)
		{
			isCollision = true;
		}
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

	void Goomba::Collision(vector<Enemy*>& monster_list,int pos)
	{
		int position = pos; //小怪在list裡面第幾個
		if (pos != 0) {
			if (charactor.IsOverlap(charactor, monster_list[pos - 1]->charactor) && (charactor.GetLeft() != monster_list[pos - 1]->GetLeft()) && monster_list[pos - 1]->IsDead() == false)
			{
				if (monster_list[pos - 1]->charactor.GetFrameIndexOfBitmap() == 2) {
					horizontalSpeed = 0;
					Die();
				}
				else if (monster_list[pos - 1]->IsDead() == false) {
					isCollision = true;
				}
			}
		}
		if (pos != monster_list.size()-1) {
			if (charactor.IsOverlap(charactor, monster_list[pos + 1]->charactor) && (charactor.GetLeft() != monster_list[pos + 1]->GetLeft()) && monster_list[pos + 1]->IsDead() == false)
			{
				if (monster_list[pos + 1]->charactor.GetFrameIndexOfBitmap() == 2) {
					horizontalSpeed = 0;
					Die();
				}
				else if (monster_list[pos + 1]->IsDead() == false) {
					isCollision = true;
				}
			}
		}
		/*
		for (auto enemy : monster_list) {
			if (charactor.IsOverlap(charactor, enemy->charactor) && (charactor.GetLeft() != enemy->GetLeft()) && enemy->IsDead() == false)
			{
				if (enemy->charactor.GetFrameIndexOfBitmap() == 2) {
					horizontalSpeed = 0;
					Die();
				}
				else if(enemy->IsDead() == false){
					isCollision = true;
				}
			}
		}*/
		
	}
	void Goomba::OnGround(Map& map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int goomba_x = (GetLeft() - map.GetLeft()) / 32;
		int goomba_y = GetTop() / 32;
		if (goomba_y > 0 && goomba_x > 0) {
			if (map_vector[goomba_y + 1][goomba_x] != 0)
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