#include "Particle.h"
#include "particlesystem/IParticleEmitter.h"
#include "particleemitterimpl.h"

namespace panda
{
	Particle::Particle( void )
		:mRotationSpeed(0),
		mIsDead(false),
		mTimeToLive(0)
	{
		mSize.x = 1;
		mSize.y = 1;
		mSize.z = 1;
	}

	Particle::~Particle( void )
	{
		mCreater->mImpl->decNum();
	}

	bool Particle::Update( f32 time )
	{
		Vector3Df dir = mDirection * mSpeed * time;
		mPos += dir;

		mTimeToLive += time;
		if(mTimeToLive > mTotalTimeToLive && mTotalTimeToLive > 0)
		{
			return false;
		}
		return true;
	}

	void Particle::GetTransform( Matrix44f& outMat )
	{
		outMat = Matrix44f::NormalMat();
		mRotation.GetMatrix(outMat);
		if (mSize != Vector3Df(1.0f, 1.0f, 1.0f))
		{
			Matrix44f smat;
			smat.Scaling(mSize);
			outMat *= smat;
		}
		outMat.Translation(mPos);
	}
}