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
#include "Flower.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>
#include <ctime>

namespace game_framework
{
	Flower::Flower() : Enemy() 
	{
		showtime = 1;
		
	}
	Flower::~Flower() 
	{
		
	}
	void Flower::Show()
	{
		if (showtime == 0) {
			charactor.ShowBitmap();
		}
	}
	void Flower::SetTopLeft(int x, int y)
	{
		charactor.SetTopLeft(x, y);
	}
	void Flower::fireballSetTopLeft(int x, int y)
	{
	}
	void Flower::UpData(vector<Enemy*>& monster_list, Mario& mario, Map& map,int pos)
	{
		//Collision(map);
		int mario_x;
		int mario_y;
		if (charactor.IsOverlap(charactor, mario.charactor) && mario.IsInvincible() == true)
		{
			Die();
		}
		if (mario.isCrouching == true) {
			mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
			mario_y = (mario.GetTop() - 4) / 32;
		}
		else {
			mario_x = (mario.charactorbig_left.GetLeft() - map.GetLeft()) / 32;
			mario_y = (mario.charactorbig_left.GetTop()+32) / 32;
		}
		int enemy_x = (GetLeft() - map.GetLeft()) / 32;
		int enemy_y = GetTop() / 32;
		if (abs(mario_x - enemy_x) <= 5)
		{
			trigger = 1;
			
		}
		if (trigger == 1) {
			if (GetTop() == (original_y-52) && active == 1) {
				verticalSpeed = 4;
			}
			else if (GetTop() == original_y) {
				verticalSpeed = -4;
				active = 0;
			}
			else if (GetTop() == (original_y - 52) && active == 0) {
				verticalSpeed = 0;
			}
			if (showtime != 0) {
				showtime--;
			}
			if (GetTop() <= (original_y - 39)) {
				charactor.SetFrameIndexOfBitmap(3);
			}
			else if (GetTop() <= (original_y - 26)) {
				charactor.SetFrameIndexOfBitmap(2);
			}
			else if (GetTop() <= (original_y - 13)) {
				charactor.SetFrameIndexOfBitmap(1);
			}
			charactor.SetTopLeft(charactor.GetLeft(), charactor.GetTop() + verticalSpeed);
		}
	}

	void Flower::Reset()
	{

	}

	void Flower::Load()
	{
		charactor.LoadBitmapByString({
			"resources/flower1_1.bmp",
			"resources/flower1_2.bmp",
			"resources/flower1_3.bmp",
			"resources/flower1_4.bmp",
			"resources/empty.bmp"
			}, RGB(146, 144, 255));
	}

	void Flower::Die()
	{
		isDead = true;
	}

	bool Flower::IsDead()
	{
		return isDead;
	}

	void Flower::Collision(Map& map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		int enemy_x = (GetLeft() - map.GetLeft()) / 32;
		int enemy_y = GetTop() / 32;

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