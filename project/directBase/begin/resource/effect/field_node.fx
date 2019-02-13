
// 행렬
float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;
float4x4 _mViewProjection;

float4x4 _mWorldPlane;

// 카메라
float4 _viewPosition;

// 색상
float4 _diffuse;

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
};

// 출력
struct output
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
};

// vertex
output vsSphere(input iput)
{
    output oput = (output)0;

    float4 worldPos = mul(float4(iput.pos, 1.0f), _mWorld);

    oput.pos = mul(worldPos, _mViewProjection);
    oput.uv = iput.uv;

    return oput;
}

output vsPlane(input iput)
{
    output oput = (output)0;

    float4 worldPos = mul(float4(iput.pos, 1.0f), _mWorldPlane);

    oput.pos = mul(worldPos, _mViewProjection);
    oput.uv = iput.uv;

    return oput;
}

// pixel
float4 psSphere(output iput) : COLOR0
{
    return _diffuse;
}

float4 psPlane(output iput) : COLOR0
{
	return tex2D(_sampler, iput.uv);
}

// tech
technique techSphere
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsSphere();
        PixelShader = compile ps_3_0 psSphere();
    }
}

technique techPlane
{
    pass P0
    {
        cullMode = none;
        zWriteEnable = false;
        
        alphaBlendEnable = true;
        srcBlend = srcAlpha;
        destBlend = invSrcAlpha;

        VertexShader = compile vs_3_0 vsPlane();
        PixelShader = compile ps_3_0 psPlane();
    }
}