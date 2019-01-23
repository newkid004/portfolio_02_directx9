
// 행렬
float4x4 _mView;
float4x4 _mProjection;

// 광원
float4 _lightDirection;

// 카메라
float4 _viewPosition;

// 스키닝
int _numBlend;
float4x4 _mWorld[4];

// 텍스쳐
texture _texture;

// 입출력
struct input
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float3 binormal : BINORMAL;
    float3 tangent : TANGENT;
    float2 uv : TEXCOORD;
    float4 weight : BLENDWEIGHT;
};

struct output
{
    float4 pos : POSITION;
    float3 normal : TEXCOORD0;
    float3 binormal : TEXCOORD1;
    float3 tangent : TEXCOORD2;
    float2 uv : TEXCOORD3;
    
    float3 lightDirection : TEXCOORD4;
    float3 viewDirection : TEXCOORD5;
};

// 정점
output vsMain(input iput)
{
    output oput = (output)0;

    float leftWeight = 1.0f;
    for (int i = 1; i <= _numBlend; ++i)
    {
        float weight = iput.weight[i];
        float4x4 mWorld = _mWorld[i];

        leftWeight -= weight;

        oput.pos        += mul(float4(iput.pos, 1.0f), mWorld) * weight;
        oput.normal     += mul(iput.normal,     (float3x3)mWorld) * weight;
        oput.binormal   += mul(iput.binormal,   (float3x3)mWorld) * weight;
        oput.tangent    += mul(iput.tangent,    (float3x3)mWorld) * weight;
    }

    oput.pos        += mul(float4(iput.pos, 1.0f), _mWorld[0]) * leftWeight;
    oput.normal     += mul(iput.normal,     (float3x3)_mWorld[0]) * leftWeight;
    oput.binormal   += mul(iput.binormal,   (float3x3)_mWorld[0]) * leftWeight;
    oput.tangent    += mul(iput.tangent,    (float3x3)_mWorld[0]) * leftWeight;

    // 동차 좌표에 있는 마지막 w요소는 0 또는 1로 설정되어야 하기 때문에
    // 뼈대 가중치에 의한 정점 연산이 완료된 후 해당 값을 0 또는 1로 보정해줘야 함
    // 정점 쉐이더의 결과값은 위치 개념이기 때문에 1이 일반적
    oput.pos.w = 1.0f;

    float4 worldPos = oput.pos;
    oput.pos = mul(worldPos, _mView);
    oput.pos = mul(oput.pos, _mProjection);

    oput.normal = normalize(oput.normal);
    oput.binormal = normalize(oput.binormal);
    oput.tangent = normalize(oput.tangent);

    oput.uv = iput.uv;

    oput.lightDirection = normalize(_lightDirection);
    oput.viewDirection = normalize(_viewPosition);

    return oput;
}

// 샘플러
sampler2D _sampler = sampler_state
{
    Texture = _texture;

    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};

// 픽셀
float4 psMain(output iput) : COLOR0
{
	float3 normal = normalize(iput.normal);
	float3 lightDirection = normalize(iput.lightDirection);
	float3 viewDirection = normalize(iput.viewDirection);

	// 난반사
	float diffuse = saturate(dot(normal, -lightDirection));

	// 정반사
	float3 specular = reflect(lightDirection, normal);
	specular = dot(specular, viewDirection);
	specular = saturate(specular);
	specular = pow(specular, 20.0f);

    float4 diffuseColor = tex2D(_sampler, iput.uv);

	float4 finalColor = diffuseColor * diffuse;
	finalColor.rgb += diffuseColor * specular;
	finalColor.rgb += diffuseColor * 0.2f;    // 환경광

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