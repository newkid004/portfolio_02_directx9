#include "kGlobalDefine.h"
#include "windowManager.h"
#include "deviceManager.h"

deviceManager::~deviceManager()
{
	/*
		direct3D 관련 객체는 내부적으로 REF counting 방식으로 메모리를 관리하기 때문에
		해당 객체를 제거하기 위해선 명시적으로 delete를 호출하는 것이 아니라
		내부적으로 지닌 맴버 함수 Release를 이용해야 한다.

		direct3d 내에 REF counting 방식으로 관리되는 클래스는
		접두어가 I로 시작하는것이 관례.
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

	// 하드웨어 연산 지원가능 여부 확인
	DWORD vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)	vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS dParam;
	ZeroMemory(&dParam, sizeof(D3DPRESENT_PARAMETERS));
	
	// 크기, 출력 포멧 설정
	dParam.BackBufferWidth				= GET_WINDOW_SIZE().cx;
	dParam.BackBufferHeight				= GET_WINDOW_SIZE().cy;
	dParam.BackBufferCount				= 1;
	dParam.BackBufferFormat				= D3DFORMAT::D3DFMT_A8R8G8B8;
	dParam.SwapEffect					= D3DSWAPEFFECT::D3DSWAPEFFECT_DISCARD;

	// 멀티 샘플링 설정
	dParam.MultiSampleType				= D3DMULTISAMPLE_TYPE::D3DMULTISAMPLE_NONE;
	dParam.MultiSampleQuality			= 0;

	// 깊이 버퍼, 스텐실 버퍼 설정	
	dParam.EnableAutoDepthStencil		= true;
	dParam.AutoDepthStencilFormat		= D3DFORMAT::D3DFMT_D24S8;

	// 윈도우 설정
	dParam.Flags						= 0;
	dParam.Windowed						= true;
	dParam.hDeviceWindow				= GET_WINDOW_HANDLE();

	// 교체 주기 설정
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

