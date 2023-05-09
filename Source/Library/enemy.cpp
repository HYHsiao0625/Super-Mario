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
#include "Enemy.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework
{
	Enemy::Enemy()
	{
	}

	Enemy::~Enemy()
	{

	}


	void Enemy::ShowBitmap()
	{
		charactor.ShowBitmap();
	}

	void Enemy::LoadBitmapByString(vector<string> filepaths, COLORREF color)
	{
		charactor.LoadBitmapByString(filepaths, color);
	}
	void Enemy::Limit(CMovingBitmap floor, Mario mario)
	{
		if (floor.GetLeft() < 0 && mario.GetLeft() <= 384)
		{
			this->SetTopLeft(this->GetLeft() - mario.GetHorizontalSpeed(), this->GetTop());
		}
		if (mario.GetLeft() >= 512 && floor.GetLeft() + floor.GetWidth() >= 1024)
		{
			this->SetTopLeft(this->GetLeft() - mario.GetHorizontalSpeed(), this->GetTop());
		}
	}

	int Enemy::GetFrameIndexOfBitmap()
	{
		return charactor.GetFrameIndexOfBitmap();
	}

	void Enemy::SetFrameIndexOfBitmap(int frameIndex)
	{
		charactor.SetFrameIndexOfBitmap(frameIndex);
	}

	void Enemy::SetAnimation(int delay, bool _once)
	{
		charactor.SetAnimation(delay, _once);
	}
	void Enemy::SetTopLeft(int x, int y)
	{
		charactor.SetTopLeft(x, y);
	}
	int Enemy::GetTop()
	{
		return charactor.GetTop();
	}

	int Enemy::GetLeft()
	{
		return charactor.GetLeft();
	}
	int Enemy::GetHeight()
	{
		return charactor.GetHeight();
	}

	int Enemy::GetWidth()
	{
		return charactor.GetWidth();
	}

	void Enemy::SetVerticalSpeed(int value)
	{
		verticalSpeed = value;
	}

	void Enemy::SetHorizontalSpeed(int value)
	{
		horizontalSpeed = value;
	}

	void Enemy::SetCollision(bool value)
	{
		isCollision = value;
	}

	void Enemy::SetDie(bool flag)
	{
		dead = flag;
	}
	void Enemy::SetStatus(string action)
	{
		status = action;
	}

	int Enemy::GetVerticalSpeed()
	{
		return verticalSpeed;
	}
	int Enemy::GetHorizontalSpeed()
	{
		return horizontalSpeed;
	}

	bool Enemy::GetDie()
	{
		return dead;
	}

	string Enemy::GetStatus()
	{
		return status;
	}

	
}