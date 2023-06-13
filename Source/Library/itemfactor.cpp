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
#include "itemfactor.h"
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
	Itemfactor::Itemfactor() {

	}
	Itemfactor::~Itemfactor()
	{
	}
	vector<Item*> Itemfactor::GetItemList()
	{
		return itemList;
	}
	vector<int> Itemfactor::GetItemTemp()
	{
		return itemTemp;
	}
	void Itemfactor::Load()
	{
	}

	void Itemfactor::Show()
	{

		for (auto item : itemList) {
			item->ShowBitmap();
		}

	}

	void Itemfactor::UpData(Mario& mario, Map& map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		vector<vector<CMovingBitmap>> map_charactor = map.GetMapcharactor();

		/*int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
		int mario_y = (mario.GetTop()) / 32;*/

		int mario_x = (mario.GetLeft() - map.GetLeft()) / 32;
		int mario_y = (mario.GetTop() - 4) / 32;

		if (mario.IsHitbox() == true)
		{
			if (map_vector[mario_y][mario_x] != 2 && map_charactor[mario_y][mario_x].GetFrameIndexOfBitmap()== 0) {
				switch (map_vector[mario_y][mario_x]) {
				case 12:
					itemList.push_back(new Mushroom());
					itemList.back()->Load();
					itemList.back()->SetTopLeft(mario.GetLeft(), (mario_y - 1) * 32);
					itemList.back()->SetHorizontalSpeed(2);
					itemTemp.push_back(1);
					break;
				case 13:
					itemList.push_back(new Star());
					itemList.back()->Load();
					itemList.back()->SetTopLeft(mario.GetLeft(), (mario_y - 1) * 32);
					itemList.back()->SetHorizontalSpeed(2);
					itemTemp.push_back(2);
					break;
				case 14:
					itemList.push_back(new FireFlower());
					itemList.back()->Load();
					itemList.back()->SetTopLeft(mario.GetLeft(), (mario_y - 1) * 32);
					itemList.back()->SetHorizontalSpeed(0);
					itemTemp.push_back(3);
					break;
				default:
					break;
				}
			
			}
			if (map_vector[mario_y][mario_x + 1]!=2 && map_charactor[mario_y][mario_x + 1].GetFrameIndexOfBitmap() == 0) {
				switch (map_vector[mario_y][mario_x+1]) {
				case 12:
					itemList.push_back(new Mushroom());
					itemList.back()->Load();
					itemList.back()->SetTopLeft(mario.GetLeft(), (mario_y - 1) * 32);
					itemList.back()->SetHorizontalSpeed(2);
					itemTemp.push_back(1);
					break;
				case 13:
					itemList.push_back(new Star());
					itemList.back()->Load();
					itemList.back()->SetTopLeft(mario.GetLeft(), (mario_y - 1) * 32);
					itemList.back()->SetHorizontalSpeed(2);
					itemTemp.push_back(2);
					break;
				case 14:
					itemList.push_back(new FireFlower());
					itemList.back()->Load();
					itemList.back()->SetTopLeft(mario.GetLeft(), (mario_y - 1) * 32);
					itemList.back()->SetHorizontalSpeed(0);
					itemTemp.push_back(3);
					break;
				default:
					break;
				}
			}
		}
		//Collision(map);
		for(auto item : itemList) {
			item->UpData(mario, map);
		}

		for (unsigned int i = 0; i < itemList.size(); i++) {
			if (itemList[i]->IsDead() == true) {
				delete itemList[i];
				itemList.erase(itemList.begin() + i);
				itemTemp.erase(itemTemp.begin() + i);
			}
		}
	}

	void Itemfactor::SetTopLeft(int x, int y)
	{
		for (auto item : itemList) {
			item->SetTopLeft(item->GetLeft() - x, item->GetTop() - y);
		}
	}
	void Itemfactor::Reset() {
		for (unsigned int i = 0; i < itemList.size(); i++) {
			delete itemList[i];
		}
		itemList.clear();
		itemTemp.clear();
	}
	// ! ENEMYFACTO
}