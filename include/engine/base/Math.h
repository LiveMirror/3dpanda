////////////////////////////////////////////////////////
// Copyright(c) 1986-2006, TT, All Rights Reserved
// Author:  Hu Tianzhi
// Created: 2010-7-21 21:18:55
// Describe:
////////////////////////////////////////////////////////

#ifndef	_Tian_2010721211855_H_	
#define	_Tian_2010721211855_H_

#include <math.h>
#include "Config.h"

namespace panda
{
#define PI	3.14159265359f
#define DEGREE	PI / 180.0f
#define F32_MAX         3.402823466e+38F        /* max value */
#define F32_MIN         1.175494351e-38F        /* min positive value */

	class math
	{
	public:
		//----------------------------------
		//快速的浮点数平方根求解
		//----------------------------------
		static f32 QuickSqrt(f32 x)
		{
			union{
				int intPart;
				f32 floatPart;
			} convertor;
			union{
				int intPart;
				f32 floatPart;
			} convertor2;
			convertor.floatPart = x;
			convertor2.floatPart = x;
			convertor.intPart = 0x1FBCF800 + (convertor.intPart >> 1);
			convertor2.intPart = 0x5f3759df - (convertor2.intPart >> 1);
			return 0.5f * (convertor.floatPart + (x * convertor2.floatPart));
		}

		//----------------------------------
		//快速整数平方根求解
		//逐位确定法
		//----------------------------------
		static int QuickSqrt(int n) 
		{ 
			int temp, nHat = 0, b = 0x8000, bshft = 15; 
			do 
			{ 
				if (n >= (temp = (((nHat<<1)+b)<<bshft--))) 
				{ 
					nHat += b; 
					n -= temp; 
				} 
			} while (b >>= 1); 
			return nHat; 
		}
		//----------------------------------
		//计算参数x的平方根的倒数
		// Inv -> inverse
		//----------------------------------
		static f32 InvSqrt (f32 x)
		{
			f32 xhalf = 0.5f * x;
			int i = *(int*)&x;
			i = 0x5f3759df - (i >> 1); // 计算第一个近似根
			x = *(f32*)&i;
			x = x * (1.5f - xhalf * x * x); // 牛顿迭代法
			return x;
		}

		//----------------------------------
		//求绝对值
		//----------------------------------
		template<typename T>
		static inline T absValue(T value)
		{
			return value>0 ? value : -value;
		}

		//----------------------------------
		//求两者较大
		//----------------------------------
		template<typename T>
		static inline T Max(T value1, T value2)
		{
			return value1 >= value2 ? value1 : value2;
		}

		//----------------------------------
		//求两者较小
		//----------------------------------
		template<typename T>
		static inline T Min(T value1, T value2)
		{
			return value1 <= value2 ? value1 : value2;
		}

		//---------------------------------------
		//判断浮点数相等
		//---------------------------------------
		static inline bool Equal(f32 fValue1, f32 fValue2, f32 fMistake = 0.0001f)
		{
			return absValue(fValue1 - fValue2) <= fMistake; 
		}

		// 将值限定在0-255之间
		static inline void Regular255(int& value)
		{
			if (value > 255)
			{
				value = 255;
			}
			else if (value < 0)
			{
				value = 0;
			}
		}

		//---------------------------------------
		//判断浮点数是否为零
		//---------------------------------------
		static inline bool Equal(f32 fValue, f32 fMistake = 0.0001f)
		{
			return absValue(fValue) <= fMistake; 
		}

		static f32 Cos(f32 x)
		{
			return ::cos(x);
		}

		static f32 ACos(f32 x)
		{
			return ::acos(x);
		}

		static f32 Sin(f32 x)
		{
			return ::sin(x);
		}

		static f32 Sqrt(f32 x)
		{
			return ::sqrt(x);
		}

		static f32 Atan2(f32 x, f32 y)
		{
			return ::atan2(x, y);
		}

		// 求fValue的x次幂
		template<typename T>
		static T PowerX(T fValue, int x)
		{
			if (0 == x)
			{
				return 1;
			}
			T r = 1;
			for(int i = 0; i < x; i++)
			{
				r *= fValue;
			}
			return r;
		}

		static f32 FMod(f32 x, f32 y)
		{
			while (x > y)
			{
				x -= y;
			}
			return x;
		}
	};
}

#endif