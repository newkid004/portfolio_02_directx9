
// ���
float4x4 _mViewProjection;

// ����
float4 _diffuse;

// �Է�
struct input
{
    float3 pos : POSITION;
};

// ���
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
