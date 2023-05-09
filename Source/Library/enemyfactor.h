#ifndef ENEMYFACTOR_H
#define ENEMYFACTOR_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "enemy.h"
#include "goomba.h"
using namespace std;

namespace game_framework
{
	class Enemyfactor
	{
		
	public:
		Enemyfactor();
		~Enemyfactor();
		void Load();
		void Show();
		void UpData(Mario mario, Map map);
		vector<Goomba> GetMonsterlist();
		vector<int> monster_temp;
		vector<vector<int>> monster_position;
		vector<Goomba> monster_list;
	};
}
#endif // !GOOMBA_H