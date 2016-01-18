////////////////////////////////////////////////////////////////////////
// Copyright(c) 1986-2006, TT, All Rights Reserved
// Author:  Hu Tianzhi
// Created: 2010-7-21 0:26:21
// Describe:3维向量
////////////////////////////////////////////////////////////////////////

#ifndef	_Tian_201072102621_H_
#define	_Tian_201072102621_H_

#include "Math.h"

namespace panda
{
	template<typename T>
	struct Vector3D
	{
		static Vector3D<T> ZERO;
		static Vector3D<T> UNIT_X;
		static Vector3D<T> UNIT_Y;
		static Vector3D<T> UNIT_Z;

		Vector3D()
		{ 
			x = 0;
			y = 0;
			z = 0;
		}
		Vector3D(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
	public:
		T x,y,z;
	public:
		Vector3D<T>& operator = (const Vector3D<T>& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			return *this;
		}

		Vector3D<T> operator +(const Vector3D<T>& other)const
		{
			return Vector3D<T>( x + other.x, y + other.y, z + other.z);			
		}

		Vector3D<T>& operator +=(const Vector3D<T>& other)
		{			
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vector3D<T> operator -(const Vector3D<T>& other)const
		{
			return Vector3D<T>(x - other.x, y - other.y, z - other.z);			
		}

		Vector3D<T> operator -(void)const
		{
			return Vector3D<T>(-x , -y, -z);
		}

		Vector3D<T>& operator -=(const Vector3D<T>& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vector3D<T> operator *(T a)const
		{
			return Vector3D<T> (x * a, y * a, z * a);
		}		

		Vector3D<T>& operator *=(T a)
		{
			x *= a;
			y *= a;
			z *= a;
			return *this;
		}
		Vector3D<T> operator /(T a)const
		{
			return Vector3D<T> (x / a, y / a, z / a);
		}

		Vector3D<T>& operator /=(T a)
		{
			T i = (T)1/a;
			x *= i;
			y *= i;
			z *= i;
			return *this;
		}

		T operator *(const Vector3D<T>& other)const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		bool operator >(const Vector3D<T>& other)const
		{
			return x > other.x && y > other.y && z > other.z;
		}

		bool operator >=(const Vector3D<T>& other)const
		{
			return x >= other.x && y >= other.y && z >= other.z;
		}

		bool operator <(const Vector3D<T>& other)const
		{
			return x < other.x && y < other.y && z < other.z;
		}

		bool operator <=(const Vector3D<T>& other)const
		{
			return x <= other.x && y <= other.y && z <= other.z;
		}

		bool operator ==(const Vector3D<T>& other)const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool operator !=(const Vector3D<T>& other)const
		{
			return x != other.x || y != other.y || z != other.z;
		}

	public:
		Vector3D<T>& Normalize()
		{
			f32 magSq = x*x + y*y + z*z;
			if (magSq > 0)
			{
				f32 oneOverMag = 1/math::Sqrt(magSq);
				x *= oneOverMag;
				y *= oneOverMag;
				z *= oneOverMag;
			}
			return *this;
		}

		Vector3D<T> Cross(const Vector3D<T>& other)const
		{
			return Vector3D<T>(
				y * other.z - z * other.y,
				z * other.x - x * other.z,
				x * other.y - y * other.x
				);
		}
		f32 DotProduct(const Vector3D<T>&other) const
		{
			return x*other.x + y*other.y + z*other.z;
		}
		f32 Length()const
		{
			return math::Sqrt((f32)(x*x + y*y + z*z));
		}
		// 距离平方
		f32 LengthSQ()const
		{
			return x*x + y*y + z*z;
		}

		f32 DistanceFrom(const Vector3D<T>& other)const
		{
			return Vector3D<T>(x - other.x, y - other.y, z - other.z).Length();
		}

		f32 DistanceFromSQ(const Vector3D<T>& other)const
		{
			return Vector3D<T>(x - other.x, y - other.y, z - other.z).LengthSQ();
		}

		Vector3D<T> perpendicular(void) const
		{
			static const f32 fSquareZero = f32(1e-06 * 1e-06);

			Vector3D<T> perp = this->Cross( Vector3D<T>::UNIT_X );

			// Check length
			if( perp.LengthSQ() < fSquareZero )
			{
				/* This vector is the Y axis multiplied by a scalar, so we have
				to use another axis.
				*/
				perp = this->Cross( Vector3D<T>::UNIT_Y );
			}
			perp.Normalize();

			return perp;
		}

		Vector3D<T> RandomDeviant(
			f32 angle,
			const Vector3D<T>& up = Vector3D<T>::ZERO ) const
		{
			Vector3D<T> newUp;

			if (up == Vector3D<T>::ZERO)
			{
				// Generate an up vector
				newUp = this->perpendicular();
			}
			else
			{
				newUp = up;
			}

			// Rotate up vector by random amount around this
			Quaternion q;
			q.FromAngleAxis( 3.14f * (rand() % 180), *this );
			newUp = q * newUp;

			// Finally rotate this by given angle around randomised up
			q.FromAngleAxis( angle, newUp );
			return q * (*this);
		}

		//----------------------------
		// fuction:绕 坐标轴 旋转  顺时针
		// degrees [in]: 度数 如 90 度
		// centerPoint [in]: 旋转的中心点 默认为坐标原点
		// return:void
		//----------------------------
		Vector3D<T>& RotateByX(f32 degrees, const Vector3D<T>& centerPoint=Vector3D<T>())
		{
			degrees *= DEGREE;
			f32 cs = math::Cos(degrees);
			f32 sn = math::Sin(degrees);
			z -= centerPoint.z;
			y -= centerPoint.y;

			y = y*cs - z*sn;
			z = y*sn + z*cs;

			z += centerPoint.z;
			y += centerPoint.y;
			return *this;
		}
		Vector3D<T>& RotateByY(f32 degrees, const Vector3D<T>& centerPoint=Vector3D<T>())
		{
			degrees *= DEGREE;
			f32 cs = math::Cos(degrees);
			f32 sn = math::Sin(degrees);
			x -= centerPoint.x;
			z -= centerPoint.z;

			x = x*cs - z*sn;
			z = x*sn + z*cs;

			x += centerPoint.x;
			z += centerPoint.z;
			return *this;
		}
		Vector3D<T>& RotateByZ(f32 degrees, const Vector3D<T>& centerPoint=Vector3D<T>())
		{
			degrees *= DEGREE;
			f32 cs = math::Cos(degrees);
			f32 sn = math::Sin(degrees);
			x -= centerPoint.x;
			y -= centerPoint.y;

			x = x*cs - y*sn;
			y = x*sn + y*cs;

			x += centerPoint.x;
			y += centerPoint.y;
			return *this;
		}
	};

	typedef Vector3D<s32>	Vector3Dn;
	typedef Vector3D<f32>	Vector3Df;
}

#endif