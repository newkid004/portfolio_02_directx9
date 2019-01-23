
// ���
float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;

// ����
float4 _lightDirection;

// ī�޶�
float4 _viewPosition;

// �ؽ���
texture _texture;

// �Է�
struct input
{
    float3 pos : POSITION;
    float3 normal : NORMAL;
    float3 binormal : BINORMAL;
    float3 tangent : TANGENT;
    float2 uv : TEXCOORD;
};

// ���
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

// ���� ���̴�
output vsMain(input iput)
{
    output oput = (output)0;

    float4 worldPos = mul(float4(iput.pos, 1.0f), _mWorld);

    oput.pos = mul(worldPos, _mView);
    oput.pos = mul(oput.pos, _mProjection);

    oput.normal     = normalize(mul(iput.normal,    (float3x3)_mWorld));
    oput.binormal   = normalize(mul(iput.binormal,  (float3x3)_mWorld));
    oput.tangent    = normalize(mul(iput.tangent,   (float3x3)_mWorld));
    oput.uv = iput.uv;

    oput.lightDirection = normalize(_lightDirection);
    oput.viewDirection = normalize(_viewPosition);

    return oput;
}

// ���÷�
sampler2D _sampler = sampler_state
{
    texture = _texture;

    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};

// �ȼ� ���̴�
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
	finalColor.rgb = finalColor.rgb + (float3(1.0f, 1.0f, 1.0f) * specular);
	finalColor.rgb = finalColor.rgb + (diffuseColor * 0.2f);    // ȯ�汤

	return finalColor;
}

technique myTechnique
{
    pass P0
    {
        CULLMODE = NONE;

        VertexShader = compile vs_3_0 vsMain();
        PixelShader = compile ps_3_0 psMain();
    }
}