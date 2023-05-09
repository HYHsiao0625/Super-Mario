#ifndef MAP_H
#define MAP_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
using namespace std;

namespace game_framework
{
	class Map
	{
	public:
		Map();
		~Map();

		void	Updata(Mario mario, Map map);
		void	Show();
		void	Load(int world, int level);
		int		GetTop();
		int		GetLeft();
		int		GetWidth();
		void	initalize();
		
		void	SetTopLeft(int, int);
		vector<vector<int>>	GetMap();
		CMovingBitmap GetMapCharactor(int x, int y);

	private:
		int width, height = 15;
		vector<int> map_temp;
		vector<vector<int>> map;
		vector<CMovingBitmap> array1;
		vector<vector<CMovingBitmap>> charactor;
	};
}
#endif // !GOOMBA_H