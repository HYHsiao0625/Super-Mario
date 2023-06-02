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
#include "fireball.h"
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
		void	Load();
		void	Show();
		void	Die();
		//--------------
		void	LoadBitmapByString(vector<string>, COLORREF = CLR_INVALID);

		void	SetAnimation(int delay, bool _once);
		void	SetFrameIndexOfBitmap(int);
		void	SetTopLeft(int x, int y);
		void	FireballSetTopLeft(int x, int y);
		void	SetShot(bool);

		int		GetFrameIndexOfBitmap();
		int		GetTop();
		int		GetLeft();
		int		GetHeight();
		int		GetWidth();
		std::vector<Fireball> GetFireball();
		//--------------
		void	SetVerticalSpeed(int);
		void	SetHorizontalSpeed(int);
		void	SetJump(bool);
		//--------------
		int		GetVerticalSpeed();
		int		GetHorizontalSpeed();
		int		GetHnbeatable_time();
		//--------------
		bool	IsDead();
		bool	IsOnGround();
		bool	IsHitbox();
		bool	IsJump();
		//--------------
		void	Collision(Mario mario, Map map);
		void	Collision(Mario mario, Goomba goomba);
		void    Collision(Enemyfactor enemyfactor);
		void    Collision(Itemfactor itemyfactor);

		void	OnGround(Mario mario, Map map);
		void	HitBox(Mario mario, Map map);
		//----------
		CMovingBitmap charactor; 
		int		face = 1;
	private:
		bool	isDead = false;
		bool	isCrouching = true;
		bool	isCollision = false;
		bool	isFlipped = false;
		bool	isOnGround = false;
		bool	isHitbox = false;
		bool	isJump = false;
		bool	isOnHit = false;
		bool	isShot = false;
		
		int		x;
		int		y;

		int		jump_timer;

		int		horizontalSpeed = 0;
		int		verticalSpeed = 0;
		int     unbeatable_time = 0;
		int     shot_time = 0;
		std::vector<Fireball> fireball;

		int const GRAVITY = 1;
	};

}
#endif // !MARIO_H