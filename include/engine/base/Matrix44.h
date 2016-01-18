////////////////////////////////////////////////////////
// Copyright(c) 1986-2006, TT, All Rights Reserved
// Author:  Hu Tianzhi
// Created: 2010-7-24 11:42:14
// Describe:
////////////////////////////////////////////////////////

#ifndef	_Tian_2010724114214_H_	
#define	_Tian_2010724114214_H_

#include <Windows.h>
#include "vector3d.h"
#include "math.h"

namespace panda
{
	template<typename T>
	struct Matrix44
	{
		Matrix44()	//默认构造一个单位矩阵
		{
			m_value[0] = 1;
			m_value[1] = 0;
			m_value[2] = 0;
			m_value[3] = 0;

			m_value[4] = 0;
			m_value[5] = 1;
			m_value[6] = 0;
			m_value[7] = 0;

			m_value[8] = 0;
			m_value[9] = 0;
			m_value[10] = 1;
			m_value[11] = 0;

			m_value[12] = 0;
			m_value[13] = 0;
			m_value[14] = 0;
			m_value[15] = 1;
		}

		Matrix44 (const Matrix44<T>& other)
		{
			//不用循环可是省掉跳转语句的开销
			m_value[0]=other[0];
			m_value[1]=other[1];
			m_value[2]=other[2];
			m_value[3]=other[3];
			m_value[4]=other[4];
			m_value[5]=other[5];
			m_value[6]=other[6];
			m_value[7]=other[7];
			m_value[8]=other[8];
			m_value[9]=other[9];
			m_value[10]=other[10];
			m_value[11]=other[11];
			m_value[12]=other[12];
			m_value[13]=other[13];
			m_value[14]=other[14];
			m_value[15]=other[15];
		}

		Matrix44<T>& Translation(T x, T y, T z)
		{
			this->_41 = x;
			this->_42 = y;
			this->_43 = z;
			return *this;
		}

		Matrix44<T>& Translation(const Vector3D<T>& pos)
		{
			return Translation(pos.x, pos.y, pos.z);
		}

		Vector3D<T>	GetTransltion()const
		{
			return Vector3D<T>(this->_41, this->_42, this->_43);
		}

		Matrix44<T>& Scaling(T x, T y, T z)
		{
			this->_11 = x;
			this->_22 = y;
			this->_33 = z;
			return *this;
		}

		void Inverse()
		{
			
		}


		Matrix44<T>& Scaling(const Vector3D<T>& scale)
		{
			return Scaling(scale.x, scale.y, scale.z);
		}

		Vector3D<T>	GetScaleing()
		{
			return Vector3D<T>(this->_11, this->_22, this->_33);
		}

		Matrix44<T>& Rotation(T x, T y, T z)
		{
			f32 cr = math::Cos( x );
			f32 sr = math::Sin( x );
			f32 cp = math::Cos( y );
			f32 sp = math::Sin( y );
			f32 cy = math::Cos( z );
			f32 sy = math::Sin( z );

			m_value[0] = (T)( cp*cy );
			m_value[1] = (T)( cp*sy );
			m_value[2] = (T)( -sp );

			f32 srsp = sr*sp;
			f32 crsp = cr*sp;

			m_value[4] = (T)( srsp*cy-cr*sy );
			m_value[5] = (T)( srsp*sy+cr*cy );
			m_value[6] = (T)( sr*cp );

			m_value[8] = (T)( crsp*cy+sr*sy );
			m_value[9] = (T)( crsp*sy-sr*cy );
			m_value[10] = (T)( cr*cp );
			return *this;
		}
		Matrix44<T>& Rotation(const Vector3D<T>& rot)
		{
			return Rotation(rot.x, rot.y, rot.z);
		}

		Vector3D<T> GetRotation()
		{
			
		}

		T operator()(int nRow, int nCol) const
		{
			return m_value[nRow * 4 + nCol];
		}
		T& operator()(int nRow, int nCol)
		{
			return m_value[nRow * 4 + nCol];
		}

		T operator[](int nIndex)  const
		{
			return m_value[nIndex];
		}
		T& operator[](int nIndex) 
		{
			return m_value[nIndex];
		}



		// 单位矩阵
		static const Matrix44<T>& NormalMat()
		{
			static Matrix44<T> normalMat;
			return normalMat;
		}

		//----------------------------------
		//操作符重载
		//----------------------------------
	public:
		Matrix44<T> operator+(const Matrix44<T>& other)	const
		{
			Matrix44<T> temp;

			//不用循环可是省掉跳转语句的开销
			temp[0] = m_value[0]+other[0];
			temp[1] = m_value[1]+other[1];
			temp[2] = m_value[2]+other[2];
			temp[3] = m_value[3]+other[3];
			temp[4] = m_value[4]+other[4];
			temp[5] = m_value[5]+other[5];
			temp[6] = m_value[6]+other[6];
			temp[7] = m_value[7]+other[7];
			temp[8] = m_value[8]+other[8];
			temp[9] = m_value[9]+other[9];
			temp[10] = m_value[10]+other[10];
			temp[11] = m_value[11]+other[11];
			temp[12] = m_value[12]+other[12];
			temp[13] = m_value[13]+other[13];
			temp[14] = m_value[14]+other[14];
			temp[15] = m_value[15]+other[15];

			return temp;
		}

		Matrix44<T>& operator+=(const Matrix44<T>& other)
		{
			//不用循环可是省掉跳转语句的开销
			m_value[0]+=other[0];
			m_value[1]+=other[1];
			m_value[2]+=other[2];
			m_value[3]+=other[3];
			m_value[4]+=other[4];
			m_value[5]+=other[5];
			m_value[6]+=other[6];
			m_value[7]+=other[7];
			m_value[8]+=other[8];
			m_value[9]+=other[9];
			m_value[10]+=other[10];
			m_value[11]+=other[11];
			m_value[12]+=other[12];
			m_value[13]+=other[13];
			m_value[14]+=other[14];
			m_value[15]+=other[15];

			return *this;
		}

		void operator=(const Matrix44<T>& other)
		{
			//不用循环可是省掉跳转语句的开销
			m_value[0]=other[0];
			m_value[1]=other[1];
			m_value[2]=other[2];
			m_value[3]=other[3];
			m_value[4]=other[4];
			m_value[5]=other[5];
			m_value[6]=other[6];
			m_value[7]=other[7];
			m_value[8]=other[8];
			m_value[9]=other[9];
			m_value[10]=other[10];
			m_value[11]=other[11];
			m_value[12]=other[12];
			m_value[13]=other[13];
			m_value[14]=other[14];
			m_value[15]=other[15];
		}

		Matrix44<T> operator-(const Matrix44<T>& other)	const
		{
			Matrix44<T> temp;

			//不用循环可是省掉跳转语句的开销
			temp[0] = m_value[0]-other[0];
			temp[1] = m_value[1]-other[1];
			temp[2] = m_value[2]-other[2];
			temp[3] = m_value[3]-other[3];
			temp[4] = m_value[4]-other[4];
			temp[5] = m_value[5]-other[5];
			temp[6] = m_value[6]-other[6];
			temp[7] = m_value[7]-other[7];
			temp[8] = m_value[8]-other[8];
			temp[9] = m_value[9]-other[9];
			temp[10] = m_value[10]-other[10];
			temp[11] = m_value[11]-other[11];
			temp[12] = m_value[12]-other[12];
			temp[13] = m_value[13]-other[13];
			temp[14] = m_value[14]-other[14];
			temp[15] = m_value[15]-other[15];

			return temp;
		}

		Matrix44<T>& operator-=(const Matrix44<T>& other)
		{
			//不用循环可是省掉跳转语句的开销
			m_value[0]-=other[0];
			m_value[1]-=other[1];
			m_value[2]-=other[2];
			m_value[3]-=other[3];
			m_value[4]-=other[4];
			m_value[5]-=other[5];
			m_value[6]-=other[6];
			m_value[7]-=other[7];
			m_value[8]-=other[8];
			m_value[9]-=other[9];
			m_value[10]-=other[10];
			m_value[11]-=other[11];
			m_value[12]-=other[12];
			m_value[13]-=other[13];
			m_value[14]-=other[14];
			m_value[15]-=other[15];

			return *this;
		}

		Matrix44<T> operator*(T scalar) const
		{
			Matrix44<T> temp;

			temp[0] = m_value[0]*scalar;
			temp[1] = m_value[1]*scalar;
			temp[2] = m_value[2]*scalar;
			temp[3] = m_value[3]*scalar;
			temp[4] = m_value[4]*scalar;
			temp[5] = m_value[5]*scalar;
			temp[6] = m_value[6]*scalar;
			temp[7] = m_value[7]*scalar;
			temp[8] = m_value[8]*scalar;
			temp[9] = m_value[9]*scalar;
			temp[10] = m_value[10]*scalar;
			temp[11] = m_value[11]*scalar;
			temp[12] = m_value[12]*scalar;
			temp[13] = m_value[13]*scalar;
			temp[14] = m_value[14]*scalar;
			temp[15] = m_value[15]*scalar;

			return temp;
		}

		Matrix44<T>& operator*(T scalar)
		{
			m_value[0]*=scalar;
			m_value[1]*=scalar;
			m_value[2]*=scalar;
			m_value[3]*=scalar;
			m_value[4]*=scalar;
			m_value[5]*=scalar;
			m_value[6]*=scalar;
			m_value[7]*=scalar;
			m_value[8]*=scalar;
			m_value[9]*=scalar;
			m_value[10]*=scalar;
			m_value[11]*=scalar;
			m_value[12]*=scalar;
			m_value[13]*=scalar;
			m_value[14]*=scalar;
			m_value[15]*=scalar;

			return *this;
		}

		Matrix44<T> operator*(const Matrix44<T>& other) const
		{
			Matrix44<T> temp;

			temp._11 = _11*other._11 + _12*other._21 + _13*other._31 + _14*other._41;
			temp._12 = _11*other._12 + _12*other._22 + _13*other._32 + _14*other._42;
			temp._13 = _11*other._13 + _12*other._23 + _13*other._33 + _14*other._43;
			temp._14 = _11*other._14 + _12*other._24 + _13*other._34 + _14*other._44;

			temp._21 = _21*other._11 + _22*other._21 + _23*other._31 + _24*other._41;
			temp._22 = _21*other._12 + _22*other._22 + _23*other._32 + _24*other._42;
			temp._23 = _21*other._13 + _22*other._23 + _23*other._33 + _24*other._43;
			temp._24 = _21*other._14 + _22*other._24 + _23*other._34 + _24*other._44;

			temp._31 = _31*other._11 + _32*other._21 + _33*other._31 + _34*other._41;
			temp._32 = _31*other._12 + _32*other._22 + _33*other._32 + _34*other._42;
			temp._33 = _31*other._13 + _32*other._23 + _33*other._33 + _34*other._43;
			temp._34 = _31*other._14 + _32*other._24 + _33*other._34 + _34*other._44;

			temp._41 = _41*other._11 + _42*other._21 + _43*other._31 + _44*other._41;
			temp._42 = _41*other._12 + _42*other._22 + _43*other._32 + _44*other._42;
			temp._43 = _41*other._13 + _42*other._23 + _43*other._33 + _44*other._43;
			temp._44 = _41*other._14 + _42*other._24 + _43*other._34 + _44*other._44;


			return temp;
		}

		Matrix44<T>& operator*=(const Matrix44<T>& other)
		{
			Matrix44<T> temp;

			temp[0] = _11*other._11 + _12*other._21 + _13*other._31 + _14*other._41;
			temp[1] = _11*other._12 + _12*other._22 + _13*other._32 + _14*other._42;
			temp[2] = _11*other._13 + _12*other._23 + _13*other._33 + _14*other._43;
			temp[3] = _11*other._14 + _12*other._24 + _13*other._34 + _14*other._44;

			temp[4] = _21*other._11 + _22*other._21 + _23*other._31 + _24*other._41;
			temp[5] = _21*other._12 + _22*other._22 + _23*other._32 + _24*other._42;
			temp[6] = _21*other._13 + _22*other._23 + _23*other._33 + _24*other._43;
			temp[7] = _21*other._14 + _22*other._24 + _23*other._34 + _24*other._44;

			temp[8] = _31*other._11 + _32*other._21 + _33*other._31 + _34*other._41;
			temp[9] = _31*other._12 + _32*other._22 + _33*other._32 + _34*other._42;
			temp[10] = _31*other._13 + _32*other._23 + _33*other._33 + _34*other._43;
			temp[11] = _31*other._14 + _32*other._24 + _33*other._34 + _34*other._44;

			temp[12] = _41*other._11 + _42*other._21 + _43*other._31 + _44*other._41;
			temp[13] = _41*other._12 + _42*other._22 + _43*other._32 + _44*other._42;
			temp[14] = _41*other._13 + _42*other._23 + _43*other._33 + _44*other._43;
			temp[15] = _41*other._14 + _42*other._24 + _43*other._34 + _44*other._44;

			*this = temp;

			return *this;
		}

		bool operator==(const Matrix44<T>& other)const
		{
			int r = memcmp(this, &other, sizeof(Matrix44<T>));
			return r == 0;
		}

		bool operator!=(const Matrix44<T>& other)const
		{			
			return !(*this == other);
		}

	public:
		union
		{
			struct
			{
				T _11,_12,_13,_14;
				T _21,_22,_23,_24;
				T _31,_32,_33,_34;
				T _41,_42,_43,_44;
			};	
			T m_value[16];
		};
	};
	
	typedef Matrix44<f32>	Matrix44f;
}

#endif