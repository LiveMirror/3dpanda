////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2012-10-19 19:21:50
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_20121019192150_H_
#define	_Tian_20121019192150_H_

#include "Config.h"
#include "Vector3D.h"
#include "Color.h"

namespace panda
{
	struct RenderWindowParam
	{
		bool	bFullScereen;	// 是否全屏
		s32		nWidth;
		s32		nHeight;
		tstring strTitle;		// 窗口标题
		HWND	hWnd;			// 窗口句柄, 如果未指定，由引擎内部创建窗口
		bool	bBoder;			// 仅窗口模式，且hWnd为NULL时有效
		bool	bAutoUpdate;	// 是否自动更新
		WNDPROC fun;

		RenderWindowParam()
		{
			bFullScereen = false;
			hWnd = NULL;
			nWidth = 1024;
			nHeight = 600;
			strTitle = _T("panda by Tian");
			bBoder = true;
			bAutoUpdate = true;
			fun = NULL;
		}
	};

	struct FontFormat
	{
		enum eValue
		{
			TOP					= 0x00000000,
			LEFT				= 0x00000000,
			CENTER              = 0x00000001,
			RIGHT               = 0x00000002,
			VCENTER             = 0x00000004,
			BOTTOM              = 0x00000008,
			WORDBREAK           = 0x00000010,
			SINGLELINE          = 0x00000020,
			EXPANDTABS          = 0x00000040,
			TABSTOP             = 0x00000080,
			NOCLIP              = 0x00000100,
			EXTERNALLEADING     = 0x00000200,
			CALCRECT            = 0x00000400,
			NOPREFIX            = 0x00000800,
			INTERNAL            = 0x00001000,
			EDITCONTROL         = 0x00002000,
			PATH_ELLIPSIS       = 0x00004000,
			END_ELLIPSIS        = 0x00008000,
			MODIFYSTRING        = 0x00010000,
			RTLREADING          = 0x00020000,
			WORD_ELLIPSIS       = 0x00040000
		};
	};

	//-----------------------------------------
	//! 转换空间
	struct TransformSpace
	{
		enum eValue
		{
			TS_LOCAL,
			TS_PARENT,
			TS_WORLD
		};
	};

	//----------------------------------------
	// 资源类型
	struct ResType
	{
		enum eValue
		{
			ResType_Texure = 0,
			ResType_Material,
			ResType_Mesh,
			ResType_Skeletion,
			ResType_Terrain,
			ResType_Effect,
			ResType_Count
		};
	};

	struct MaterialType
	{
		enum eValue
		{
			Type_StaticMesh,
			Type_SknMesh,
			Type_Line,
			Type_Terrain,
			Type_Water,
			Type_Effect,
		};
	};

	//----------------------------------------
	// 资源状态
	struct ResState
	{
		enum eValue
		{
			UnLoad,
			Loading,
			Loaded,
			Error
		};
	};

	//-----------------------------------------
	//! 光源类型
	struct LightType
	{
		enum eValue
		{
			Point,
			Direction,
			Spot
		};
	};

	struct DeclareUsage
	{
		enum eValue
		{
			DECLUSAGE_POSITION      = 0,
			DECLUSAGE_BLENDWEIGHT   = 1,
			DECLUSAGE_BLENDINDICES  = 2,
			DECLUSAGE_NORMAL        = 3,
			DECLUSAGE_PSIZE         = 4,
			DECLUSAGE_TEXCOORD      = 5,
			DECLUSAGE_TANGENT       = 6,
			DECLUSAGE_BINORMAL      = 7,
			DECLUSAGE_TESSFACTOR    = 8,
			DECLUSAGE_POSITIONT     = 9,
			DECLUSAGE_COLOR         = 10,
			DECLUSAGE_FOG           = 11,
			DECLUSAGE_DEPTH         = 12,
			DECLUSAGE_SAMPLE        = 13
		};
	};

	struct DeclareType
	{
		enum eValue
		{
			DECLTYPE_FLOAT1    =  0,  // 1D float expanded to (value, 0., 0., 1.)
			DECLTYPE_FLOAT2    =  1,  // 2D float expanded to (value, value, 0., 1.)
			DECLTYPE_FLOAT3    =  2,  // 3D float expanded to (value, value, value, 1.)
			DECLTYPE_FLOAT4    =  3,  // 4D float
			DECLTYPE_D3DCOLOR  =  4,  // 4D packed unsigned bytes mapped to 0. to 1. range
			// Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)
			DECLTYPE_UBYTE4    =  5,  // 4D unsigned byte
			DECLTYPE_SHORT2    =  6,  // 2D signed short expanded to (value, value, 0., 1.)
			DECLTYPE_SHORT4    =  7,  // 4D signed short

			// The following types are valid only with vertex shaders >= 2.0


			DECLTYPE_UBYTE4N   =  8,  // Each of 4 bytes is normalized by dividing to 255.0
			DECLTYPE_SHORT2N   =  9,  // 2D signed short normalized (v[0]/32767.0,v[1]/32767.0,0,1)
			DECLTYPE_SHORT4N   = 10,  // 4D signed short normalized (v[0]/32767.0,v[1]/32767.0,v[2]/32767.0,v[3]/32767.0)
			DECLTYPE_USHORT2N  = 11,  // 2D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,0,1)
			DECLTYPE_USHORT4N  = 12,  // 4D unsigned short normalized (v[0]/65535.0,v[1]/65535.0,v[2]/65535.0,v[3]/65535.0)
			DECLTYPE_UDEC3     = 13,  // 3D unsigned 10 10 10 format expanded to (value, value, value, 1)
			DECLTYPE_DEC3N     = 14,  // 3D signed 10 10 10 format normalized and expanded to (v[0]/511.0, v[1]/511.0, v[2]/511.0, 1)
			DECLTYPE_FLOAT16_2 = 15,  // Two 16-bit floating point values, expanded to (value, value, 0, 1)
			DECLTYPE_FLOAT16_4 = 16,  // Four 16-bit floating point values
			DECLTYPE_UNUSED    = 17,  // When the type field in a decl is unused.
		};
	};

	/*
	*! 顶点格式
	*/
	struct VertexDeclare
	{
		VertexDeclare()
		{
			Stream = 0xFF;
			Offset = 0;
			Type = DeclareType::DECLTYPE_UNUSED;
			Method = 0;
			Usage = 0;
			UsageIndex = 0;
		}
		s32		Stream;     // Stream index
		s32		Offset;     // Offset in the stream in bytes
		s8		Type;       // Data type
		s8		Method;     // Processing method
		s8		Usage;      // Semantics
		s8		UsageIndex; // Semantic index

		static VertexDeclare DeclareEnd;
	};

	struct RenderOperation
	{
		enum eValue
		{
			/// A list of points, 1 vertex per point
			OT_POINT_LIST = 1,
			/// A list of lines, 2 vertices per line
			OT_LINE_LIST = 2,
			/// A strip of connected lines, 1 vertex per line plus 1 start vertex
			OT_LINE_STRIP = 3,
			/// A list of triangles, 3 vertices per triangle
			OT_TRIANGLE_LIST = 4,
			/// A strip of triangles, 3 vertices for the first triangle, and 1 per triangle after that 
			OT_TRIANGLE_STRIP = 5,
			/// A fan of triangles, 3 vertices for the first triangle, and 1 per triangle after that
			OT_TRIANGLE_FAN = 6
		};
	};

	class ISceneObject;
	struct ProbeResult
	{
		Vector3Df		pos;
		f32				distance;
		ISceneObject*	object;

		ProbeResult()
		{
			distance = 0;
			object = NULL;
		}
	};

	//! 地形顶点格式
	struct TerrainVertex
	{
		Vector3Df	pos;
		Color		textureTens;
		Vector3Df	normal;
		f32			u0,v0;
	};

	struct TimeIndex
	{
		f32 timePos;
		u32	keyIndex;
		TimeIndex(f32 time)
			:timePos(time),
			keyIndex(-1)
		{

		}

		TimeIndex(f32 time, u32 index)
			:timePos(time),
			keyIndex(index)
		{

		}

		bool HasKeyIndex()
		{
			return keyIndex != (u32)-1;
		}
	};


	//材质
	struct Mtrl
	{
		Mtrl()
			:ambient(SysColorf::white), diffuse(SysColorf::white), specular(SysColorf::white), specPower(8.0f){}
		Mtrl(const Colorf& a, const Colorf& d, 
			const Colorf& s, float power)
			:ambient(a), diffuse(d), specular(s), specPower(power){}

		Colorf ambient;
		Colorf diffuse;
		Colorf specular;

		f32 specPower;
	};

	struct ParticleRenderType
	{
		enum eValue
		{
			Billborad,
			Box,
			Ball,
			Mesh
		};
	};

	struct ParticleEmitterType
	{
		enum eValue
		{
			Point,
			Box,
			Ball,
			Cylinder
		};
	};

	struct ParticleAffectorType
	{
		enum eValue
		{
			Colour,
			LinerForce,
		};
	};
}

#endif _Tian_20121019192150_H_