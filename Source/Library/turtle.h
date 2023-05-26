#ifndef Turtle_H
#define Turtle_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "enemy.h"
#include "mario.h"

using namespace std;

namespace game_framework
{
	class Turtle : public Enemy
	{
	public:
		Turtle();
		~Turtle();
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

	private:
		bool isKickAble = false;
		bool isdead = false;
		bool on_kick = false;
	};
}
#endif // !Turtle_H