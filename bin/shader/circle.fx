float2	gUiSize;
float4	gCircleColor;
float2	gCenter;
float	gRadius;

struct VS_INPUT
{
    float4 Pos		: POSITION;   // vertex position 
};

struct VS_OUTPUT
{
	float4 Pos		: POSITION;
	float2 p		: TEXCOORD0;
};

VS_OUTPUT Main_VS( VS_INPUT In)
{
	VS_OUTPUT o;
    o.Pos = In.Pos;
    o.Pos.x *= 2 * gRadius * 2 / gUiSize.x;
    o.Pos.y *= 2 * gRadius * 2 / gUiSize.y;
    o.Pos -= float4(1 - (gCenter.x - gRadius)/ gUiSize.x * 2, -1 + (gCenter.y - gRadius) / gUiSize.y * 2, 0, 0);
    o.p = o.Pos.xy;
    return o;
}

float4 Fill_PS(VS_OUTPUT i):COLOR0
{
	float4 c = float4(0, 0, 0, 0);
	float x = (i.p.x + 1.0) * gUiSize.x * 0.5 - gCenter.x;
	float y = -(i.p.y - 1.0) * gUiSize.y * 0.5 - gCenter.y;
	float r = sqrt(x * x + y * y);
	if(r < gRadius)
	{
		c = gCircleColor;
	}
	return c;
}

float4 Draw_PS(VS_OUTPUT i):COLOR0
{
	float4 c = float4(0, 0, 0, 0);
	c = gCircleColor;
	return c;
}

technique FillCircle
{
    pass P0
    {
		FillMode = SOLID;
        VertexShader = compile vs_2_0 Main_VS();
        PixelShader	 = compile ps_2_0 Fill_PS();
    }
}

technique DrawCircle
{
    pass P0
    {
		FillMode = SOLID;
        VertexShader = compile vs_2_0 Main_VS();
        PixelShader	 = compile ps_2_0 Draw_PS();
    }
}