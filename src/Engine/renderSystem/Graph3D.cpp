#include "Graph3D.h"
#include "../resource/VertexData.h"
#include "RenderSystem.h"
#include "../resource/IndexData.h"
#include "base/Vector2D.h"

namespace panda
{
	struct Vertex
	{
		Vector3Df pos;
		Vector2Df uv;
	};

	Graph3D::Graph3D( RenderSystem* renderSys )
		:mRenderSys(renderSys)
	{
		_Init();
	}

	void Graph3D::_Init( void )
	{
		mVbPanel = new VertexData(mRenderSys->mDevicePtr);
		mVbPanel->mVertexCount = 4;
		mVbPanel->AddElement(0, 0, DeclareType::DECLTYPE_FLOAT3, 0, DeclareUsage::DECLUSAGE_POSITION, 0);
		mVbPanel->AddElement(0, sizeof(Vector3Df), DeclareType::DECLTYPE_FLOAT2, 0, DeclareUsage::DECLUSAGE_TEXCOORD, 0);

		VertexData::HardwareBuffer* buf = mVbPanel->CreateHardwareBuffer(0, sizeof(Vertex));
		Vertex* vb = (Vertex*)buf->LockBuffer();

		vb[0].pos.x = -0.5f;	vb[0].pos.y = 0.5f;	vb[0].pos.z = 0;
		vb[0].uv.x = 0;			vb[0].uv.y = 0;

		vb[1].pos.x = 0.5f;		vb[1].pos.y = 0.5f;		vb[1].pos.z = 0;
		vb[1].uv.x = 1;			vb[1].uv.y = 0;

		vb[2].pos.x = 0.5f;		vb[2].pos.y = -0.5f;	vb[2].pos.z = 0;
		vb[2].uv.x = 1;			vb[2].uv.y = 1;

		vb[3].pos.x = -0.5f;	vb[3].pos.y = -0.5f;	vb[3].pos.z = 0;
		vb[3].uv.x = 0;			vb[3].uv.y = 1;

		buf->Unlock();

		mIbPanel = new IndexData(mRenderSys->mDevicePtr);
		mIbPanel->CreateHardwareBuffer(6, true);
		s32* ib = (s32*)mIbPanel->LockBuffer();
		ib[0] = 0;	ib[1] = 1;	ib[2] = 2;
		ib[3] = 0;	ib[4] = 2;	ib[5] = 3;
		mIbPanel->Unlock();
	}

	void Graph3D::DrawPanel( void )
	{
		mRenderSys->SetIndexBuffer(mIbPanel);
		mRenderSys->SetVertexBuffer(mVbPanel);
		mRenderSys->DrawIndexedPrimitive(RenderOperation::OT_TRIANGLE_LIST, 4, 2);
	}
}