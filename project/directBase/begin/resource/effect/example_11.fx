
// ----- 전역 ----- //
// 행렬
float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;

// 광원
float4 _lightDirection;

// 카메라
float4 _viewPosition;

// ----- 입력 ----- //
struct input
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
};

/*
픽셀 셰이더에선 인식할 수 있는 시멘틱은 정점 셰이더와 달리
COLOR / TEXCOORD만 인식함
-> normal등 다른 시멘틱에 해당하는 데이터를 픽셀 셰이더로 넘기기 위해선
텍스쳐 좌표로 인지할 수 있도록 시멘틱을 표기해야 함
*/
// ----- 출력 ----- //
struct output
{
	float4 pos : POSITION;
	float3 normal : TEXCOORD0;
	float3 lightDirection : TEXCOORD1;
	float3 viewDirection : TEXCOORD2;
};

// ----- 정점 셰이더 ----- //
output vsMain(input iput)
{
	output oput = (output)0;

	// 위치
	oput.pos = float4(iput.pos, 1.0f);
	float4 worldPos = mul(oput.pos, _mWorld);
	oput.pos = mul(worldPos, _mView);
	oput.pos = mul(oput.pos, _mProjection);

	// 법선
	oput.normal = iput.normal;
	oput.normal = mul(oput.normal, (float3x3)_mWorld);
	oput.normal = normalize(oput.normal);

	// 광원
	oput.lightDirection = normalize(_lightDirection.xyz);

	// 물체 -> 카메라
	oput.viewDirection = normalize(_viewPosition.xyz - worldPos.xyz);

	return oput;
}

// ----- 픽셀 셰이더 ----- //
float4 psMain(output iput) : COLOR0
{
	float3 normal = normalize(iput.normal);
	float3 lightDirection = normalize(iput.lightDirection);
	float3 viewDirection = normalize(iput.viewDirection);

	// 난반사
	// dot		: 두 벡터의 내적
	// saturate	: 값의 범위를 0 ~ 1 까지 제한
	float diffuse = saturate(dot(normal, -lightDirection));

	// 정반사
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
< 테크닉 >
3차원 물체를 그리기 위한 과정을 단계별로 그룹화 시키는 것이 가능
*/
technique myTechnique
{
	/*
	< 패스 >
	3차원 물체를 그리기 위해 거치는 단계( 식별자N 으로 N단계로 구분 )
	*/
	pass P0
	{
		cullMode = none;

		VertexShader = compile vs_3_0 vsMain();
		PixelShader = compile ps_3_0 psMain();
	}

	pass P1
	{
		// 렌더링 상태 변경
		cullMode = none;
		fillMode = wireFrame;

		VertexShader = compile vs_3_0 vsMain();
		PixelShader = compile ps_3_0 psMainWireFrame();
	}
}