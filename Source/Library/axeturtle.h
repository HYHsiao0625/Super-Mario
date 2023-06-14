#ifndef AxeTurtle_H
#define AxeTurtle_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "enemy.h"
#include "enemyfireball.h"
#include "mario.h"
#include "axe.h"

using namespace std;

namespace game_framework
{
	class AxeTurtle : public Enemy
	{
	public:
		AxeTurtle();
		~AxeTurtle();
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
		std::vector<Axe> fireball;
		int shot_time = 20;
		int breaktime=0;
		int attacktimes = 0;
	private:
		bool isKickAble = false;
		bool isdead = false;
		bool on_kick = false;
	};
}
#endif // !AxeTurtle_H