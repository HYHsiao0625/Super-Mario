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
		emeny_data.clear();

		std::string filePath = "resources/map/" + std::to_string(world) + "-" + std::to_string(level) + "/enemy/position.txt";
		ifstream ifs(filePath);

		int monsterType, monsterPosLeft, monsterPosTop, mosterSpeed;
		while (ifs >> monsterType >> monsterPosLeft >> monsterPosTop>>mosterSpeed)
		{
			emeny_data.push_back({ monsterType, monsterPosLeft, monsterPosTop,mosterSpeed });
		}

		ifs.close();

		for (unsigned int i = 0; i < emeny_data.size(); i++)
		{
			int monsterType = emeny_data[i][0];
			int monsterPosLeft = emeny_data[i][1];
			int monsterPosTop = emeny_data[i][2];
			int mosterSpeed = emeny_data[i][3];

			switch (monsterType)
			{
			case 1: // Goomba怪物
				monster_list.push_back(new Goomba());
				monster_list[i]->Load();
				monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
				monster_list[i]->SetHorizontalSpeed(mosterSpeed);
				break;
			case 2: // flower怪物
				monster_list.push_back(new Flower());
				monster_list[i]->Load();
				monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
				monster_list[i]->original_y = monsterPosTop;
				monster_list[i]->SetHorizontalSpeed(mosterSpeed);
				break;
			case 3: // turtle怪物
				monster_list.push_back(new Turtle());
				monster_list[i]->Load();
				monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
				monster_list[i]->SetHorizontalSpeed(mosterSpeed);
				break;
			case 4: // hatgoomba怪物
				monster_list.push_back(new HatGoomba());
				monster_list[i]->Load();
				monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
				monster_list[i]->SetHorizontalSpeed(mosterSpeed);
				break;
			case 5: // missile怪物
				monster_list.push_back(new Missile());
				monster_list[i]->Load();
				monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
				monster_list[i]->SetHorizontalSpeed(mosterSpeed);
				break;
			case 6: // missile怪物
				monster_list.push_back(new FireTurtle());
				monster_list[i]->Load();
				monster_list[i]->SetTopLeft(monsterPosLeft, monsterPosTop);
				monster_list[i]->SetHorizontalSpeed(mosterSpeed);
				break;
			default:
				break;
			}
		}
	}


	void Enemyfactor::Show()
	{

		for (unsigned int i = 0; i < monster_list.size(); i++) {
			monster_list[i]->Show();
		}
	}

	void Enemyfactor::SetTopLeft(int x, int y)
	{

		for (auto enemy : monster_list)
		{
			enemy->SetTopLeft(enemy->GetLeft() - x, enemy->GetTop() - y);
			enemy->fireballSetTopLeft(x,y);
		}

	}

	void Enemyfactor::UpData(Mario& mario, Map& map)
	{
		for (int i = monster_list.size() - 1; i >= 0; i--) {
			if (abs(monster_list[i]->GetLeft() - mario.GetLeft()) < 1024) {
				monster_list[i]->UpData(monster_list, mario, map,i);
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
		for (int i = monster_list.size() - 1; i >= 0; i--) {
				monster_list[i]->Reset();
				delete monster_list[i];
				monster_list.erase(monster_list.begin() + i);
		}
		
	}


	// ! ENEMYFACTO
}