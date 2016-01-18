#include "../ResMeshImpl.h"
#include "Resources/IResMesh.h"
#include "../VertexData.h"
#include "../SubMesh.h"
#include "../IndexData.h"
#include "../ResourceMgr.h"
#include "SerializeHelper.h"
#include <assert.h>
#include "OgreMeshSerialize.h"

namespace panda
{

	enum MeshChunkID {
		M_HEADER                = 0x1000,
		// char*          version           : Version number check
		M_MESH                = 0x3000,
		// bool skeletallyAnimated   // important flag which affects h/w buffer policies
		// Optional M_GEOMETRY chunk
			M_SUBMESH             = 0x4000, 
			// char* materialName
			// bool useSharedVertices
			// unsigned int indexCount
			// bool indexes32Bit
			// unsigned int* faceVertexIndices (indexCount)
			// OR
			// unsigned short* faceVertexIndices (indexCount)
			// M_GEOMETRY chunk (Optional: present only if useSharedVertices = false)
				M_SUBMESH_OPERATION = 0x4010, // optional, trilist assumed if missing
				// unsigned short operationType
				M_SUBMESH_BONE_ASSIGNMENT = 0x4100,
				// Optional bone weights (repeating section)
				// unsigned int vertexIndex;
				// unsigned short boneIndex;
				// float weight;
				// Optional chunk that matches a texture name to an alias
				// a texture alias is sent to the submesh material to use this texture name
				// instead of the one in the texture unit with a matching alias name
				M_SUBMESH_TEXTURE_ALIAS = 0x4200, // Repeating section
				// char* aliasName;
				// char* textureName;

			M_GEOMETRY          = 0x5000, // NB this chunk is embedded within M_MESH and M_SUBMESH
			// unsigned int vertexCount
				M_GEOMETRY_VERTEX_DECLARATION = 0x5100,
					M_GEOMETRY_VERTEX_ELEMENT = 0x5110, // Repeating section
					// unsigned short source;  	// buffer bind source
					// unsigned short type;    	// VertexElementType
					// unsigned short semantic; // VertexElementSemantic
					// unsigned short offset;	// start offset in buffer in bytes
					// unsigned short index;	// index of the semantic (for colours and texture coords)
				M_GEOMETRY_VERTEX_BUFFER = 0x5200, // Repeating section
				// unsigned short bindIndex;	// Index to bind this buffer to
				// unsigned short vertexSize;	// Per-vertex size, must agree with declaration at this index
					M_GEOMETRY_VERTEX_BUFFER_DATA = 0x5210,
					// raw buffer data
			M_MESH_SKELETON_LINK = 0x6000,
			// Optional link to skeleton
			// char* skeletonName           : name of .skeleton to use
			M_MESH_BONE_ASSIGNMENT = 0x7000,
			// Optional bone weights (repeating section)
			// unsigned int vertexIndex;
			// unsigned short boneIndex;
			// float weight;
			M_MESH_LOD = 0x8000,
			// Optional LOD information
			// string strategyName;
			// unsigned short numLevels;
			// bool manual;  (true for manual alternate meshes, false for generated)
				M_MESH_LOD_USAGE = 0x8100,
				// Repeating section, ordered in increasing depth
				// NB LOD 0 (full detail from 0 depth) is omitted
				// LOD value - this is a distance, a pixel count etc, based on strategy
				// float lodValue;
				M_MESH_LOD_MANUAL = 0x8110,
				// Required if M_MESH_LOD section manual = true
				// String manualMeshName;
				M_MESH_LOD_GENERATED = 0x8120,
				// Required if M_MESH_LOD section manual = false
				// Repeating section (1 per submesh)
				// unsigned int indexCount;
				// bool indexes32Bit
				// unsigned short* faceIndexes;  (indexCount)
				// OR
				// unsigned int* faceIndexes;  (indexCount)
			M_MESH_BOUNDS = 0x9000,
			// float minx, miny, minz
			// float maxx, maxy, maxz
			// float radius

			// Added By DrEvil
			// optional chunk that contains a table of submesh indexes and the names of
			// the sub-meshes.
			M_SUBMESH_NAME_TABLE = 0xA000,
			// Subchunks of the name table. Each chunk contains an index & string
				M_SUBMESH_NAME_TABLE_ELEMENT = 0xA100,
				// short index
				// char* name

				// Optional chunk which stores precomputed edge data
			M_EDGE_LISTS = 0xB000,
			// Each LOD has a separate edge list
				M_EDGE_LIST_LOD = 0xB100,
				// unsigned short lodIndex
				// bool isManual			// If manual, no edge data here, loaded from manual mesh
				// bool isClosed
				// unsigned long numTriangles
				// unsigned long numEdgeGroups
				// Triangle* triangleList
				// unsigned long indexSet
				// unsigned long vertexSet
				// unsigned long vertIndex[3]
				// unsigned long sharedVertIndex[3] 
				// float normal[4] 

				M_EDGE_GROUP = 0xB110,
				// unsigned long vertexSet
				// unsigned long triStart
				// unsigned long triCount
				// unsigned long numEdges
				// Edge* edgeList
				// unsigned long  triIndex[2]
				// unsigned long  vertIndex[2]
				// unsigned long  sharedVertIndex[2]
				// bool degenerate

				// Optional poses section, referred to by pose keyframes
			M_POSES = 0xC000,
				M_POSE = 0xC100,
				// char* name (may be blank)
				// unsigned short target	// 0 for shared geometry, 
				// 1+ for submesh index + 1
					M_POSE_VERTEX = 0xC111,
					// unsigned long vertexIndex
					// float xoffset, yoffset, zoffset
					// Optional vertex animation chunk
		M_ANIMATIONS = 0xD000, 
		M_ANIMATION = 0xD100,
		// char* name
		// float length
			M_ANIMATION_TRACK = 0xD110,
			// unsigned short type			// 1 == morph, 2 == pose
			// unsigned short target		// 0 for shared geometry, 
			// 1+ for submesh index + 1
				M_ANIMATION_MORPH_KEYFRAME = 0xD111,
				// float time
				// float x,y,z			// repeat by number of vertices in original geometry
				M_ANIMATION_POSE_KEYFRAME = 0xD112,
				// float time
					M_ANIMATION_POSE_REF = 0xD113, // repeat for number of referenced poses
					// unsigned short poseIndex 
					// float influence

		// Optional submesh extreme vertex list chink
		M_TABLE_EXTREMES = 0xE000,
		// unsigned short submesh_index;
		// float extremes [n_extremes][3];

		/* Version 1.2 of the .mesh format (deprecated)
		enum MeshChunkID {
		M_HEADER                = 0x1000,
		// char*          version           : Version number check
		M_MESH                = 0x3000,
		// bool skeletallyAnimated   // important flag which affects h/w buffer policies
		// Optional M_GEOMETRY chunk
		M_SUBMESH             = 0x4000, 
		// char* materialName
		// bool useSharedVertices
		// unsigned int indexCount
		// bool indexes32Bit
		// unsigned int* faceVertexIndices (indexCount)
		// OR
		// unsigned short* faceVertexIndices (indexCount)
		// M_GEOMETRY chunk (Optional: present only if useSharedVertices = false)
		M_SUBMESH_OPERATION = 0x4010, // optional, trilist assumed if missing
		// unsigned short operationType
		M_SUBMESH_BONE_ASSIGNMENT = 0x4100,
		// Optional bone weights (repeating section)
		// unsigned int vertexIndex;
		// unsigned short boneIndex;
		// float weight;
		M_GEOMETRY          = 0x5000, // NB this chunk is embedded within M_MESH and M_SUBMESH
		*/
		// unsigned int vertexCount
		// float* pVertices (x, y, z order x numVertices)
		M_GEOMETRY_NORMALS = 0x5100,    //(Optional)
		// float* pNormals (x, y, z order x numVertices)
		M_GEOMETRY_COLOURS = 0x5200,    //(Optional)
		// unsigned long* pColours (RGBA 8888 format x numVertices)
		M_GEOMETRY_TEXCOORDS = 0x5300    //(Optional, REPEATABLE, each one adds an extra set)
		// unsigned short dimensions    (1 for 1D, 2 for 2D, 3 for 3D)
		// float* pTexCoords  (u [v] [w] order, dimensions x numVertices)
		/*
		M_MESH_SKELETON_LINK = 0x6000,
		// Optional link to skeleton
		// char* skeletonName           : name of .skeleton to use
		M_MESH_BONE_ASSIGNMENT = 0x7000,
		// Optional bone weights (repeating section)
		// unsigned int vertexIndex;
		// unsigned short boneIndex;
		// float weight;
		M_MESH_LOD = 0x8000,
		// Optional LOD information
		// unsigned short numLevels;
		// bool manual;  (true for manual alternate meshes, false for generated)
		M_MESH_LOD_USAGE = 0x8100,
		// Repeating section, ordered in increasing depth
		// NB LOD 0 (full detail from 0 depth) is omitted
		// float fromSquaredDepth;
		M_MESH_LOD_MANUAL = 0x8110,
		// Required if M_MESH_LOD section manual = true
		// String manualMeshName;
		M_MESH_LOD_GENERATED = 0x8120,
		// Required if M_MESH_LOD section manual = false
		// Repeating section (1 per submesh)
		// unsigned int indexCount;
		// bool indexes32Bit
		// unsigned short* faceIndexes;  (indexCount)
		// OR
		// unsigned int* faceIndexes;  (indexCount)
		M_MESH_BOUNDS = 0x9000
		// float minx, miny, minz
		// float maxx, maxy, maxz
		// float radius

		// Added By DrEvil
		// optional chunk that contains a table of submesh indexes and the names of
		// the sub-meshes.
		M_SUBMESH_NAME_TABLE,
		// Subchunks of the name table. Each chunk contains an index & string
		M_SUBMESH_NAME_TABLE_ELEMENT,
		// short index
		// char* name

		*/
	};

	/// Vertex element semantics, used to identify the meaning of vertex buffer contents
	enum VertexElementSemantic {
		/// Position, 3 reals per vertex
		VES_POSITION = 1,
		/// Blending weights
		VES_BLEND_WEIGHTS = 2,
		/// Blending indices
		VES_BLEND_INDICES = 3,
		/// Normal, 3 reals per vertex
		VES_NORMAL = 4,
		/// Diffuse colours
		VES_DIFFUSE = 5,
		/// Specular colours
		VES_SPECULAR = 6,
		/// Texture coordinates
		VES_TEXTURE_COORDINATES = 7,
		/// Binormal (Y axis if normal is Z)
		VES_BINORMAL = 8,
		/// Tangent (X axis if normal is Z)
		VES_TANGENT = 9

	};

	/// Vertex element type, used to identify the base types of the vertex contents
	enum VertexElementType
	{
		VET_FLOAT1 = 0,
		VET_FLOAT2 = 1,
		VET_FLOAT3 = 2,
		VET_FLOAT4 = 3,
		/// alias to more specific colour type - use the current rendersystem's colour packing
		VET_COLOUR = 4,
		VET_SHORT1 = 5,
		VET_SHORT2 = 6,
		VET_SHORT3 = 7,
		VET_SHORT4 = 8,
		VET_UBYTE4 = 9,
		/// D3D style compact colour
		VET_COLOUR_ARGB = 10,
		/// GL style compact colour
		VET_COLOUR_ABGR = 11
	};

	const unsigned short HEADER_CHUNK_ID = 0x1000;
	bool OgreMeshSerialize::ImportMesh( FileStream& file, IResMesh* pMesh )
	{
		u16 headerID;
		file.Read(headerID);
		if(headerID != HEADER_CHUNK_ID)
		{
			// the file is not mesh format
			return false;
		}
		tstring ver;
		SerializeHelper::ReadString(file, ver);

		u16 streamID;
		while (!file.Eof())
		{
			streamID = readChunk(file);
			switch(streamID)
			{
			case M_MESH:
				{
					readMesh(file, pMesh);
					_CompileMesh(pMesh);
					break;
				}
			}
		}

		return true;
	}

	u16 OgreMeshSerialize::readChunk( FileStream& file )
	{
		u16 id;
		file.Read(id);
		file.Read(mStreamLen);
		return id;
	}

	void OgreMeshSerialize::readMesh( FileStream& file, IResMesh* pMesh)
	{
		bool skeletallyAnimated;
		file.Read(skeletallyAnimated);

		// find all substream
		u16 streamID;
		ResMeshImpl* pImpl = (ResMeshImpl*)pMesh->mImpl;
		while (!file.Eof())
		{
			streamID = readChunk(file);
			switch(streamID)
			{
			case M_GEOMETRY:
				{
					pImpl->mVertexData = new VertexData(pImpl->mResMgr->GetDevice());
					readGeometry(file, pImpl, pImpl->mVertexData);
					break;
				}
			case M_SUBMESH:
				{
					readSubMesh(file, pImpl);
					break;
				}
			case M_MESH_SKELETON_LINK:
				{
					readSkeletonLink(file, pImpl);
					break;
				}
			case M_MESH_BONE_ASSIGNMENT:
				{
					readMeshBoneAssignment(file, pImpl);
					break;
				}
			case M_MESH_LOD:
				break;
			case M_MESH_BOUNDS:
				{
					readBoundsInfo(file);
					break;
				}
			case M_SUBMESH_NAME_TABLE:
				{
					readSubMeshNameTable(file);
					break;
				}
			case M_EDGE_LISTS:
				{
					// skip this
					file.Seek(mStreamLen - 6);
					break;
				}
			case M_POSES:
				break;
			case M_ANIMATIONS:
				break;
			case M_TABLE_EXTREMES:
				break;
			default:
				{
					_turnBack(file);
					return;
				}
			}
			int i = 0;
		}

	}

	void OgreMeshSerialize::readSubMesh( FileStream& file, ResMeshImpl* pImpl)
	{
		SubMesh* pSM = pImpl->CreateSubMesh();
		SerializeHelper::ReadString(file, pSM->mMatrailName);

		file.Read(pSM->mUserSharedVertices);
		pSM->mIndexData = new IndexData(pImpl->mResMgr->GetDevice());
		u32 count;
		file.Read(count);
		bool is32Bit;
		file.Read(is32Bit);

		// 顶点索引
		if(count > 0)
		{
			pSM->mIndexData->CreateHardwareBuffer(count, is32Bit);
			void* buffer = pSM->mIndexData->LockBuffer();
			if(pSM->mIndexData->mIs32Bit)
			{
				file.Read(buffer, pSM->mIndexData->mCount * sizeof(s32));
			}
			else
			{
				file.Read(buffer, pSM->mIndexData->mCount * sizeof(s16));
			}
			pSM->mIndexData->Unlock();
		}

		if(!pSM->mUserSharedVertices)
		{
			u16 streamID = readChunk(file);
			if (streamID != M_GEOMETRY)
			{
				throw _T("Missing geometry data in mesh file");
			}
			pSM->mVertexData = new VertexData(pImpl->mResMgr->GetDevice());
			readGeometry(file, pImpl, pSM->mVertexData);
		}

		u16 streamID;

		// Find all bone assignments, submesh operation, and texture aliases (if present)
		while (!file.Eof())
		{
			streamID = readChunk(file);
			switch(streamID)
			{
			case M_SUBMESH_OPERATION:
				{
					u16 opType;
					file.Read(opType);
					pSM->mRenderOp = (RenderOperation::eValue)opType;
					break;
				}
			case M_SUBMESH_BONE_ASSIGNMENT:
				{
					if (pSM->mUserSharedVertices)
					{
						throw _T("This SubMesh uses shared geometry,  you must assign bones to the Mesh, not the SubMesh");
					}
					if(NULL == pSM->mUserData)
					{
						// 为子模型添加AssignmentList
						pSM->mUserData = new AssignmentList;
					}
					AssignmentList* assigns = (AssignmentList*)pSM->mUserData;
					VertexBoneAssignment assign;
					file.Read(assign.vertexIndex);
					file.Read(assign.boneIndex);
					file.Read(assign.weight);
					assigns->insert(AssignmentList::value_type(assign.vertexIndex, assign));
					break;
				}
			case M_SUBMESH_TEXTURE_ALIAS:
				{
					tstring aliasName;
					tstring textureName;
					SerializeHelper::ReadString(file, aliasName);
					SerializeHelper::ReadString(file, textureName);
					break;
				}
			default:
				{
					_turnBack(file);
					return;
				}
			}
		}
	}

	void OgreMeshSerialize::readGeometry( FileStream& file, ResMeshImpl* pMesh, VertexData* dest)
	{
		file.Read(dest->mVertexCount);

		u16 streamID;
		while (!file.Eof())
		{
			streamID = readChunk(file);
			switch(streamID)
			{
			case M_GEOMETRY_VERTEX_DECLARATION:
				{
					readGeometryVertexDeclaration(file, dest);
					break;
				}
			case M_GEOMETRY_VERTEX_BUFFER:
				{
					readGeometryVertexBuffer(file, pMesh, dest);
					break;
				}
			default:
				{
					_turnBack(file);
					return;
				}
			}
		}
	}

	void OgreMeshSerialize::readGeometryVertexDeclaration( FileStream& file, VertexData* dest)
	{
		u16 streamID;
		while (!file.Eof())
		{
			streamID = readChunk(file);
			switch(streamID)
			{
			case M_GEOMETRY_VERTEX_ELEMENT:
				{
					u16 source;		// buffer bind source
					u16 offset;		// start offset in buffer in bytes
					u16 index;		// index of the usage
					u16 vType;		// DeclareType
					u16 vUsage;		// DeclareUsage
					file.Read(source);
					file.Read(vType);
					file.Read(vUsage);
					vUsage = _ConvertUsage(vUsage);
					file.Read(offset);
					file.Read(index);
					dest->AddElement(source, offset, (s8)vType, 0, (s8)vUsage, (s8)index);
					break;
				}
			default:
				{
					_turnBack(file);
					return;
				}
			}
		}
	}

	void OgreMeshSerialize::readGeometryVertexBuffer( FileStream& file, ResMeshImpl* pMesh, VertexData* dest)
	{
		u16 bindIndex;
		file.Read(bindIndex);				//  Index to bind this buffer to
		u16 vertexSize;
		file.Read(vertexSize);				//  Per-vertex size, must agree with declaration at this index

		u16 headerID = readChunk(file);
		if (headerID != M_GEOMETRY_VERTEX_BUFFER_DATA)
		{
			throw _T("Can't find vertex buffer data area");
		}
		VertexData::HardwareBuffer* data = dest->CreateHardwareBuffer(bindIndex, vertexSize);
		u32 size = dest->mVertexCount * vertexSize;
		void* buffer = data->LockBuffer();
		file.Read(buffer, size);
		data->Unlock();
	}

	void OgreMeshSerialize::_turnBack( FileStream& file )
	{
		file.Seek(-6);
	}

	void OgreMeshSerialize::readBoundsInfo( FileStream& file )
	{
		Vector3Df min, max;
		// float minx, miny, minz
		file.Read(min.x);
		file.Read(min.y);
		file.Read(min.z);
		// float maxx, maxy, maxz
		file.Read(max.x);
		file.Read(max.y);
		file.Read(max.z);
		// float radius
		f32 radius;
		file.Read(radius);
	}

	void OgreMeshSerialize::readSubMeshNameTable( FileStream& file )
	{
		// I don't need this info, so I don't record these infos;
		// just read it out
		u16 streamID, subMeshIndex;
		s32 offset = file.Tell();
		s32 size = file.GetFileSize();
		while (!file.Eof())
		{
			streamID = readChunk(file);
			if(streamID == M_SUBMESH_NAME_TABLE_ELEMENT)
			{
				file.Read(subMeshIndex);
				tstring name;
				SerializeHelper::ReadString(file, name);
			}
			else
			{
				_turnBack(file);
				break;
			}
		}
	}

	void OgreMeshSerialize::_CompileMesh( IResMesh* pMesh )
	{	
		ResMeshImpl* pImpl = (ResMeshImpl*)pMesh->mImpl;

		// 如果数组不为空
		// 为模型重新构建顶点数据
		if (NULL != pImpl->mUserData)
		{
			_RebulidVertexData(pImpl->mVertexData, (AssignmentList*)pImpl->mUserData);
		}
		ResMeshImpl::SubMeshList::iterator itr = pImpl->mSubMeshs.begin();
		while (itr != pImpl->mSubMeshs.end())
		{
			SubMesh* subMesh = *itr;
			if (NULL != subMesh->mUserData)
			{
				_RebulidVertexData(subMesh->mVertexData, (AssignmentList*)subMesh->mUserData);
			}
			itr++;
		}
	}

	s16 OgreMeshSerialize::_ConvertUsage( s16 ogreUsage )
	{
		s16 usage;
		if(ogreUsage <= VES_NORMAL)
		{
			usage = ogreUsage - 1;
			return usage;
		}
		switch(ogreUsage)
		{
		case VES_DIFFUSE:
		case VES_SPECULAR:
			{
				usage = DeclareUsage::DECLUSAGE_COLOR;
				return usage;
			}
		case VES_TEXTURE_COORDINATES:
			{
				usage = DeclareUsage::DECLUSAGE_TEXCOORD;
				return usage;
			}
		default:
			{
				break;
			}
		}
		return 0;
	}

	void OgreMeshSerialize::readSkeletonLink( FileStream& file, ResMeshImpl* pMesh )
	{
		tstring name;
		SerializeHelper::ReadString(file, name);
		int i = 0;
	}

	void OgreMeshSerialize::_RebulidVertexData( VertexData* pData, AssignmentList* assigns)
	{
		u16 maxBone = 1;
		// 计算使用最大骨骼数
		s32 num = 1;
		u32 curVertexIndex = -1;
		AssignmentList::iterator i, endIter;
		i = assigns->begin();
		endIter = assigns->end();
		while (i != endIter)
		{
			if (curVertexIndex == i->first)
			{
				num++;
			}
			else
			{
				curVertexIndex = i->first;
				if (maxBone < num)
				{
					maxBone = num;
				}
				num = 1;
			}
			i++;
		}
		s32 vertexSize = 4 + maxBone * sizeof(f32);

		s32 sourceID = 0;
		// find a new sourceID for the bone assginment
		VertexData::DeclareList::iterator itr = pData->mDeclElments.begin();
		while(itr != pData->mDeclElments.end())
		{
			const VertexDeclare& declare = *itr;
			if (declare.Stream >= sourceID)
			{
				sourceID++;
			}
			itr++;
		}
		pData->AddElement(sourceID, 0, DeclareType::DECLTYPE_UBYTE4, 0, DeclareUsage::DECLUSAGE_BLENDINDICES, 0);
		pData->AddElement(sourceID, 4, DeclareType::DECLTYPE_FLOAT1 + maxBone - 1, 0, DeclareUsage::DECLUSAGE_BLENDWEIGHT, 0);

		VertexData::HardwareBuffer* pBuffer = pData->CreateHardwareBuffer(sourceID, vertexSize);

		s32 fSize = vertexSize / 4;
		u8* dest = (u8*)pBuffer->LockBuffer();
		f32* fdest = (f32*)dest;
		i = assigns->begin();
		for (u32 n = 0; n < pData->mVertexCount; n++)
		{
			num = 0;
			while(i != endIter && i->first == n)
			{
				dest[n * vertexSize + num] = (u8)i->second.boneIndex;
				fdest[n * fSize + num + 1] = i->second.weight;
				i++;
				num++;
			}
		}
		pBuffer->Unlock();

		delete assigns;
	}

	void OgreMeshSerialize::readMeshBoneAssignment( FileStream& file, ResMeshImpl* pMesh )
	{
		if(NULL == pMesh->mUserData)
		{
			// 为子模型添加AssignmentList
			pMesh->mUserData = new AssignmentList;
		}
		AssignmentList* assigns = (AssignmentList*)pMesh->mUserData;
		VertexBoneAssignment assign;
		file.Read(assign.vertexIndex);
		file.Read(assign.boneIndex);
		file.Read(assign.weight);
		assigns->insert(AssignmentList::value_type(assign.vertexIndex, assign));
	}
}