#ifndef GOOMBA_H
#define GOOMBA_H

#pragma
#include "gameutil.h"
#include <list>
#include <vector>
#include <map>
using namespace std;

namespace game_framework
{
	class Goomba
	{
	public:
		Goomba();
		~Goomba();

		void	UpData();
		void	ShowBitmap();
		void	LoadBitmapByString(vector<string>, COLORREF = CLR_INVALID);
		void	SetAnimation(int delay, bool _once);
		int		GetFrameIndexOfBitmap();
		void	SetFrameIndexOfBitmap(int);
		int		GetTop();
		int		GetLeft();
		int		GetHeight();
		int		GetWidth();

		void	SetTopLeft(int, int);
		void	SetVerticalSpeed(int);
		void	SetHorizontalSpeed(int);
		void	SetKeyPressed(bool);
		void	SetPressedKey(int);
		void	SetCollision(bool);
		void	SetDie(bool);
		void	SetStatus(string);

		int		GetVerticalSpeed();
		int		GetHorizontalSpeed();
		int		GetPressedKey();
		bool	GetDie();
		string	GetStatus();

		bool	IsKeyPressed();
		bool	IsCollision();

		CMovingBitmap charactor;
	private:
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
		int		pressedKey = 0;
		string	status = "initial";
		bool	isKeyPressed = false;
		bool	isCollision = false;
	};
}
#endif // !GOOMBA_H
