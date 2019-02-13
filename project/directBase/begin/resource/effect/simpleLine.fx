
// 행렬
float4x4 _mViewProjection;

// 색상
float4 _diffuse;

// 입력
struct input
{
    float3 pos : POSITION;
};

// 출력
struct output
{
    float4 pos : POSITION;
};

output vsMain(input iput)
{
    output oput = (output)0;

    oput.pos = mul(float4(iput.pos, 1.0f), _mViewProjection);

    return oput;
}

float4 psMain(output iput) : COLOR0
{
    return _diffuse;
}

technique techMain
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain();
    }
}
