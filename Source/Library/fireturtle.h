#ifndef FireTurtle_H
#define FireTurtle_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "enemy.h"
#include "enemyfireball.h"
#include "mario.h"

using namespace std;

namespace game_framework
{
	class FireTurtle : public Enemy
	{
	public:
		FireTurtle();
		~FireTurtle();
		void UpData(vector<Enemy*> monster_list, Mario& mario, Map map,int pos);
		void Reset();
		void Load();
		void Die();
		bool IsDead();
		//-------------------
		void Collision(Map map);
		void Collision(vector<Enemy*> monster_list,int pos);
		//-------------------
		void OnGround(Map map);
		void LoadDieIamge();
		void Show();
		void SetTopLeft(int, int);
		void fireballSetTopLeft(int, int);
		std::vector<EnemyFireBall> fireball;
		int shot_time = 20;
	private:
		bool isKickAble = false;
		bool isdead = false;
		bool on_kick = false;
	};
}
#endif // !FireTurtle_H