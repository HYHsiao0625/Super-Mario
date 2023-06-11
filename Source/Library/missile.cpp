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
#include "Missile.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>
#include <ctime>

namespace game_framework
{
	Missile::Missile() : Enemy()
	{
	}
	Missile::~Missile()
	{

	}
	void Missile::Show()
	{
		if (showtime == 0) {
			charactor.ShowBitmap();
		}

	}
	void Missile::SetTopLeft(int x, int y)
	{
		charactor.SetTopLeft(x, y);
	}
	void Missile::fireballSetTopLeft(int x, int y)
	{
	}
	void Missile::UpData(vector<Enemy*> monster_list, Mario& mario, Map map, int pos)
	{
		///Collision(map);
		if (abs(mario.GetLeft() - GetLeft()) > 48) {
		}
		else {
			trigger = 1;
			
		}
		
		if (trigger == 1) {
			verticalSpeed = -32;
		}
		if (GetTop() <= 0) {
			Die();
		}
		charactor.SetTopLeft(charactor.GetLeft(), charactor.GetTop() + verticalSpeed);
	}

	void Missile::Reset()
	{

	}

	void Missile::Load()
	{
		charactor.LoadBitmapByString({
			"resources/missile1.bmp",
			"resources/empty.bmp"
			}, RGB(146, 144, 255));
	}

	void Missile::Die()
	{
		isDead = true;
	}

	bool Missile::IsDead()
	{
		return isDead;
	}

	void Missile::Collision(Map map)
	{
		
	}
}