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
#include "item.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>

namespace game_framework
{
	Item::Item()
	{
	}

	Item::~Item()
	{

	}


	void Item::ShowBitmap()
	{
		charactor.ShowBitmap();
	}

	void Item::LoadBitmapByString(vector<string> filepaths, COLORREF color)
	{
		charactor.LoadBitmapByString(filepaths, color);
	}
	
	int Item::GetFrameIndexOfBitmap()
	{
		return charactor.GetFrameIndexOfBitmap();
	}

	void Item::SetFrameIndexOfBitmap(int frameIndex)
	{
		charactor.SetFrameIndexOfBitmap(frameIndex);
	}

	void Item::SetAnimation(int delay, bool _once)
	{
		charactor.SetAnimation(delay, _once);
	}
	void Item::SetTopLeft(int x, int y)
	{
		charactor.SetTopLeft(x, y);
	}

	int Item::GetTop()
	{
		return charactor.GetTop();
	}

	int Item::GetLeft()
	{
		return charactor.GetLeft();
	}
	int Item::GetHeight()
	{
		return charactor.GetHeight();
	}

	int Item::GetWidth()
	{
		return charactor.GetWidth();
	}

	void Item::SetVerticalSpeed(int value)
	{
		verticalSpeed = value;
	}

	void Item::SetHorizontalSpeed(int value)
	{
		horizontalSpeed = value;
	}


	int Item::GetVerticalSpeed()
	{
		return verticalSpeed;
	}
	int Item::GetHorizontalSpeed()
	{
		return horizontalSpeed;
	}
}