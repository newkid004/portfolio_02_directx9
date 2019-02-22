// 행렬
//float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;

// 스키닝
int _numBlend;
float4x4 _mWorld[4];

//텍스처
texture _texture;
texture _normalTexture;

//광원
float4 _lightDirection;

// 카메라 위치
float4 _viewPosition;

//! 입력 정보
struct STInput
{
	float3 m_stPosition : POSITION;
	float3 m_stNormal : NORMAL;
	float3 m_stBinormal : BINORMAL;
	float3 m_stTangent: TANGENT;
	float2 m_stUV : TEXCOORD;
	float4 m_stWeight :BLENDWEIGHT;
};

//! 출력 정보
struct STOutput
{
	float4 m_stPosition : POSITION;
	float3 m_stNormal : TEXCOORD0;
	float3 m_stBinormal : TEXCOORD1;
	float3 m_stTangent: TEXCOORD2;
	float2 m_stUV : TEXCOORD3;
	float3 m_stViewDirection : TEXCOORD4;
	float3 m_stLightDirection : TEXCOORD5;
};

//! 정점 쉐이더
STOutput VSMain(STInput a_stInput)
{
	STOutput stOutput = (STOutput)0;
	float fLeftWeight = 1.0f;

	for (int i = 1; i <= _numBlend; ++i)
	{
		float fWeight = a_stInput.m_stWeight[i];
		float4x4 stWorldMatrix = _mWorld[i];

		fLeftWeight -= fWeight;

		stOutput.m_stPosition += mul(float4(a_stInput.m_stPosition, 1.0f), stWorldMatrix)*fWeight;
		stOutput.m_stNormal += mul(a_stInput.m_stNormal, (float3x3)stWorldMatrix)*fWeight;
		stOutput.m_stBinormal += mul(a_stInput.m_stBinormal, (float3x3)stWorldMatrix)*fWeight;
		stOutput.m_stTangent += mul(a_stInput.m_stTangent, (float3x3)stWorldMatrix)*fWeight;
	}

	stOutput.m_stPosition += mul(float4(a_stInput.m_stPosition, 1.0f), _mWorld[0])*fLeftWeight;
	stOutput.m_stNormal += mul(a_stInput.m_stNormal, (float3x3)_mWorld[0])*fLeftWeight;
	stOutput.m_stBinormal += mul(a_stInput.m_stBinormal, (float3x3)_mWorld[0])*fLeftWeight;
	stOutput.m_stTangent += mul(a_stInput.m_stTangent, (float3x3)_mWorld[0])*fLeftWeight;

	stOutput.m_stPosition.w = 1.0f;
	float4 stWorldPosition = stOutput.m_stPosition;

	stOutput.m_stPosition = mul(stOutput.m_stPosition, _mView);
	stOutput.m_stPosition = mul(stOutput.m_stPosition, _mProjection);

	stOutput.m_stNormal = normalize(stOutput.m_stNormal);
	stOutput.m_stBinormal = normalize(stOutput.m_stBinormal);
	stOutput.m_stTangent = normalize(stOutput.m_stTangent);

	float3 stLightDirection = _lightDirection.xyz;
	stOutput.m_stLightDirection = normalize(stLightDirection);

	float3 stViewDirection = _viewPosition.xyz - stWorldPosition.xyz;
	stOutput.m_stViewDirection = normalize(stViewDirection);

	stOutput.m_stUV = a_stInput.m_stUV;

	return stOutput;
}

// 샘플러
sampler2D g_pSampler = sampler_state
{
	Texture = _texture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler2D g_pNormalSampler = sampler_state
{
	Texture = _normalTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

//! 픽셀 쉐이더
float4 PSMain(STOutput a_stInput):COLOR0
{
	float3 stNormal = normalize(a_stInput.m_stNormal);
	float3 stBinormal = normalize(a_stInput.m_stBinormal);
	float3 stTangent = normalize(a_stInput.m_stTangent);

	float3 stLightDirection = normalize(a_stInput.m_stLightDirection);
	float3 stViewDirection = normalize(a_stInput.m_stViewDirection);

	//법선 정보를 계산한다.
	float3x3 stInverseMatrix = float3x3(stTangent,
		stBinormal,
		stNormal);

	stInverseMatrix = transpose(stInverseMatrix);

	float3 stTangentNormal = tex2D(g_pNormalSampler, a_stInput.m_stUV).xyz;
	stTangentNormal = normalize((stTangentNormal*2.0f) - 1.0f);
	stTangentNormal = mul(stTangentNormal, stInverseMatrix);



	//난반사를 계산한다.
	float fColor = saturate(dot(stTangentNormal, -stLightDirection));

	// 정반사를 계산한다.
	float fSpecular = saturate(dot(reflect(stLightDirection, stTangentNormal), stViewDirection));
	fSpecular = pow(fSpecular,20.0f);

	//색상 정보
	float4 texColor = tex2D(g_pSampler, a_stInput.m_stUV);

	//최종 색상을 계산한다.
	float4 stFinalColor = texColor * fColor;
	stFinalColor.rgb = stFinalColor.rgb + (texColor.rgb*fSpecular);
	stFinalColor.rgb = stFinalColor.rgb + (texColor.rgb*0.3f);

	return stFinalColor;
}


technique MyTechnique
{
	pass P0
	{
		cullMode = cw;
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}