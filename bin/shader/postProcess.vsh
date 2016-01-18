//-----------------------------------
// PostProcess vertex shader
//-----------------------------------

float mSacle = 1.0f;
float mUvScale = 1.0f;
struct VS_INPUT
{
    float4  Pos       : POSITION;
    float2  TexUV	  : TEXCOORD0;		// vertex diffuse color
};

struct VS_OUTPUT
{
    float4 Position   : POSITION;		// vertex position
    float2 TexUV      : TEXCOORD0;		// vertex diffuse color
    float2 TexUV2     : TEXCOORD1;		// vertex diffuse color
};

VS_OUTPUT Main( VS_INPUT i )
{
	VS_OUTPUT o;
	float4 pos = i.Pos * mSacle;
	o.Position = float4(float3(pos.x - 1, pos.y + 1, 0), 1);
	o.TexUV = i.TexUV;
	o.TexUV2 = i.TexUV * mUvScale;
	return o;
}