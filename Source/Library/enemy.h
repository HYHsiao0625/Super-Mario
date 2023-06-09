#ifndef Enemy_H
#define Enemy_H

#pragma
#include "gameutil.h"
#include "map.h"
#include <list>
#include <vector>
#include <map>
using namespace std;

namespace game_framework
{
	class Enemy
	{
	public:
		Enemy();
		virtual ~Enemy()=0;

		virtual void UpData(vector<Enemy*> monster_list, Mario mario, Map map,int pos) = 0;
		virtual void Reset() = 0;
		virtual void Load() = 0;
		virtual void Die() = 0;
		virtual bool IsDead() = 0;

		//-------------
		void	ShowBitmap();
		void	LoadBitmapByString(vector<string>, COLORREF = CLR_INVALID);

		void	SetAnimation(int delay, bool _once);
		void	SetFrameIndexOfBitmap(int);

		int		GetFrameIndexOfBitmap();
		int		GetTop();
		int		GetLeft();
		int		GetHeight();
		int		GetWidth();

		void	SetTopLeft(int, int);
		
		void	SetVerticalSpeed(int);
		void	SetHorizontalSpeed(int);

		int		GetVerticalSpeed();
		int		GetHorizontalSpeed();
		//-----------------------

		CMovingBitmap charactor;
	
	protected:
		int     showtime=0;
		int		horizontalSpeed = 0;
		int		verticalSpeed = 0;
		bool	isCollision = false;
		bool    isOnGround = false;
		bool	isDead = false;
	};
}
#endif // !Enemy_H