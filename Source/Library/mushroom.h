#ifndef MUSHROOM_H
#define MUSHROOM_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "mario.h"
#include "map.h"
using namespace std;

namespace game_framework
{
	class Mushroom
	{
	public:
		Mushroom();
		~Mushroom();
		void UpData(Mario mario, Map map);
		void Collision(Map map);
		void Load();
		CMovingBitmap charactor;
	private:
		int		horizontalSpeed = 0;
		int		verticalSpeed = 0;
		string	status = "initial";
		bool	isCollision = false;
	};
}
#endif // !MUSHROOM_H