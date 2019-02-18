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
// Pass 0
//--------------------------------------------------------------//
string Example_21_Pass_0_Model : ModelData = "..\\..\\..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Teapot.3ds";

float4x4 _mWorld : World;
float4x4 _mView : View;
float4x4 _mProjection : Projection;

texture g_pCubeTexture
<
   string ResourceName = "..\\..\\..\\..\\..\\..\\..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Textures\\Snow.dds";
>;
samplerCUBE g_pCubeSampler = sampler_state
{
   Texture = (g_pCubeTexture);
};

struct STSkyboxInput
{
	float4 m_stPosition : POSITION;
	float3 m_stNormal : NORMAL;
};

struct STSkyboxOutput
{
	float4 m_stPosition : POSITION;
	float3 m_stNormal : TEXCOORD;
};

//! 스카이 박스 정점 쉐이더
STSkyboxOutput SkyboxVSMain(STSkyboxInput a_stInput)
{
	STSkyboxOutput stOutput = (STSkyboxOutput)0;
	float4 stWorldPosition = mul(a_stInput.m_stPosition, _mWorld);

	stOutput.m_stPosition = mul(stWorldPosition, _mView);
	stOutput.m_stPosition = mul(stOutput.m_stPosition, _mProjection);

	float3 stNormal = mul(a_stInput.m_stNormal, (float3x3)_mWorld);
	stOutput.m_stNormal = normalize(stNormal);

	return stOutput;
}

//! 스카이 박스 픽셀 쉐이더
float4 SkyboxPSMain(STSkyboxOutput a_stInput) : COLOR0
{
	float3 stNormal = normalize(a_stInput.m_stNormal);

	return texCUBE(g_pCubeSampler, stNormal);
}


//--------------------------------------------------------------//
// Technique Section for Example_21
//--------------------------------------------------------------//

technique SkyboxTechnique
{
	pass Pass_0
	{
		CullMode = CW;

		VertexShader = compile vs_3_0 SkyboxVSMain();
		PixelShader = compile ps_3_0 SkyboxPSMain();
	}
}

