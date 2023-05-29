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

		void	Updata(Mario mario);
		void	Show();
		void	Load(int world, int level);
		void	Reset();

		int		GetTop();
		int		GetLeft();
		int		GetWidth();

		void	SetTopLeft(int, int);

		vector<vector<int>>	GetMap();
		vector<vector<CMovingBitmap>> GetMapcharactor();
		CMovingBitmap GetMapCharactor(int x, int y);

	private:
		int width = 211;
		int height = 15;

		vector<vector<int>> map_vector;
		vector<vector<CMovingBitmap>> charactor;

	};
}
#endif // !GOOMBA_H