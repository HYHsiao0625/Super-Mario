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
		void UpData(Mario mario, Map map);
		void Collision(Map map);
		void OnGround(Map map);
		void ToggleAnimation(int frameIndex);
		void Load();
		void LoadDieIamge();
		void Die();
	};
}
#endif // !GOOMBA_H