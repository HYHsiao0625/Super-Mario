#ifndef Itemfactor_H
#define Itemfactor_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "item.h"
#include "mushroom.h"
using namespace std;

namespace game_framework
{
	class Itemfactor
	{

	public:
		Itemfactor();
		~Itemfactor();
		void Load();
		void Show();
		void UpData(Mario mario, Map map);
		vector<Item*> GetItemlist();
		vector<int> item_temp;
		vector<vector<int>> item_position;
		vector<Item*> item_list;
	};
}
#endif // !GOOMBA_H