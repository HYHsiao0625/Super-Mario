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
#include "Goomba.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework
{
	Goomba::Goomba()
	{

	}

	Goomba::~Goomba()
	{

	}

	void Goomba::UpData()
	{
		charactor.SetTopLeft(charactor.GetLeft() + horizontalSpeed, charactor.GetTop() + verticalSpeed);
	}

	void Goomba::ShowBitmap()
	{
		charactor.ShowBitmap();
	}

	void Goomba::LoadBitmapByString(vector<string> filepaths, COLORREF color)
	{
		charactor.LoadBitmapByString(filepaths, color);
	}

	int Goomba::GetFrameIndexOfBitmap()
	{
		return charactor.GetFrameIndexOfBitmap();
	}

	void Goomba::SetFrameIndexOfBitmap(int frameIndex)
	{
		charactor.SetFrameIndexOfBitmap(frameIndex);
	}

	void Goomba::SetAnimation(int delay, bool _once)
	{
		charactor.SetAnimation(delay, _once);
	}
	void Goomba::SetTopLeft(int x, int y)
	{
		charactor.SetTopLeft(x, y);
	}
	int Goomba::GetTop()
	{
		return charactor.GetTop();
	}

	int Goomba::GetLeft()
	{
		return charactor.GetLeft();
	}
	int Goomba::GetHeight()
	{
		return charactor.GetHeight();
	}

	int Goomba::GetWidth()
	{
		return charactor.GetWidth();
	}

	void Goomba::SetVerticalSpeed(int value)
	{
		verticalSpeed = value;
	}

	void Goomba::SetHorizontalSpeed(int value)
	{
		horizontalSpeed = value;
	}

	void Goomba::SetPressedKey(int value)
	{
		pressedKey = value;
	}

	void Goomba::SetCollision(bool value)
	{
		isCollision = value;
	}

	void Goomba::SetKeyPressed(bool flags)
	{
		isKeyPressed = flags;
	}

	void Goomba::SetDie(bool flag)
	{
		dead = flag;
	}
	void Goomba::SetStatus(string action)
	{
		status = action;
	}

	int Goomba::GetVerticalSpeed()
	{
		return verticalSpeed;
	}
	int Goomba::GetHorizontalSpeed()
	{
		return horizontalSpeed;
	}

	bool Goomba::GetDie()
	{
		return dead;
	}

	int Goomba::GetPressedKey()
	{
		return pressedKey;
	}

	string Goomba::GetStatus()
	{
		return status;
	}

	bool Goomba::IsKeyPressed()
	{
		return isKeyPressed;
	}

	bool Goomba::IsCollision()
	{
		return isCollision;
	}
}