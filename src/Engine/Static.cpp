#include "Base/Vector3D.h"
#include "Base/Struct.h"
#include "Base/Quaternion.h"

namespace panda
{
	Vector3Df Vector3Df::ZERO = Vector3Df(0,0,0);
	Vector3Df Vector3Df::UNIT_X = Vector3Df(1,0,0);
	Vector3Df Vector3Df::UNIT_Y = Vector3Df(0,1,0);
	Vector3Df Vector3Df::UNIT_Z = Vector3Df(0,0,1);	

	VertexDeclare VertexDeclare::DeclareEnd = VertexDeclare();

	Quaternion Quaternion::IDENTITY = Quaternion();
}