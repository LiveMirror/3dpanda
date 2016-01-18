//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
float4x4    mWorldMatrix:WORLDMATRIX0;
float4x4    mViewProj;  //View * Projection transformation
float3		mEyePos;

struct VS_INPUT
{
    float4  Pos             : POSITION;
    float3	Normal			: NORMAL;
    float3  TexUV			: TEXCOORD0;
};

//-----------------------------------------------------------------------------
// Vertex shader output structure
//-----------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Position   : POSITION;		// vertex position 
    float2 TexUV      : TEXCOORD0;		// vertex diffuse color
    float3 Normal	  : TEXCOORD1;
    float3 EyeTo      : TEXCOORD2;
};


//-----------------------------------------------------------------------------
// Name: Ripple
// Type: Vertex shader
// Desc: This shader ripples the vertices
//-----------------------------------------------------------------------------
VS_OUTPUT Main( VS_INPUT i )
{
	VS_OUTPUT Output;
	
	Output.Position = mul(i.Pos, mWorldMatrix);
	Output.Position = mul(Output.Position, mViewProj);
	Output.Normal = mul(i.Normal, mWorldMatrix);
	Output.TexUV = i.TexUV;
	Output.EyeTo = normalize(mEyePos - Output.Position.xyz);
	return Output;
}