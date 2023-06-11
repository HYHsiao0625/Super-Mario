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

	private:
		bool isKickAble = false;
		bool isdead = false;
		bool on_kick = false;
	};
}
#endif // !Turtle_H