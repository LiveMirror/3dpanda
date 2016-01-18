////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-25 23:08:41
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014225230841_H_
#define	_Tian_2014225230841_H_

#include "Vector2D.h"
#include "Size.h"

namespace panda
{
	/*
	*
	*/
	struct Rect
	{
		Vector2Dn	pos;
		Size		size;

		Rect(){}
		Rect(s32 x, s32 y, s32 width, s32 height)
		{
			pos.x = x;
			pos.y = y;
			size.width = width;
			size.height = height;
		}

		bool	Intersect(const Rect& other)
		{
			s32 x1, x2, y1, y2;

			x1 = math::Max(pos.x, other.pos.x);
			y1 = math::Max(pos.y, other.pos.y);

			x2 = math::Min(pos.x + size.width, other.pos.x + other.size.width);
			y2 = math::Min(pos.y + size.height, other.pos.y + other.size.height);

			s32 width = x2 - x1;
			s32 height = y2 - y1;

			if (width <= 0 || height <= 0)
			{
				return false;
			}
			return true;
		}

		//---------------------------------------------------
		//! 求出相交矩形区域
		Rect    GetIntersect(const Rect& other)const
		{
			Rect temp;
			temp.pos.x = math::Max(pos.x, other.pos.x);
			temp.pos.y = math::Max(pos.y, other.pos.y);

			s32 x2 = math::Min(pos.x + size.width, other.pos.x + other.size.width);
			s32 y2 = math::Min(pos.y + size.height, other.pos.y + other.size.height);

			temp.size.width = x2 - temp.pos.x;
			temp.size.height = y2 - temp.pos.y;

			return temp;
		}

		//---------------------------------------------------
		//! 判断矩形区域是否为空
		bool    IsNull()const
		{
			if (size.width <= 0 || size.height <= 0)
			{
				return true;
			}
			return false;
		}

		bool    IsPointIn(s32 x, s32 y)const
		{
			if (x > pos.x 
				&& y > pos.y 
				&& x < pos.x + size.width 
				&& y < pos.y + size.height)
			{
				return true;
			}
			return false;
		}
	};
}

#endif _Tian_2014225230841_H_