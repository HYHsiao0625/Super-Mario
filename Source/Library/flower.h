#ifndef flower_H
#define flower_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "mario.h"
#include "enemy.h"
#include "enemyfactor.h"
using namespace std;

namespace game_framework
{
	class Flower : public Enemy
	{
	public:
		Flower();
		~Flower();
		void UpData(vector<Enemy*> monster_list,Mario mario, Map map);
		void Collision(Map map);
		void Reset();
		void Load();
		void Die();
		bool IsDead();
	private:
		bool active = 1;
		bool trigger = 0;
	};
}
#endif // !flower_H