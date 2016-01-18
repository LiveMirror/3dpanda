//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/16 15:59:35_
// 描述:  
//

#ifndef _ENTITYVIEW_2014516155935_
#define _ENTITYVIEW_2014516155935_

#include "SceneView.h"

namespace editor
{
	class EntityView:public SceneView
	{
	public:
		EntityView(void);

		virtual void		InitUI(IUiManager* uiMgr, ISceneNode* pNode);
	};
}

#endif // _ENTITYVIEW_2014516155935_