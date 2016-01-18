//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
static const int MAX_MATRICES = 55;
float4x4    mWorldMatrixArray[MAX_MATRICES]: WORLDMATRIXARRAY;
float4x4    mWorldMatrix:WORLDMATRIX0;
float4x4    mViewProj;			//View * Projection transformation
int 	    CurNumBones = 3;

struct VS_INPUT
{
    float4  Pos             : POSITION;
    float3	Normal			: NORMAL;
    float4  BlendWeights    : BLENDWEIGHT;
    float4  BlendIndices    : BLENDINDICES;
    float2  Tex0            : TEXCOORD0;
};

//-----------------------------------------------------------------------------
// Vertex shader output structure
//-----------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Position   : POSITION;   // vertex position 
    float2 TexUV      : TEXCOORD0;		// vertex diffuse color
    float3 Normal	  : TEXCOORD1;
};


//-----------------------------------------------------------------------------
// Name: Ripple
// Type: Vertex shader
// Desc: This shader ripples the vertices
//-----------------------------------------------------------------------------
VS_OUTPUT Main( VS_INPUT i )
{
	VS_OUTPUT Output;

	//float4      Pos = i.Pos;
	float4      Pos = float4(0,0,0,0);

	// cast the vectors to arrays for use in the for loop below
	float BlendWeightsArray[4] = (float[4])i.BlendWeights;
	float IndexArray[4]        = (float[4])i.BlendIndices;

	if(IndexArray[0] == 255)
	{
		Pos = i.Pos;
	}
	else
	{
		for (int iBone = 0; iBone < 3; iBone++)
		{
			Pos += mul(i.Pos, mWorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
		}
	}
	Pos = mul(Pos, mWorldMatrix);
	Pos = mul(Pos, mViewProj);
	
	Output.Normal = mul(i.Normal, mWorldMatrix);
	Output.Normal = mul(Output.Normal, mViewProj);

    Output.Position = Pos;
	Output.TexUV = i.Tex0;

	return Output;
}