#ifndef ENEMYFACTOR_H
#define ENEMYFACTOR_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
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
		vector<Goomba> Get_List();
		vector<int> monster_temp = {1,1,1,1,1};
		vector<int> monster_position = {1468,2036,2456,3500,3800};
		//vector<vector<int>> monster_position;
		vector<Goomba> monster_list;
	};
}
#endif // !GOOMBA_H