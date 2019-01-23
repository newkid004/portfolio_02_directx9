
// 행렬
float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;

// 텍스쳐
texture _textureA;
texture _textureB;
texture _textureC;
texture _textureD;
texture _textureSplat;

// 입출력
struct input
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float3 binormal : BINORMAL;
    float3 tangent : TANGENT;
    float2 uv : TEXCOORD;
};

struct output
{
    float4 pos : POSITION;
    float3 normal : TEXCOORD0;
    float3 binormal : TEXCOORD1;
    float3 tangent : TEXCOORD2;
    float2 uv : TEXCOORD3;
};

// vectex
output vsMain(input iput)
{
    output oput = (output)0;

    float4 posWorld = mul(float4(iput.pos, 1.0f), _mWorld);
    oput.pos = mul(posWorld, _mView);
    oput.pos = mul(oput.pos, _mProjection);

    oput.normal     = normalize(mul(iput.normal, (float3x3)_mWorld));
    oput.binormal   = normalize(mul(iput.binormal, (float3x3)_mWorld));
    oput.tangent    = normalize(mul(iput.tangent, (float3x3)_mWorld));

    oput.uv = iput.uv;

    return oput;
}

// sampler
sampler2D _samplerA = sampler_state
{
    texture = _textureA;

    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};
sampler2D _samplerB = sampler_state
{
    texture = _textureB;

    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};
sampler2D _samplerC = sampler_state
{
    texture = _textureC;

    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};
sampler2D _samplerD = sampler_state
{
    texture = _textureD;

    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};
sampler2D _samplerSplat = sampler_state
{
    texture = _textureSplat;

    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};

// pixel
float4 psMain(output iput) : COLOR0
{
    float4 colorA = tex2D(_samplerA, iput.uv);  // Red
    float4 colorB = tex2D(_samplerB, iput.uv);  // Green
    float4 colorC = tex2D(_samplerC, iput.uv);  // Blue
    float4 colorD = tex2D(_samplerD, iput.uv);  // Black
    float4 colorSplat = tex2D(_samplerSplat, iput.uv);

    float blackPercent = 1.0f - saturate(colorSplat.r + colorSplat.g + colorSplat.b);

    float4 diffuseColor = 
        (colorA * colorSplat.r) +
        (colorB * colorSplat.g) +
        (colorC * colorSplat.b) +
        (colorD * blackPercent);

    float4 finalColor = diffuseColor;

    return finalColor;
}

technique myTechnique
{
    pass P0
    {
        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain();
    }
}