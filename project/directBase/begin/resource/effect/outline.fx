
float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;

float4 _viewPosition;
float4 _lightDirection;

texture _texture;
texture _textureCube;
texture _renderOutline;

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

output vsMain(input iput)
{
	output oput = (output)0;

	float4 worldPos = mul(float4(iput.pos.xyz, 1.0f), _mWorld);
	oput.pos = mul(worldPos, _mView);
	oput.pos = mul(oput.pos, _mProjection);

	float3 normal = mul(iput.normal, (float3x3)_mWorld);
	oput.normal = normalize(normal);

	oput.viewDirection = normalize(worldPos.xyz - _viewPosition.xyz);
	oput.uv = iput.uv;

	return oput;
}

sampler2D _sampler = sampler_state
{
	texture = _texture;
	
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

samplerCUBE _samplerCube = sampler_state
{
	texture = _textureCube;
	
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

float4 psMain(output iput) : COLOR0
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

float4 psWhite(output iput) : COLOR0
{
	return float4(1.0f, 0.0f, 0.0f, 1.0f);
}

// ----- pass1 ----- //

output vsPass1(input iput)
{
	output oput = (output)0;

	oput.pos = iput.pos;
	oput.uv = iput.uv;

	return oput;
}

sampler2D _samplerRenderOutline = sampler_state
{
	texture = _renderOutline;
	
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

float4 psPass1(output iput) : COLOR0
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
		VertexShader = compile vs_3_0 vsMain();
		PixelShader = compile ps_3_0 psWhite();
	}
}

technique techScreen
{
	pass p0
	{
		cullMode = NONE;

		VertexShader = compile vs_3_0 vsPass1();
		PixelShader = compile ps_3_0 psPass1();
	}
}

technique myTechnique
{
	pass p0
	{
		VertexShader = compile vs_3_0 vsMain();
		PixelShader = compile ps_3_0 psMain();
	}
}