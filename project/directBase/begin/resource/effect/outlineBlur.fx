
float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;
float4x4 _mViewProjection;

float4 _viewPosition;
float4 _lightDirection;

texture _textureDiffuse;
texture _renderOutline;

sampler2D _samplerDiffuse = sampler_state
{
	texture = _textureDiffuse;
	
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler2D _samplerRenderOutline = sampler_state
{
	texture = _renderOutline;
	
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

// ----- sovel outline ----- //
float3x3 _mHrz = {
	-1.0f, 0.0f, 1.0f,
	-2.0f, 0.0f, 2.0f,
	-1.0f, 0.0f, 1.0f
};

float3x3 _mVtc = {
	1.0f, 2.0f, 1.0f,
	0.0f, 0.0f, 0.0f,
	-1.0f, -2.0f, -1.0f
};

// ----- blur ----- //
float4 filterH[7] = {
	0.0f,	-3.0f,	0.0f,	1.0f / 64.0f,
	0.0f,	-2.0f,	0.0f,	6.0f / 64.0f,
	0.0f,	-1.0f,	0.0f,	15.0f / 64.0f,
	0.0f,	 0.0f,	0.0f,	20.0f / 64.0f,
	0.0f,	 1.0f,	0.0f,	15.0f / 64.0f,
	0.0f,	 2.0f,	0.0f,	6.0f / 64.0f,
	0.0f,	 3.0f,	0.0f,	1.0f / 64.0f,
};

float4 filterV[7] = {
	-3.0f,	0.0f,	0.0f,	1.0f / 64.0f,
	-2.0f,	0.0f,	0.0f,	6.0f / 64.0f,
	-1.0f,	0.0f,	0.0f,	15.0f / 64.0f,
	0.0f,	0.0f,	0.0f,	20.0f / 64.0f,
	1.0f,	0.0f,	0.0f,	15.0f / 64.0f,
	2.0f,	0.0f,	0.0f,	6.0f / 64.0f,
	3.0f,	0.0f,	0.0f,	1.0f / 64.0f,
};

struct input
{
	float4 pos : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD0;
};

struct output
{
	float4 pos : POSITION;
	float3 normal : TEXCOORD0;
	float2 uv : TEXCOORD1;

	float3 viewDirection : TEXCOORD2;
};

// ----- origin ----- //
output vsOrigin(input iput)
{
	output oput = (output)0;

	float4 worldPos = mul(float4(iput.pos.xyz, 1.0f), _mWorld);
	oput.pos = mul(worldPos, _mViewProjection);

	float3 normal = mul(iput.normal, (float3x3)_mWorld);
	oput.normal = normalize(normal);

	oput.viewDirection = normalize(worldPos.xyz - _viewPosition.xyz);
	oput.uv = iput.uv;

	return oput;
}

float4 psOrigin(output iput) : COLOR0
{
	float3 normal = normalize(iput.normal);
	float3 viewDirection = normalize(iput.viewDirection);
	float3 lightDirection = normalize(_lightDirection.xyz);

	float4 diffuseColor = tex2D(_sampler, iput.uv);

	float4 environmentColor = texCUBE(_samplerCube, reflect(-viewDirection, normal));
	float diffuse = saturate(dot(-lightDirection, normal));
	float specular = saturate(dot(reflect(lightDirection, normal), viewDirection));

	float4 finalColor = diffuseColor;
	finalColor.rgb = finalColor.rgb * diffuse;
	finalColor.rgb = finalColor.rgb + (finalColor.rgb * specular);
	finalColor.rgb = finalColor.rgb + (environmentColor.rgb * 0.5f);

	return finalColor;
}

float4 psSolid(output iput) : COLOR0
{
	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}

// ----- pass1 ----- //

output vsPanel(input iput)
{
	output oput = (output)0;

	oput.pos = iput.pos;
	oput.uv = iput.uv;

	return oput;
}


float4 psBlur(output iput) : COLOR0
{
	float sumHrz = 0.0f;
	float sumVtc = 0.0f;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			float2 offset = float2(i - 1, j - 1) * (1.0f / 640.0f);
			float3 pColor = tex2D(_samplerRenderOutline, iput.uv + offset).rgb;

			float calValue = dot(pColor, float3(0.3f, 0.59f, 0.12f));

			sumHrz += calValue * _mHrz[i][j];
			sumVtc += calValue * _mVtc[i][j];
		}
	}
	float finalValue = sqrt(pow(sumHrz, 2.0f) + pow(sumVtc, 2.0f));

	return float4(finalValue.rrr, 1.0f);
}

technique techOutline
{
	pass p0
	{
		VertexShader = compile vs_3_0 vsOrigin();
		PixelShader = compile ps_3_0 psSolid();
	}
}

technique techScreen
{
	pass p0
	{
		cullMode = NONE;

		VertexShader = compile vs_3_0 vsPanel();
		PixelShader = compile ps_3_0 psBlur();
	}
}

technique myTechnique
{
	pass p0
	{
		VertexShader = compile vs_3_0 vsOrigin();
		PixelShader = compile ps_3_0 psOrigin();
	}
}