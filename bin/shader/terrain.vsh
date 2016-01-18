//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
float4x4    mWorldMatrix:WORLDMATRIX0;
float4x4    mViewProj;  //View * Projection transformation
float3		mEyePos;

struct VS_INPUT
{
    float4  Pos             : POSITION;
    float4  TextureTens     : COLOR0;   // 各纹理的比重
    float3  Nor				: NORMAL;
    float3  TexUV0			: TEXCOORD0;
};

//-----------------------------------------------------------------------------
// Vertex shader output structure
//-----------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Position   : POSITION;		// vertex position 
    float4 TextureTens: COLOR0;			// 各纹理的比重
    float2 TexUV0     : TEXCOORD0;		// vertex diffuse color
    float3 Nor	      : TEXCOORD1;
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
	Output.EyeTo = normalize(mEyePos - Output.Position.xyz);
	Output.Position = mul(Output.Position, mViewProj);
	Output.Nor = mul(i.Nor, mWorldMatrix);
	Output.TextureTens = i.TextureTens / 100;
	Output.TexUV0 = i.TexUV0;
	return Output;
}