////////////////////////////////////////////////////////
// Copyright(c) 1986-2006, TT, All Rights Reserved
// Author:  Hu Tianzhi
// Created: 2010-7-21 23:00:55
// Describe: 平面
////////////////////////////////////////////////////////

#ifndef	_Tian_2010721230055_H_
#define	_Tian_2010721230055_H_

#include "Vector3D.h"

namespace panda
{
	// fuction: n*p + d = 0	
	// d = - n*p1
	struct Plane
	{
	public:
		Vector3Df	sNormal;
		f32		fD;
	public:
		Plane()
		{
			sNormal.x = 0.0f;
			sNormal.y = 1.0f;
			sNormal.z = 0.0f;
			fD = 0.0f;
		}
		
		// sPoint：the point which is on the plane
		Plane(Vector3Df& normal, Vector3Df& sPoint)
		{
			sNormal = normal;
			sNormal.Normalize();
			fD = (sNormal * sPoint);
		}
		
		// three point all on the plane
		Plane(Vector3Df& p1, Vector3Df& p2, Vector3Df& p3)
		{
			sNormal = (p2 - p1).Cross(p3 - p1);
			sNormal.Normalize();
			fD = (sNormal * p1);
		}

	public:
		// The minimum distance of the point to the plane
		// outPoint:the nearest point on the plane to return
		f32 Distance(const Vector3Df& sPoint, Vector3Df& outPoint)const
		{
			return sPoint.DotProduct(sNormal) + fD;
		}

		// whether the point on the plane
		bool IsPointOn(const Vector3Df& sPoint)const
		{
			f32 r = sNormal* sPoint + fD;		// depend on the plane fuction
			return math::Equal(r);
		}

		// 与射线碰撞
		bool IntersectWithRay(const Vector3Df& pos, const Vector3Df& sDirction, Vector3Df& outPoint)const
		{
			f32 dn = sDirction * sNormal;
			if (0 == dn)
			{
				return false;
			}

			f32 t = (fD - pos * sNormal) / dn;
			outPoint = pos + sDirction * t;
			return true;
		}

	};
}

#endif