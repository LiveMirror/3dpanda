//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/26 9:55:04_
// 描述:  
//

#ifndef _SIZE_201422695504_
#define _SIZE_201422695504_

namespace panda
{
	struct Size
	{
		s32 width, height;

		Size(void)
		{
			width = height = 0;
		}
		Size(s32 nWidth, s32 nHeight)
		{
			width = nWidth;
			height = nHeight;
		}
		bool operator > (const Size& other)const
		{
			if (width > other.width && height > other.height)
			{
				return true;
			}
			return false;
		}

		bool operator >= (const Size& other)const
		{
			if (width >= other.width && height >= other.height)
			{
				return true;
			}
			return false;
		}

		bool operator == (const Size& other)const
		{
			if (width == other.width && height == other.height)
			{
				return true;
			}
			return false;
		}

		bool operator != (const Size& other)const
		{
			if (*this == other)
			{
				return false;
			}
			return true;
		}

		Size operator + (const Size& other)const
		{
			Size temp = *this;
			temp.width += other.width;
			temp.height += other.height;
			return temp;
		}

		Size& operator += (const Size& other)
		{
			this->width += other.width;
			this->height += other.height;
			return *this;
		}

		Size operator - (const Size& other)const
		{
			Size temp = *this;
			temp.width -= other.width;
			temp.height -= other.height;
			return temp;
		}

		Size& operator -= (const Size& other)
		{
			this->width -= other.width;
			this->height -= other.height;
			return *this;
		}
	};
}

#endif // _SIZE_201422695504_