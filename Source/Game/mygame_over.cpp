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
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g) : CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	//GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
}

void CGameStateOver::OnInit()
{
	finish.LoadBitmapByString({
		"resources/finish.bmp"
		});
}

void CGameStateOver::OnShow()
{
	finish.ShowBitmap();
}
