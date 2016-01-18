#include "FlatBrush.h"
#include "../Editor.h"

namespace editor
{
	FlatBrush::FlatBrush( void )
	{
		mName = _T("推平笔刷");
	}

	void FlatBrush::OnPaint( f32 x, f32 y )
	{
		ResTerrain ter = Editor::Singleton()->mLevel->GetTerrain();

		s32 terWidth = ter->GetWidth();
		f32 tileSize = ter->GetTileSize();
		f32 startX, startY;
		f32 endX, endY;
		f32 halfWidth = terWidth * tileSize / 2;
		f32 halfHeight = ter->GetHeight() * tileSize / 2;
		startX = x - mRadius + halfWidth;
		startY = y - mRadius + halfHeight;
		endX = x + mRadius + halfWidth;
		endY = y + mRadius + halfHeight;

		// 计算锁定区域
		s32 startCol = (s32)(startX / tileSize);
		s32 startRow = (s32)(startY / tileSize);
		s32 endCol = (s32)(endX / tileSize) + 1;
		s32 endRow = (s32)(endY / tileSize) + 1;

		if(startRow < 0)
		{
			startRow = 0;
		}
		if (endRow > ter->GetHeight())
		{
			endRow = ter->GetHeight();
		}
		if(startCol < 0)
		{
			startCol = 0;
		}
		if(endCol > terWidth)
		{
			endCol = terWidth;
		}
		u32 offset = startRow * terWidth * sizeof(TerrainVertex);
		u32 len = (endRow - startRow) * terWidth * sizeof(TerrainVertex);
		TerrainVertex* vb = ter->LockVertexBuffer(offset, len);

		s32 index = 0;
		f32 effect;
		for (s32 row = startRow; row < endRow; row++)
		{
			for (s32 col = startCol; col < endCol; col++)
			{
				index = (row - startRow) * terWidth + col;
				effect = GetEffect(x, y, vb[index].pos.x, vb[index].pos.z);
				if (effect > 0 && effect < 1)
				{
					vb[index].pos.y = vb[index].pos.y * (1 - effect) + mValue * effect;
				}
				else if(effect == 1)
				{
					vb[index].pos.y = mValue;
				}
				else
				{
					continue;
				}
				// update normal
				if(row > startRow && row < endRow - 1
					&& col > startCol && col < endCol - 1)
				{
					Vector3Df& sNormal = vb[index].normal;
					sNormal.x = vb[(row - startRow-1)* terWidth + col].pos.y - vb[(row - startRow+1)* terWidth + col].pos.y;
					sNormal.y = 10;
					sNormal.z = vb[(row - startRow)* terWidth + col-1].pos.y - vb[(row - startRow)* terWidth + col+1].pos.y;

					sNormal.Normalize();	//归一化
				}
			}
		}
		ter->UnLockBuffer();
	}
}