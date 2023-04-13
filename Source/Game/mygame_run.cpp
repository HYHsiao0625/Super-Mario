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
	if (-10 <= mario.GetTop() + mario.GetHeight() - goomba.GetTop()
		&& mario.GetTop() + mario.GetHeight() - goomba.GetTop() <= 0
		&& mario.GetLeft() + mario.GetWidth() > goomba.GetLeft()
		&& mario.GetLeft() < goomba.GetLeft() + goomba.GetWidth()
		) {
		mario.SetDie(false);
		goomba.SetStatus("dead");
		goomba.SetFrameIndexOfBitmap(2);
	}
	else if (mario.GetTop() > 900 || goomba.charactor.IsOverlap(mario.charactor, goomba.charactor) && goomba.GetStatus() != "dead")
	{
		mario.SetDie(true);
	}
	if (mario.GetDie()) {
		OnBeginState();
		mario.SetDie(false);
	}
	/*
	if (mario.GetStatus() == "rightwalk" && map.Isoverlamp(mario, floor)) {
		mario.SetStatus("initial");
		mario.SetHorizontalSpeed(0);
		mario.SetKeyPressed(false);
	}
	if (mario.GetStatus() == "leftwalk" && map.Isoverlamp(mario, floor)) {
		mario.SetStatus("initial");
		mario.SetHorizontalSpeed(0);
		mario.SetKeyPressed(false);
	}
	if (mario.GetJump() && map.Isoverlamp(mario, floor)) {
		mario.SetStatus("initial");
		mario.SetHorizontalSpeed(0);
		mario.SetKeyPressed(false);
		mario.SetVerticalSpeed(24);
	}
	else if (mario.GetJump()==false && !(map.Ontheground(mario, floor))) {

		mario.SetVerticalSpeed(24);
	}
	if (mario.GetJump() == false && map.Ontheground(mario, floor)) {
		mario.SetTopLeft(mario.GetLeft(), mario.GetTop());
		mario.SetVerticalSpeed(0);
	}*/
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	LoadBackground();
	LoadFloor();
	LoadMario();
	LoadGoomba();
	LoadMap();
	mario.SetDie(false);
	goomba.SetTopLeft(1468, 768);
	goomba.SetHorizontalSpeed(0);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == 0x41)
	{
		mario.SetStatus("leftwalk");
		mario.SetHorizontalSpeed(-32);
	}
	if (nChar == 0x44) //key(2) == D
	{
		mario.SetStatus("rightwalk");
		mario.SetHorizontalSpeed(32);
	}
	if (nChar == VK_SPACE)
	{
		if (mario.GetOnGround() == "true" ) {
			mario.SetStatus("jump");
			mario.SetOnGround(false);
		}
		else {
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
		mario.SetOnGround(false);
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

	mario.UpData(mario, map);
	goomba.UpData(mario ,map);
	goomba1.UpData(mario, map);
	if (world == 1)
	{
		if (level == 1)
		{
			background.ShowBitmap();
			//floor.ShowBitmap();
			map.Show();
			mario.Show();
			goomba.ShowBitmap();
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

	//-------------floor-LIMIT-------------
	if (map.GetLeft() < 0 && mario.GetLeft() <= 384)
	{
		background.SetTopLeft(background.GetLeft() - mario.GetHorizontalSpeed(), background.GetTop());
		//floor.SetTopLeft(floor.GetLeft() - mario.GetHorizontalSpeed(), floor.GetTop());
		mario.SetTopLeft(384, mario.GetTop());
		goomba.Limit(floor, mario);
		map.SetTopLeft(map.GetLeft() - mario.GetHorizontalSpeed(), 0);
	}
	if (mario.GetLeft() >= 512 && map.GetLeft() + map.GetWidth() >= 1024)
	{
		background.SetTopLeft(background.GetLeft() - mario.GetHorizontalSpeed(), background.GetTop());
		floor.SetTopLeft(floor.GetLeft() - mario.GetHorizontalSpeed(), floor.GetTop());
		//floor.SetTopLeft(floor.GetLeft() - mario.GetHorizontalSpeed(), floor.GetTop());
		goomba.Limit(floor, mario);
		map.SetTopLeft(map.GetLeft() - mario.GetHorizontalSpeed(), 0);
		mario.SetTopLeft(512, mario.GetTop());
	}

	//-------------MonsterSet------------
	

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
	goomba.LoadBitmapByString({
		"resources/goomba1.bmp",
		"resources/goomba2.bmp",
		"resources/goomba3.bmp",
		}, RGB(146, 144, 255));
	goomba.SetTopLeft(2368, 768);
	goomba.SetTopLeft(1468, 768);
	goomba.SetHorizontalSpeed(0);
	goomba.SetStatus("appear");

	goomba1.LoadBitmapByString({
		"resources/goomba1.bmp",
		"resources/goomba2.bmp",
		"resources/goomba3.bmp",
		}, RGB(146, 144, 255));
	goomba1.SetTopLeft(2000, 768);
	goomba1.SetHorizontalSpeed(0);
	goomba1.SetStatus("appear");
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
	CDC *pDC = CDDraw::GetBackCDC();
	if (world == 1 && level == 1)
	{

		CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(0, 0, 0), 800);

		CTextDraw::Print(pDC, 0, 0, "MARIO:");
		CTextDraw::Print(pDC, 0, 16, "x:" + std::to_string(mario.GetLeft() / 64));
		CTextDraw::Print(pDC, 0, 32, "y:" + std::to_string((mario.GetTop()) / 64));
		CTextDraw::Print(pDC, 0, 48, "OnGround"+mario.GetOnGround());
		CTextDraw::Print(pDC, 0, 64, "GetHitbox"+mario.GetHitbox());
		CTextDraw::Print(pDC, 0, 80, "GetStatus"+mario.GetStatus());

		CTextDraw::Print(pDC, 0, 96, "floor:");
		CTextDraw::Print(pDC, 0, 112, "x:" + std::to_string(floor.GetLeft()));
		CTextDraw::Print(pDC, 0, 128, "y:" + std::to_string(floor.GetTop()));
		CTextDraw::Print(pDC, 0, 48, "HorizontalSpeed"+ std::to_string(mario.GetHorizontalSpeed()));
		CTextDraw::Print(pDC, 0, 64, "GetHitbox"+mario.GetHitbox());
		CTextDraw::Print(pDC, 0, 80, "GetStatus"+mario.GetStatus());

		CTextDraw::Print(pDC, 0, 96, "map:");
		CTextDraw::Print(pDC, 0, 112, "x:" + std::to_string(map.GetLeft()));
		CTextDraw::Print(pDC, 0, 128, "width:" + std::to_string(map.GetWidth()));
	}
	CDDraw::ReleaseBackCDC();

}