#include "stdafx.h"
#include "../Core/game.h"
#include "../Core/MainFrm.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <direct.h>
#include <string.h>
#include "audio.h"
#include "gameutil.h"
#include "gamecore.h"
#include "Enemy.h"
#include "Shlwapi.h"
#include "../Game/config.h"
#include "../Game/mygame.h"
#include "goomba.h"
#include <filesystem>
#include <experimental/filesystem> // Header file for pre-standard implementation
#include <comdef.h>
#include <iostream>
#include <fstream>

namespace game_framework
{
	Enemyfactor::Enemyfactor() {

	}
	Enemyfactor::~Enemyfactor()
	{
	}
	void Enemyfactor::Load()
	{
		Goomba monster;

		for (int i = 0; i < 5; i++)
		{
			//monster_temp.push_back(0);
			monster_list.push_back(monster);
		}
		for (int i = 0; i < 5; i++)
		{
			//monster_temp.push_back(0);
			monster_list[i].LoadBitmapByString({
						"resources/block.bmp"
				}, RGB(148, 148, 255));
			monster_list[i].SetTopLeft(monster_position[i], 768);
			monster_list[i].SetHorizontalSpeed(0);
			monster_list[i].SetStatus("appear");
		}
	}

	void Enemyfactor::Show()
	{
		for (int i = 0; i < 5; i++) {
			monster_list[i].ShowBitmap();
		}

	}

	void Enemyfactor::UpData(Mario mario, Map map)
	{
		//Collision(map);

		for (int i = 0; i < 5; i++) {
			monster_list[i].UpData(mario,map);
		}
	}
	vector<Goomba> Enemyfactor::Get_List()
	{
		
		return monster_list;

	}
	// ! ENEMYFACTO
}