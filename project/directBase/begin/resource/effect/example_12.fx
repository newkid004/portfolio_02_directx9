
// ----- ���� ----- //
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

// ----- �Է� ----- //
struct input
{
	float3 pos      : POSITION;
	float3 normal   : NORMAL;
    float2 uv	    : TEXCOORD;
};

// ----- ��� ----- //
struct output
{
	float4 pos              : POSITION;
	float3 normal           : TEXCOORD0;
	float3 lightDirection   : TEXCOORD1;
	float3 viewDirection    : TEXCOORD2;
    float2 uv	            : TEXCOORD3;
};

// ----- ���� ���̴� ----- //
output vsMain(input iput)
{
	output oput = (output)0;

	// ��ġ
	float4 worldPos = mul(float4(iput.pos, 1.0f), _mWorld);
	oput.pos = mul(worldPos, _mView);
	oput.pos = mul(oput.pos, _mProjection);

	// ����
	oput.normal = mul(iput.normal, (float3x3)_mWorld);
	oput.normal = normalize(oput.normal);

	// ����
	oput.lightDirection = normalize(_lightDirection.xyz);
    
	// ��ü -> ī�޶�
	oput.viewDirection = normalize(_viewPosition.xyz - worldPos.xyz);

    // �ؽ���
    oput.uv = iput.uv;

	return oput;
}

// ----- ���÷� ----- //
sampler2D _sampler = sampler_state
{
    Texture = _texture;

    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;
};

// ----- �ȼ� ���̴� ----- //
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
	finalColor.rgb = finalColor.rgb + (diffuseColor * 0.2f);

	return finalColor;
}

float4 psMainWireFrame(output iput) : COLOR0
{
	return float4(0, 0, 0, 0);
}

// ----- ��ũ�� ----- //
technique myTechnique
{
	pass P0
	{
		cullMode = none;

		VertexShader = compile vs_3_0 vsMain();
		PixelShader = compile ps_3_0 psMain();
	}

	pass P1
	{
		// ������ ���� ����
		cullMode = none;
		fillMode = wireFrame;

		VertexShader = compile vs_3_0 vsMain();
		PixelShader = compile ps_3_0 psMainWireFrame();
	}
}