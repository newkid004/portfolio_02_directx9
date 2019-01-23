/*
�Է�
	��� ���̴��� �Է°� ��� �������� �ݵ�� �ø�ƽ�� ��������� ��
	�ø�ƽ : �׷��� ī�忡�� �ش� ������ ��� �뵵�� ��Ÿ������ �˸��� ����

	�ø�ƽ Ű����� D3DDECLUSAGE ����

���
	���� ���̴��� ������� ���ԵǴ� ��ġ�� ������
	���� ��ǥ�� �ش��ϴ� ����� ��Ÿ���� ������
	�ݵ�� float4�� ������ Ÿ������ ��ȯ�Ǿ�� ��

*/

// ���
float4x4 _mWorld;
float4x4 _mView;
float4x4 _mProjection;

// �Է� ����
struct input
{
	float3 pos : POSITION;
	float2 texCoord : TEXCOORD0;
};

// ��� ����
struct output
{
	float4 pos : POSITION;
	float2 texCoord : TEXCOORD0;
};

// ���� ���̴� : ���� �Լ�
output vsMain(input iput)
{
	output oput = (output)0;
	
	// ���Ϳ� ����� ���� ����
	oput.pos = mul(float4(iput.pos, 1.0f), _mWorld);
	oput.pos = mul(oput.pos, _mView);
	oput.pos = mul(oput.pos, _mProjection);

	oput.texCoord = iput.texCoord;

	return oput;
}