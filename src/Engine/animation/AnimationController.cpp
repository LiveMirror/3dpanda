#include "AnimationController.h"
#include "Animation.h"
#include "AnimationEntity.h"
#include "resources/IResSkeleton.h"
#include "../resource/ResSkeletonImpl.h"

namespace panda
{
	AnimationController::AnimationController( SceneMgrImpl* sceneMgr )
		:AniObject(sceneMgr),
		mAutoUpdate(true)
	{

	}

	void AnimationController::Update( f32 tick )
	{
		if(!mAutoUpdate)
		{
			return;
		}
		AnimationEntity* entity;
		EntityList::iterator it = mCurEntity.begin();
		while(it != mCurEntity.end())
		{
			entity = *it;
			if(!entity->AddTime(tick))
			{
				it = mCurEntity.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

	void AnimationController::Play( IAnimationEntity* pAni, f32 blendTime )
	{
		bool isIn = false;
		AnimationEntity* entity;
		EntityList::const_iterator it = mCurEntity.begin();
		while(it != mCurEntity.end())
		{
			entity = *it;
			if(entity == pAni)
			{
				isIn = true;
			}
			entity->mBlendTime = blendTime;
			entity->mFadeOut = true;	// µ­³ö
			entity->mFadeTime = 0;
			it++;
		}

		entity = (AnimationEntity*)pAni;
		entity->mBlendTime = blendTime;
		entity->mFadeOut = false;		// µ­Èë
		entity->mFadeTime = 0;
		if(!isIn)
		{
			// ±ÜÃâÖØ¸´
			mCurEntity.push_back(entity);
		}
		SetEnabled(true);
	}

	void AnimationController::Reset( void )
	{
		mCurEntity.clear();
		SetEnabled(false);
	}

	IAnimationEntity* AnimationController::GetEntity( const tstring& name ) const
	{
		EntityList::const_iterator it = mEntitys.begin();
		while(it != mEntitys.end())
		{
			if(name == (*it)->mName)
			{
				return *it;
			}
			it++;
		}
		return NULL;
	}

	IAnimationEntity* AnimationController::GetEntity( u32 index ) const
	{
		if(index <= mEntitys.size())
		{
			return mEntitys[index];
		}
		return NULL;
	}

	u32 AnimationController::GetEntityNum( void ) const
	{
		return mEntitys.size();
	}

	void AnimationController::ManualAdd( IAnimationEntity* entity )
	{
		mCurEntity.push_back((AnimationEntity*)entity);
	}

	void AnimationController::ManualRemove( IAnimationEntity* entity )
	{
		EntityList::const_iterator it = mCurEntity.begin();
		while(it != mCurEntity.end())
		{
			if(*it == (AnimationEntity*)entity)
			{
				mCurEntity.erase(it);
				return;
			}
			it++;
		}
	}

	void AnimationController::SetAutoUpdate( bool automatic )
	{
		mAutoUpdate = automatic;
	}

	bool AnimationController::GetAutoUpdate( void ) const
	{
		return mAutoUpdate;
	}

	void AnimationController::InitWithSkn( ResSkeletion skn )
	{
		Release();
		ResSkeletonImpl* impl = (ResSkeletonImpl*)skn->mImpl;
		ResSkeletonImpl::AnimationMap::iterator it = impl->mAnimations.begin();
		while(it != impl->mAnimations.end())
		{
			AnimationEntity* entity = new AnimationEntity;
			entity->mName = it->second->GetName();
			entity->mLen = it->second->GetLen();
			entity->mAni = (Animation*)it->second;
			mEntitys.push_back(entity);
			it++;
		}
	}

	void AnimationController::Apply( void )
	{
		AnimationEntity* entity;
		EntityList::iterator it = mCurEntity.begin();
		while(it != mCurEntity.end())
		{
			entity = *it;
			entity->Apply();
			it++;
		}
	}

	void AnimationController::Release( void )
	{
		mCurEntity.clear();
		EntityList::iterator it = mEntitys.begin();
		while(it != mEntitys.end())
		{
			delete *it;
			it++;
		}
		mEntitys.clear();
	}
}