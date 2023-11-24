matrix World;
matrix View;
matrix Projection;

float3 LightDirection;

Texture2D DiffuseMap;

struct VertexInput
{
    float4 Position : Position;
    float2 Uv : Uv;
    float3 Normal : Normal;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float3 Normal : Normal;
    float2 Uv : Uv;
};

RasterizerState FillMode_WireFrame
{
    FillMode = WIREFRAME;
};

SamplerState LinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
	
    output.Normal = mul(input.Normal, (float3x3) World);
	
    output.Uv = input.Uv;
	
    return output;
}

float4 PS(VertexOutput input) : SV_Target
{
    float3 normal = normalize(input.Normal);
    
    float4 baseColor = DiffuseMap.Sample(LinearSampler, input.Uv);
    float lambert = saturate(dot(normal, -LightDirection));

    //return baseColor;
    return baseColor * lambert;
}

float4 PS_WireFrame(VertexOutput input) : SV_Target
{
    return float4(0, 1, 0, 1);
}

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P1
    {
        SetRasterizerState(FillMode_WireFrame);

        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_WireFrame()));
    }
}