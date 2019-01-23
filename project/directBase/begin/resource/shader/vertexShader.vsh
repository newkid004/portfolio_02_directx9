/*
입력
	모든 셰이더의 입력과 출력 변수에는 반드시 시멘틱을 기입해줘야 함
	시멘틱 : 그래픽 카드에게 해당 변수가 어떠한 용도를 나타내는지 알리는 역할

	시멘틱 키워드는 D3DDECLUSAGE 참조

출력
	정점 셰이더의 결과값에 포함되는 위치의 정보는
	동차 좌표에 해당하는 결과를 나타내기 때문에
	반드시 float4의 데이터 타입으로 반환되어야 함

*/

// 행렬
float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;

// 입력 정보
struct input
{
	float3 pos : POSITION;
	float2 texCoord : TEXCOORD0;
};

// 출력 정보
struct output
{
	float4 pos : POSITION;
	float2 texCoord : TEXCOORD0;
};

// 정점 셰이더 : 진입 함수
output vsMain(input iput)
{
	output oput = (output)0;
	
	// 벡터와 행렬의 곱셈 연산
	oput.pos = mul(float4(iput.pos, 1.0f), _mWorld);
	oput.pos = mul(oput.pos, _mView);
	oput.pos = mul(oput.pos, _mProjection);

	oput.texCoord = iput.texCoord;

	return oput;
}