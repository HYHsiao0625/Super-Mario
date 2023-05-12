#ifndef flower_H
#define flower_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "mario.h"
#include "enemy.h"
using namespace std;

namespace game_framework
{
	class Flower : public Enemy
	{
	public:
		void UpData(Mario mario, Map map);
		void Collision(Map map);
		void Load();
	private:
		bool active = 1;
		bool trigger = 0;
	};
}
#endif // !flower_H