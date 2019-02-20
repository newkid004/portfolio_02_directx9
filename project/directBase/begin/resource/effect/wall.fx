// 행렬
float4x4 g_stWorldMatrix;
float4x4 g_stViewMatrix;
float4x4 g_stProjectionMatrix;

// 카메라, 광원
float4 g_stViewPosition;
float4 g_stLightDirection;

// 기타
//float g_fParallax;

// 텍스처
texture g_pTexture;
texture g_pNormalTexture;

// 입력 정보
struct STInput
{
	float3 m_stPosition : POSITION;
	float3 m_stNormal : NORMAL;
	float3 m_stBinormal : BINORMAL;
	float3 m_stTangent : TANGENT;
	float2 m_stUV : TEXCOORD;
};

// 출력 정보
struct STOutput
{
	float4 m_stPosition : POSITION;
	float3 m_stNormal : TEXCOORD0;
	float3 m_stBinormal : TEXCOORD1;
	float3 m_stTangent : TEXCOORD2;
	float2 m_stUV : TEXCOORD3;
	float3 m_stViewDirection : TEXCOORD4;
	float3 m_stLightDirection : TEXCOORD5;
};

// 정점 쉐이더
STOutput VSMain(STInput a_stInput)
{
	STOutput stOutput = (STOutput)0;
	
	float4 stWorldPosition = mul(float4(a_stInput.m_stPosition, 1.0f), g_stWorldMatrix);

	stOutput.m_stPosition = mul(stWorldPosition, g_stViewMatrix);
	stOutput.m_stPosition = mul(stOutput.m_stPosition, g_stProjectionMatrix);

	float3 stNormal = mul(a_stInput.m_stNormal, (float3x3)g_stWorldMatrix);
	stOutput.m_stNormal = normalize(stNormal);

	float3 stBinormal = mul(a_stInput.m_stBinormal, (float3x3)g_stWorldMatrix);
	stOutput.m_stBinormal = normalize(stBinormal);

	float3 stTangent = mul(a_stInput.m_stTangent, (float3x3)g_stWorldMatrix);
	stOutput.m_stTangent = normalize(stTangent);

	float3 stViewDirection = g_stViewPosition.xyz - stWorldPosition.xyz;
	stOutput.m_stViewDirection = normalize(stViewDirection);

	float3 stLightDirection = g_stLightDirection.xyz;
	stOutput.m_stLightDirection = normalize(stLightDirection);

	stOutput.m_stUV = a_stInput.m_stUV;

	return stOutput;
}
// 샘플러
// {
sampler2D g_pSampler = sampler_state
{
	Texture = g_pTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler2D g_pNormalSampler = sampler_state
{
	Texture = g_pNormalTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};
// }

// 픽셀 쉐이더
float4 PSMain(STOutput a_stInput) : COLOR0
{
	float3 stNormal = normalize(a_stInput.m_stNormal);
	float3 stBinormal = normalize(a_stInput.m_stBinormal);
	float3 stTangent = normalize(a_stInput.m_stTangent);

	float3 stViewDirection = normalize(a_stInput.m_stViewDirection);
	float3 stLightDirection = normalize(a_stInput.m_stLightDirection);

	//float fHeight = tex2D(g_pBumpSampler, a_stInput.m_stUV).w;

	//float2 stParallaxUV = a_stInput.m_stUV + ((fHeight * g_fParallax) * normalize(stViewDirection.xy));

	// 법선 정보를 계산한다
	// {
	float3x3 stInverseMatrix = float3x3(stTangent, stBinormal, stNormal);
	
	stInverseMatrix = transpose(stInverseMatrix);

	float3 stTangentNormal = tex2D(g_pNormalSampler, a_stInput.m_stUV).xyz;
	stTangentNormal = normalize((stTangentNormal * 2.0f) - 1.0f);
	stTangentNormal = mul(stTangentNormal, stInverseMatrix);
	// }

	// 난반사를 계산한다
	float fDiffuse = saturate(dot(-stLightDirection, stTangentNormal));

	// 정반사를 계산한다
	float fSpecular = saturate(dot(reflect(stLightDirection, stTangentNormal), stViewDirection));
	fSpecular = pow(fSpecular, 20.0f);

	float4 stDiffuseColor = tex2D(g_pSampler, a_stInput.m_stUV);

	float4 stFinalColor = stDiffuseColor;
	stFinalColor.rgb = stFinalColor.rgb * fDiffuse;
	stFinalColor.rgb = stFinalColor.rgb + (stDiffuseColor.rgb * fSpecular);
	
	return stFinalColor;
}

technique MyTechnique
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}

