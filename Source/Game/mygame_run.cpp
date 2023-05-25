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
	map.initalize();
	mario.Load();
	background.SetTopLeft(0, 0);
	mario.SetTopLeft(0, 0);
	mario.SetVerticalSpeed(12);
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	if (mario.IsDead() == true)
	{
		mario.Reset();
		OnBeginState();
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	LoadBackground();
	LoadMap(1, 1);
	mario.Load();
	enemyfactor.Load();
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
		mario.SetJump(false);
	}
	if (nChar == 0x52)
	{
		OnBeginState();
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

void CGameStateRun::LoadBackground()
{
	background.LoadBitmapByString({
		"resources/1-1 backgorund.bmp"
		});
	background.SetTopLeft(0, 0);
}


void CGameStateRun::LoadMap(int world, int level)
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

		CTextDraw::ChangeFontLog(pDC, 21, "�L�n������", RGB(0, 0, 0), 800);

		CTextDraw::Print(pDC, 0, 0, "MARIO: ");
		CTextDraw::Print(pDC, 0, 16, "x: " + std::to_string((mario.GetLeft() - map.GetLeft()) / 64));
		CTextDraw::Print(pDC, 0, 32, "y: " + std::to_string((mario.GetTop()) / 64));
		CTextDraw::Print(pDC, 0, 48, "HorizontalSpeed: " + std::to_string(mario.GetHorizontalSpeed()));
		CTextDraw::Print(pDC, 0, 64, "HIT: " + std::to_string(mario.IsHitbox()));
		CTextDraw::Print(pDC, 0, 80, "GetStatus: " + mario.IsJump());

		CTextDraw::Print(pDC, 0, 96, "map:");
		CTextDraw::Print(pDC, 0, 112, "type:" + std::to_string(map.GetMap()[mario_y][mario_x]));
		//CTextDraw::Print(pDC, 0, 128, "position:" + std::to_string(enemyfactor.Get_List()[0].GetTop()));
	}
	CDDraw::ReleaseBackCDC();

}