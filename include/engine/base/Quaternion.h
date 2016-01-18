////////////////////////////////////////////////////////
// Copyright(c) 1986-2006, TT, All Rights Reserved
// Author:  Hu Tianzhi
// Created: 2010-8-18 21:18:14
// Describe:四元数
////////////////////////////////////////////////////////

#ifndef	_Tian_2010818211814_H_
#define	_Tian_2010818211814_H_

#include "Matrix44.h"
#include "Vector3D.h"
#include "math.h"

namespace panda
{
	struct Quaternion
	{
	public:
		f32	X, Y, Z, W;

		Quaternion()
		{
			X = Y = Z = 0.0f;
			W = 1.0f;
		}

		Quaternion(f32 x, f32 y, f32 z, f32 w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}

		// 根据欧拉角构造四元数
		Quaternion(const Vector3Df& euler)
		{
			float cr, cp, cy, sr, sp, sy, cpcy, spsy;

			//计算求四元数时使用到的所有三角值
			cr = math::Cos(euler.x * 0.5f);
			cp = math::Cos(euler.y * 0.5f);
			cy = math::Cos(euler.z * 0.5f);

			sr = math::Sin(euler.x * 0.5f);
			sp = math::Sin(euler.y * 0.5f);
			sy = math::Sin(euler.z * 0.5f);
			cpcy = cp * cy;
			spsy = sp * sy;

			//组合这些值,生成四元数的向量和w
			W = cr*cpcy + sr*spsy;
			X = sr*cpcy - cr*spsy;
			Y = cr*sp*cy + sr*cp*sy;
			Z = cr*cp*sy - sr*sp*cy;
		}

		Quaternion(f32 fAngle, const Vector3Df& sAxis)
		{
			f32 fHalfAngle = fAngle * 0.5f;
			f32 fSin = math::Sin(fHalfAngle);
			W = math::Cos(fHalfAngle);
			X = fSin*sAxis.x;
			Y = fSin*sAxis.y;
			Z = fSin*sAxis.z;
		}

		void FromAngleAxis(f32 fAngle, const Vector3Df& sAxis)
		{
			f32 fHalfAngle = fAngle * 0.5f;
			f32 fSin = math::Sin(fHalfAngle);
			W = math::Cos(fHalfAngle);
			X = fSin*sAxis.x;
			Y = fSin*sAxis.y;
			Z = fSin*sAxis.z;
		}

		//! Normalizes the quaternion
		Quaternion& Normalize()
		{
			f32 n = X*X + Y*Y + Z*Z + W*W;

			if (n == 1)
				return *this;

			//n = 1.0f / sqrtf(n);
			*this *= 1 / math::Sqrt(n);
			return *this;
		}

		Quaternion Inverse()const
		{
			f32 fNorm = W*W+X*X+Y*Y+Z*Z;
			if ( fNorm > 0.0 )
			{
				f32 fInvNorm = 1.0f/fNorm;
				return Quaternion(-X*fInvNorm,-Y*fInvNorm,-Z*fInvNorm,W*fInvNorm);
			}
			else
			{
				// return an invalid result to flag the error
				return Quaternion(0,0,0,0);
			}
		}

		Matrix44f GetMatrix()const
		{
			Matrix44f m;
			GetMatrix(m);
			return m;
		}

		void GetMatrix(Matrix44f& dest)const
		{
			dest[0] = 1.0f - 2.0f*Y*Y - 2.0f*Z*Z;
			dest[4] = 2.0f*X*Y + 2.0f*Z*W;
			dest[8] = 2.0f*X*Z - 2.0f*Y*W;
			dest[12] = 0.0f;

			dest[1] = 2.0f*X*Y - 2.0f*Z*W;
			dest[5] = 1.0f - 2.0f*X*X - 2.0f*Z*Z;
			dest[9] = 2.0f*Z*Y + 2.0f*X*W;
			dest[13] = 0.0f;

			dest[2] = 2.0f*X*Z + 2.0f*Y*W;
			dest[6] = 2.0f*Z*Y - 2.0f*X*W;
			dest[10] = 1.0f - 2.0f*X*X - 2.0f*Y*Y;
			dest[14] = 0.0f;

			dest[3] = 0.f;
			dest[7] = 0.f;
			dest[11] = 0.f;
			dest[15] = 1.f;	
		}

		void FromRotationMatrix(const Matrix44f& m)
		{
			// 4 * w * w - 1
			float _4xWxW_1 = m._11 + m._22 + m._33;
			float _4xXxX_1 = m._11 - m._22 - m._33;
			float _4xYxY_1 = -m._11 + m._22 - m._33;
			float _4xZxZ_1 = -m._11 - m._22 + m._33;
			int idxMax = 0;
			float max4x_1 = _4xWxW_1;
			if (_4xXxX_1 > max4x_1)
				max4x_1 = _4xXxX_1, idxMax = 1;
			if (_4xYxY_1 > max4x_1)
				max4x_1 = _4xYxY_1, idxMax = 2;
			if (_4xZxZ_1 > max4x_1)
				max4x_1 = _4xZxZ_1, idxMax = 3;
			float maxVal = math::Sqrt(max4x_1 + 1.0f) * 0.5f;
			float oneOver4Val = 0.25f / maxVal;
			switch (idxMax)
			{
			case 0:
				W = maxVal;
				X = (m._23 - m._32) * oneOver4Val;
				Y = (m._31 - m._13) * oneOver4Val;
				Z = (m._12 - m._21) * oneOver4Val;
				break;
			case 1:
				W = maxVal;
				X = (m._23 - m._32) * oneOver4Val;
				Y = (m._12 + m._21) * oneOver4Val;
				Z = (m._31 + m._13) * oneOver4Val;
				break;
			case 2:
				W = maxVal;
				X = (m._31 - m._13) * oneOver4Val;
				Y = (m._12 + m._21) * oneOver4Val;
				Z = (m._23 + m._32) * oneOver4Val;
				break;
			case 3:
				W = maxVal;
				X = (m._12 - m._21) * oneOver4Val;
				Y = (m._31 + m._13) * oneOver4Val;
				Z = (m._23 + m._32) * oneOver4Val;
				break;
			}
		}

		
		//! 根据四元数获得欧拉角的旋转值
		void GetEuler(Vector3Df& rot)const
		{
			rot.x = atan2(2*(Y*Z + W*X), W*W - X*X - Y*Y + Z*Z); 
			rot.y = asin(2 * (W * Y + Z * X));
			rot.z = atan2(2 * (W * Z + X * Y) , W*W + X*X - Y*Y - Z*Z);
		}

		f32 DotProduct(const Quaternion& other)const
		{
			return (X * other.X) + (Y * other.Y) + (Z * other.Z) + (W * other.W);
		}		

		Quaternion& Assign(float w_, float x_, float y_, float z_)
		{
			W = w_;
			X = x_;
			Y = y_;
			Z = z_;
			return (*this);
		}

		Quaternion& Slerp(const Quaternion& p0, const Quaternion& p1, float t)
		{
			if (t <= 0)
				return (*this = p0);
			if (t >= 1.0f)
				return (*this = p1);
			float cosVal = p0.DotProduct(p1);
			Quaternion p1_;
			if (cosVal < 0)
			{
				p1_.Assign(-p1.W, -p1.X, -p1.Y, -p1.Z), cosVal = -cosVal;
			}
			else
			{
				p1_.Assign(p1.W, p1.X, p1.Y, p1.Z);
			}
			float a0, a1;
			// p(t) = p0 + (p1 - p0) * t
			if (cosVal > 0.99999f)// / cos(Angle(0.25).ToRadian())
			{
				a0 = 1.0f - t;
				a1 = t;
			}
			// p(t) = p0 * (sin((1 - t) * a) / sin(a)) + p1 * (sin(t * a) / sin(a))
			else
			{
				float sinVal = math::Sqrt(1.0f - cosVal * cosVal);
				float ang = math::Atan2(sinVal, cosVal);
				float oneOverSin = 1.0f / sinVal;
				a0 = math::Sin((1.0f - t) * ang) * oneOverSin;
				a1 = math::Sin(t * ang) * oneOverSin;
			}
			W = a0 * p0.W + a1 * p1_.W;
			X = a0 * p0.X + a1 * p1_.X;
			Y = a0 * p0.Y + a1 * p1_.Y;
			Z = a0 * p0.Z + a1 * p1_.Z;
			Normalize();
			return (*this);
		}


		/************************************************************************/
		/*                              操作符重载                                  */
		/************************************************************************/
		Quaternion operator*(const Quaternion& other)const
		{
			Quaternion tmp;
			tmp.W = (other.W * W) - (other.X * X) - (other.Y * Y) - (other.Z * Z);
			tmp.X = (other.W * X) + (other.X * W) + (other.Y * Z) - (other.Z * Y);
			tmp.Y = (other.W * Y) + (other.Y * W) + (other.Z * X) - (other.X * Z);
			tmp.Z = (other.W * Z) + (other.Z * W) + (other.X * Y) - (other.Y * X);
			return tmp;
		}
		Quaternion& operator*=(const Quaternion& other)
		{
			*this = other * (*this);
			return *this;
		}

		Quaternion operator*(f32 s)const
		{
			return Quaternion(s*X, s*Y, s*Z, s*W);
		}
		Quaternion& operator*=(f32 s)
		{
			X*=s;
			Y*=s;
			Z*=s;
			W*=s;
			return *this;
		}

		Quaternion operator+(const Quaternion& other)const
		{
			return Quaternion(X+other.X, Y+other.Y, Z+other.Z, W+other.W);
		}

		Quaternion& operator+=(const Quaternion& other)
		{
			*this = other + (*this);
			return *this;
		}

		Quaternion operator-(const Quaternion& other)const
		{
			return Quaternion(X-other.X, Y-other.Y, Z-other.Z, W-other.W);
		}

		Quaternion& operator-=(const Quaternion& other)
		{
			*this = other - (*this);
			return *this;
		}

		Quaternion& operator=(const Matrix44f& m)
		{
			f32 diag = m(0,0) + m(1,1) + m(2,2) + 1;

			if( diag > 0.0f )
			{
				f32 scale = math::Sqrt(diag) * 2.0f; // get scale from diagonal

				// TODO: speed this up
				X = ( m(2,1) - m(1,2)) / scale;
				Y = ( m(0,2) - m(2,0)) / scale;
				Z = ( m(1,0) - m(0,1)) / scale;
				W = 0.25f * scale;
			}
			else
			{
				if ( m(0,0) > m(1,1) && m(0,0) > m(2,2))
				{
					// 1st element of diag is greatest value
					// find scale according to 1st element, and double it
					f32 scale = math::Sqrt( 1.0f + m(0,0) - m(1,1) - m(2,2)) * 2.0f;

					// TODO: speed this up
					X = 0.25f * scale;
					Y = (m(0,1) + m(1,0)) / scale;
					Z = (m(2,0) + m(0,2)) / scale;
					W = (m(2,1) - m(1,2)) / scale;
				}
				else if ( m(1,1) > m(2,2))
				{
					// 2nd element of diag is greatest value
					// find scale according to 2nd element, and double it
					f32 scale = math::Sqrt( 1.0f + m(1,1) - m(0,0) - m(2,2)) * 2.0f;

					// TODO: speed this up
					X = (m(0,1) + m(1,0) ) / scale;
					Y = 0.25f * scale;
					Z = (m(1,2) + m(2,1) ) / scale;
					W = (m(0,2) - m(2,0) ) / scale;
				}
				else
				{
					// 3rd element of diag is greatest value
					// find scale according to 3rd element, and double it
					f32 scale = math::Sqrt( 1.0f + m(2,2) - m(0,0) - m(1,1)) * 2.0f;

					// TODO: speed this up
					X = (m(0,2) + m(2,0)) / scale;
					Y = (m(1,2) + m(2,1)) / scale;
					Z = 0.25f * scale;
					W = (m(1,0) - m(0,1)) / scale;
				}
			}

			return Normalize();
		}

		Vector3Df operator * (const Vector3Df& v) const
		{
			// nVidia SDK implementation
			Vector3Df uv, uuv;
			Vector3Df qvec(X, Y, Z);
			uv = qvec.Cross(v);
			uuv = qvec.Cross(uv);
			uv *= (2.0f * W);
			uuv *= 2.0f;
			return v + uv + uuv;
		}
		static Quaternion IDENTITY;
	};
}

#endif