#include "ResourceManager.h"


#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

ResourceManager* ResourceManager::_instance = nullptr;

bool cmp(const D2DSpriteSheet* a, const D2DSpriteSheet* b)
{
	return a->_spriteSheetIndex < b->_spriteSheetIndex;
}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (auto iter : m_SpriteSheetMetas)
	{
		for (auto iter2 : iter.second->_spriteSheet)
		{
			if (iter2.second != nullptr)
			{
				delete iter2.second;
				iter2.second = nullptr;
			}
		}
		if (iter.second != nullptr)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	for (auto iter : m_SpriteSheets)
	{
		if (iter.second != nullptr)
		{
			iter.second->Release();
			iter.second = nullptr;
		}
	}

	for (auto iter : m_AnimationClipMetas)
	{
		if (iter.second != nullptr)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	for (auto iter : m_AnimatorControllerMetas)
	{
		if (iter.second != nullptr)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	for (auto iter : m_AudioClips)
	{
		if (iter.second != nullptr)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
}

ResourceManager* ResourceManager::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new ResourceManager();
	}

	return _instance;
}

void ResourceManager::Release()
{
	// 싱글톤 객체가 있다면 해제한다.
	if (_instance != nullptr)
	{
		delete _instance;
		_instance = nullptr;
	}
}


void ResourceManager::Initialize(ID2D1HwndRenderTarget* renderTarget, IWICImagingFactory* imagingFactory)
{
	_rt = renderTarget;
	_if = imagingFactory;

	LoadAllSpriteSheet(spriteMetasjsonfilepath);
	LoadAllAnimationClip(animationClipMetasjsonfilepath);
	LoadAllAnimatorController(animatorControllerMetasjsonfilepath);
	LoadAllAudioClips(audioClipsjsonfilepath);
}

void ResourceManager::LoadAllSpriteSheet(string filepath)
{
	_jsonParse.LoadAllSpriteSheetMeta(filepath, m_SpriteSheetMetas);

	vector<D2DSpriteSheet*> sortBySheetIndex;
	for (auto iter : m_SpriteSheetMetas)
	{
		sortBySheetIndex.push_back(iter.second);
	}

	sort(sortBySheetIndex.begin(), sortBySheetIndex.end(), cmp);

	for (auto iter : sortBySheetIndex)
	{
		// string to wchar_t*
		std::wstring widestr = std::wstring(iter->_imageFilePath.begin(), iter->_imageFilePath.end());
		LoadSpriteSheet(widestr.c_str());
	}
}

void ResourceManager::LoadSpriteSheet(const wchar_t* filePath)
{
	HRESULT hr;
	ID2D1Bitmap* pNewBitmap;

	// Create a bitmap by loading it from a file.
	hr = LoadBitmapFromFile(
		_rt,
		_if,
		filePath,
		0,
		0,
		&pNewBitmap
	);

	if (SUCCEEDED(hr))
	{
		m_SpriteSheets.insert(std::pair<int, ID2D1Bitmap*>(m_SpriteSheetCount, pNewBitmap));
		m_SpriteSheetCount++;
	}
}

HRESULT ResourceManager::LoadResourceBitmap(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR resourceName, PCWSTR resourceType, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	void* pImageFile = NULL;
	DWORD imageFileSize = 0;

	// Locate the resource.
	imageResHandle = FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType);

	hr = imageResHandle ? S_OK : E_FAIL;
	if (SUCCEEDED(hr))
	{
		// Load the resource.
		imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageResDataHandle ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Lock it to get a system memory pointer.
		pImageFile = LockResource(imageResDataHandle);

		hr = pImageFile ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Calculate the size.
		imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);

		hr = imageFileSize ? S_OK : E_FAIL;
	}
	if (SUCCEEDED(hr))
	{
		// Create a WIC stream to map onto the memory.
		hr = pIWICFactory->CreateStream(&pStream);
	}
	if (SUCCEEDED(hr))
	{
		// Initialize the stream with the memory pointer and size.
		hr = pStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create a decoder for the stream.
		hr = pIWICFactory->CreateDecoderFromStream(
			pStream,
			NULL,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
	}
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
					if (SUCCEEDED(hr))
					{
						hr = pConverter->Initialize(
							pScaler,
							GUID_WICPixelFormat32bppPBGRA,
							WICBitmapDitherTypeNone,
							NULL,
							0.f,
							WICBitmapPaletteTypeMedianCut
						);
					}
				}
			}
		}
		else
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		//create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeReleaseMacro(&pDecoder);
	SafeReleaseMacro(&pSource);
	SafeReleaseMacro(&pStream);
	SafeReleaseMacro(&pConverter);
	SafeReleaseMacro(&pScaler);

	return hr;
}

HRESULT ResourceManager::LoadBitmapFromFile(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	hr = pIWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr))
	{

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeReleaseMacro(&pDecoder);
	SafeReleaseMacro(&pSource);
	SafeReleaseMacro(&pStream);
	SafeReleaseMacro(&pConverter);
	SafeReleaseMacro(&pScaler);

	return hr;
}

D2DSpriteSheet* ResourceManager::GetSpriteSheet(string name)
{
	auto sheet = m_SpriteSheetMetas.find(name);
	if (sheet != m_SpriteSheetMetas.end())
	{
		return (*sheet).second;
	}
	return nullptr;
}

D2DSprite* ResourceManager::GetSprite(string sheetName, string spriteName)
{
	auto sheet = m_SpriteSheetMetas.find(sheetName);
	if (sheet != m_SpriteSheetMetas.end())
	{
		auto sprite = (*sheet).second->_spriteSheet.find(spriteName);
		if (sprite != (*sheet).second->_spriteSheet.end())
		{
			return (*sprite).second;
		}
		else return nullptr;
	}
	else
		return nullptr;
}

ID2D1Bitmap* ResourceManager::GetImage(int idx)
{
	auto bitmap = m_SpriteSheets.find(idx);
	if (bitmap != m_SpriteSheets.end())
	{
		return (*bitmap).second;
	}
	return nullptr;
}

void ResourceManager::LoadAllAnimationClip(string filepath)
{
	_jsonParse.LoadAllAnimationClipMeta(filepath, m_AnimationClipMetas);
}

AnimationClip* ResourceManager::GetAnimationClip(string name)
{
	auto clip = m_AnimationClipMetas.find(name);
	if (clip != m_AnimationClipMetas.end())
	{
		return new AnimationClip(*m_AnimationClipMetas[name]);
	}
	return nullptr;

}

void ResourceManager::LoadAllAnimatorController(string filepath)
{
	_jsonParse.LoadAllAnimatorControllerMeta(filepath, m_AnimatorControllerMetas);
}

AnimatorController* ResourceManager::GetAnimationController(string name)
{
	auto controller = m_AnimatorControllerMetas.find(name);
	if (controller != m_AnimatorControllerMetas.end())
	{
		return m_AnimatorControllerMetas[name];
	}
	return nullptr;
}

void ResourceManager::LoadAllAudioClips(std::string filePath)
{
	// json 파일 하나에서 모든 사운드 파일을 읽는다.
	_jsonParse.LoadAllAudioClip(filePath, m_AudioClips);
}

AudioClip* ResourceManager::GetAudioClip(std::string name)
{
	auto item = m_AudioClips.find(name);
	if (item != m_AudioClips.end())
	{
		return m_AudioClips[name];
	}
	// 위험천만한데.. 키 값이 없는 경우?
	return nullptr;
}
