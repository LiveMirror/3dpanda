////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2011-7-9 11:23:33
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201179112333_H_
#define	_Tian_201179112333_H_


#include "Config.h"
#include "math.h"

namespace panda
{
	struct Colorf
	{
		f32 r;
		f32 g;
		f32 b;
		f32 a;

		Colorf()
		{
			a = 1.0f;
			r = 1.0f;
			g = 1.0f;
			b = 1.0f;
		}
		Colorf(f32 A, f32 R, f32 G, f32 B)
		{
			a = A;
			r = R;
			g = G;
			b = B;
		}
		

		Colorf operator -(const Colorf& other)const
		{
			Colorf c;
			c.a = a - other.a;
			c.r = r - other.r;
			c.g = g - other.g;
			c.b = b - other.b;
			return c;
		}

		Colorf operator +(const Colorf& other)const
		{
			Colorf c;
			c.a = a + other.a;
			c.r = r + other.r;
			c.g = g + other.g;
			c.b = b + other.b;
			return c;
		}

		Colorf operator *(f32 value)const
		{
			Colorf c;
			c.a = a * value;
			c.r = r * value;
			c.g = g * value;
			c.b = b * value;
			return c;
		}

		Colorf& operator =(f32 value)
		{
			a = value;
			r = value;
			g = value;
			b = value;
			return *this;
		}

		Colorf& operator *=(f32 value)
		{			
			a *= value;
			r *= value;
			g *= value;
			b *= value;
			return *this;
		}


		Colorf& operator -=(const Colorf& other)
		{
			a -= other.a;
			r -= other.r;
			g -= other.g;
			b -= other.b;
			return *this;
		}

		Colorf& operator +=(const Colorf& other)
		{
			a += other.a;
			r += other.r;
			g += other.g;
			b += other.b;
			return *this;
		}
		bool operator ==(const Colorf& other)
		{
			if (a != other.a && r != other.r && g != other.g && b != other.b)
			{
				return true;
			}
			return false;
		}


		bool operator !=(const Colorf& other)
		{
			if (a != other.a || r != other.r || g != other.g || b != other.b)
			{
				return true;
			}
			return false;
		}
	};


	struct Color
	{
		Color()
		{
			value = 0xFF000000;
		}
		Color(u32 color)
		{
			value = color;
		}
		Color(int a, int r, int g, int b)
		{
			A = a;
			R = r;
			G = g;
			B = b;
		}		
		template<typename T>
		Color& operator *=(T value)
		{			
			int temp = (int)A * value;
			if (temp > 255)
			{
				temp = 255;
			}
			A = temp;

			temp = (int)R * value;
			if (temp > 255)
			{
				temp = 255;
			}
			R = temp;

			temp = (int)G * value;
			if (temp > 255)
			{
				temp = 255;
			}
			G = temp;

			temp = (int)B * value;
			if (temp > 255)
			{
				temp = 255;
			}
			B = temp;
			return *this;
		}

		template<typename T>
		Color operator *(T value)
		{
			Color c;
			int temp = (int)(A * value);
			if (temp > 255)
			{
				temp = 255;
			}
			c.A = temp;

			temp = (int)(R * value);
			if (temp > 255)
			{
				temp = 255;
			}
			c.R = temp;

			temp = (int)(G * value);
			if (temp > 255)
			{
				temp = 255;
			}
			c.G = temp;

			temp = (int)(B * value);
			if (temp > 255)
			{
				temp = 255;
			}
			c.B = temp;
			return c;
		}
		Color operator -(const Color& other)
		{
			Color c;
			int temp = A - other.A;
			math::Regular255(temp);
			c.A = temp;

			temp = R - other.R;
			math::Regular255(temp);
			c.R = temp;

			temp = G - other.G;
			math::Regular255(temp);
			c.G = temp;

			temp = B - other.B;
			math::Regular255(temp);
			c.B = temp;
			return c;
		}

		Color& operator +=(const Color& other)
		{
			int temp = A + other.A;
			math::Regular255(temp);
			A = temp;

			temp = R + other.R;
			math::Regular255(temp);
			R = temp;

			temp = G + other.G;
			math::Regular255(temp);
			G = temp;

			temp = B + other.B;
			math::Regular255(temp);
			B = temp;
			return *this;
		}

		bool operator ==(const Color& other)
		{
			if (value == other.value)
			{
				return true;
			}
			return false;
		}

		union
		{
			struct
			{
				u8	B;
				u8	G;
				u8	R;
				u8	A;
			};
			u32 value;
		};
		
	};

	
	
	namespace SysColor
	{
		const Color white = 0xFFFFFFFF;
		const Color black = 0xFF000000;
		const Color red = 0xFFFF0000;
		const Color pink = 0xFFFFD3F5;
	}

	namespace SysColorf
	{
		const Colorf white(1, 1, 1, 1);
		const Colorf black(1, 0, 0, 0);
		const Colorf red(1, 1, 0, 0);
	}

}

#endif _Tian_201179112333_H_