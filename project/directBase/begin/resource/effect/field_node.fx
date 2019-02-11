
// 행렬
float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;
float4x4 _mViewProjection;

// 카메라
float4 _viewPosition;

// 텍스쳐
texture _texture;

// 샘플러
sampler2D _sampler = sampler_state
{
    texture = _texture;

    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};

// 입력
struct input
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};

// 출력
struct output
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
    float4 color : TEXCOORD1;
};

// vertex
output vsMain(input iput)
{
    output oput = (output)0;

    float4 worldPos = mul(float4(iput.pos, 1.0f), _mWorld);

    oput.pos = mul(worldPos, _mViewProjection);
    
    oput.uv = iput.uv;
    oput.color = iput.color;

    return oput;
}

// pixel
float4 psSphere(output iput) : COLOR0
{
	return tex2D(_sampler, iput.uv);
}

float4 psPlane(output iput) : COLOR0
{
    return iput.color;
}

// tech
technique techSphere
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psSphere();
    }
}

technique techPlane
{
    pass P0
    {
        CULLMODE = NONE;

        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psSphere();
    }
}