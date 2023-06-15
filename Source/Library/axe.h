#ifndef Axe_H
#define Axe_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
#include "item.h"

using namespace std;

namespace game_framework
{
	class Axe : public Item
	{
	public:
		void UpData(Mario& mario, Map& map);
		void Reset();
		void Load();
		void Die();
		bool IsDead();

		void Collision(Map& map);
		void LoadDieIamge();


	private:
		bool isdead = false;
		int	 cd = 10;
	};
}
#endif // !Axe_H