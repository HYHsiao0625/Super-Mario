#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "../Library/mario.h"
#include "../Library/goomba.h"
#include "../Library/enemy.h"
#include "../Library/enemyfactor.h"
#include "../Library/map.h"
#include "../Library/item.h"
#include "../Library/mushroom.h"
#include "mygame.h"
#include "string"


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
	background.SetTopLeft(0, 0);
	mario.SetTopLeft(0, 0);
	mario.SetVerticalSpeed(32);
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	LoadBackground();
	map.Load(1, 1);
	enemyfactor.Load(1, 1);
	mario.Load();
	//goomba.Load();
	//goomba.SetTopLeft(50, 384);
	//mushroom.Load();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == 0x41)
	{
		mario.SetHorizontalSpeed(-16);
	}
	if (nChar == 0x44) //key(2) == D
	{
		mario.SetHorizontalSpeed(16);
	}
	if (nChar == VK_SPACE)
	{
		if (mario.IsOnGround() == true) {
			mario.SetJump(true);
		}
		else
		{
			mario.SetJump(false);
		}
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x41)
	{
		mario.SetHorizontalSpeed(0);
	}
	if (nChar == 0x44) //key(2)== D
	{
		mario.SetHorizontalSpeed(0);
	}
	if (nChar == VK_SPACE)
	{
		mario.SetVerticalSpeed(mario.GetVerticalSpeed() + 1);
		mario.SetJump(false);
	}
	if (nChar == 0x52)
	{
		OnBeginState();
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
	int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
	int mario_y = mario.GetTop() / 32;
	mario.UpData(mario, map, enemyfactor, itemfactor);
	itemfactor.UpData(mario ,map);
	map.Updata(mario);
	enemyfactor.UpData(mario, map);
	if (mario.IsDead() == true)
	{
		OnBeginState();
		mario.Reset();
	}

	if (world == 1)
	{
		if (level == 1)
		{
			background.ShowBitmap();
			map.Show();
			mario.Show();
			enemyfactor.Show();
			itemfactor.Show();
			//goomba.ShowBitmap();
			//--------
			ShowMarioPostion();
		}
	}
	//----------MARIO-floor-LIMIT----------
	if (mario.GetLeft() <= map.GetLeft())
	{
		mario.SetHorizontalSpeed(0);
		mario.SetTopLeft(map.GetLeft(), mario.GetTop());
	}
	if (mario.GetLeft() + mario.GetWidth() >= 512)
	{
		mario.SetHorizontalSpeed(0);
		mario.SetTopLeft(map.GetLeft(), mario.GetTop());
	}
	//----------MARIO-floor-LIMIT----------
	if (mario.GetHorizontalSpeed() > 0)
	{
		if (map.GetWidth() + map.GetLeft() > 512 && mario.GetLeft() > 256)
		{
			mario.SetTopLeft(256, mario.GetTop());
			map.SetTopLeft(map.GetLeft() - mario.GetHorizontalSpeed(), map.GetTop());
			background.SetTopLeft(background.GetLeft() - mario.GetHorizontalSpeed(), background.GetTop());
			itemfactor.SetTopLeft(mario.GetHorizontalSpeed(), 0);
		}
	}
	else if (mario.GetHorizontalSpeed() < 0)
	{
		if (map.GetLeft() < 0 && mario.GetLeft() < 128)
		{
			mario.SetTopLeft(128, mario.GetTop());
			map.SetTopLeft(map.GetLeft() - mario.GetHorizontalSpeed(), map.GetTop());
			background.SetTopLeft(background.GetLeft() - mario.GetHorizontalSpeed(), background.GetTop());
		}
	}

}

void CGameStateRun::LoadBackground()
{
	background.LoadBitmapByString({
		"resources/1-1 backgorund.bmp"
		});
	background.SetTopLeft(0, 0);
}

void CGameStateRun::ShowMarioPostion()
{
	int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
	int mario_y = mario.GetTop() / 32;
	CDC *pDC = CDDraw::GetBackCDC();
	if (world == 1 && level == 1)
	{

		CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(0, 0, 0), 800);

		CTextDraw::Print(pDC, 0, 0, "MARIO: ");
		CTextDraw::Print(pDC, 0, 16, "x: " + std::to_string(mario.GetLeft() - map.GetLeft()));
		CTextDraw::Print(pDC, 0, 32, "y: " + std::to_string(mario.GetTop()));
		CTextDraw::Print(pDC, 0, 48, "HorizontalSpeed: " + std::to_string(mario.GetHorizontalSpeed()));
		CTextDraw::Print(pDC, 0, 64, "HIT: " + std::to_string(mario.IsHitbox()));
		CTextDraw::Print(pDC, 0, 80, "VerticalSpeed: " + std::to_string(mario.GetVerticalSpeed()));

		CTextDraw::Print(pDC, 0, 96, std::to_string(mario.IsDead()));
		CTextDraw::Print(pDC, 0, 112, "type:" + std::to_string(map.GetMap()[mario_y][mario_x]));
		//CTextDraw::Print(pDC, 0, 128, "position:" + std::to_string(enemyfactor.Get_List()[0].GetTop()));
	}
	CDDraw::ReleaseBackCDC();

}