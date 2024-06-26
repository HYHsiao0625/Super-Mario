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
		void Reset();
		void UpData(Mario& mario, Map& map);
		void SetTopLeft(int x, int y);
		vector<Item*> GetItemList();
		vector<int> GetItemTemp();
		vector<int> itemTemp;
		vector<vector<int>> itemPosition;
		vector<Item*> itemList;
	};
}
#endif // !GOOMBA_H