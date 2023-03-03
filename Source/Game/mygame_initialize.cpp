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
// 這個class為遊戲的遊戲開頭畫面物件
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g) : CGameState(g)
{
	
}

void CGameStateInit::OnInit()
{
	//
	// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
	//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
	//
	load_background();

	ShowInitProgress(0, "Start Initialize...");	// 一開始的loading進度為0%
	Sleep(200);

	ShowInitProgress(66, "Initialize...");
	Sleep(200);
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
	
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x4A)
	{
		GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
	}
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateInit::OnShow()
{
	background.ShowBitmap(4);
	show_title_animation();
	draw_text();
}

void CGameStateInit::load_background() {
	background.LoadBitmapByString({ "resources/title/.bmp/title_background.bmp" });
	background.SetTopLeft(0, 0);
}

void CGameStateInit::show_title_animation() 
{
	titleAnimation.LoadBitmapByString({
		"resources/title/.bmp/title1.bmp", "resources/title/.bmp/title2.bmp", "resources/title/.bmp/title3.bmp", "resources/title/.bmp/title4.bmp",
		"resources/title/.bmp/title5.bmp", "resources/title/.bmp/title6.bmp", "resources/title/.bmp/title7.bmp", "resources/title/.bmp/title8.bmp",
		"resources/title/.bmp/title9.bmp", "resources/title/.bmp/title10.bmp", "resources/title/.bmp/title11.bmp", "resources/title/.bmp/title12.bmp",
		"resources/title/.bmp/title13.bmp", "resources/title/.bmp/title14.bmp", "resources/title/.bmp/title15.bmp", "resources/title/.bmp/title16.bmp",
		"resources/title/.bmp/title17.bmp", "resources/title/.bmp/title18.bmp", "resources/title/.bmp/title19.bmp", "resources/title/.bmp/title20.bmp",
		}, RGB(255, 255, 255));
	titleAnimation.SetTopLeft(100, 100);
	titleAnimation.SetAnimation(80, false);
	titleAnimation.ShowBitmap(3);
}

void CGameStateInit::draw_text() {
	/*
	CDC *pDC = CDDraw::GetBackCDC();
	CFont* fp;

	// Print title 
	CTextDraw::ChangeFontLog(pDC, fp, 36, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 79, 228, "Game Framework Practice");

	// Print info 
	CTextDraw::ChangeFontLog(pDC, fp, 24, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 182, 431, "Press any key to start");

	CDDraw::ReleaseBackCDC();
	*/
}