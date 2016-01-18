//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/29 10:14:59_
// ����:  
//

#ifndef _PARTICLE_2014529101459_
#define _PARTICLE_2014529101459_

#include "base/Vector3D.h"
#include "base/Color.h"
#include "base/Matrix44.h"
#include "base/Quaternion.h"

namespace panda
{
	class IParticleEmitter;
	class Particle
	{
	public:
		Particle(void);
		~Particle(void);

		bool			Update(f32 time);
		void			GetTransform(Matrix44f& outMat);
	public:
		Vector3Df		mPos;
		Vector3Df		mDirection;			// Direction
		Vector3Df		mSize;
		f32				mSpeed;				// speed
		Colorf			mColor;
		Quaternion		mRotation;
		f32				mRotationSpeed;		// Speed of rotation
		f32				mTimeToLive;
		f32				mTotalTimeToLive;
		bool			mIsDead;			// ������������Ƿ����
		IParticleEmitter*	mCreater;
	};
}

#endif // _PARTICLE_2014529101459_