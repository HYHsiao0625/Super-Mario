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
	mario.Reset();
	map.Reset();
	enemyfactor.Reset();
	itemfactor.Reset();
	enemyfactor.Load(world, level);
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (mario.IsDead() == true)
	{
		OnBeginState();
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	LoadBackground();
	map.Load(1, 1);
	enemyfactor.Load(1, 1);
	mario.Load();
	
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == 0x41)//left
	{
		mario.SetHorizontalSpeed(-8);
		mario.face = -1;
	}
	if (nChar == 0x44) //right
	{
		mario.SetHorizontalSpeed(8);
		mario.face = 1;
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
	if (nChar == 0x52)
	{
		mario.SetShot(true);
	}
	if (nChar == 0x53)
	{
		mario.SetDown(true);
	}
	if (nChar == 0x5A)
	{
		OnBeginState();
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
	if (nChar == 0x53)
	{
		mario.SetDown(false);
	}
	if (nChar == 0x58)
	{
		mario.SetMode(!mario.GetMode());
	}
	if (nChar == 0x4A)
	{
		if (level < 4)
		{
			SwitchMap(1, level + 1);
			map.Clear();
			map.Load(1, level + 1);
			mario.SetSwitchMap(false);
			world = 1;
			level++;
			OnBeginState();
		}
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
	itemfactor.UpData(mario ,map);
	map.Updata(mario);
	enemyfactor.UpData(mario, map);
	mario.UpData(mario, map, enemyfactor, itemfactor);

	if (mario.IsDead() == true)
	{
		OnBeginState();
	}

	background.ShowBitmap();
	map.Show();

	mario.Show();
	enemyfactor.Show();
	itemfactor.Show();
	if (mario.IsSwitchMap() == true && level < 4)
	{
		mario.SetVerticalSpeed(8);
		if (mario.IsOnGround() == true)
		{
			SwitchMap(1, level + 1);
			map.Clear();
			map.Load(1, level + 1);
			mario.SetSwitchMap(false);
			world = 1;
			level++;
			OnBeginState();
		}
	}
	else if (mario.IsSwitchMap() == true && level == 4)
	{
		mario.SetVerticalSpeed(8);
		if (mario.IsOnGround() == true)
		{
			mario.Reset();
			map.Reset();
			enemyfactor.Reset();
			itemfactor.Reset();
			ThemeSoundEffect->Stop(0);
			GotoGameState(GAME_STATE_OVER);
		}
	}
	ShowMarioPostion();

	/*
	if (world == 1 && level == 1)
	{
		background.ShowBitmap();
		map.Show();
		mario.Show();
		enemyfactor.Show();
		itemfactor.Show();
		//--------
		ShowMarioPostion();
		if (mario.IsSwitchMap() == true)
		{
			mario.SetVerticalSpeed(4);
			if (mario.IsOnGround() == true)
			{
				SwitchMap(1, 2);
				map.Clear();
				map.Load(1, 2);
				mario.SetSwitchMap(false);
				world = 1;
				level = 2;
				OnBeginState();
			}
		}
	}
	else if (world == 1 && level == 2)
	{
		background.ShowBitmap();
		map.Show();
		mario.Show();
		enemyfactor.Show();
		itemfactor.Show();
	}*/
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
			enemyfactor.SetTopLeft(mario.GetHorizontalSpeed(), 0);

			mario.FireballSetTopLeft(mario.GetHorizontalSpeed(), 0);
		}
	}
	else if (mario.GetHorizontalSpeed() < 0)
	{
		if (map.GetLeft() < 0 && mario.GetLeft() < 128)
		{
			mario.SetTopLeft(128, mario.GetTop());
			map.SetTopLeft(map.GetLeft() - mario.GetHorizontalSpeed(), map.GetTop());
			background.SetTopLeft(background.GetLeft() - mario.GetHorizontalSpeed(), background.GetTop());
			itemfactor.SetTopLeft(mario.GetHorizontalSpeed(), 0);
			enemyfactor.SetTopLeft(mario.GetHorizontalSpeed(), 0);
			mario.FireballSetTopLeft(mario.GetHorizontalSpeed(), 0);
		}
	}
	
}

void CGameStateRun::LoadBackground()
{
	background.LoadBitmapByString({
		"resources/1-1 backgorund.bmp"
		});
	background.SetTopLeft(0, 0);

	//Load ThemeSoundEffect
	ThemeSoundEffect->Load(0, "Resources/SoundEffects/Theme.mp3");
	ThemeSoundEffect->Play(0, true);

}

void CGameStateRun::ShowMarioPostion()
{
	int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
	int mario_y = mario.GetTop() / 32;
	CDC *pDC = CDDraw::GetBackCDC();

  CTextDraw::ChangeFontLog(pDC, 16, "微軟正黑體", RGB(0, 0, 0), 800);

  CTextDraw::Print(pDC, 0, 0, "STAGE: " + to_string(world) + "-" + to_string(level));
  CTextDraw::Print(pDC, 0, 16, "Hnbeatable_time: " + std::to_string(mario.GetHnbeatable_time()));
  CTextDraw::Print(pDC, 0, 32, "fireable: " + std::to_string(mario.isShotable));
  //CTextDraw::Print(pDC, 0, 48, "VerticalSpeed: " + std::to_string(mario.GetVerticalSpeed()));
  CTextDraw::Print(pDC, 0, 72, "x: " + std::to_string(mario.GetLeft() - map.GetLeft()));
  CTextDraw::Print(pDC, 0, 84, "y: " + std::to_string(mario.GetTop()));
  //CTextDraw::Print(pDC, 0, 100, "IsOnGround: " + std::to_string(mario.IsOnGround()));
  //CTextDraw::Print(pDC, 0, 128, "position:" + std::to_string(enemyfactor.Get_List()[0].GetTop()));
	CDDraw::ReleaseBackCDC();

}

void CGameStateRun::SwitchMap(int world, int level)
{
	switchAnimation.LoadBitmapByString({
		"resources/switchAnimation.bmp"
		});
	switchAnimation.SetTopLeft(0, 0);
	switchAnimation.ShowBitmap();
}