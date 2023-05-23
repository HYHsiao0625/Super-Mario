#ifndef MARIO_H
#define MARIO_H

#pragma
#include "gameutil.h"
#include "map.h"
#include <list>
#include <vector>
#include <map>
#include "enemyfactor.h"
#include "itemfactor.h"
#include "goomba.h"
using namespace std;

namespace game_framework
{
	class Mario
	{
	public:
		Mario();
		void	UpData(Mario mario, Map map, Enemyfactor enemyfactor, Itemfactor itemfactor);
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
		void	SetStatus(string);

		void	Die();
		int		GetX();
		int		GetY();

		int		GetVerticalSpeed();
		int		GetHorizontalSpeed();
		bool	GetDead() const;
		int		GetPressedKey();
		string	GetStatus();


		bool	IsKeyPressed();
		bool	IsOnGround();
		bool	IsHitbox();
		void	Collision(Mario mario, Map map);
		void	Collision(Mario mario, Goomba goomba);
		void    Collision(Enemyfactor enemyfactor);
		void    Collision(Itemfactor itemyfactor);

		void	OnGround(Mario mario, Map map);
		void	HitBox(Mario mario, Map map);

		CMovingBitmap charactor;
	private:
		bool	isCrouching = true;
		bool	dead = false;
		bool	isFlipped = false;
		bool	isOnGround = false;
		bool	isHitbox = false;
		bool	isJump = false;
		bool	isCollision = false;
		int		x;
		int		y;

		unsigned char jump_timer;
		unsigned short death_timer;
		unsigned short growth_timer;
		unsigned short invincible_timer;

		int		horizontalSpeed = 0;
		int		verticalSpeed = 0;
		int		pressedKey = 0;
		double  size = 1;
		string	status = "initial";
		bool	isKeyPressed = false;


		int const GRAVITY = 1;
	};

}
#endif // !MARIO_H