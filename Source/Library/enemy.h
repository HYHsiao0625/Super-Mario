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

		int horizontal_speed;
		int vertical_speed;
		int x;
		int y;
	public:
		Enemy(const int i_x, const int i_y);

		virtual bool get_dead(const bool i_deletion) const = 0;

		virtual void die(const unsigned char i_death_type) = 0;

		virtual void show() = 0;
		virtual void update() = 0;

	};
}
#endif // !GOOMBA_H
