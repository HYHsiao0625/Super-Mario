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

}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	LoadBackground();
	LoadMap();
	LoadMario();
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
	if (world == 1)
	{
		if (level == 1)
		{
			background.ShowBitmap(4);
			map.ShowBitmap(4);
			mario.ShowBitmap(4);
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
	if (mario.GetStatus() == "jump")
	{
		mario.SetFrameIndexOfBitmap(0);
	}


	if(map.GetLeft() + 1104 * 4 <= mario.GetLeft() && mario.GetLeft() <= map.GetLeft() + 1135 * 4)
	{
		mario.SetCollision(false);
		mario.SetVerticalSpeed(12);
	}
	else
	{
		mario.SetCollision(true);
	}

	if (mario.GetTop() + mario.GetHeight() * 4 >= map.GetTop() && mario.IsCollision())
	{   
		mario.SetVerticalSpeed(0);
		mario.SetTopLeft(mario.GetLeft(), 770);
		//mario.SetTopLeft(0, 0);
	}
	//----------MARIO-MAP-LIMIT----------
	if (mario.GetLeft() <= map.GetLeft())
	{
		mario.SetHorizontalSpeed(0);
		mario.SetTopLeft(map.GetLeft(), mario.GetTop());
	}
	if (mario.GetLeft() + mario.GetWidth() * 4 >= map.GetLeft() + map.GetWidth() * 4)
	{
		mario.SetHorizontalSpeed(0);
	}
	//----------MARIO-MAP-LIMIT----------

	//-------------MAP-LIMIT-------------
	if (map.GetLeft() < 0 && mario.GetLeft() <= 384)
	{
		background.SetTopLeft(background.GetLeft() - mario.GetHorizontalSpeed() * 2, background.GetTop());
		map.SetTopLeft(map.GetLeft() - mario.GetHorizontalSpeed() * 2, map.GetTop());
		mario.SetTopLeft(384, mario.GetTop());
	}
	if (mario.GetLeft() >= 512 && map.GetLeft() + map.GetWidth() * 4 >= 1024)
	{
		background.SetTopLeft(background.GetLeft() - mario.GetHorizontalSpeed() * 2, background.GetTop());
		map.SetTopLeft(map.GetLeft() - mario.GetHorizontalSpeed() * 2, map.GetTop());
		mario.SetTopLeft(512, mario.GetTop());
	}
	//-------------MAP-LIMIT-------------
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

		CTextDraw::Print(pDC, 0, 64, "MAP:");
		CTextDraw::Print(pDC, 0, 80, std::to_string(map.GetLeft()));
		CTextDraw::Print(pDC, 0, 96, std::to_string(map.GetTop()));
	}
	CDDraw::ReleaseBackCDC();
	
}