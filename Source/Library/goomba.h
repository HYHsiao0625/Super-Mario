#ifndef GOOMBA_H
#define GOOMBA_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "enemy.h"
#include "enemyfireballfactor.h" 
#include "audio.h"

using namespace std;

namespace game_framework
{
	class Goomba : public Enemy
	{
	public:
		Goomba();
		~Goomba();		
		void UpData(vector<Enemy*>& monster_list, Mario& mario, Map& map,int pos);
		void Reset();
		void Load();
		void Die();
		bool IsDead();
		void Show();
		void SetTopLeft(int, int);
		void fireballSetTopLeft(int, int);
		//-------------------
		void Collision(Map& map);
		void Collision(vector<Enemy*>& monster_list, int pos);
		//-------------------
		void OnGround(Map& map);

		bool trigger = 0;
		
	};
}
#endif // !GOOMBA_H