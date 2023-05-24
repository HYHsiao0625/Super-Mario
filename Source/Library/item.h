#ifndef Item_H
#define Item_H

#pragma
#include "gameutil.h"
#include "map.h"
#include <list>
#include <vector>
#include <map>
using namespace std;

namespace game_framework
{
	class Item
	{
	public:
		Item();
		~Item();

		virtual void Load() = 0;
		virtual void UpData(Mario mario, Map map) = 0;
		void	ShowBitmap();
		void	LoadBitmapByString(vector<string>, COLORREF = CLR_INVALID);
		void	SetAnimation(int delay, bool _once);
		void	Limit(CMovingBitmap floor, Mario mario);
		int		GetFrameIndexOfBitmap();
		void	SetFrameIndexOfBitmap(int);
		int		GetTop();
		int		GetLeft();
		int		GetHeight();
		int		GetWidth();

		void	SetTopLeft(int, int);
		void	SetVerticalSpeed(int);
		void	SetHorizontalSpeed(int);
		void	SetCollision(bool);
		void	SetDie(bool);
		void	SetStatus(string);

		int		GetVerticalSpeed();
		int		GetHorizontalSpeed();

		bool	GetDie();
		string	GetStatus();

		bool	isUsed = false;
		CMovingBitmap charactor;
	protected:
		bool	crouching;
		bool	dead = false;
		bool	flipped;
		bool	on_ground;
		int		x;
		int		y;

		unsigned char jump_timer;
		unsigned short death_timer;
		unsigned short growth_timer;
		unsigned short invincible_timer;

		int		horizontalSpeed = 0;
		int		verticalSpeed = 0;
		string	status = "initial";
		bool	isCollision = false;
		bool	isOnGround = true;
		
	};
}
#endif // !Item_H