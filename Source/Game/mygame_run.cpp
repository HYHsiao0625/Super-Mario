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
	background.ShowBitmap(3);
	map.ShowBitmap(3);
	character.ShowBitmap();
	if (character.GetHolding())
	{
		int x = character.Left();
		int y = character.Top();
		switch (character.GetKey())
		{
		case 0:
			break;
		case 1:
			character.SetTopLeft(character.Left(), character.Top() - 1);
			break;
		case 2:
			character.LoadBitmapByString({ "Resources/Playable Characters/walk/.bmp/walk1.bmp","Resources/Playable Characters/walk/.bmp/walk2.bmp",
											"Resources/Playable Characters/walk/.bmp/walk3.bmp","Resources/Playable Characters/walk/.bmp/walk4.bmp" }, RGB(207, 176, 255));
			character.SetAnimation(200, false);
			character.SetTopLeft(x + 2, y);
			break;
		case 3:
			character.SetTopLeft(character.Left(), character.Top() + 1);
			break;
		case 4:
			character.SetTopLeft(character.Left() - 1, character.Top());
			break;
		default:
			break;
		}
	}

}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	int characterstate = 0;
	background.LoadBitmapByString({ 
		"resources/map/hub/hub_background.bmp",
	});
	background.SetTopLeft(0, 0);

	map.LoadBitmapByString({
		"resources/map/hub/hub.bmp",
		}, RGB(255, 255, 255));
	map.SetTopLeft(0, 0);

	character.LoadBitmapByString({ "Resources/Playable Characters/others/.bmp/basic1.bmp","Resources/Playable Characters/others/.bmp/basic2.bmp" }, RGB(207, 176, 255));
	character.SetAnimation(700, false);
	character.SetTopLeft(300, 200);

}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//GotoGameState(GAME_STATE_OVER);

	if (nChar == VK_UP)
	{
		character.SetKey(1);
		character.SetHolding(true);
	}
	if (nChar == VK_RIGHT)
	{
		character.SetKey(2);
		character.SetHolding(true);
	}
	if (nChar == VK_DOWN)
	{
		character.SetKey(3);
		character.SetHolding(true);
	}
	if (nChar == VK_LEFT)
	{
		character.SetKey(4);
		character.SetHolding(true);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP)
	{
		character.SetHolding(false);
	}
	if (nChar == VK_RIGHT)
	{
		character.SetHolding(false);
	}
	if (nChar == VK_DOWN)
	{
		character.SetHolding(false);
	}
	if (nChar == VK_LEFT)
	{
		character.SetHolding(false);
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

}

/*
void CGameStateRun::show_text_by_phase() {
	CDC *pDC = CDDraw::GetBackCDC();
	CFont* fp;

	CTextDraw::ChangeFontLog(pDC, fp, 21, "�L�n������", RGB(0, 0, 0), 800);

	if (phase == 1 && sub_phase == 1) {
		CTextDraw::Print(pDC, 237, 128, "�ק�A���D���I");
		CTextDraw::Print(pDC, 55, 163, "�N�Ǧ��洫�� resources ���� giraffe.bmp �ϼˡI");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 2 && sub_phase == 1) {
		CTextDraw::Print(pDC, 26, 128, "�U�@�Ӷ��q�A�����V������z�L�W�U���k���ʨ�o�Ӧ�m�I");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 3 && sub_phase == 1) {
		CTextDraw::Print(pDC, 205, 128, "���A�ǳƤF�@���_�c");
		CTextDraw::Print(pDC, 68, 162, "�]�p�{�������V���N���_�c��A�N�_�c�����I");
		CTextDraw::Print(pDC, 68, 196, "�O�o�_�c�n�h�I�A�ϥ� RGB(255, 255, 255)");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 4 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "���A�ǳƤF�@�ӻe���n�B��");
		CTextDraw::Print(pDC, 89, 162, "�w�g�������F��V���ʵe�A�����i�H�W�U����");
		CTextDraw::Print(pDC, 110, 196, "�g�ӵ{�������A���e���n�B�;֦��ʵe�I");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 5 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "���A�ǳƤF�T����");
		CTextDraw::Print(pDC, 89, 162, "�]�p�{�������V���N�������A���|���}");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
	} else if (phase == 6 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "���A�ǳƤF�@���|�˼ƪ��y");
		CTextDraw::Print(pDC, 89, 162, "�]�p�{�����y�˼ơA�M����� OK �ᰱ��ʵe");
		CTextDraw::Print(pDC, 373, 537, "���U Enter �������");
		
	} else if (sub_phase == 2) {
		CTextDraw::Print(pDC, 268, 128, "�����I");
	}

	CDDraw::ReleaseBackCDC();
}*/