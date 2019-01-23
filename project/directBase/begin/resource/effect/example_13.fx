
// ���
float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;

// ����
float4 _diffuseColor;

// ----- �Է� ----- //
struct input
{
    float3 pos : POSITION;
    float4 diffuse : COLOR;
};

// ----- ��� ----- //
struct output
{
    float4 pos : POSITION;
    float4 diffuse : COLOR;
};

// ----- ���� ���̴� ----- //
output vsMain(input iput)
{
    output oput = (output)0;
    float4 posWorld = mul(float4(iput.pos, 1.0f), _mWorld);
    oput.pos = mul(posWorld, _mView);
    oput.pos = mul(oput.pos, _mProjection);

    oput.diffuse = iput.diffuse;

    return oput;
}

// ----- �ȼ� ���̴� ----- //
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