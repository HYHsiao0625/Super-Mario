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
	vector<Item*> Itemfactor::GetItemlist()
	{
		return item_list;
	}
	void Itemfactor::Load()
	{
	}

	void Itemfactor::Show()
	{

		for (auto item : item_list) {
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
				item_list.push_back(new Mushroom());
				item_list.back()->Load();
				item_list.back()->SetTopLeft(mario_x*64, (mario_y-1)*64);
				item_list.back()->SetHorizontalSpeed(4);
				item_list.back()->SetStatus("appear");
				
			}
			if (map_vector[mario_y][mario_x+1] == 2 && map_charactor[mario_y][mario_x + 1].GetFrameIndexOfBitmap() == 0) {
				item_list.push_back(new Mushroom());
				item_list.back()->Load();
				item_list.back()->SetTopLeft((mario_x+1) * 64, (mario_y - 1) * 64);
				item_list.back()->SetHorizontalSpeed(4);
				item_list.back()->SetStatus("appear");

			}
		}
		//Collision(map);
		for(auto item : item_list) {
			item->UpData(mario, map);
		}
	}
	// ! ENEMYFACTO
}