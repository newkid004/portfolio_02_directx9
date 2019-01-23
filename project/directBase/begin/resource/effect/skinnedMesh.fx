
// ���
float4x4 _mView;
float4x4 _mProjection;

// ����
float4 _lightDirection;

// ī�޶�
float4 _viewPosition;

// ��Ű��
int _numBlend;
float4x4 _mWorld[4];

// �ؽ���
texture _texture;

// �����
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

// ����
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

    // ���� ��ǥ�� �ִ� ������ w��Ҵ� 0 �Ǵ� 1�� �����Ǿ�� �ϱ� ������
    // ���� ����ġ�� ���� ���� ������ �Ϸ�� �� �ش� ���� 0 �Ǵ� 1�� ��������� ��
    // ���� ���̴��� ������� ��ġ �����̱� ������ 1�� �Ϲ���
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

// ���÷�
sampler2D _sampler = sampler_state
{
    Texture = _texture;

    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};

// �ȼ�
float4 psMain(output iput) : COLOR0
{
	float3 normal = normalize(iput.normal);
	float3 lightDirection = normalize(iput.lightDirection);
	float3 viewDirection = normalize(iput.viewDirection);

	// ���ݻ�
	float diffuse = saturate(dot(normal, -lightDirection));

	// ���ݻ�
	float3 specular = reflect(lightDirection, normal);
	specular = dot(specular, viewDirection);
	specular = saturate(specular);
	specular = pow(specular, 20.0f);

    float4 diffuseColor = tex2D(_sampler, iput.uv);

	float4 finalColor = diffuseColor * diffuse;
	finalColor.rgb += diffuseColor * specular;
	finalColor.rgb += diffuseColor * 0.2f;    // ȯ�汤

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