#ifndef MARIO_H
#define MARIO_H

#pragma
#include "gameutil.h"
#include "map.h"
#include <list>
#include <vector>
#include <map>
using namespace std;

namespace game_framework
{
	class Mario
	{
	public:
		Mario();
		void	UpData(Mario mario, Map map);
		void	Reset();

		void	Show();
		void	Load(vector<string>, COLORREF = CLR_INVALID);

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

		void	SetDie(bool);
		void	SetStatus(string);
		void	SetJump(bool);
		void	SetOnGround(bool status);
		void	SetHitbox(bool status);

		int		GetX();
		int		GetY();

		int		GetVerticalSpeed();
		int		GetHorizontalSpeed();
		bool	GetDead() const;
		int		GetPressedKey();
		bool	GetDie();
		string	GetStatus();
		bool	GetJump();
		string	GetOnGround();
		string	GetHitbox();

		bool	IsKeyPressed();

		void	Collision(Mario mario, Map map);
		CMovingBitmap charactor;
	private:
		bool	crouching;
		bool	dead = false;
		bool	flipped;
		bool	onGround;
		bool	hitbox;
		bool	jump;
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

		int const GRAVITY = 4;
	};

}
#endif // !MARIO_H
