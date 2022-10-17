#pragma once
#include <map>
#include <string>
#include "nlohmann/json.hpp"

using namespace nlohmann;
using namespace std;

class D2DSpriteSheet;
class AnimationClip;
class AnimatorController;
class AudioClip;

class JsonParse
{
public:
	JsonParse();
	~JsonParse();

public:

#pragma region Sprite

	// 모든 sprite meta json 파일을 읽어와서 spriteSheetMeta에 push
	void LoadAllSpriteSheetMeta(string filepath, std::map<string, D2DSpriteSheet*>& spriteSheetMeta);

	// 모든 SpriteMeta를 각 json 파일에 저장함
	void SaveAllSpriteSheetMeta(std::map<string, D2DSpriteSheet*>& spriteSheetMeta);

	// SpriteSheetmeta들의 위치를 저장할 json 데이타를 저장함
	void SaveAllSpriteSheetMetaFilePath(string filepath, std::map<string, D2DSpriteSheet*>& spriteSheetMeta);

	// 스프라이트 시트의 정보를 Json 파일로 부터 읽어와서 D2DSpriteSheet*로 반환해줌
	D2DSpriteSheet* LoadSpriteSheetMeta(string filepath);

	// filepath 경로의 json 파일에 sprite sheet meta를 저장
	void SaveSpriteSheetMeta(string filepath, D2DSpriteSheet* spriteSheet);

#pragma endregion

#pragma region AnimationClip

	// 모든 AnimationClip meta json 파일을 읽어와서 animationClipMeta에 push
	void LoadAllAnimationClipMeta(string filepath, std::map<string, AnimationClip*>& animationClips);

	// 모든 SpriteMeta를 각 json 파일에 저장함
	void SaveAllAnimationClipMeta(std::map<string, AnimationClip*>& animationClips);

	// AnimationClip meta들의 위치를 저장할 json 데이타를 저장함
	void SaveAllAnimationClipMetaFilePath(string filepath, std::map<string, AnimationClip*>& animationClips);

	// filepath 경로의 json 파일에 AnimationClip meta를 저장
	void SaveAnimationClipMeta(string filepath, AnimationClip* animationClip);

	// 애니메이션 클립 정보를 Json 파일로부터 읽어와서 AnimationClip*로 반환해줌
	AnimationClip* LoadAnimationClipMeta(string filepath);

#pragma endregion

#pragma region AnimationClip

	// 모든 AnimatorController meta json 파일을 읽어와서 animatorControllerMeta에 push
	void LoadAllAnimatorControllerMeta(string filepath, std::map<string, AnimatorController*>& animationControllers);

	// 모든 AnimatorController meta를 각 json 파일에 저장함
	void SaveAllAnimatorControllerMeta(std::map<string, AnimatorController*>& animationControllers);

	// AnimatorController meta들의 위치를 저장할 json 데이타를 저장함
	void SaveAllAnimatorControllerMetaFilePath(string filepath, std::map<string, AnimatorController*>& animatorControllers);

	// filepath 경로의 json 파일에 AnimatorController meta를 저장
	void SaveAnimatorControllerMeta(string filepath,  AnimatorController* animatorController);

	// 애니메이션 클립 정보를 Json 파일로부터 읽어와서 AnimatorController*로 반환해줌
	AnimatorController* LoadAnimatorControllerMeta(string filepath);

#pragma endregion


#pragma region AudioClip

	// 모든 사운드파일을 읽어서 오디오클립으로 만든다.
	void LoadAllAudioClip(std::string filePath, std::map<string, AudioClip*>& soundList);

#pragma endregion
};
