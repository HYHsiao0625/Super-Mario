#ifndef ENEMY_H
#define ENEMY_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
using namespace std;

namespace game_framework
{
	class Enemy
	{
	protected:
		bool dead;

		float horizontal_speed;
		float vertical_speed;
		float x;
		float y;
	public:
		Enemy(const float i_x, const float i_y);

		virtual bool get_dead(const bool i_deletion) const;

		virtual void die(const unsigned char i_death_type);
		//Apparently, we can set the function declaration to 0 and that's called a pure virtual function. Again, C++ is weird.
		virtual void draw() = 0;
		virtual void update() = 0;

	};
}
#endif // !GOOMBA_H
