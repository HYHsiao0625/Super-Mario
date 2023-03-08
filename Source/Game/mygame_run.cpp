#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	LoadBackground();
	LoadMap();
	LoadMario();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x41) //key == A
	{
		mario.SetKeyPressed(true);
		mario.SetHorizontalSpeed(-8);
	}
	if (nChar == 0x44) //key == D
	{
		mario.SetKeyPressed(true);
		mario.SetHorizontalSpeed(8);
	}
	if (nChar == VK_SPACE)
	{
		mario.SetKeyPressed(true);
		mario.SetVerticalSpeed(-12);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x41)
	{
		mario.SetHorizontalSpeed(0);
		mario.SetKeyPressed(false);
	}
	if (nChar == 0x44) //key == D
	{
		mario.SetHorizontalSpeed(0);
		mario.SetKeyPressed(false);
	}
	if (nChar == VK_SPACE)
	{
		mario.SetVerticalSpeed(12);
		mario.SetKeyPressed(false);
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	if (world == 1)
	{
		if (level == 1)
		{
			background.SelectShowBitmap(0);
			background.ShowBitmap(4);
			map.ShowBitmap(4);
			mario.ShowBitmap(4);
		}
	}
	mario.UpData();
	if (mario.Top() + mario.Height() * 4 >= map.Top())
	{
		mario.SetVerticalSpeed(0);
		//mario.SetTopLeft(0, 0);
	}

	//----------MARIO-MAP-LIMIT----------
	if (mario.Left() <= map.Left())
	{
		mario.SetHorizontalSpeed(0);
		mario.SetTopLeft(map.Left(),mario.Top());
	}
	if (mario.Left() + mario.Width() * 4 >= map.Left() + map.Width() * 4)
	{
		mario.SetHorizontalSpeed(0);
	}
	//----------MARIO-MAP-LIMIT----------
	//-------------MAP-LIMIT-------------
	if (map.Left() < 0 && mario.Left() <= 384)
	{
		background.SetTopLeft(background.Left() - mario.GetHorizontalSpeed() * 2, background.Top());
		map.SetTopLeft(map.Left() - mario.GetHorizontalSpeed() * 2, map.Top());
		mario.SetTopLeft(384, mario.Top());
	}
	if (mario.Left() >= 512 && map.Left() + map.Width() * 4 >= 1024)
	{
		background.SetTopLeft(background.Left() - mario.GetHorizontalSpeed() * 2, background.Top());
		map.SetTopLeft(map.Left() - mario.GetHorizontalSpeed() * 2, map.Top());
		mario.SetTopLeft(512, mario.Top());
	}
	//-------------MAP-LIMIT-------------
}

void CGameStateRun::LoadMario()
{
	mario.LoadBitmapByString({
		"resources/mario1.bmp",
		"resources/mario2.bmp",
		"resources/mario3.bmp",
		"resources/mario4.bmp"
		}, RGB(146, 144, 255));
	mario.SetTopLeft(0, 0);
	mario.SelectShowBitmap(0);
	mario.SetHorizontalSpeed(0);
	mario.SetVerticalSpeed(GRAVITY);
}

void CGameStateRun::LoadBackground()
{
	background.LoadBitmapByString({
		"resources/1-1 backgorund.bmp"
		});
	background.SetTopLeft(0, 0);
}
void CGameStateRun::LoadMap()
{
	map.LoadBitmapByString({
		"resources/1-1 floor.bmp"
		});
	map.SetTopLeft(0, 208 * 4 + 1);
}