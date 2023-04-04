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
		void UpData(Mario mario, Map map) ;
		void Collision(Map map);
	};
}
#endif // !GOOMBA_H