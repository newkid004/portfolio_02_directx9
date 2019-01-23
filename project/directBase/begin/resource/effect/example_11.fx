
// ----- ���� ----- //
// ���
float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;

// ����
float4 _lightDirection;

// ī�޶�
float4 _viewPosition;

// ----- �Է� ----- //
struct input
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
};

/*
�ȼ� ���̴����� �ν��� �� �ִ� �ø�ƽ�� ���� ���̴��� �޸�
COLOR / TEXCOORD�� �ν���
-> normal�� �ٸ� �ø�ƽ�� �ش��ϴ� �����͸� �ȼ� ���̴��� �ѱ�� ���ؼ�
�ؽ��� ��ǥ�� ������ �� �ֵ��� �ø�ƽ�� ǥ���ؾ� ��
*/
// ----- ��� ----- //
struct output
{
	float4 pos : POSITION;
	float3 normal : TEXCOORD0;
	float3 lightDirection : TEXCOORD1;
	float3 viewDirection : TEXCOORD2;
};

// ----- ���� ���̴� ----- //
output vsMain(input iput)
{
	output oput = (output)0;

	// ��ġ
	oput.pos = float4(iput.pos, 1.0f);
	float4 worldPos = mul(oput.pos, _mWorld);
	oput.pos = mul(worldPos, _mView);
	oput.pos = mul(oput.pos, _mProjection);

	// ����
	oput.normal = iput.normal;
	oput.normal = mul(oput.normal, (float3x3)_mWorld);
	oput.normal = normalize(oput.normal);

	// ����
	oput.lightDirection = normalize(_lightDirection.xyz);

	// ��ü -> ī�޶�
	oput.viewDirection = normalize(_viewPosition.xyz - worldPos.xyz);

	return oput;
}

// ----- �ȼ� ���̴� ----- //
float4 psMain(output iput) : COLOR0
{
	float3 normal = normalize(iput.normal);
	float3 lightDirection = normalize(iput.lightDirection);
	float3 viewDirection = normalize(iput.viewDirection);

	// ���ݻ�
	// dot		: �� ������ ����
	// saturate	: ���� ������ 0 ~ 1 ���� ����
	float diffuse = saturate(dot(normal, -lightDirection));

	// ���ݻ�
	float3 specular = reflect(lightDirection, normal);
	specular = dot(specular, viewDirection);
	specular = saturate(specular);
	specular = pow(specular, 20.0f);

	float4 finalColor = float4(1.0f, 0.0f, 0.0f, 1.0f) * diffuse;
	finalColor.rgb = finalColor.rgb + (float3(1.0f, 1.0f, 1.0f) * specular);
	finalColor.rgb = finalColor.rgb + float3(0.3f, 0.0f, 0.0f);

	return finalColor;
}

float4 psMainWireFrame(output iput) : COLOR0
{
	return float4(
		1.0f - 1.0f,
		1.0f - 0.0f,
		1.0f - 0.0f,
		1.0f);
}

/*
< ��ũ�� >
3���� ��ü�� �׸��� ���� ������ �ܰ躰�� �׷�ȭ ��Ű�� ���� ����
*/
technique myTechnique
{
	/*
	< �н� >
	3���� ��ü�� �׸��� ���� ��ġ�� �ܰ�( �ĺ���N ���� N�ܰ�� ���� )
	*/
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