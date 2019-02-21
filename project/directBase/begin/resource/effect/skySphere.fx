//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// Default_DirectX_Effect
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//

float4x4 g_stWorldMatrix : World;
float4x4 g_stViewMatrix : View;
float4x4 g_stProjectionMatrix : Projection;

texture g_pTexture;

struct STInput
{
	float4 m_stPosition : POSITION;
	float3 m_stNormal : NORMAL;
	float2 m_stUV : TEXCOORD;
};

struct STOutput
{
	float4 m_stPosition : POSITION;
	float3 m_stNormal : TEXCOORD0;
	float2 m_stUV : TEXCOORD1;
};

STOutput VSMain(STInput a_stInput)
{
	STOutput stOutput = (STOutput)0;
	float4 stWorldPosition = mul(a_stInput.m_stPosition, g_stWorldMatrix);

	stOutput.m_stPosition = mul(stWorldPosition, g_stViewMatrix);
	stOutput.m_stPosition = mul(stOutput.m_stPosition, g_stProjectionMatrix);

	float3 stNormal = mul(a_stInput.m_stNormal, (float3x3)g_stWorldMatrix);
	stOutput.m_stNormal = normalize(stNormal);

	stOutput.m_stUV = a_stInput.m_stUV;
	
	return stOutput;
}

sampler g_pSampler = sampler_state
{
   Texture = g_pTexture;

   MinFilter = LINEAR;
   MagFilter = LINEAR;
   MipFilter = LINEAR;
};

float4 PSMain(STOutput a_stInput) : COLOR0
{   
	return tex2D(g_pSampler, a_stInput.m_stUV); 
}

//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique SkyboxTechnique
{
	pass Pass_0
	{
		CullMode = CW;

		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}

}

