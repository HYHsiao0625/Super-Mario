#ifndef Mushroom_H
#define Mushroom_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "item.h"

using namespace std;

namespace game_framework
{
	class Mushroom : public Item
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
#endif // !Mushroom_H