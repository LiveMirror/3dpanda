#include "renderSystem/IRenderTarget.h"
#include "RenderTargetImpl.h"

namespace panda
{
	IRenderTarget::IRenderTarget( RenderTargetImpl* pImpl )
		:ITexture(pImpl)
	{

	}
}