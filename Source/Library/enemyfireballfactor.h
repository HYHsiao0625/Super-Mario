#ifndef Enemyfireballfactor_H
#define Enemyfireballfactor_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "item.h"
#include "enemyfireball.h"

using namespace std;

namespace game_framework
{
	class Enemyfireballfactor
	{

	public:
		Enemyfireballfactor();
		~Enemyfireballfactor();

		void Load();
		void Show();
		void Reset();
		void UpData(Mario mario, Map map);
		void SetTopLeft(int x, int y);
		void AddFireBall(EnemyFireBall);
		vector<Item*> GetList();
		vector<Item*> enemyfireballlist;
	};
}
#endif // !GOOMBA_H