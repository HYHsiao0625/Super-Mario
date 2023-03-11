#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include <string>
#include <windows.h>


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
	int postition_X = mario.Left();
	int postition_Y = mario.Top();
	if (mario.IsKeyPressed() == true) {
		switch (mario.GetPressedKey()) {
			case 1:
				mario.LoadBitmapByString({
				"resources/marioreverse1.bmp",
				"resources/marioreverse2.bmp",
				"resources/marioreverse3.bmp",
				"resources/marioreverse4.bmp"
					}, RGB(146, 144, 255));
				mario.SetTopLeft(postition_X, postition_Y);
				mario.SetHorizontalSpeed(-8);
				break;
			case 2:
				mario.LoadBitmapByString({
				"resources/mario1.bmp",
				"resources/mario2.bmp",
				"resources/mario3.bmp",
				"resources/mario4.bmp"
					}, RGB(146, 144, 255));
				mario.SetTopLeft(postition_X, postition_Y);
				mario.SetHorizontalSpeed(8);
				break;
			}
		mario.SetAnimation(120, false);
	}
	else{
		mario.SetAnimation(100, true);
		mario.SelectShowBitmap(0);
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	LoadBackground();
	LoadMap();
	LoadMario();
	ShowMarioPostion();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == 0x41) //key(1) == A
	{
		mario.SetPressedKey(1);
		mario.SetKeyPressed(true);
	}
	if (nChar == 0x44) //key(2) == D
	{
		mario.SetPressedKey(2);
		mario.SetKeyPressed(true);
	}
	if (nChar == VK_SPACE)
	{
		mario.SetKeyPressed(true);
		mario.SetVerticalSpeed(-8);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x41)
	{
		mario.SetHorizontalSpeed(0);
		mario.SetKeyPressed(false);
	}
	if (nChar == 0x44) //key(2)== D
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
			background.SelectShowBitmap(0);
			background.ShowBitmap(4);
			map.ShowBitmap(4);
			mario.ShowBitmap(4);
			ShowMarioPostion();
		}
	}
	
	if(map.Left() + 1104 * 4 <= mario.Left() && mario.Left() <= map.Left() + 1135 * 4)
	{
		mario.SetCollision(false);
		mario.SetVerticalSpeed(12);
	}
	else
	{
		mario.SetCollision(true);
	}
	if (mario.Top() + mario.Height() * 4 >= map.Top() && mario.IsCollision())
	{   
			mario.SetVerticalSpeed(0);
			mario.SetTopLeft(mario.Left(), 770);
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

void CGameStateRun::ShowMarioPostion()
{
	CDC *pDC = CDDraw::GetBackCDC();
	CFont* fp;
	if (world == 1 && level == 1)
	{

		CTextDraw::ChangeFontLog(pDC, fp, 21, "�L�n������", RGB(0, 0, 0), 800);
		
		CTextDraw::Print(pDC, 0, 0, "MARIO:");
		CTextDraw::Print(pDC, 0, 16, std::to_string(mario.Left()));
		CTextDraw::Print(pDC, 0, 32, std::to_string(mario.Top()));
		CTextDraw::Print(pDC, 0, 48, std::to_string(mario.GetVerticalSpeed()));

		CTextDraw::Print(pDC, 0, 64, "MAP:");
		CTextDraw::Print(pDC, 0, 80, std::to_string(map.Left()));
		CTextDraw::Print(pDC, 0, 96, std::to_string(map.Top()));
	}
	CDDraw::ReleaseBackCDC();
	
}