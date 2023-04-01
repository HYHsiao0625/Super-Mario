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
	Mario::Mario()
	{

	}

	void Mario::UpData()
	{
		charactor.SetTopLeft(charactor.GetLeft() + horizontalSpeed, charactor.GetTop() + verticalSpeed);
	}

	void Mario::ShowBitmap()
	{
		charactor.ShowBitmap();
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
	void Mario::SetTopLeft(int x,int y)
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

	void Mario::SetPressedKey(int value)
	{
		pressedKey = value;
	}

	void Mario::SetCollision(bool value)
	{
		isCollision = value;
	}

	void Mario::SetKeyPressed(bool flags)
	{
		isKeyPressed = flags;
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

	bool Mario::IsCollision()
	{
		return isCollision;
	}
}