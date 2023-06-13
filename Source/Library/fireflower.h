#ifndef FireFlower_H
#define FireFlower_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "item.h"

using namespace std;

namespace game_framework
{
	class FireFlower : public Item
	{
	public:
		void UpData(Mario& mario, Map& map);
		void Reset();
		void Load();
		void Die();
		bool IsDead();

		void Collision(Map& map);
		void OnGround(Map& map);
		void LoadDieIamge();


	private:
		bool isdead = false;
		int	 cd = 2;
	};
}
#endif // !FireFlower_H