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
	map.initalize();
	background.SetTopLeft(0, 0);
	mario.SetTopLeft(0, 0);
	mario.SetVerticalSpeed(12);
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (mario.GetDead() == true)
	{
		mario.Reset();
		OnBeginState();
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	LoadBackground();
	LoadFloor();
	LoadMario();
	LoadGoomba();
	LoadMap();
	mario.Reset();
	enemyfactor.Load();
	//mushroom.Load();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == 0x41)
	{
		mario.SetStatus("leftwalk");
		mario.SetHorizontalSpeed(-16);
	}
	if (nChar == 0x44) //key(2) == D
	{
		mario.SetStatus("rightwalk");
		mario.SetHorizontalSpeed(16);
	}
	if (nChar == VK_SPACE)
	{
		if (mario.IsOnGround() == true) {
			mario.SetStatus("jump");
		}
		else
		{
			mario.SetStatus("stand");
		}
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x41)
	{
		mario.SetHorizontalSpeed(0);
		mario.SetStatus("stand");
	}
	if (nChar == 0x44) //key(2)== D
	{
		mario.SetHorizontalSpeed(0);
		mario.SetStatus("stand");
	}
	if (nChar == VK_SPACE)
	{
		//mario.SetOnGround(false);
		mario.SetStatus("stand");
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
	int mario_x = (mario.GetLeft() - map.GetLeft()) / 64;
	int mario_y = mario.GetTop() / 64;
	mario.UpData(mario, map, enemyfactor,itemfactor);
	itemfactor.UpData(mario ,map);
	//goomba1.UpData(mario, map);
	map.Updata(mario, map);
	enemyfactor.UpData(mario, map);
	if (world == 1)
	{
		if (level == 1)
		{
			background.ShowBitmap();
			map.Show();
			mario.Show();
			enemyfactor.Show();
			itemfactor.Show();
			//mushroom.ShowBitmap();
			ShowMarioPostion();
		}
	}
	//----------MARIO-floor-LIMIT----------
	if (mario.GetLeft() <= map.GetLeft())
	{
		mario.SetHorizontalSpeed(0);
		mario.SetTopLeft(map.GetLeft(), mario.GetTop());
	}
	if (mario.GetLeft() + mario.GetWidth() >= 1024)
	{
		mario.SetHorizontalSpeed(0);
		mario.SetTopLeft(map.GetLeft(), mario.GetTop());
	}
	//----------MARIO-floor-LIMIT----------


}

void CGameStateRun::LoadMario()
{
	mario.Load({
		"resources/mario1.bmp",
		"resources/mario2.bmp",
		"resources/mario3.bmp",
		"resources/mario4.bmp",
		}/*, RGB(146, 144, 255)*/);
}

void CGameStateRun::LoadGoomba()
{
	/*
	flower.LoadBitmapByString({
		"resources/goomba1.bmp",
		"resources/goomba2.bmp",
		"resources/goomba3.bmp",
		}, RGB(146, 144, 255));
	flower.SetTopLeft(800, 570);
	flower.SetHorizontalSpeed(0);
	*/
	/*
	goomba1.LoadBitmapByString({
		"resources/goomba1.bmp",
		"resources/goomba2.bmp",
		"resources/goomba3.bmp",
		}, RGB(146, 144, 255));
	
	goomba1.SetTopLeft(2000, 768);
	goomba1.SetHorizontalSpeed(0);
	goomba1.SetStatus("appear");
	*/
}

void CGameStateRun::LoadBackground()
{
	background.LoadBitmapByString({
		"resources/1-1 backgorund.bmp"
		});
	background.SetTopLeft(0, 0);
}
void CGameStateRun::LoadFloor()
{
	floor.LoadBitmapByString({
		"resources/1-1 floor.bmp"
		}, RGB(255, 255, 255));
	floor.SetTopLeft(0, 832);
}


void CGameStateRun::LoadMap()
{
	map.Load(1, 1);
}

void CGameStateRun::ShowMarioPostion()
{
	int mario_x = (mario.GetLeft() - map.GetLeft()) / 64;
	int mario_y = mario.GetTop() / 64;
	CDC *pDC = CDDraw::GetBackCDC();
	if (world == 1 && level == 1)
	{

		CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(0, 0, 0), 800);

		CTextDraw::Print(pDC, 0, 0, "MARIO: ");
		CTextDraw::Print(pDC, 0, 16, "x: " + std::to_string((mario.GetLeft() - map.GetLeft()) / 64));
		CTextDraw::Print(pDC, 0, 32, "y: " + std::to_string((mario.GetTop()) / 64));
		CTextDraw::Print(pDC, 0, 48, "HorizontalSpeed: " + std::to_string(mario.GetHorizontalSpeed()));
		CTextDraw::Print(pDC, 0, 64, "HIT: " + std::to_string(mario.IsHitbox()));
		CTextDraw::Print(pDC, 0, 80, "GetStatus: " + mario.GetStatus());

		CTextDraw::Print(pDC, 0, 96, "map:");
		CTextDraw::Print(pDC, 0, 112, "type:" + std::to_string(map.GetMap()[mario_y][mario_x]));
		//CTextDraw::Print(pDC, 0, 128, "position:" + std::to_string(enemyfactor.Get_List()[0].GetTop()));
	}
	CDDraw::ReleaseBackCDC();

}