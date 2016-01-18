float2	gUiSize;
texture gTexture;              // Color texture
float2	gPos;
float2	gSize;
float4	gColor;

sampler diffuseTextureSampler = 
sampler_state
{
    Texture = <gTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

struct VS_INPUT
{
    float4 Pos		: POSITION;   // vertex position
    float2 UV		: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 Pos		: POSITION;
	float2 UV		: TEXCOORD0;
};

VS_OUTPUT Main_VS( VS_INPUT In)
{ 
	VS_OUTPUT o;
    o.Pos = In.Pos;
    o.Pos.x *= 2 * gSize.x / gUiSize.x;
    o.Pos.y *= 2 * gSize.y / gUiSize.y;
    o.Pos -= float4(1 - gPos.x / gUiSize.x * 2, -1 + gPos.y / gUiSize.y * 2, 0, 0);
    o.UV = In.UV;
    return o;
}

float4 Main_PS( VS_OUTPUT i):COLOR0
{ 
	float4 c = tex2D(diffuseTextureSampler, i.UV);
    return c;
}

float4 Color_PS( VS_OUTPUT i):COLOR0
{ 
	float4 c = tex2D(diffuseTextureSampler, i.UV);
	c *= gColor;
    return c;
}

technique NormalImage
{
    pass P0
    {
		FillMode = SOLID;
        VertexShader = compile vs_2_0 Main_VS();
        PixelShader	 = compile ps_2_0 Main_PS();
    }
}

technique ColorImage
{
    pass P0
    {
		FillMode = SOLID;
        VertexShader = compile vs_2_0 Main_VS();
        PixelShader	 = compile ps_2_0 Color_PS();
    }
}