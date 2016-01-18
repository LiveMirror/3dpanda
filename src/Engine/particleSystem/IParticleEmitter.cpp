#include "particleSystem/IParticleEmitter.h"
#include "ParticleEmitterImpl.h"

namespace panda
{
	IParticleEmitter::IParticleEmitter( ParticleEmitterImpl* impl )
		:mImpl(impl)
	{
		if(NULL != mImpl)
		{
			mImpl->mThis = this;
		}
	}

	ParticleEmitterType::eValue IParticleEmitter::GetType( void ) const
	{
		return mImpl->mType;
	}

	void IParticleEmitter::SetName( const tstring& name )
	{
		mImpl->mName = name;
	}

	const tstring& IParticleEmitter::GetName( void ) const
	{
		return mImpl->mName;
	}

	void IParticleEmitter::SetPosition( const Vector3Df& pos )
	{
		mImpl->mPos = pos;
	}

	const Vector3Df& IParticleEmitter::GetPosition( void ) const
	{
		return mImpl->mPos;
	}

	void IParticleEmitter::SetDirection( const Vector3Df& direction )
	{
		mImpl->mDirection = direction;
	}

	const Vector3Df& IParticleEmitter::GetDirection( void ) const
	{
		return mImpl->mDirection;
	}

	IParticleTechnique* IParticleEmitter::GetParent( void ) const
	{
		return mImpl->mParent;
	}

	void IParticleEmitter::SetAngle( s32 angle )
	{
		if(angle > 180)
		{
			angle = 180;
		}
		else if(angle < 0)
		{
			angle = 0;
		}
		mImpl->mAngle = angle;
	}

	s32 IParticleEmitter::GetAngle( void ) const
	{
		return mImpl->mAngle;
	}

	void IParticleEmitter::SetMaxSpeed( f32 speed )
	{
		mImpl->mMaxSpeed = speed;
	}

	f32 IParticleEmitter::GetMaxSpeed( void ) const
	{
		return mImpl->mMaxSpeed;
	}

	void IParticleEmitter::SetMinSpeed( f32 speed )
	{
		mImpl->mMinSpeed = speed;
	}

	f32 IParticleEmitter::GetMinSpeed( void ) const
	{
		return mImpl->mMinSpeed;
	}

	void IParticleEmitter::SetLoop( bool loop )
	{
		mImpl->mLoop = loop;
	}

	bool IParticleEmitter::GetLoop( void ) const
	{
		return mImpl->mLoop;
	}

	void IParticleEmitter::SetMinNum( s32 num )
	{
		mImpl->mMinNum = num;
	}

	s32 IParticleEmitter::GetMinNum( void ) const
	{
		return mImpl->mMinNum;
	}

	void IParticleEmitter::SetMaxNum( s32 num )
	{
		mImpl->mMaxNum = num;
	}

	s32 IParticleEmitter::GetMaxNum( void ) const
	{
		return mImpl->mMaxNum;
	}

	void IParticleEmitter::SetStartTime( f32 v )
	{
		mImpl->mStartTime = v;
	}

	f32 IParticleEmitter::GetStartTime( void ) const
	{
		return mImpl->mStartTime;
	}

	void IParticleEmitter::SetDuration( f32 v )
	{
		mImpl->mDuration = v;
	}

	f32 IParticleEmitter::GetDuration( void ) const
	{
		return mImpl->mDuration;
	}

	void IParticleEmitter::SetTimeToLive( f32 v )
	{
		mImpl->mTimeToLive = v;
	}

	f32 IParticleEmitter::GetTimeToLive( void ) const
	{
		return mImpl->mTimeToLive;
	}

	void IParticleEmitter::SetRate( s32 num )
	{
		mImpl->mRate = num;
	}

	s32 IParticleEmitter::GetRate( void ) const
	{
		return mImpl->mRate;
	}

	void IParticleEmitter::SetColorStart( const Colorf& c )
	{
		mImpl->mStartColor = c;
	}

	const Colorf& IParticleEmitter::GetColorStart( void ) const
	{
		return mImpl->mStartColor;
	}

	void IParticleEmitter::SetColorEnd( const Colorf& c )
	{
		mImpl->mEndColor = c;
	}

	const Colorf& IParticleEmitter::GetColorEnd( void ) const
	{
		return mImpl->mEndColor;
	}

	void IParticleEmitter::SetParticleMaxSize( const Vector3Df& size )
	{
		mImpl->mMaxSize = size;
	}

	const Vector3Df& IParticleEmitter::GetParticleMaxSize( void ) const
	{
		return mImpl->mMaxSize;
	}

	void IParticleEmitter::SetParticleMinSize( const Vector3Df& size )
	{
		mImpl->mMinSize = size;
	}

	const Vector3Df& IParticleEmitter::GetParticleMinSize( void ) const
	{
		return mImpl->mMinSize;
	}
}