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
	ShowInitProgress(0, "Start Initialize...");	// �@�}�l��loading�i�׬�0%
	Sleep(200);

	LoadTitle();

	ShowInitProgress(66, "Initialize...");
	Sleep(200);
	//
	// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
	//
}

void CGameStateInit::OnBeginState()
{
	
}

void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP || nChar == 0x57)
	{
		switch (player)
		{
		default:
			break;
		case 1:
			break;
		case 2:
			player = 1;
			select.SetTopLeft(72 * 4 + 1, 144 * 4 + 2);
		}
	}
	if (nChar == VK_DOWN || nChar == 0x53)
	{
		switch (player)
		{
		default:
			break;
		case 1:
			player = 2;
			select.SetTopLeft(72 * 4 + 1, 160 * 4 + 2);
		case 2:
			break;
		}
	}
	if (nChar == VK_RETURN)
	{
		GotoGameState(GAME_STATE_RUN);
	}

}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//GotoGameState(GAME_STATE_RUN);		// 切換至GAME_STATE_RUN
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CGameStateInit::OnShow()
{
	title.ShowBitmap(4);
	coin.ShowBitmap(4);
	coin.SetAnimation(150, false);
	select.ShowBitmap(4);
	//draw_text();
}

void CGameStateInit::LoadTitle() {
	player = 1;
	title.LoadBitmapByString({ "resources/title.bmp" });
	title.SetTopLeft(0, 0);
	coin.LoadBitmapByString({
		"resources/coin_overworld1.bmp",
		"resources/coin_overworld2.bmp",
		"resources/coin_overworld3.bmp",
		"resources/coin_overworld1.bmp",
		});
	coin.SetTopLeft(88 * 4 + 1, 24 * 4);
	select.LoadBitmapByString({
		"resources/select.bmp",
		"resources/reject.bmp"
		});
	if (player == 1)
	{
		select.SetTopLeft(72 * 4 + 1, 144 * 4 + 2);
	}
	else
	{
		select.SetTopLeft(72 * 4 + 1, 160 * 4 + 2);
	}

}

/*void CGameStateInit::draw_text() {
	CDC *pDC = CDDraw::GetBackCDC();
	CFont* fp;

	// Print title 
	CTextDraw::ChangeFontLog(pDC, fp, 36, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 79, 228, "Game Framework Practice");

	// Print info 
	CTextDraw::ChangeFontLog(pDC, fp, 24, "微軟正黑體", RGB(255, 255, 255));
	CTextDraw::Print(pDC, 182, 431, "Press any key to start");

	CDDraw::ReleaseBackCDC();
}*/