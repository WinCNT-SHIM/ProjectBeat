#pragma once
#include "JsonParse.h"
#include "ResouceDefine.h"

#define RESOURCE ResourceManager::Instance()

/// <summary>
/// 리소스 매니저
/// Json으로 부터 읽은 데이터를 관리하는 매니저
/// </summary>
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static ResourceManager* Instance();
	static void Release();

private:
	// Singleton
	static ResourceManager* _instance;

	JsonParse _jsonParse;

	ID2D1HwndRenderTarget* _rt;
	IWICImagingFactory* _if;

public:
	/// <summary>
	/// meta json file들을 읽어와 파싱해줌
	/// </summary>
	/// <param name="renderTarget">랜더 타겟</param>
	/// <param name="imagingFactory">이미지 팩토리</param>
	void Initialize(ID2D1HwndRenderTarget* renderTarget, IWICImagingFactory* imagingFactory);

private: // 메타 파일을 읽어오기 위한 json 파일 위치
	const std::string spriteMetasjsonfilepath = "SpriteMetas.json";
	const std::string animationClipMetasjsonfilepath = "AnimationClipMetas.json";
	const std::string animatorControllerMetasjsonfilepath = "AnimatorControllerMetas.json";
	const std::string audioClipsjsonfilepath = "AudioClips.json";

private: // 스프라이트 관련
	int m_SpriteCount = 0;			// 스프라이트의 갯수 (인덱스는 0부터)
	int m_SpriteSheetCount = 0;		// 스프라이트 시트의 갯수 (인덱스는 0부터)
	std::map<string, D2DSpriteSheet*> m_SpriteSheetMetas;		/// 스프라이트의 정보. 시트 로드 방식이라면 한 개의 클래스로 될 것도 같다. 스프라이트 클래스조차 상속받아서 2개의 구현으로 가는 이유는, 실제로 비트맵을 읽어서 스프라이트 클래스 내부에 내장하는 경우 때문이다.
	std::map<int, ID2D1Bitmap*> m_SpriteSheets;	// 스프라이트 시트

	void LoadAllSpriteSheet(string filepath);
	void LoadSpriteSheet(const wchar_t* filePath);

	// Create a bitmap by loading it from a file.
	HRESULT LoadResourceBitmap(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

public:
	D2DSpriteSheet* GetSpriteSheet(string name);
	D2DSprite* GetSprite(string sheetName, string spriteName);
	ID2D1Bitmap* GetImage(int idx);

private: // animationClip 관련
	std::map<std::string, AnimationClip*> m_AnimationClipMetas;

	void LoadAllAnimationClip(string filepath);

public:
	AnimationClip* GetAnimationClip(string name);

private: // animatorController 관련
	std::map<std::string, AnimatorController*> m_AnimatorControllerMetas;

	void LoadAllAnimatorController(string filepath);

public:
	AnimatorController* GetAnimationController(string name);

private: // AudioClip 관련
	std::map<std::string, AudioClip*> m_AudioClips;

	void LoadAllAudioClips(std::string filePath);

public:
	AudioClip* GetAudioClip(std::string name);
	const std::map<std::string, AudioClip*>& GetAudioClipsAll() const { return m_AudioClips; }
};

