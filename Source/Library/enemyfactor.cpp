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

		for (int i = 0; i < 2; i++)
		{
			monster_temp.push_back(0);

		}
		for (int i = 0; i < 5; i++)
		{
			monster_position.push_back(monster_temp);
		}
		monster_temp.clear();
		//讀取位子
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				ifs >> monster_position[i][j];
			}
		}

		for (int i = 0; i < 5; i++) 
		{
			switch (monster_position[i][0])
			{
			case 1://Goomba怪物
				monster_list.push_back(new Goomba());
				monster_list[i]->Load();
				monster_list[i]->SetTopLeft(monster_position[i][1], 768);
				monster_list[i]->SetHorizontalSpeed(-4);
				monster_list[i]->SetStatus("appear");
				break;
			case 2://flower怪物
				monster_list.push_back(new Flower());
				monster_list[i]->Load();
				monster_list[i]->SetTopLeft(monster_position[i][1], 580);
				monster_list[i]->SetHorizontalSpeed(0);
				monster_list[i]->SetStatus("appear");
				break;
			case 3://turtle怪物
				monster_list.push_back(new Turtle());
				monster_list[i]->Load();
				monster_list[i]->SetTopLeft(monster_position[i][1], 736);
				monster_list[i]->SetHorizontalSpeed(-4);
				monster_list[i]->SetStatus("appear");
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
		//Collision(map);

		for (auto enemy : monster_list) {
			enemy->UpData(mario, map);
		}
	}
	// ! ENEMYFACTO
}