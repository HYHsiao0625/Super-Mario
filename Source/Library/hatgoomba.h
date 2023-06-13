#ifndef HatGoomba_H
#define HatGoomba_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "enemy.h"
using namespace std;

namespace game_framework
{
	class HatGoomba : public Enemy
	{
	public:
		HatGoomba();
		~HatGoomba();

		void UpData(vector<Enemy*>& monster_list, Mario& mario, Map& map, int pos);
		void Reset();
		void Load();
		void Die();
		bool IsDead();
		//-------------------
		void Collision(Map& map);
		void Collision(vector<Enemy*>& monster_list, int pos);
		//-------------------
		void OnGround(Map& map);
		void LoadDieIamge();
		void Show();
		void SetTopLeft(int, int);
		void fireballSetTopLeft(int, int);
		bool havehat = true;
	};
}
#endif // !HatGoomba_H