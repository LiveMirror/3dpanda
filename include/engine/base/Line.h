////////////////////////////////////////////////////////
// Copyright(c) 1986-2006, TT, All Rights Reserved
// Author:  Hu Tianzhi
// Created: 2010-7-21 23:05:22
// Describe:直线(采用两点表示法)
////////////////////////////////////////////////////////

#ifndef	_Tian_2010721230522_H_
#define	_Tian_2010721230522_H_

#include "Vector3D.h"
#include "Plane.h"

namespace panda
{
	struct Line
	{
	public:	
		Vector3Df sSatrt;
		Vector3Df sEnd;

	public:
		// The minimum distance of the point to the line
		// outPoint:the nearest point on the line to return
		f32 Distance(const Vector3Df& sPoint, Vector3Df& outPoint)const
		{
			Vector3Df c = sPoint - sSatrt;
			Vector3Df v = sEnd - sSatrt;

			f32 d = v.Length();
			v /= d;
			f32 t = v.DotProduct(c);

			if (t < 0.0f)
			{
				outPoint = sSatrt;
				return outPoint.DistanceFrom(sPoint);
			}
			if (t > d)
			{
				outPoint = sEnd;
				return outPoint.DistanceFrom(sPoint);
			}

			v *= t;
			outPoint = sSatrt + v;
			return outPoint.DistanceFrom(sPoint);
		}

		// The minimum distance of the line to the line
		// outPoint:the nearest point on the line to return
		f32 Distance(const Line& sLine, Vector3Df& outPoint1, Vector3Df& outPoint2)const
		{
			return 0.0f;
		}

		// outPoint:the intersected point to return
		bool Intersect(const Plane& sPlane, Vector3Df& outPoint)const
		{
			return sPlane.IntersectWithRay(sSatrt, sEnd - sSatrt, outPoint);
		}

		Vector3Df GetVector()
		{
			return sSatrt - sEnd;
		}
		
	};
}

#endif