#ifndef GOOMBA_H
#define GOOMBA_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "enemy.h"
using namespace std;

namespace game_framework
{
	class Goomba : public Enemy
	{
	public:
		void UpData(vector<Enemy*> monster_list, Mario mario, Map map);
		void Reset();
		void Load();
		void Die();
		bool IsDead();
		//-------------------
		void Collision(Map map);
		void Collision(vector<Enemy*> monster_list);
		//-------------------
		void OnGround(Map map);
		void LoadDieIamge();
		
	};
}
#endif // !GOOMBA_H