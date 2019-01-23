#include "kGlobalDefine.h"
#include "windowManager.h"
#include "deviceManager.h"

deviceManager::~deviceManager()
{
	/*
		direct3D ���� ��ü�� ���������� REF counting ������� �޸𸮸� �����ϱ� ������
		�ش� ��ü�� �����ϱ� ���ؼ� ��������� delete�� ȣ���ϴ� ���� �ƴ϶�
		���������� ���� �ɹ� �Լ� Release�� �̿��ؾ� �Ѵ�.

		direct3d ���� REF counting ������� �����Ǵ� Ŭ������
		���ξ I�� �����ϴ°��� ����.
	*/
	SAFE_RELEASE(_device);
	SAFE_RELEASE(_direct3d);
}

void deviceManager::init(void)
{
	this->_direct3d = this->createDirect3D();
	this->_device = this->createDevice();
}

LPDIRECT3D9 deviceManager::createDirect3D(void)
{
	return Direct3DCreate9(D3D_SDK_VERSION);
}

LPDIRECT3DDEVICE9 deviceManager::createDevice(void)
{
	D3DCAPS9 caps;
	_direct3d->GetDeviceCaps(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		&caps);

	// �ϵ���� ���� �������� ���� Ȯ��
	DWORD vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)	vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS dParam;
	ZeroMemory(&dParam, sizeof(D3DPRESENT_PARAMETERS));
	
	// ũ��, ��� ���� ����
	dParam.BackBufferWidth				= GET_WINDOW_SIZE().cx;
	dParam.BackBufferHeight				= GET_WINDOW_SIZE().cy;
	dParam.BackBufferCount				= 1;
	dParam.BackBufferFormat				= D3DFORMAT::D3DFMT_A8R8G8B8;
	dParam.SwapEffect					= D3DSWAPEFFECT::D3DSWAPEFFECT_DISCARD;

	// ��Ƽ ���ø� ����
	dParam.MultiSampleType				= D3DMULTISAMPLE_TYPE::D3DMULTISAMPLE_NONE;
	dParam.MultiSampleQuality			= 0;

	// ���� ����, ���ٽ� ���� ����	
	dParam.EnableAutoDepthStencil		= true;
	dParam.AutoDepthStencilFormat		= D3DFORMAT::D3DFMT_D24S8;

	// ������ ����
	dParam.Flags						= 0;
	dParam.Windowed						= true;
	dParam.hDeviceWindow				= GET_WINDOW_HANDLE();

	// ��ü �ֱ� ����
	dParam.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
	dParam.PresentationInterval			= D3DPRESENT_INTERVAL_IMMEDIATE;

	LPDIRECT3DDEVICE9 d3dDevice = NULL;
	HRESULT result = _direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		dParam.hDeviceWindow,
		vertexProcessing,
		&dParam,
		&d3dDevice);

	return d3dDevice;
}

