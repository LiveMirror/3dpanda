float2	gUiSize;
float4	gRectColor = float4(1,1,1,1);      // Material's ambient color
float4	gRectColor2;
bool	gVertical;
float2	gPos;
float2	gSize;

struct VS_INPUT
{
    float4 Pos		: POSITION;   // vertex position 
};

struct VS_OUTPUT
{
	float4 Pos		: POSITION;
	float4 Color	: COLOR0;
};

VS_OUTPUT Main_VS( VS_INPUT In)
{ 
	VS_OUTPUT o;
    o.Color = gRectColor;
    o.Pos = In.Pos;
    o.Pos.x *= 2 * gSize.x / gUiSize.x;
    o.Pos.y *= 2 * gSize.y / gUiSize.y;
    o.Pos -= float4(1 - gPos.x / gUiSize.x * 2, -1 + gPos.y / gUiSize.y * 2, 0, 0);
    return o;
}

VS_OUTPUT Gradual_VS(VS_INPUT In)
{
	VS_OUTPUT o;
    
    if(gVertical)
    {
		if(In.Pos.y == 0)
		{
			o.Color = gRectColor;
		}
		else
		{
			o.Color = gRectColor2;
		}
	}
	else
	{
		if(In.Pos.x == 0)
		{
			o.Color = gRectColor2;
		}
		else
		{
			o.Color = gRectColor;
		}
	}
	o.Pos = In.Pos;
    o.Pos.x *= 2 * gSize.x / gUiSize.x;
    o.Pos.y *= 2 * gSize.y / gUiSize.y;
    o.Pos -= float4(1 - gPos.x / gUiSize.x * 2, -1 + gPos.y / gUiSize.y * 2, 0, 0);
    return o;
}

float4 Main_PS( VS_OUTPUT i):COLOR0
{ 
    return i.Color;
}


technique FillRect
{
    pass P0
    {
		FillMode = SOLID;
        VertexShader = compile vs_2_0 Main_VS();
        PixelShader	 = compile ps_2_0 Main_PS();
    }
}

technique GradualFillRect
{
    pass P0
    {
		FillMode = SOLID;
        VertexShader = compile vs_2_0 Gradual_VS();
        PixelShader	 = compile ps_2_0 Main_PS();
    }
}