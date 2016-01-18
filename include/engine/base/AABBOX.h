////////////////////////////////////////////////////////
// Copyright(c) 1986-2006, TT, All Rights Reserved
// Author:  Hu Tianzhi
// Created: 2010-7-21 23:06:56
// Describe:绑定盒
////////////////////////////////////////////////////////

#ifndef	_Tian_2010721230656_H_
#define	_Tian_2010721230656_H_

#include "Vector3D.h"
#include "Plane.h"
#include "line.h"
#include "ray.h"
#include "matrix44.h"

namespace panda
{
	struct AABBOX
	{
	public:
		Vector3Df maxPoint, minPoint;

		AABBOX(){}
		AABBOX(const Vector3Df& max, const Vector3Df& min)
		{
			maxPoint = max;
			minPoint = min;
		}

	public:
		bool	operator==(const AABBOX& other)const
		{
			return maxPoint == other.maxPoint && minPoint == other.minPoint;
		}

		AABBOX operator +(const Vector3Df& point)const
		{
			AABBOX box;
			box.maxPoint.x = math::Max(maxPoint.x, point.x);
			box.maxPoint.y = math::Max(maxPoint.y, point.y);
			box.maxPoint.z = math::Max(maxPoint.z, point.z);


			box.minPoint.x = math::Min(minPoint.x, point.x);
			box.minPoint.y = math::Min(minPoint.y, point.y);
			box.minPoint.z = math::Min(minPoint.z, point.z);

			return box;
		}
		AABBOX operator +=(const Vector3Df& point)
		{
			maxPoint.x = math::Max(maxPoint.x, point.x);
			maxPoint.y = math::Max(maxPoint.y, point.y);
			maxPoint.z = math::Max(maxPoint.z, point.z);


			minPoint.x = math::Min(minPoint.x, point.x);
			minPoint.y = math::Min(minPoint.y, point.y);
			minPoint.z = math::Min(minPoint.z, point.z);

			return *this;
		}


		AABBOX operator +(const AABBOX& other)const
		{
			AABBOX box;
			box.maxPoint.x = math::Max(maxPoint.x, other.maxPoint.x);
			box.maxPoint.y = math::Max(maxPoint.y, other.maxPoint.y);
			box.maxPoint.z = math::Max(maxPoint.z, other.maxPoint.z);


			box.minPoint.x = math::Min(minPoint.x, other.minPoint.x);
			box.minPoint.y = math::Min(minPoint.y, other.minPoint.y);
			box.minPoint.z = math::Min(minPoint.z, other.minPoint.z);

			return box;
		}

		AABBOX& operator +=(const AABBOX& other)
		{
			maxPoint.x = math::Max(maxPoint.x, other.maxPoint.x);
			maxPoint.y = math::Max(maxPoint.y, other.maxPoint.y);
			maxPoint.z = math::Max(maxPoint.z, other.maxPoint.z);


			minPoint.x = math::Min(minPoint.x, other.minPoint.x);
			minPoint.y = math::Min(minPoint.y, other.minPoint.y);
			minPoint.z = math::Min(minPoint.z, other.minPoint.z);

			return *this;
		}

	public:
		void	ResetBox()
		{
			minPoint.x = F32_MAX;
			minPoint.y = F32_MAX;
			minPoint.z = F32_MAX;

			maxPoint.x = F32_MIN;
			maxPoint.y = F32_MIN;
			maxPoint.z = F32_MIN;
		}

		// 根据矩阵变换包围盒
		void	TransformBox(const Matrix44f& sMat)
		{
			// 算法参见
			// http://hi.baidu.com/gwrensheng/blog/item/387dd63f597fa8cd7c1e7194.html

			Vector3Df sMax = maxPoint;
			Vector3Df sMin = minPoint;

			maxPoint = minPoint = Vector3Df(sMat._41, sMat._42, sMat._43);

			if (sMat._11 > 0.0f)
			{
				minPoint.x += sMat._11 * sMin.x;	maxPoint.x += sMat._11 * sMax.x;
			}
			else
			{
				minPoint.x += sMat._11 * sMax.x;	maxPoint.x += sMat._11 * sMin.x;
			}

			if (sMat._12 > 0.0f)
			{
				minPoint.y += sMat._12 * sMin.x;	maxPoint.y += sMat._12 * sMax.x;
			}
			else
			{
				minPoint.y += sMat._12 * sMax.x;	maxPoint.y += sMat._12 * sMin.x;
			}

			if (sMat._13 > 0.0f)
			{
				minPoint.z += sMat._13 * sMin.x;	maxPoint.z += sMat._13 * sMax.x;
			}
			else
			{
				minPoint.z += sMat._13 * sMax.x;	maxPoint.z += sMat._13 * sMin.x;
			}

			if (sMat._21 > 0.0f)
			{
				minPoint.x += sMat._11 * sMin.y;	maxPoint.x += sMat._11 * sMax.y;
			}
			else
			{
				minPoint.x += sMat._11 * sMax.y;	maxPoint.x += sMat._11 * sMin.y;
			}

			if (sMat._22 > 0.0f)
			{
				minPoint.y += sMat._12 * sMin.y;	maxPoint.y += sMat._12 * sMax.y;
			}
			else
			{
				minPoint.y += sMat._12 * sMax.y;	maxPoint.y += sMat._12 * sMin.y;
			}

			if (sMat._23 > 0.0f)
			{
				minPoint.z += sMat._13 * sMin.y;	maxPoint.z += sMat._13 * sMax.y;
			}
			else
			{
				minPoint.z += sMat._13 * sMax.y;	maxPoint.z += sMat._13 * sMin.y;
			}

			if (sMat._31 > 0.0f)
			{
				minPoint.x += sMat._11 * sMin.z;	maxPoint.x += sMat._11 * sMax.z;
			}
			else
			{
				minPoint.x += sMat._11 * sMax.z;	maxPoint.x += sMat._11 * sMin.z;
			}

			if (sMat._32 > 0.0f)
			{
				minPoint.y += sMat._12 * sMin.z;	maxPoint.y += sMat._12 * sMax.z;
			}
			else
			{
				minPoint.y += sMat._12 * sMax.z;	maxPoint.y += sMat._12 * sMin.z;
			}

			if (sMat._33 > 0.0f)
			{
				minPoint.z += sMat._13 * sMin.z;	maxPoint.z += sMat._13 * sMax.z;
			}
			else
			{
				minPoint.z += sMat._13 * sMax.z;	maxPoint.z += sMat._13 * sMin.z;
			}
			
		}
		bool	IsAbsInside(const Vector3Df& point)const
		{
			return point > minPoint && point < maxPoint;
		}

		bool	IsInside(const Vector3Df& point)const
		{
			return point >= minPoint && point <= maxPoint;
		}

		bool	IsAbsInside(const AABBOX& other)const
		{
			return maxPoint > other.maxPoint && minPoint < other.minPoint;
		}

		bool	IsInside(const AABBOX& other)const
		{
			return maxPoint >= other.maxPoint && minPoint <= other.minPoint;
		}

		// 与平面的相交检查
		// 1 在平面正面
		// -1 在平面背面
		// 0 相交
		int		IntersectsWithPlane(const Plane& Plane)const
		{
			// 检查法向量， 计算最小和最大D值，即距离
			f32 minD, maxD;
			
			if (Plane.sNormal.x > 0.0f)
			{
				minD = Plane.sNormal.x * minPoint.x;
				maxD = Plane.sNormal.x * maxPoint.x;
			}
			else
			{
				minD = Plane.sNormal.x * maxPoint.x;
				maxD = Plane.sNormal.x * minPoint.x;
			}

			if (Plane.sNormal.y > 0.0f)
			{
				minD += Plane.sNormal.y * minPoint.y;
				maxD += Plane.sNormal.y * maxPoint.y;
			}
			else
			{
				minD += Plane.sNormal.y * maxPoint.y;
				maxD += Plane.sNormal.y * minPoint.y;
			}


			if (Plane.sNormal.z > 0.0f)
			{
				minD += Plane.sNormal.z * minPoint.z;
				maxD += Plane.sNormal.z * maxPoint.z;
			}
			else
			{
				minD += Plane.sNormal.z * maxPoint.z;
				maxD += Plane.sNormal.z * minPoint.z;
			}

			if (minD >= Plane.fD)
			{
				return 1;
			}

			if (maxD <= Plane.fD)
			{
				return -1;
			}

			return 0;
		}

		bool	IntersectsWithAABBOX(const AABBOX& other)const
		{
			if (minPoint.x > other.maxPoint.x)
			{
				return false;
			}
			if (minPoint.y > other.maxPoint.y)
			{
				return false;
			}
			if (minPoint.z > other.maxPoint.z)
			{
				return false;
			}

			if (maxPoint.x < other.minPoint.x)
			{
				return false;
			}
			if (maxPoint.y < other.minPoint.y)
			{
				return false;
			}
			if (maxPoint.z < other.minPoint.z)
			{
				return false;
			}

			return true;
		}

		bool	IntersectsWithLine(const Line& line)const
		{
			return false;
		}

		bool	IntersectsWithRay(const Ray& ray, Vector3Df& outPoint)const
		{
			// 射线起点在盒子内
			if (ray.sPosition <= maxPoint && ray.sPosition >= minPoint)
			{
				outPoint = ray.sPosition;
				return true;
			}

			f32 lowt = 0.0f;
			bool bHit = false;
			f32 t;

			//依次检查各面的相交情况
			if(ray.sPosition.x < minPoint.x && ray.sDirction.x > 0)
			{
				t = (minPoint.x - ray.sPosition.x)/ray.sDirction.x;
				if(t>0)
				{
					outPoint = ray.sPosition + ray.sDirction * t;
					if(outPoint.y>=minPoint.y && outPoint.y<=maxPoint.y && outPoint.z>=minPoint.z && outPoint.z<=maxPoint.z && (!bHit || t<lowt))
					{
						bHit = true;
						lowt = t;
					}
				}
			}

			if(ray.sPosition.x > maxPoint.x && ray.sDirction.x < 0)
			{
				t = (maxPoint.x - ray.sPosition.x)/ray.sDirction.x;
				if(t>0)
				{
					outPoint = ray.sPosition + ray.sDirction*t;
					if(outPoint.y>minPoint.y && outPoint.y<=maxPoint.y &&
						outPoint.z>=minPoint.z && outPoint.z<=maxPoint.z &&
						(!bHit || t<lowt))
					{
						bHit = true;
						lowt = t;
					}
				}
			}

			if(ray.sPosition.y<minPoint.y && ray.sDirction.y>0)
			{
				t = (minPoint.y-ray.sPosition.y)/ray.sDirction.y;
				if(t>0)
				{
					outPoint = ray.sPosition + ray.sDirction*t;
					if (outPoint.x >= minPoint.x && outPoint.x <= maxPoint.x &&
						outPoint.z >= minPoint.z && outPoint.z <= maxPoint.z &&
						(!bHit || t < lowt))
					{
						bHit = true;
						lowt = t;
					}
				}
			}

			if (ray.sPosition.y > maxPoint.y && ray.sDirction.y < 0)
			{
				t = (maxPoint.y - ray.sPosition.y) / ray.sDirction.y;
				if (t > 0)
				{
					outPoint = ray.sPosition + ray.sDirction * t;
					if (outPoint.x >= minPoint.x && outPoint.x <= maxPoint.x &&
						outPoint.z >= minPoint.z && outPoint.z <= maxPoint.z &&
						(!bHit || t < lowt))
					{
						bHit = true;
						lowt = t;
					}
				}
			}

			if (ray.sPosition.z < minPoint.z && ray.sDirction.z > 0)
			{
				t = (minPoint.z - ray.sPosition.z) / ray.sDirction.z;
				if (t > 0)
				{
					outPoint = ray.sPosition + ray.sDirction * t;
					if (outPoint.x >= minPoint.x && outPoint.x <= maxPoint.x &&
						outPoint.y >= minPoint.y && outPoint.y <= maxPoint.y &&
						(!bHit || t < lowt))
					{
						bHit = true;
						lowt = t;
					}
				}
			}

			if (ray.sPosition.z > maxPoint.z && ray.sDirction.z < 0)
			{
				t = (maxPoint.z - ray.sPosition.z) / ray.sDirction.z;
				if (t > 0)
				{
					outPoint = ray.sPosition + ray.sDirction * t;
					if (outPoint.x >= minPoint.x && outPoint.x <= maxPoint.x &&
						outPoint.y >= minPoint.y && outPoint.y <= maxPoint.y &&
						(!bHit || t < lowt))
					{
						bHit = true;
						lowt = t;
					}
				}
			}

			return bHit;			
		}

		// AABB 上距离点point最近的距离
		// outPoint 最近的点
		f32	ClosestPoint(const Vector3Df& point, Vector3Df& outPoint)
		{
			outPoint = point;
			if (point.x < minPoint.x)
			{
				outPoint.x = minPoint.x;
			}
			else if (point.x > maxPoint.x)
			{
				outPoint.x = maxPoint.x;
			}

			if (point.y < minPoint.y)
			{
				outPoint.y = minPoint.y;
			}
			else if (point.y > maxPoint.y)
			{
				outPoint.y = maxPoint.y;
			}

			if (point.z < minPoint.z)
			{
				outPoint.z = minPoint.z;
			}
			else if (point.z > maxPoint.z)
			{
				outPoint.z = maxPoint.z;
			}
			return outPoint.DistanceFrom(point);
		}



	};
}

#endif