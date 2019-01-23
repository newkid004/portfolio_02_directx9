
// ----- 전역 ----- //
// 행렬
float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;

// 광원
float4 _lightDirection;

// 카메라
float4 _viewPosition;

// 색상
float4 _diffuse;

// ----- 입력 ----- //
struct input
{
	float3 pos      : POSITION;
	float3 normal   : NORMAL;
};

// ----- 출력 ----- //
struct output
{
	float4 pos              : POSITION;
	float3 normal           : TEXCOORD0;
	float3 lightDirection   : TEXCOORD1;
	float3 viewDirection    : TEXCOORD2;
};

// ----- 정점 셰이더 ----- //
output vsMain(input iput)
{
	output oput = (output)0;

	// 위치
	float4 worldPos = mul(float4(iput.pos, 1.0f), _mWorld);
	oput.pos = mul(worldPos, _mView);
	oput.pos = mul(oput.pos, _mProjection);

	// 법선
	oput.normal = mul(iput.normal, (float3x3)_mWorld);
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
	float diffuse = saturate(dot(normal, -lightDirection));

	// 정반사
	float3 specular = reflect(lightDirection, normal);
	specular = dot(specular, viewDirection);
	specular = saturate(specular);
	specular = pow(specular, 20.0f);

    // 색상
	float4 finalColor = _diffuse * diffuse;
	finalColor.rgb = finalColor.rgb + (float4(1.0f, 1.0f, 1.0f, 1.0f) * specular);
	finalColor.rgb = finalColor.rgb + (_diffuse * 0.2f);

	return finalColor;
}

float4 psMainWireFrame(output iput) : COLOR0
{
	return float4(0, 0, 0, 0);
}

// ----- 테크닉 ----- //
technique myTechnique
{
	pass P0
	{
		cullMode = none;

		VertexShader = compile vs_3_0 vsMain();
		PixelShader = compile ps_3_0 psMain();
	}
}