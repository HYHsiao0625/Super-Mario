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
	vector<Enemy*> Enemyfactor::GetMonsterlist()
	{
		return monster_list;
	}
	void Enemyfactor::Load()
	{
		ifstream ifs("resources/enemyposition.txt");

		int numMonsters = 0;
		int temp;
		while (ifs >> temp)
		{
			numMonsters++;
			monster_temp.push_back(temp);
		}

		int numPositions = numMonsters / 2;
		monster_position.resize(numPositions, vector<int>(2));
		for (int i = 0; i < numPositions; i++)
		{
			monster_position[i][0] = monster_temp[i * 2];
			monster_position[i][1] = monster_temp[i * 2 + 1];
		}

		for (int i = 0; i < numPositions; i++)
		{
			int monsterType = monster_position[i][0];
			int monsterPos = monster_position[i][1];
			switch (monsterType)
			{
			case 1://Goomba怪物
				monster_list.push_back(new Goomba());
				monster_list[i]->Load();
				monster_list[i]->SetTopLeft(monsterPos, 768);
				monster_list[i]->SetHorizontalSpeed(-4);
				//monster_list[i]->SetStatus("appear");
				break;
			case 2://flower怪物
				monster_list.push_back(new Flower());
				monster_list[i]->Load();
				monster_list[i]->SetTopLeft(monsterPos, 580);
				monster_list[i]->SetHorizontalSpeed(0);
				//monster_list[i]->SetStatus("appear");
				break;
			case 3://turtle怪物
				monster_list.push_back(new Turtle());
				monster_list[i]->Load();
				monster_list[i]->SetTopLeft(monsterPos, 736);
				monster_list[i]->SetHorizontalSpeed(-4);
				//monster_list[i]->SetStatus("appear");
				break;
			default:
				break;
			}
		}
		ifs.close();
	}

	void Enemyfactor::Show()
	{

		for (auto enemy : monster_list) {
			enemy->ShowBitmap();
		}

	}

	void Enemyfactor::UpData(Mario mario, Map map)
	{

		for (auto enemy : monster_list) {
			enemy->UpData(monster_list, mario, map);
		}

		for (int i = monster_list.size() - 1; i >= 0; i--) {
			if (monster_list[i]->IsDead() == true) {
				delete monster_list[i];
				monster_list.erase(monster_list.begin() + i);
			}
		}
	}
	void Enemyfactor::clear()
	{

		for (int i = monster_list.size() - 1; i >= 0; i--) {
				delete monster_list[i];
				monster_list.erase(monster_list.begin() + i);		
		}
	}
	// ! ENEMYFACTO
}