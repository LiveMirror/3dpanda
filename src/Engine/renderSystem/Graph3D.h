//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/6/3 15:08:00_
// 描述:  
//

#ifndef _GRAPH3D_201463150800_
#define _GRAPH3D_201463150800_

namespace panda
{
	class VertexData;
	class IndexData;
	class RenderSystem;
	class Graph3D
	{
	public:
		Graph3D(RenderSystem* renderSys);

		void		DrawPanel(void);
		void		DrawBox(void);
	protected:
		void		_Init(void);
	public:
		RenderSystem*			mRenderSys;		// 设备指针

		VertexData*				mVbPanel;		// 面板数据
		IndexData*				mIbPanel;
	};
}

#endif // _GRAPH3D_201463150800_