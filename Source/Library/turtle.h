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
		void UpData(Mario mario, Map map);
		void Collision(Map map);
		void ToggleAnimation(int frameIndex);
		void Load();
		void LoadDieIamge();
		void Die();
	private:
		bool on_kick = 0;
	};
}
#endif // !Turtle_H