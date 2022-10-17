#pragma once
#include "JsonParse.h"
#include "ResouceDefine.h"

#define RESOURCE ResourceManager::Instance()

/// <summary>
/// ���ҽ� �Ŵ���
/// Json���� ���� ���� �����͸� �����ϴ� �Ŵ���
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
	/// meta json file���� �о�� �Ľ�����
	/// </summary>
	/// <param name="renderTarget">���� Ÿ��</param>
	/// <param name="imagingFactory">�̹��� ���丮</param>
	void Initialize(ID2D1HwndRenderTarget* renderTarget, IWICImagingFactory* imagingFactory);

private: // ��Ÿ ������ �о���� ���� json ���� ��ġ
	const std::string spriteMetasjsonfilepath = "SpriteMetas.json";
	const std::string animationClipMetasjsonfilepath = "AnimationClipMetas.json";
	const std::string animatorControllerMetasjsonfilepath = "AnimatorControllerMetas.json";
	const std::string audioClipsjsonfilepath = "AudioClips.json";

private: // ��������Ʈ ����
	int m_SpriteCount = 0;			// ��������Ʈ�� ���� (�ε����� 0����)
	int m_SpriteSheetCount = 0;		// ��������Ʈ ��Ʈ�� ���� (�ε����� 0����)
	std::map<string, D2DSpriteSheet*> m_SpriteSheetMetas;		/// ��������Ʈ�� ����. ��Ʈ �ε� ����̶�� �� ���� Ŭ������ �� �͵� ����. ��������Ʈ Ŭ�������� ��ӹ޾Ƽ� 2���� �������� ���� ������, ������ ��Ʈ���� �о ��������Ʈ Ŭ���� ���ο� �����ϴ� ��� �����̴�.
	std::map<int, ID2D1Bitmap*> m_SpriteSheets;	// ��������Ʈ ��Ʈ

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

private: // animationClip ����
	std::map<std::string, AnimationClip*> m_AnimationClipMetas;

	void LoadAllAnimationClip(string filepath);

public:
	AnimationClip* GetAnimationClip(string name);

private: // animatorController ����
	std::map<std::string, AnimatorController*> m_AnimatorControllerMetas;

	void LoadAllAnimatorController(string filepath);

public:
	AnimatorController* GetAnimationController(string name);

private: // AudioClip ����
	std::map<std::string, AudioClip*> m_AudioClips;

	void LoadAllAudioClips(std::string filePath);

public:
	AudioClip* GetAudioClip(std::string name);
	const std::map<std::string, AudioClip*>& GetAudioClipsAll() const { return m_AudioClips; }
};

