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
	void Enemyfactor::Load(int world, int level)
	{
		if (world == 1 && level == 1)
		{
			ifstream ifs("resources/map/1-1/enemy/position.txt");

			vector<int> data_temp;

			for (int i = 0; i < 3; i++)
			{
				data_temp.push_back(0);
			}
			for (int i = 0; i < 7; i++)
			{
				emeny_data.push_back(data_temp);
			}
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					ifs >> emeny_data[i][j];
				}
			}
			ifs.close();

			for (int i = 0; i < 7; i++)
			{
				int monsterType = emeny_data[i][0];
				int monsterPosLeft = emeny_data[i][1];
				int monsterPosTop = emeny_data[i][2];
				switch (monsterType)
				{
				case 1://Goomba怪物
					monster_list.push_back(new Goomba());
					monster_list[i]->Load();
					monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
					monster_list[i]->SetHorizontalSpeed(4);
					break;
				case 2://flower怪物
					monster_list.push_back(new Flower());
					monster_list[i]->Load();
					monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
					break;
				case 3://turtle怪物
					monster_list.push_back(new Turtle());
					monster_list[i]->Load();
					monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
					monster_list[i]->SetHorizontalSpeed(4);
					break;
				case 4://hat goomba怪物
					monster_list.push_back(new HatGoomba());
					monster_list[i]->Load();
					monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
					monster_list[i]->SetHorizontalSpeed(4);
					break;
				default:
					break;
				}
			}
		}
		else if (world == 1 && level == 2)
		{
			ifstream ifs("resources/map/1-2/enemy/position.txt");

			vector<int> data_temp;

			for (int i = 0; i < 3; i++)
			{
				data_temp.push_back(0);
			}
			for (int i = 0; i < 2; i++)
			{
				emeny_data.push_back(data_temp);
			}
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					ifs >> emeny_data[i][j];
				}
			}
			ifs.close();

			for (int i = 0; i < 2; i++)
			{
				int monsterType = emeny_data[i][0];
				int monsterPosLeft = emeny_data[i][1];
				int monsterPosTop = emeny_data[i][2];
				switch (monsterType)
				{
				case 1://Goomba怪物
					monster_list.push_back(new Goomba());
					monster_list[i]->Load();
					monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
					monster_list[i]->SetHorizontalSpeed(4);
					break;
				case 2://flower怪物
					monster_list.push_back(new Flower());
					monster_list[i]->Load();
					monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
					break;
				case 3://turtle怪物
					monster_list.push_back(new Turtle());
					monster_list[i]->Load();
					monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
					monster_list[i]->SetHorizontalSpeed(4);
					break;
				case 4://hatgoomba怪物
					monster_list.push_back(new HatGoomba());
					monster_list[i]->Load();
					monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
					monster_list[i]->SetHorizontalSpeed(4);
					break;
				default:
					break;
				}
			}
		}

	}

	void Enemyfactor::Show()
	{

		for (auto enemy : monster_list) {
			enemy->ShowBitmap();
		}

	}

	void Enemyfactor::SetTopLeft(int x, int y)
	{

		for (auto enemy : monster_list)
		{
			enemy->SetTopLeft(enemy->GetLeft() - x, enemy->GetTop() - y);
		}

	}

	void Enemyfactor::UpData(Mario mario, Map map)
	{
		for (int i = monster_list.size() - 1; i >= 0; i--) {
			if (abs(monster_list[i]->GetLeft() - mario.GetLeft()) < 800) {
				monster_list[i]->UpData(monster_list, mario, map, i);
			}
		}

		for (int i = monster_list.size() - 1; i >= 0; i--) {
			if (monster_list[i]->IsDead() == true) {
				delete monster_list[i];
				monster_list.erase(monster_list.begin() + i);
			}
		}
	}

	void Enemyfactor::Reset()
	{
		for (auto enemy : monster_list)
		{
			for (int i = monster_list.size() - 1; i >= 0; i--) {
				delete monster_list[i];
				monster_list.erase(monster_list.begin() + i);

			}
		}
	}


	// ! ENEMYFACTO
}