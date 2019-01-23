
// 행렬
float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;

// 색상
float4 _diffuseColor;

// ----- 입력 ----- //
struct input
{
    float3 pos : POSITION;
    float4 diffuse : COLOR;
};

// ----- 출력 ----- //
struct output
{
    float4 pos : POSITION;
    float4 diffuse : COLOR;
};

// ----- 정점 셰이더 ----- //
output vsMain(input iput)
{
    output oput = (output)0;
    float4 posWorld = mul(float4(iput.pos, 1.0f), _mWorld);
    oput.pos = mul(posWorld, _mView);
    oput.pos = mul(oput.pos, _mProjection);

    oput.diffuse = iput.diffuse;

    return oput;
}

// ----- 픽셀 셰이더 ----- //
float4 psMain(output iput) : COLOR0
{
    return iput.diffuse * _diffuseColor;
}

technique myTechnicque
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain();
    }
}