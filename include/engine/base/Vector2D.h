////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2011-8-25 19:23:49
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2011825192349_H_
#define	_Tian_2011825192349_H_

#include "Math.h"

namespace panda
{
	template<typename T>
	struct Vector2D
	{
	public:
		T x, y;
		Vector2D(void)
		{
			x = y = 0;
		}
		Vector2D(T x, T y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2D<T>& operator = (const Vector2D<T>& other)
		{
			x = other.x;
			y = other.y;
			return *this;
		}

		bool operator ==(const Vector2D<T>& other)const
		{
			return x == other.x && y == other.y;
		}

		Vector2D<T> operator +(const Vector2D<T>& other)const
		{
			return Vector3D<T>( x + other.x, y + other.y,);
		}

		Vector2D<T>& operator +=(const Vector2D<T>& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		Vector2D<T> operator -(const Vector2D<T>& other)const
		{
			return Vector2D<T>(x - other.x, y - other.y);
		}

		Vector2D<T>& operator -=(const Vector2D<T>& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		T operator *(const Vector2D<T>& other)const
		{
			return x * other.x + y * other.y;
		}
		Vector2D<T> operator *(T v)const
		{
			return Vector2D<T>(v * x, v * y);
		}
	};
	
	typedef Vector2D<s32>	Vector2Dn;
	typedef Vector2D<f32>	Vector2Df;
}

#endif _Tian_2011825192349_H_