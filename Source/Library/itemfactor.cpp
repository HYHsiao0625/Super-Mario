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
	void Itemfactor::Load()
	{
	}

	void Itemfactor::Show()
	{

		for (auto item : itemList) {
			item->ShowBitmap();
		}

	}

	void Itemfactor::UpData(Mario mario, Map map)
	{
		vector<vector<int>> map_vector = map.GetMap();
		vector<vector<CMovingBitmap>> map_charactor = map.GetMapcharactor();
		int mario_x = (mario.GetLeft() - map.GetLeft()) / 64;
		int mario_y = (mario.GetTop() - 4) / 64;
		if (mario.IsHitbox() == true)
		{
			if (map_vector[mario_y][mario_x] == 2 && map_charactor[mario_y][mario_x].GetFrameIndexOfBitmap()== 0) {
				itemList.push_back(new Mushroom());
				itemList.back()->Load();
				itemList.back()->SetTopLeft(mario_x * 64, (mario_y - 1) * 64);
				itemList.back()->SetHorizontalSpeed(4);
				
			}
			if (map_vector[mario_y][mario_x+1] == 2 && map_charactor[mario_y][mario_x + 1].GetFrameIndexOfBitmap() == 0) {
				itemList.push_back(new Mushroom());
				itemList.back()->Load();
				itemList.back()->SetTopLeft((mario_x + 1) * 64, (mario_y - 1) * 64);
				itemList.back()->SetHorizontalSpeed(4);
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
			}
		}
	}
	// ! ENEMYFACTO
}