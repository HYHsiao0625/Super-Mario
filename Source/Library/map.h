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
		void	Reset(bool);

		int		GetTop();
		int		GetLeft();
		int		GetWidth();
		int		GetWorld();
		int		GetLevel();

		void	SetTopLeft(int, int);

		void	Clear();
		vector<vector<int>>	GetMap();
		vector<vector<CMovingBitmap>> GetMapcharactor();
		CMovingBitmap GetMapCharactor(int x, int y);

	private:
		int width;
		int height = 15;
		int _world, _level;
		vector<vector<int>> resetblock_vector;
		vector<vector<int>> map_vector;
		vector<vector<CMovingBitmap>> charactor;

	};
}
#endif // !GOOMBA_H