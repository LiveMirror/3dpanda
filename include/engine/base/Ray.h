////////////////////////////////////////////////////////
// Copyright(c) 1986-2006, TT, All Rights Reserved
// Author:  Hu Tianzhi
// Created: 2010-7-24 11:36:30
// Describe:
////////////////////////////////////////////////////////

#ifndef	_Tian_2010724113630_H_	
#define	_Tian_2010724113630_H_

#include "Vector3D.h"

namespace panda
{
	struct Ray
	{
		Vector3Df	sPosition;
		Vector3Df	sDirction;
	
		Ray(){}
		Ray(const Vector3Df& pos, const Vector3Df& dir)
		{
			sPosition = pos;
			sDirction = dir;
			sDirction.Normalize();
		}

		//! 焦点坐标可以用以下两种方式求得
		//!	O + Dt
		//!	(1 - u - v)V0 + uV1 + vV2
		// t(out): weight of the intersection for the ray
		// u(out), v(out): barycentric coordinate of intersection
		bool IntersectTriangle(Vector3Df& v0, Vector3Df& v1, Vector3Df& v2,
			f32* t, f32* u, f32* v)const
		{
			// E1
			Vector3Df E1 = v1 - v0;

			// E2
			Vector3Df E2 = v2 - v0;

			// P
			Vector3Df P = sDirction.Cross(E2);

			// determinant
			f32 det = E1.DotProduct(P);

			// keep det > 0, modify T accordingly
			Vector3Df T;
			if( det > 0 )
			{
				T = sPosition - v0;
			}
			else
			{
				T = v0 - sPosition;
				det = -det;
			}

			// If determinant is near zero, ray lies in plane of triangle
			if( det < 0.0001f )
				return false;

			// Calculate u and make sure u <= 1
			*u = T.DotProduct(P);
			if( *u < 0.0f || *u > det )
				return false;

			// Q
			Vector3Df Q = T.Cross(E1);
			// Calculate v and make sure u + v <= 1
			*v = sDirction.DotProduct(Q);
			if( *v < 0.0f || *u + *v > det )
				return false;

			// Calculate t, scale parameters, ray intersects triangle
			*t = E2.DotProduct(Q);

			f32 fInvDet = 1.0f / det;
			*t *= fInvDet;
			*u *= fInvDet;
			*v *= fInvDet;

			return true;
		}
	};
}

#endif