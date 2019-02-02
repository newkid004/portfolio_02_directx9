#include "terrain.h"

#include "managerList.h"
#include "gFunc.h"
#include "direct3dApplication.h"
#include "camera.h"
#include "lightBase.h"

#include "sceneBase.h"

D3DXPLANE terrain::_defPlane = D3DXPLANE(0, 1, 0, 0);

terrain::terrain(const params & param) :
	_param(param)
{
	setupTerrainInfo();

	_effect = MN_SRC->getEffect(param.pathEffect);
	_mesh = createTerrainMesh();
	_vTextureList = createTerrainTextures(&_textureSplat);
}

terrain::~terrain()
{
	SAFE_RELEASE(_mesh);
}

void terrain::drawDo(void)
{
	renderObject::drawDo();

	// 행렬
	_effect->SetMatrix("_mWorld", &getMatrixFinal());
	_effect->SetMatrix("_mView", &GET_CAMERA()->getMatrixView());
	_effect->SetMatrix("_mProjection", &GET_CAMERA()->getMatrixProjection());

	// 텍스쳐
	_effect->SetTexture("_textureSplat", _textureSplat);
	for (int i = 0; i < _vTextureList.size(); ++i)
	{
		char variableName[MAX_PATH] = "";
		sprintf(variableName, "_texture%c", 'A' + i);

		_effect->SetTexture(variableName, _vTextureList[i]);
	}

	gFunc::runEffectLoop(_effect, "myTechnique", [&](int passs)->void {
		_mesh->DrawSubset(0);
	});
}

void terrain::smoothTerrainMesh(int smoothLevel)
{
	float ratio = 0.5f;

	for (int i = 0; i < smoothLevel; ++i)
	{
		vector<float> vNormalize(_vHeightList);
		for (int y = 1; y < _sizeMap.cy - 1; ++y)
		{
			for (int x = 1; x < _sizeMap.cx - 1; ++x)
			{
				int index = y * _sizeMap.cy + x;

				float sizeIndex[4] = {
					index - 1,
					index + 1,
					index - _sizeMap.cx,
					index + _sizeMap.cx};

				float normalHeight = 0;
				for (int i = 0; i < 4; ++i)
				{
					if (0 <= sizeIndex[i] && sizeIndex[i] < vNormalize.size())
						normalHeight += vNormalize[sizeIndex[i]] / 4.0f;
					else
						normalHeight += vNormalize[index] / 4.0f;
				}

				_vHeightList[index] =
					normalHeight * ratio +
					_vHeightList[index] * (1.0f - ratio);
			}
		}
	}
}

void terrain::setupTerrainInfo(void)
{
	// 기본 정보 입력
	_sizeMap.cx = _param.mapSize.cx;
	_sizeMap.cy = _param.mapSize.cy;

	_sizeTile.cx = _param.tileSize.cx;
	_sizeTile.cy = _param.tileSize.cy;

	_sizeTotal.cx = _sizeMap.cx * _sizeTile.cx;
	_sizeTotal.cy = _sizeMap.cy * _sizeTile.cy;

	_heightScale = _param.heightScale;

	if (_param.pathHeight.rfind(".raw") != string::npos)
	{
		// shared_ptr 클래스 생성자의 두번째 매개 변수는 메모리가 정리되는 시점에
		// 호출되는 콜백 함수를 의미
		auto readStream = fopen(_param.pathHeight.c_str(), "rb");
		auto readStreamPtr = std::shared_ptr<FILE>(readStream, [=](FILE * fileStream)->void {
			fclose(fileStream);
		});

		for (int y = 0; y < _sizeMap.cy; ++y)
		{
			for (int x = 0; x < _sizeMap.cx; ++x)
			{
				USHORT height;
				fread(&height, sizeof(height), 1, readStreamPtr.get());

				_vHeightList.push_back(height * _heightScale);
			}
		}
	}
	else
	{
		auto heightTexture = MN_SRC->getTexture(_param.pathHeight);

		// 높이 정보 추출
		D3DLOCKED_RECT rcLocked;
		ZeroMemory(&rcLocked, sizeof(rcLocked));

		if (SUCCEEDED(heightTexture->LockRect(0, &rcLocked, NULL, 0)))
		{
			D3DCOLOR* cByte = (D3DCOLOR*)rcLocked.pBits;

			for (int y = 0; y < _sizeMap.cy; ++y)
			{
				for (int x = 0; x < _sizeMap.cx; ++x)
				{
					int index = y * _sizeMap.cx + x;
					D3DCOLOR color = cByte[index];

					int colorR = (color >> 0x10) & 0xff;
					int colorG = (color >> 0x08) & 0xff;
					int colorB = (color >> 0x00) & 0xff;

					int height = colorR + colorG + colorB;
					_vHeightList.push_back(height * _heightScale);
				}
			}
			heightTexture->UnlockRect(0);
		}

		// 지형 부드럽게
		smoothTerrainMesh(_param.smoothLevel);
	}

}

LPD3DXMESH terrain::createTerrainMesh(void)
{
	D3DVERTEXELEMENT9 elements[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
		{ 0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
		{ 0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	LPD3DXMESH result = nullptr;

	D3DXCreateMesh(
		_sizeMap.cx * _sizeMap.cy * 2,
		_sizeMap.cx * _sizeMap.cy,
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		elements,
		MN_DEV,
		&result);

	vertex* v = nullptr;
	if (SUCCEEDED(result->LockVertexBuffer(0, (void**)&v)))
	{
		D3DXVECTOR3 basePos = D3DXVECTOR3(
			(_sizeTotal.cx / -2.0f) + (_sizeTile.cx / 2.0),
			0,
			(_sizeTotal.cy / 2.0f) - (_sizeTile.cy / 2.0));

		for (int y = 0; y < _sizeMap.cy; ++y)
		{
			for (int x = 0; x < _sizeMap.cx; ++x)
			{
				int index = y * _sizeMap.cx + x;

				v[index].position = basePos + D3DXVECTOR3(
					x * _sizeTile.cx,
					_vHeightList[index],
					y * -_sizeTile.cy);

				v[index].uv = D3DXVECTOR2((float)x / (_sizeMap.cx - 1), (float)y / (_sizeMap.cy - 1));
			}
		}
		result->UnlockVertexBuffer();
	}

	DWORD* i = nullptr;
	if (SUCCEEDED(result->LockIndexBuffer(0, (void**)&i)))
	{
		for (int y = 0; y < _sizeMap.cy - 1; ++y)
		{
			for (int x = 0; x < _sizeMap.cx - 1; ++x)
			{
				int vertexIndex = y * _sizeMap.cx + x;
				int index = vertexIndex * 6;

				// 좌
				i[index + 0] = vertexIndex;
				i[index + 1] = vertexIndex + 1;
				i[index + 2] = vertexIndex + _sizeMap.cx;

				// 우
				i[index + 3] = vertexIndex + _sizeMap.cx;
				i[index + 4] = vertexIndex + 1;
				i[index + 5] = vertexIndex + _sizeMap.cx + 1;
			}
		}
		result->UnlockIndexBuffer();
	}

	D3DXComputeNormals(result, NULL);
	D3DXComputeTangent(result, 0, 0, 0, TRUE, NULL);

	return result;
}

vector<LPDIRECT3DTEXTURE9> terrain::createTerrainTextures(LPDIRECT3DTEXTURE9 * outSplatTexture)
{
	vector<LPDIRECT3DTEXTURE9> result;

	for (string filePath : _param.vPathTextureFile)
		result.push_back(MN_SRC->getTexture(filePath));

	*outSplatTexture = MN_SRC->getTexture(_param.pathSplat);
	return result;
}

float terrain::getHeight(D3DXVECTOR2 pos)
{
	// 중심점 보정
	pos.x = ((float)_sizeTotal.cx / 2.0f) + pos.x;
	pos.y = ((float)_sizeTotal.cy / 2.0f) - pos.y;
	pos.x /= (float)_sizeTile.cx;
	pos.y /= (float)_sizeTile.cy;

	D3DXVECTOR2 tile;
	tile.x = floorf(pos.x);
	tile.y = floorf(pos.y);

	// 정점
	float height[4];	// ↖ ↗ ↙ ↘
	ZeroMemory(height, sizeof(height));
	for (int y = 0; y < 2; ++y)
	{
		for (int x = 0; x < 2; ++x)
		{
			int index = _sizeMap.cx * (y + tile.y) + (x + tile.x);
			if (index < _vHeightList.size())
				height[y * 2 + x] = _vHeightList[index];
		}
	}

	// uv
	pos.x = pos.x - tile.x;
	pos.y = pos.y - tile.y;

	// 상단
	D3DXVECTOR2 uv;
	float result = 0;
	if (pos.x + pos.y < 1.0f)
	{
		uv.x = height[1] - height[0];	// ↗ - ↖
		uv.y = height[2] - height[0];	// ↙ - ↖
		result = height[0] +
			lerp(0.0f, uv.x, pos.x) + 
			lerp(0.0f, uv.y, pos.y);
	}
	// 하단
	else
	{
		uv.x = height[2] - height[3];	// ↙ - ↘
		uv.y = height[1] - height[3];	// ↗ - ↘
		result = height[3] + 
			lerp(0.0f, uv.x, 1.0f - pos.x) + 
			lerp(0.0f, uv.y, 1.0f - pos.y);
	}

	return result;
}

bool terrain::getIntersectPoint(const pick::ray & ray, D3DXVECTOR3 & out_position)
{
	BOOL isHit;
	LPD3DXBUFFER bufIntersect = nullptr;
	DWORD numIntersect;

	HRESULT isSucceeded = D3DXIntersect(
		_mesh,
		&ray.origin,
		&ray.direction,
		&isHit,
		NULL,
		NULL,
		NULL,
		NULL,
		&bufIntersect,
		&numIntersect);

	if (SUCCEEDED(isSucceeded))
	{
		if (isHit)
		{
			D3DXINTERSECTINFO* info = (D3DXINTERSECTINFO*)bufIntersect->GetBufferPointer();
			out_position = ray.origin + ray.direction * info[0].Dist;
		}
		SAFE_RELEASE(bufIntersect);
	}

	return isHit;
}