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
#include "Enemyfireballfactor.h"
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
	Enemyfireballfactor::Enemyfireballfactor() {

	}
	Enemyfireballfactor::~Enemyfireballfactor()
	{
	}
	vector<Item*> Enemyfireballfactor::GetList()
	{
		return enemyfireballlist;
	}

	void Enemyfireballfactor::Load()
	{

	}

	void Enemyfireballfactor::Show()
	{

		for (auto item : enemyfireballlist) {
			item->ShowBitmap();
		}

	}

	void Enemyfireballfactor::UpData(Mario mario, Map map)
	{
		//Collision(map);
		for (auto item : enemyfireballlist) {
			item->UpData(mario, map);
		}
		for (int i = enemyfireballlist.size() - 1; i >= 0; i--) {
			if (enemyfireballlist[i]->IsDead() == true) {
				delete enemyfireballlist[i];
				enemyfireballlist.erase(enemyfireballlist.begin() + i);
			}
		}
	}
	void Enemyfireballfactor::AddFireBall(EnemyFireBall fireball) {
		enemyfireballlist.push_back(&fireball);
	}
	void Enemyfireballfactor::SetTopLeft(int x, int y)
	{
		for (auto item : enemyfireballlist) {
			item->SetTopLeft(item->GetLeft() - x, item->GetTop() - y);
		}
	}
	void Enemyfireballfactor::Reset() {
			for (int i = enemyfireballlist.size() - 1; i >= 0; i--) {
				delete enemyfireballlist[i];
				enemyfireballlist.erase(enemyfireballlist.begin() + i);
			}
		
	}
	// ! ENEMYFACTO
}