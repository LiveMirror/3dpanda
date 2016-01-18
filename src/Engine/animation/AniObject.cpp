#include "AniObject.h"
#include "../Scene/SceneMgrImpl.h"

namespace panda
{
	AniObject::AniObject( SceneMgrImpl* sceneMgr )
		:mSceneMgr(sceneMgr),
		mEnabled(false)
	{
		//
	}

	AniObject::~AniObject( void )
	{

	}

	void AniObject::SetEnabled( bool enabled )
	{
		if(mEnabled == enabled)
		{
			return;
		}
		mEnabled = enabled;
		if(mEnabled)
		{
			mSceneMgr->mAnimations.push_back(this);
		}
		else
		{
			SceneMgrImpl::AniObjectList::iterator it = mSceneMgr->mAnimations.begin();
			while (it != mSceneMgr->mAnimations.end())
			{
				if(*it == this)
				{
					mSceneMgr->mAnimations.erase(it);
					return;
				}
				it++;
			}
		}
	}

	bool AniObject::GetEnabled( void ) const
	{
		return mEnabled;
	}
}