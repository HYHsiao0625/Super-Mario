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
#include "enemy.h"
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
	vector<Goomba> Enemyfactor::GetMonsterlist()
	{
		return monster_list;
	}
	void Enemyfactor::Load()
	{
		Goomba monster;

		for (int i = 0; i < 2; i++)
		{
			monster_temp.push_back(0);
			
		}
		for (int i = 0; i < 5; i++)
		{
			monster_list.push_back(monster);
			monster_position.push_back(monster_temp);
		}
		monster_temp.clear();
		ifstream ifs("resources/enemyposition.txt");
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				ifs >> monster_position[i][j];
				switch (monster_position[i][0])
				{
					case 1:
						monster_list[i].Load();
						monster_list[i].SetTopLeft(monster_position[i][1], 768);
						monster_list[i].SetHorizontalSpeed(-4);
						monster_list[i].SetStatus("appear");
					default:
						break;
				}
			}
		}
		ifs.close();
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
			monster_list[i].UpData(monster_list[i], mario,map);
		}
	}
	// ! ENEMYFACTO
}