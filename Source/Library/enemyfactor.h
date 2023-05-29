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
		void Load(int world, int level);
		void Show();
		void UpData(Mario mario, Map map);
		void SetTopLeft(int x, int y);
		vector<Enemy*> GetMonsterlist();

		vector<int> monster_temp;
		vector<vector<int>> monster_position;
		vector<vector<int>> emeny_data;
		vector<Enemy*> monster_list;
	};
}
#endif // !GOOMBA_H