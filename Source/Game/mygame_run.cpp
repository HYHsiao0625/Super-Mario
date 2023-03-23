#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "string"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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

void CGameStateRun::OnMove()							// ���ʹC������
{
	if (-10 <= mario.GetTop() + mario.GetHeight() - monster.GetTop() 
		&& mario.GetTop() + mario.GetHeight() - monster.GetTop() <= 0 
		&& mario.GetLeft()+ mario.GetWidth() > monster.GetLeft() 
		&& mario.GetLeft() < monster.GetLeft() + monster.GetWidth()
		){
		mario.SetDie(false);
		monster.SetStatus("dead");
	}
	else if (mario.GetTop() > 900 || monster.IsOverlap(mario, monster) && monster.GetStatus() != "dead") 
	{
		mario.SetDie(true);
	}
	if (mario.GetDie()) {
		OnInit();
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	LoadBackground();
	LoadFloor();
	LoadMario();
	LoadBlock();
	LoadMonster();
	mario.SetDie(false);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == 0x41)
	{
		mario.SetKeyPressed(true);
		mario.SetHorizontalSpeed(-8);
		mario.SetStatus("leftwalk");
	}
	if (nChar == 0x44) //key(2) == D
	{
		mario.SetKeyPressed(true);
		mario.SetHorizontalSpeed(8);
		mario.SetStatus("rightwalk");
	}
	if (nChar == VK_SPACE)
	{
		mario.SetKeyPressed(true);
		mario.SetVerticalSpeed(-12);
		mario.SetStatus("jump");
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x41)
	{
		mario.SetStatus("initial");
		mario.SetHorizontalSpeed(0);
		mario.SetKeyPressed(false);
	}
	if (nChar == 0x44) //key(2)== D
	{	
		mario.SetStatus("initial");
		mario.SetHorizontalSpeed(0);
		mario.SetKeyPressed(false);
	}
	if (nChar == VK_SPACE)
	{
		mario.SetStatus("initial");
		mario.SetVerticalSpeed(12);
		mario.SetKeyPressed(false);
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
}

void CGameStateRun::OnShow()
{
	mario.UpData();
	monster.UpData();
	if (world == 1)
	{
		if (level == 1)
		{
			background.ShowBitmap();
			floor.ShowBitmap();
			block1.ShowBitmap();
			block2.ShowBitmap();
			block3.ShowBitmap();
			monster.ShowBitmap();
			mario.ShowBitmap();
			ShowMarioPostion();
		}
	}
	if (mario.GetStatus() == "initial")
	{
		mario.SetFrameIndexOfBitmap(0);
	}
	if (mario.GetStatus() == "rightwalk")
	{
		mario.SetAnimation(120, false);
	}


	if(floor.GetLeft() + 4416 <= mario.GetLeft() && mario.GetLeft() + mario.GetWidth() <= floor.GetLeft() + 4543)
	{
		mario.SetCollision(false);
		mario.SetVerticalSpeed(24);
	}
	else
	{
		mario.SetCollision(true);
	}

	if (mario.GetTop() + mario.GetHeight() >= floor.GetTop() && mario.IsCollision())
	{   
		mario.SetVerticalSpeed(0);
		mario.SetTopLeft(mario.GetLeft(), floor.GetTop() - mario.GetHeight());

		//mario.SetTopLeft(0, 0);
	}
	//----------MARIO-floor-LIMIT----------
	if (mario.GetLeft() <= floor.GetLeft())
	{
		mario.SetHorizontalSpeed(0);
		mario.SetTopLeft(floor.GetLeft(), mario.GetTop());
	}
	if (mario.GetLeft() + mario.GetWidth() >= floor.GetLeft() + floor.GetWidth())
	{
		mario.SetHorizontalSpeed(0);
	}
	//----------MARIO-floor-LIMIT----------

	//-------------floor-LIMIT-------------
	if (floor.GetLeft() < 0 && mario.GetLeft() <= 384)
	{
		background.SetTopLeft(background.GetLeft() - mario.GetHorizontalSpeed(), background.GetTop());
		floor.SetTopLeft(floor.GetLeft() - mario.GetHorizontalSpeed(), floor.GetTop());
		block1.SetTopLeft(block1.GetLeft() - mario.GetHorizontalSpeed(), block1.GetTop());
		block2.SetTopLeft(block2.GetLeft() - mario.GetHorizontalSpeed(), block2.GetTop());
		block3.SetTopLeft(block3.GetLeft() - mario.GetHorizontalSpeed(), block3.GetTop());
		mario.SetTopLeft(384, mario.GetTop());
	    monster.SetTopLeft(monster.GetLeft() - mario.GetHorizontalSpeed(), monster.GetTop());
		
	}
	if (mario.GetLeft() >= 512 && floor.GetLeft() + floor.GetWidth() >= 1024)
	{
		background.SetTopLeft(background.GetLeft() - mario.GetHorizontalSpeed(), background.GetTop());
		floor.SetTopLeft(floor.GetLeft() - mario.GetHorizontalSpeed(), floor.GetTop());
		block1.SetTopLeft(block1.GetLeft() - mario.GetHorizontalSpeed(), block1.GetTop());
		block2.SetTopLeft(block2.GetLeft() - mario.GetHorizontalSpeed(), block2.GetTop());
		block3.SetTopLeft(block3.GetLeft() - mario.GetHorizontalSpeed(), block3.GetTop());
		monster.SetTopLeft(monster.GetLeft() - mario.GetHorizontalSpeed(), monster.GetTop());
		mario.SetTopLeft(512, mario.GetTop());
	}
	//-------------MonsterSet------------
	if (monster.GetLeft()-mario.GetLeft() <= 512 && monster.GetStatus() != "dead")
	{
		monster.SetHorizontalSpeed(-4);
	}
	else
	{
		monster.SetHorizontalSpeed(0);
	}
	//-------------floor-LIMIT-------------
}

void CGameStateRun::LoadMario()
{
	mario.LoadBitmapByString({
		"resources/mario1.bmp",
		"resources/mario2.bmp",
		"resources/mario3.bmp",
		"resources/mario4.bmp",
		
		}, RGB(146, 144, 255));
	mario.SetTopLeft(0, 0);
	mario.SetHorizontalSpeed(0);
	mario.SetVerticalSpeed(GRAVITY);
}

void CGameStateRun::LoadMonster()
{
	monster.LoadBitmapByString({
		"resources/mario7.bmp",
		}, RGB(146, 144, 255));
	monster.SetTopLeft(2000, 768);
	monster.SetHorizontalSpeed(0);
	monster.SetStatus("appear");
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

void CGameStateRun::LoadBlock()
{
	block1.LoadBitmapByString({
		"resources/block.bmp",
		});
	block2.LoadBitmapByString({
		"resources/block.bmp",
		});
	block3.LoadBitmapByString({
		"resources/block.bmp",
		});
	block1.SetTopLeft(512, floor.GetTop() - block1.GetWidth() * 1);
	block2.SetTopLeft(512, floor.GetTop() - block2.GetWidth() * 2);
	block3.SetTopLeft(256, floor.GetTop() - block3.GetWidth() * 3);
}


void CGameStateRun::ShowMarioPostion()
{
	CDC *pDC = CDDraw::GetBackCDC();
	if (world == 1 && level == 1)
	{

		CTextDraw::ChangeFontLog(pDC, 21, "�L�n������", RGB(0, 0, 0), 800);
		
		CTextDraw::Print(pDC, 0, 0, "MARIO:");
		CTextDraw::Print(pDC, 0, 16, std::to_string(mario.GetLeft()));
		CTextDraw::Print(pDC, 0, 32, std::to_string(mario.GetTop()));
		CTextDraw::Print(pDC, 0, 48, std::to_string(mario.GetVerticalSpeed()));

		CTextDraw::Print(pDC, 0, 64, "floor:");
		CTextDraw::Print(pDC, 0, 80, std::to_string(floor.GetLeft()));
		CTextDraw::Print(pDC, 0, 96, std::to_string(floor.GetTop()));
	}
	CDDraw::ReleaseBackCDC();
	
}